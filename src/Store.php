<?php

namespace Kambo\WebAssembly;

use FFI;
use Kambo\WebAssembly\Exception\WasmerException;
use Kambo\WebAssembly\Native\WasmerFFI;

/**
 * A Store holds the Engine and is needed to create Modules/Instances.
 */
final class Store
{
    /** @var FFI\CData */
    private FFI\CData $store;

    /**
     * Create a Store from an existing Engine.
     */
    public function __construct(Engine $engine)
    {
        $ffi = WasmerFFI::getFFI();
        $this->store = $ffi->wasm_store_new($engine->getInner());

        if ($this->store === null) {
            throw new WasmerException("Failed to create wasm_store_t");
        }
    }

    /**
     * Internal: get pointer
     */
    public function getInner(): FFI\CData
    {
        return $this->store;
    }

    /**
     * Clean up with wasm_store_delete().
     */
    public function __destruct()
    {
        $ffi = WasmerFFI::getFFI();
        $ffi->wasm_store_delete($this->store);
    }
}
