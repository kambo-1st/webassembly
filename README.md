# PHP WebAssembly Library

An quick POC (done in ~3 hours) for running WebAssembly modules using [Wasmer](https://wasmer.io/).

[![Latest Version on Packagist](https://img.shields.io/packagist/v/kambo/webassembly.svg?style=flat-square)](https://packagist.org/packages/kambo/webassembly)
[![Tests](https://img.shields.io/github/actions/workflow/status/kambo-1st/webassembly/run-tests.yml?branch=main&label=tests&style=flat-square)](https://github.com/kambo-1st/webassembly/actions/workflows/run-tests.yml)
[![Total Downloads](https://img.shields.io/packagist/dt/kambo/webassembly.svg?style=flat-square)](https://packagist.org/packages/kambo/webassembly)

## Installation

You can install the package via composer:

```bash
composer require kambo/webassembly
```

## Usage
Please see the [examples](examples) directory for usage examples.
```php
$engine = new Kambo\WebAssembly\Engine();
$store = new Kambo\WebAssembly\Store($engine);

// Example WAT (WebAssembly Text) code
$wat = '(module
    (func $sum (param i32 i32) (result i32)
        local.get 0
        local.get 1
        i32.add)
    (export "sum" (func $sum)))';

$wasmBytes = WasmerFFI::watToWasm($wat);
$module = new Module($store, $wasmBytes);
$instance = new Instance($store, $module);

$args = Collection::from([10, 32], Value::KIND_I32);
$result = $instance->callFunction('sum', $args);
echo $result[0]->asI32(); // Outputs: 42
```

## Current limitations

- 🔧 Needs FFI extension to be enabled.
- ⚠️ Just a POC, can segfault at any moment.
- 🧹 It's probably leaking memory.
- 📦 Wasmer runtime is bundled with the library - not a good idea for production.
- ⚡ Limited support for some WebAssembly features.
- 🍎 Does not support Mac OS (I forget password to my Mac ).

## Testing

```bash
composer test
```

## Changelog

Please see [CHANGELOG](CHANGELOG.md) for more information on what has changed recently.

## License

The MIT License (MIT). Please see [License File](LICENSE.md) for more information.
