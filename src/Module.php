<?php

namespace Kambo\WebAssembly;

use FFI;
use Kambo\WebAssembly\Exception\WasmerException;
use Kambo\WebAssembly\Native\WasmerFFI;

/**
 * A compiled WebAssembly module.
 */
final class Module
{
    /** @var FFI\CData */
    private FFI\CData $module;

    /**
     * Compile a module from WASM bytes (raw .wasm data).
     */
    public function __construct(Store $store, string $wasmBytes)
    {
        $ffi = WasmerFFI::getFFI();

        $byteVec = $ffi->new('wasm_byte_vec_t');
        $ffi->wasm_byte_vec_new(
            FFI::addr($byteVec),
            \strlen($wasmBytes),
            $wasmBytes
        );

        $mod = $ffi->wasm_module_new(
            $store->getInner(),
            FFI::addr($byteVec)
        );

        // Cleanup the input bytes
        $ffi->wasm_byte_vec_delete(FFI::addr($byteVec));

        if ($mod === null) {
            throw new WasmerException("Failed to create/compile wasm_module_t from provided bytes");
        }

        $this->module = $mod;
    }

    /**
     * Internal: get pointer
     */
    public function getInner(): FFI\CData
    {
        return $this->module;
    }

    public function __destruct()
    {
        $ffi = WasmerFFI::getFFI();
        $ffi->wasm_module_delete($this->module);
    }
}
