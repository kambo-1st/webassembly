<?php

namespace Kambo\WebAssembly;

use FFI;
use Kambo\WebAssembly\Exception\WasmerException;
use Kambo\WebAssembly\Native\WasmerFFI;

/**
 * An instantiated Module (with optional imports),
 * from which we can retrieve & call exported functions.
 */
final class Instance
{
    /** @var FFI\CData */
    private FFI\CData $instance;

    /** @var FFI\CData wasm_extern_vec_t */
    private FFI\CData $exports;

    /** @var array<string,int> name => index (to call exports by name) */
    private array $exportNameMap = [];

    /**
     * Instantiate a Module in the given Store, with no imports (for simplicity).
     */
    public function __construct(Store $store, Module $module)
    {
        $ffi = WasmerFFI::getFFI();

        // Create an empty import vector
        $importVec = $ffi->new('wasm_extern_vec_t');
        $ffi->wasm_extern_vec_new_empty(FFI::addr($importVec));

        // Create a trap pointer
        $trap = $ffi->new('wasm_trap_t*');

        // Instantiate
        $inst = $ffi->wasm_instance_new(
            $store->getInner(),
            $module->getInner(),
            FFI::addr($importVec),
            FFI::addr($trap) // Pass address of the trap pointer
        );

        // Cleanup import vector
        $ffi->wasm_extern_vec_delete(FFI::addr($importVec));

        if ($inst === null) {
            // If we have a trap, get its message
            if ($trap !== null) {
                $msgVec = $ffi->new('wasm_message_t');
                $ffi->wasm_trap_message($trap, FFI::addr($msgVec));
                $errorMsg = FFI::string($msgVec->data, $msgVec->size);
                $ffi->wasm_byte_vec_delete(FFI::addr($msgVec));
                throw new WasmerException("Failed to instantiate the module: " . $errorMsg);
            }
            throw new WasmerException("Failed to instantiate the module");
        }

        $this->instance = $inst;

        // Retrieve exports
        $exports = $ffi->new('wasm_extern_vec_t');
        $ffi->wasm_instance_exports($inst, FFI::addr($exports));
        $this->exports = $exports;

        // Build name -> index map
        $this->buildExportNameMap($module);
    }

    /**
     * Clean up exports + instance
     */
    public function __destruct()
    {
        $ffi = WasmerFFI::getFFI();
        $ffi->wasm_extern_vec_delete(FFI::addr($this->exports));
        $ffi->wasm_instance_delete($this->instance);
    }

    /**
     * Private: get the export names from the Module's export types
     */
    private function buildExportNameMap(Module $module): void
    {
        $ffi = WasmerFFI::getFFI();

        $exportTypes = $ffi->new('wasm_exporttype_vec_t');
        $ffi->wasm_module_exports($module->getInner(), FFI::addr($exportTypes));

        $size = $exportTypes->size;
        for ($i = 0; $i < $size; $i++) {
            $exType = $exportTypes->data[$i];
            // Grab the export name
            $namePtr = $ffi->wasm_exporttype_name($exType);
            $name    = FFI::string($namePtr->data, $namePtr->size);
            $this->exportNameMap[$name] = $i;
        }

        // Cleanup
        $ffi->wasm_exporttype_vec_delete(FFI::addr($exportTypes));
    }

    /**
     * Call an exported function by name, with a Collection of arguments.
     *
     * @param string          $funcName
     * @param Collection|array $args     Collection or array of Value objects
     * @return Collection
     * @throws WasmerException
     */
    public function callFunction(string $funcName, Collection|array $args = []): Collection
    {
        if (!isset($this->exportNameMap[$funcName])) {
            throw new WasmerException("Exported function '$funcName' not found.");
        }
        $index = $this->exportNameMap[$funcName];
        return $this->callFunctionByIndex($index, $args);
    }

    /**
     * Call an exported function by index.
     *
     * @param int             $index
     * @param Collection|array $args   Collection or array of Value objects
     * @return Collection
     */
    public function callFunctionByIndex(int $index, Collection|array $args = []): Collection
    {
        $ffi = WasmerFFI::getFFI();
        $ext = $this->exports->data[$index];
        $func = $ffi->wasm_extern_as_func($ext);

        if ($func === null) {
            throw new WasmerException("Export #$index is not a function or is null.");
        }

        // Convert args to Collection if it's an array
        if (is_array($args)) {
            $args = new Collection($args);
        }

        // Get args as wasm_val_vec_t
        $argsVec = $args->toWasmValVec($ffi);

        // Prepare results vector
        $resultArity = $ffi->wasm_func_result_arity($func);
        $resultsVec = $ffi->new('wasm_val_vec_t');
        
        if ($resultArity > 0) {
            $resultsVal = $ffi->new("wasm_val_t[$resultArity]", false);
            $resultsVec->size = $resultArity;
            $resultsVec->data = $resultsVal;
        } else {
            $resultsVec->size = 0;
            $resultsVec->data = null;
        }

        // Call the function
        $trap = $ffi->wasm_func_call(
            $func,
            FFI::addr($argsVec),
            FFI::addr($resultsVec)
        );

        // Clean up args vector data if allocated
        if ($argsVec->size > 0 && $argsVec->data !== null) {
            FFI::free($argsVec->data);
        }

        if ($trap) {
            throw new WasmerException("Error during wasm_func_call (trap returned).");
        }

        // Convert results to Collection
        $results = Collection::fromWasmValVec($resultsVec);

        // Clean up results array if allocated
        if ($resultsVec->size > 0 && $resultsVec->data !== null) {
            FFI::free($resultsVec->data);
        }

        return $results;
    }
}
