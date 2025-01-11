<?php

namespace Kambo\WebAssembly\Native;

use FFI;
use Kambo\WebAssembly\Exception\WasmerException;

/**
 * Static class for managing the Wasmer FFI handle.
 */
final class WasmerFFI
{
    /** @var FFI|null */
    private static ?FFI $ffi = null;

    const WASMER_HEADER_FILE = __DIR__ . DIRECTORY_SEPARATOR . 'WasmerFFI.h';
    const WASMER_LIB_DIR = __DIR__ . DIRECTORY_SEPARATOR . 'lib';

    /**
     * Private constructor to prevent instantiation
     */
    private function __construct()
    {
    }

    /**
     * Initialize the Wasmer FFI. This is called automatically when needed.
     *
     * @throws WasmerException
     */
    private static function init(): void
    {
        if (self::$ffi !== null) {
            return;
        }

        $libraryPath = self::detectLibraryPath();

        // cdef the big header, provide the path to the library
        self::$ffi = FFI::cdef(
            file_get_contents(self::WASMER_HEADER_FILE),
            $libraryPath
        );

        if (!self::$ffi) {
            throw new WasmerException("Failed to initialize Wasmer FFI with library: $libraryPath");
        }
    }

    /**
     * Detect the appropriate library path based on the operating system
     *
     * @return string
     * @throws WasmerException
     */
    private static function detectLibraryPath(): string
    {
        $os = PHP_OS_FAMILY;
        $libPath = self::WASMER_LIB_DIR . DIRECTORY_SEPARATOR;

        switch ($os) {
            case 'Windows':
                $libPath .= 'wasmer.dll';
                break;
            case 'Darwin':
                throw new WasmerException("Mac OS is not supported yet");
            case 'Linux':
                $libPath .= 'libwasmer.so';
                break;
            default:
                throw new WasmerException("Unsupported operating system: $os");
        }

        if (!file_exists($libPath)) {
            throw new WasmerException("Wasmer library not found at: $libPath");
        }

        return $libPath;
    }

    /**
     * Internal method to retrieve the FFI handle.
     *
     * @return FFI
     * @throws WasmerException if initialization fails
     */
    public static function getFFI(): FFI
    {
        if (self::$ffi === null) {
            self::init();
        }
        return self::$ffi;
    }

    /**
     * Convenient method to convert WAT -> WASM bytes (as a PHP string).
     *
     * @param string $wat
     * @return string Raw WASM bytes
     */
    public static function watToWasm(string $wat): string
    {
        $ffi = self::getFFI();

        $watVec = $ffi->new('wasm_byte_vec_t');
        $ffi->wasm_byte_vec_new(
            FFI::addr($watVec),
            \strlen($wat),
            $wat
        );

        $wasmVec = $ffi->new('wasm_byte_vec_t');
        $ffi->wat2wasm(
            FFI::addr($watVec),
            FFI::addr($wasmVec)
        );

        // Cleanup
        $ffi->wasm_byte_vec_delete(FFI::addr($watVec));

        // Convert the bytes to a PHP string
        $wasmString = FFI::string($wasmVec->data, $wasmVec->size);

        // Cleanup
        $ffi->wasm_byte_vec_delete(FFI::addr($wasmVec));

        return $wasmString;
    }
}
