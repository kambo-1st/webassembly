<?php

namespace Kambo\WebAssembly\Tests\E2E;

use PHPUnit\Framework\TestCase;
use Kambo\WebAssembly\Native\WasmerFFI;
use Kambo\WebAssembly\Engine;
use Kambo\WebAssembly\Store;
use Kambo\WebAssembly\Module;
use Kambo\WebAssembly\Instance;
use Kambo\WebAssembly\Collection;
use Kambo\WebAssembly\Value;
use Kambo\WebAssembly\Exception\WasmerException;

class WasmSumTest extends TestCase
{
    public function testWasmSumFunction(): void
    {
        // Create engine and store
        $engine = new Engine();
        $store = new Store($engine);

        // Define WAT (WebAssembly Text) code
        $wat = '(module
            (type $sum_t (func (param i32 i32) (result i32)))
            (func $sum_f (type $sum_t) (param $x i32) (param $y i32) (result i32)
            local.get $x
            local.get $y
            i32.add)
            (export "sum" (func $sum_f)))';

        // Convert WAT to WASM bytes
        $wasmBytes = WasmerFFI::watToWasm($wat);
        
        // Create and instantiate the module
        $module = new Module($store, $wasmBytes);
        $instance = new Instance($store, $module);
        
        // Test case 1: Basic addition
        $args = new Collection([
            Value::i32(10),
            Value::i32(32)
        ]);
        
        $results = $instance->callFunction('sum', $args);

        $this->assertCount(1, $results, 'Sum function should return exactly one result');
        $this->assertEquals(42, $results[0]->asI32(), 'Sum of 10 and 32 should be 42');

        // Test case 2: Using Collection::from
        $args = Collection::from([5, 7], Value::KIND_I32);
        $results = $instance->callFunction('sum', $args);
        
        $this->assertCount(1, $results, 'Sum function should return exactly one result');
        $this->assertEquals(12, $results[0]->asI32(), 'Sum of 5 and 7 should be 12');
        
        // Test case 3: Adding negative numbers
        $args = new Collection([
            Value::i32(-10),
            Value::i32(20)
        ]);
        
        $results = $instance->callFunction('sum', $args);
        
        $this->assertCount(1, $results, 'Sum function should return exactly one result');
        $this->assertEquals(10, $results[0]->asI32(), 'Sum of -10 and 20 should be 10');
    }
}
