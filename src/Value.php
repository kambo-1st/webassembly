<?php

namespace Kambo\WebAssembly;

use Kambo\WebAssembly\Exception\WasmerException;

/**
 * OOP wrapper for a single Wasm value (i32, i64, f32, f64).
 * The kind enum matches the 'wasm_valkind_enum'.
 */
final class Value
{
    public const KIND_I32 = 0; // WASM_I32
    public const KIND_I64 = 1; // WASM_I64
    public const KIND_F32 = 2; // WASM_F32
    public const KIND_F64 = 3; // WASM_F64

    private int $kind;
    private int|float $data;

    private function __construct(int $kind, int|float $value)
    {
        $this->kind = $kind;
        $this->data = $value;
    }

    // Factory methods:
    public static function i32(int $n): self
    {
        return new self(self::KIND_I32, $n);
    }

    public static function i64(int $n): self
    {
        return new self(self::KIND_I64, $n);
    }

    public static function f32(float $f): self
    {
        return new self(self::KIND_F32, $f);
    }

    public static function f64(float $f): self
    {
        return new self(self::KIND_F64, $f);
    }

    // Internal getters used by Instance to copy data into wasm_val_t:
    public function getKind(): int
    {
        return $this->kind;
    }

    public function toInt32Raw(): int
    {
        return (int) $this->data;
    }

    public function toInt64Raw(): int
    {
        return (int) $this->data;
    }

    public function toFloat32Raw(): float
    {
        return (float) $this->data;
    }

    public function toFloat64Raw(): float
    {
        return (float) $this->data;
    }

    // Optionally, user-facing typed getters:
    public function asI32(): int
    {
        if ($this->kind !== self::KIND_I32) {
            throw new WasmerException("Value is not i32");
        }
        return (int) $this->data;
    }

    public function asI64(): int
    {
        if ($this->kind !== self::KIND_I64) {
            throw new WasmerException("Value is not i64");
        }
        return (int) $this->data;
    }

    public function asF32(): float
    {
        if ($this->kind !== self::KIND_F32) {
            throw new WasmerException("Value is not f32");
        }
        return (float) $this->data;
    }

    public function asF64(): float
    {
        if ($this->kind !== self::KIND_F64) {
            throw new WasmerException("Value is not f64");
        }
        return (float) $this->data;
    }
}
