<?php

namespace Kambo\WebAssembly;

use FFI;
use Countable;
use ArrayAccess;
use Iterator;
use Kambo\WebAssembly\Exception\WasmerException;

/**
 * Collection class to handle arrays of WASM values.
 * Provides a cleaner interface for managing wasm_val_vec_t structures.
 */
final class Collection implements Countable, ArrayAccess, Iterator
{
    /** @var Value[] */
    private array $values = [];
    
    /** @var int Current position for Iterator */
    private int $position = 0;

    /**
     * Create a new Collection from Value objects
     *
     * @param Value[] $values
     */
    public function __construct(array $values = [])
    {
        foreach ($values as $value) {
            if (!($value instanceof Value)) {
                throw new WasmerException('Collection can only contain Value objects');
            }
        }
        $this->values = $values;
    }

    /**
     * Create a Collection from raw values, automatically converting to appropriate Value types
     */
    public static function from(array $values, int $kind = Value::KIND_I32): self
    {
        $collection = new self();
        foreach ($values as $value) {
            switch ($kind) {
                case Value::KIND_I32:
                    $collection->push(Value::i32((int)$value));
                    break;
                case Value::KIND_I64:
                    $collection->push(Value::i64((int)$value));
                    break;
                case Value::KIND_F32:
                    $collection->push(Value::f32((float)$value));
                    break;
                case Value::KIND_F64:
                    $collection->push(Value::f64((float)$value));
                    break;
                default:
                    throw new WasmerException("Unsupported value kind: $kind");
            }
        }
        return $collection;
    }

    /**
     * Add a Value to the collection
     */
    public function push(Value $value): void
    {
        $this->values[] = $value;
    }

    /**
     * Get all values as an array
     *
     * @return Value[]
     */
    public function toArray(): array
    {
        return $this->values;
    }

    /**
     * Convert to wasm_val_vec_t for FFI operations
     */
    public function toWasmValVec(FFI $ffi): FFI\CData
    {
        $count = count($this->values);
        
        // Create value array if we have values
        $valArray = null;
        if ($count > 0) {
            $valArray = $ffi->new("wasm_val_t[$count]", false);
            
            foreach ($this->values as $i => $val) {
                $valArray[$i]->kind = $val->getKind();
                $valArray[$i]->of->i32 = 0; // Initialize union
                
                switch ($val->getKind()) {
                    case Value::KIND_I32:
                        $valArray[$i]->of->i32 = $val->toInt32Raw();
                        break;
                    case Value::KIND_I64:
                        $valArray[$i]->of->i64 = $val->toInt64Raw();
                        break;
                    case Value::KIND_F32:
                        $valArray[$i]->of->f32 = $val->toFloat32Raw();
                        break;
                    case Value::KIND_F64:
                        $valArray[$i]->of->f64 = $val->toFloat64Raw();
                        break;
                }
            }
        }

        $valVec = $ffi->new('wasm_val_vec_t');
        $valVec->size = $count;
        $valVec->data = $valArray;

        return $valVec;
    }

    /**
     * Create Collection from wasm_val_vec_t
     */
    public static function fromWasmValVec(FFI\CData $valVec): self
    {
        $collection = new self();
        $size = $valVec->size;

        for ($i = 0; $i < $size; $i++) {
            $kind = $valVec->data[$i]->kind;
            switch ($kind) {
                case Value::KIND_I32:
                    $collection->push(Value::i32($valVec->data[$i]->of->i32));
                    break;
                case Value::KIND_I64:
                    $collection->push(Value::i64($valVec->data[$i]->of->i64));
                    break;
                case Value::KIND_F32:
                    $collection->push(Value::f32($valVec->data[$i]->of->f32));
                    break;
                case Value::KIND_F64:
                    $collection->push(Value::f64($valVec->data[$i]->of->f64));
                    break;
                default:
                    throw new WasmerException("Unsupported value kind in vec: $kind");
            }
        }

        return $collection;
    }

    // Countable implementation
    public function count(): int
    {
        return count($this->values);
    }

    // ArrayAccess implementation
    public function offsetExists($offset): bool
    {
        return isset($this->values[$offset]);
    }

    public function offsetGet($offset): ?Value
    {
        return $this->values[$offset] ?? null;
    }

    public function offsetSet($offset, $value): void
    {
        if (!($value instanceof Value)) {
            throw new WasmerException('Can only store Value objects in Collection');
        }
        if ($offset === null) {
            $this->values[] = $value;
        } else {
            $this->values[$offset] = $value;
        }
    }

    public function offsetUnset($offset): void
    {
        unset($this->values[$offset]);
    }

    // Iterator implementation
    public function current(): Value
    {
        return $this->values[$this->position];
    }

    public function key(): int
    {
        return $this->position;
    }

    public function next(): void
    {
        $this->position++;
    }

    public function rewind(): void
    {
        $this->position = 0;
    }

    public function valid(): bool
    {
        return isset($this->values[$this->position]);
    }
} 