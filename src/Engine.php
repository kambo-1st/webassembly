<?php

namespace Kambo\WebAssembly;

use FFI;
use Kambo\WebAssembly\Exception\WasmerException;
use Kambo\WebAssembly\Native\WasmerFFI;

/**
 * Wraps a wasm_engine_t pointer via OOP.
 */
final class Engine
{
    /** @var FFI\CData */
    private FFI\CData $engine;

    /**
     * Create a new Wasmer Engine using wasm_engine_new().
     *
     * @throws WasmerException if creation fails
     */
    public function __construct()
    {
        $ffi = WasmerFFI::getFFI();
        $this->engine = $ffi->wasm_engine_new();

        if ($this->engine === null) {
            throw new WasmerException("Failed to create wasm_engine_t");
        }
    }

    /**
     * Internal: for classes like Store to access the underlying pointer
     */
    public function getInner(): FFI\CData
    {
        return $this->engine;
    }

    /**
     * Clean up the engine with wasm_engine_delete().
     */
    public function __destruct()
    {
        $ffi = WasmerFFI::getFFI();
        $ffi->wasm_engine_delete($this->engine);
    }
}
