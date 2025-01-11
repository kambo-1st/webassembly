typedef char byte_t;
typedef float float32_t;
typedef double float64_t;
typedef byte_t wasm_byte_t;
typedef struct wasm_byte_vec_t { size_t size; wasm_byte_t * data; } wasm_byte_vec_t; void wasm_byte_vec_new_empty( wasm_byte_vec_t* out); void wasm_byte_vec_new_uninitialized( wasm_byte_vec_t* out, size_t); void wasm_byte_vec_new( wasm_byte_vec_t* out, size_t, wasm_byte_t const[]); void wasm_byte_vec_copy( wasm_byte_vec_t* out, const wasm_byte_vec_t*); void wasm_byte_vec_delete( wasm_byte_vec_t*);
typedef wasm_byte_vec_t wasm_name_t;
typedef struct wasm_config_t wasm_config_t; void wasm_config_delete( wasm_config_t*);
 wasm_config_t* wasm_config_new();
// Embedders may provide custom functions for manipulating configs.
// Engine
typedef struct wasm_engine_t wasm_engine_t; void wasm_engine_delete( wasm_engine_t*);
// During testing, we use a custom implementation of wasm_engine_new
 wasm_engine_t* wasm_engine_new();
 wasm_engine_t* wasm_engine_new_with_config( wasm_config_t*);
// Store
typedef struct wasm_store_t wasm_store_t; void wasm_store_delete( wasm_store_t*);
 wasm_store_t* wasm_store_new(wasm_engine_t*);
///////////////////////////////////////////////////////////////////////////////
// Type Representations
// Type attributes
typedef uint8_t wasm_mutability_t;
enum wasm_mutability_enum {
  WASM_CONST,
  WASM_VAR,
};
typedef struct wasm_limits_t {
  uint32_t min;
  uint32_t max;
} wasm_limits_t;
static const uint32_t wasm_limits_max_default = 0xffffffff;
// Generic
// Value Types
typedef struct wasm_valtype_t wasm_valtype_t; void wasm_valtype_delete( wasm_valtype_t*); typedef struct wasm_valtype_vec_t { size_t size; wasm_valtype_t ** data; } wasm_valtype_vec_t; void wasm_valtype_vec_new_empty( wasm_valtype_vec_t* out); void wasm_valtype_vec_new_uninitialized( wasm_valtype_vec_t* out, size_t); void wasm_valtype_vec_new( wasm_valtype_vec_t* out, size_t, wasm_valtype_t * const[]); void wasm_valtype_vec_copy( wasm_valtype_vec_t* out, const wasm_valtype_vec_t*); void wasm_valtype_vec_delete( wasm_valtype_vec_t*);
typedef uint8_t wasm_valkind_t;
enum wasm_valkind_enum {
  WASM_I32,
  WASM_I64,
  WASM_F32,
  WASM_F64,
  WASM_EXTERNREF = 128,
  WASM_FUNCREF,
};
 wasm_valtype_t* wasm_valtype_new(wasm_valkind_t);
 wasm_valkind_t wasm_valtype_kind(const wasm_valtype_t*);
// Function Types
typedef struct wasm_functype_t wasm_functype_t; void wasm_functype_delete( wasm_functype_t*); typedef struct wasm_functype_vec_t { size_t size; wasm_functype_t ** data; } wasm_functype_vec_t; void wasm_functype_vec_new_empty( wasm_functype_vec_t* out); void wasm_functype_vec_new_uninitialized( wasm_functype_vec_t* out, size_t); void wasm_functype_vec_new( wasm_functype_vec_t* out, size_t, wasm_functype_t * const[]); void wasm_functype_vec_copy( wasm_functype_vec_t* out, const wasm_functype_vec_t*); void wasm_functype_vec_delete( wasm_functype_vec_t*); wasm_functype_t* wasm_functype_copy(wasm_functype_t*);
 wasm_functype_t* wasm_functype_new(
  wasm_valtype_vec_t* params, wasm_valtype_vec_t* results);
 const wasm_valtype_vec_t* wasm_functype_params(const wasm_functype_t*);
 const wasm_valtype_vec_t* wasm_functype_results(const wasm_functype_t*);
// Global Types
typedef struct wasm_globaltype_t wasm_globaltype_t; void wasm_globaltype_delete( wasm_globaltype_t*); typedef struct wasm_globaltype_vec_t { size_t size; wasm_globaltype_t ** data; } wasm_globaltype_vec_t; void wasm_globaltype_vec_new_empty( wasm_globaltype_vec_t* out); void wasm_globaltype_vec_new_uninitialized( wasm_globaltype_vec_t* out, size_t); void wasm_globaltype_vec_new( wasm_globaltype_vec_t* out, size_t, wasm_globaltype_t * const[]); void wasm_globaltype_vec_copy( wasm_globaltype_vec_t* out, const wasm_globaltype_vec_t*); void wasm_globaltype_vec_delete( wasm_globaltype_vec_t*);
 wasm_globaltype_t* wasm_globaltype_new(
  wasm_valtype_t*, wasm_mutability_t);
 const wasm_valtype_t* wasm_globaltype_content(const wasm_globaltype_t*);
 wasm_mutability_t wasm_globaltype_mutability(const wasm_globaltype_t*);
// Table Types
typedef struct wasm_tabletype_t wasm_tabletype_t; void wasm_tabletype_delete( wasm_tabletype_t*); typedef struct wasm_tabletype_vec_t { size_t size; wasm_tabletype_t ** data; } wasm_tabletype_vec_t; void wasm_tabletype_vec_new_empty( wasm_tabletype_vec_t* out); void wasm_tabletype_vec_new_uninitialized( wasm_tabletype_vec_t* out, size_t); void wasm_tabletype_vec_new( wasm_tabletype_vec_t* out, size_t, wasm_tabletype_t * const[]); void wasm_tabletype_vec_copy( wasm_tabletype_vec_t* out, const wasm_tabletype_vec_t*); void wasm_tabletype_vec_delete( wasm_tabletype_vec_t*);
 wasm_tabletype_t* wasm_tabletype_new(
  wasm_valtype_t*, const wasm_limits_t*);
 const wasm_valtype_t* wasm_tabletype_element(const wasm_tabletype_t*);
 const wasm_limits_t* wasm_tabletype_limits(const wasm_tabletype_t*);
// Memory Types
typedef struct wasm_memorytype_t wasm_memorytype_t; void wasm_memorytype_delete( wasm_memorytype_t*); typedef struct wasm_memorytype_vec_t { size_t size; wasm_memorytype_t ** data; } wasm_memorytype_vec_t; void wasm_memorytype_vec_new_empty( wasm_memorytype_vec_t* out); void wasm_memorytype_vec_new_uninitialized( wasm_memorytype_vec_t* out, size_t); void wasm_memorytype_vec_new( wasm_memorytype_vec_t* out, size_t, wasm_memorytype_t * const[]); void wasm_memorytype_vec_copy( wasm_memorytype_vec_t* out, const wasm_memorytype_vec_t*); void wasm_memorytype_vec_delete( wasm_memorytype_vec_t*);
 wasm_memorytype_t* wasm_memorytype_new(const wasm_limits_t*);
 const wasm_limits_t* wasm_memorytype_limits(const wasm_memorytype_t*);
// Extern Types
typedef struct wasm_externtype_t wasm_externtype_t; void wasm_externtype_delete( wasm_externtype_t*); typedef struct wasm_externtype_vec_t { size_t size; wasm_externtype_t ** data; } wasm_externtype_vec_t; wasm_externtype_t* wasm_externtype_copy(wasm_externtype_t*);
typedef uint8_t wasm_externkind_t;
enum wasm_externkind_enum {
  WASM_EXTERN_FUNC,
  WASM_EXTERN_GLOBAL,
  WASM_EXTERN_TABLE,
  WASM_EXTERN_MEMORY,
};
 wasm_externkind_t wasm_externtype_kind(const wasm_externtype_t*);
 wasm_externtype_t* wasm_functype_as_externtype(wasm_functype_t*);
 wasm_externtype_t* wasm_globaltype_as_externtype(wasm_globaltype_t*);
 wasm_externtype_t* wasm_tabletype_as_externtype(wasm_tabletype_t*);
 wasm_externtype_t* wasm_memorytype_as_externtype(wasm_memorytype_t*);
 wasm_functype_t* wasm_externtype_as_functype(wasm_externtype_t*);
 wasm_globaltype_t* wasm_externtype_as_globaltype(wasm_externtype_t*);
 wasm_tabletype_t* wasm_externtype_as_tabletype(wasm_externtype_t*);
 wasm_memorytype_t* wasm_externtype_as_memorytype(wasm_externtype_t*);
 const wasm_externtype_t* wasm_functype_as_externtype_const(const wasm_functype_t*);
 const wasm_externtype_t* wasm_globaltype_as_externtype_const(const wasm_globaltype_t*);
 const wasm_externtype_t* wasm_tabletype_as_externtype_const(const wasm_tabletype_t*);
 const wasm_externtype_t* wasm_memorytype_as_externtype_const(const wasm_memorytype_t*);
 const wasm_functype_t* wasm_externtype_as_functype_const(const wasm_externtype_t*);
 const wasm_globaltype_t* wasm_externtype_as_globaltype_const(const wasm_externtype_t*);
 const wasm_tabletype_t* wasm_externtype_as_tabletype_const(const wasm_externtype_t*);
 const wasm_memorytype_t* wasm_externtype_as_memorytype_const(const wasm_externtype_t*);
// Import Types
typedef struct wasm_importtype_t wasm_importtype_t; void wasm_importtype_delete( wasm_importtype_t*); typedef struct wasm_importtype_vec_t { size_t size; wasm_importtype_t ** data; } wasm_importtype_vec_t; void wasm_importtype_vec_new_empty( wasm_importtype_vec_t* out); void wasm_importtype_vec_new_uninitialized( wasm_importtype_vec_t* out, size_t); void wasm_importtype_vec_new( wasm_importtype_vec_t* out, size_t, wasm_importtype_t * const[]); void wasm_importtype_vec_copy( wasm_importtype_vec_t* out, const wasm_importtype_vec_t*); void wasm_importtype_vec_delete( wasm_importtype_vec_t*); wasm_importtype_t* wasm_importtype_copy(wasm_importtype_t*);
 wasm_importtype_t* wasm_importtype_new(
  wasm_name_t* module, wasm_name_t* name, wasm_externtype_t*);
 const wasm_name_t* wasm_importtype_module(const wasm_importtype_t*);
 const wasm_name_t* wasm_importtype_name(const wasm_importtype_t*);
 const wasm_externtype_t* wasm_importtype_type(const wasm_importtype_t*);
// Export Types
typedef struct wasm_exporttype_t wasm_exporttype_t; void wasm_exporttype_delete( wasm_exporttype_t*); typedef struct wasm_exporttype_vec_t { size_t size; wasm_exporttype_t ** data; } wasm_exporttype_vec_t; void wasm_exporttype_vec_new_empty( wasm_exporttype_vec_t* out); void wasm_exporttype_vec_new_uninitialized( wasm_exporttype_vec_t* out, size_t); void wasm_exporttype_vec_new( wasm_exporttype_vec_t* out, size_t, wasm_exporttype_t * const[]); void wasm_exporttype_vec_copy( wasm_exporttype_vec_t* out, const wasm_exporttype_vec_t*); void wasm_exporttype_vec_delete( wasm_exporttype_vec_t*); wasm_exporttype_t* wasm_exporttype_copy(wasm_exporttype_t*);
 wasm_exporttype_t* wasm_exporttype_new(
  wasm_name_t*, wasm_externtype_t*);
 const wasm_name_t* wasm_exporttype_name(const wasm_exporttype_t*);
 const wasm_externtype_t* wasm_exporttype_type(const wasm_exporttype_t*);
///////////////////////////////////////////////////////////////////////////////
// Runtime Objects
// Values
struct wasm_ref_t;
typedef struct wasm_val_t {
  wasm_valkind_t kind;
  union {
    int32_t i32;
    int64_t i64;
    float32_t f32;
    float64_t f64;
    struct wasm_ref_t* ref;
  } of;
} wasm_val_t;
 void wasm_val_delete( wasm_val_t* v);
 void wasm_val_copy( wasm_val_t* out, const wasm_val_t*);
typedef struct wasm_val_vec_t { size_t size; wasm_val_t * data; } wasm_val_vec_t; void wasm_val_vec_new_empty( wasm_val_vec_t* out); void wasm_val_vec_new_uninitialized( wasm_val_vec_t* out, size_t); void wasm_val_vec_new( wasm_val_vec_t* out, size_t, wasm_val_t const[]); void wasm_val_vec_copy( wasm_val_vec_t* out, const wasm_val_vec_t*); void wasm_val_vec_delete( wasm_val_vec_t*);
// References
typedef struct wasm_ref_t wasm_ref_t;
// Frames
typedef struct wasm_frame_t wasm_frame_t; void wasm_frame_delete( wasm_frame_t*);
typedef struct wasm_frame_vec_t { size_t size; wasm_frame_t ** data; } wasm_frame_vec_t; void wasm_frame_vec_new_empty( wasm_frame_vec_t* out); void wasm_frame_vec_new_uninitialized( wasm_frame_vec_t* out, size_t); void wasm_frame_vec_new( wasm_frame_vec_t* out, size_t, wasm_frame_t * const[]); void wasm_frame_vec_copy( wasm_frame_vec_t* out, const wasm_frame_vec_t*); void wasm_frame_vec_delete( wasm_frame_vec_t*);
 wasm_frame_t* wasm_frame_copy(const wasm_frame_t*);
 struct wasm_instance_t* wasm_frame_instance(const wasm_frame_t*);
 uint32_t wasm_frame_func_index(const wasm_frame_t*);
 size_t wasm_frame_func_offset(const wasm_frame_t*);
 size_t wasm_frame_module_offset(const wasm_frame_t*);
// Traps
typedef wasm_name_t wasm_message_t; // null terminated
typedef struct wasm_trap_t wasm_trap_t;
 wasm_trap_t* wasm_trap_new(wasm_store_t* store, const wasm_message_t*);
 void wasm_trap_message(const wasm_trap_t*, wasm_message_t* out);
 wasm_frame_t* wasm_trap_origin(const wasm_trap_t*);
 void wasm_trap_trace(const wasm_trap_t*, wasm_frame_vec_t* out);
// Foreign Objects
typedef struct wasm_foreign_t wasm_foreign_t;
// Modules
typedef struct wasm_module_t wasm_module_t; void wasm_module_delete( wasm_module_t*);  typedef struct wasm_shared_module_t wasm_shared_module_t;
 wasm_module_t* wasm_module_new(
  wasm_store_t*, const wasm_byte_vec_t* binary);
 _Bool wasm_module_validate(wasm_store_t*, const wasm_byte_vec_t* binary);
 void wasm_module_imports(const wasm_module_t*, wasm_importtype_vec_t* out);
 void wasm_module_exports(const wasm_module_t*, wasm_exporttype_vec_t* out);
 void wasm_module_serialize(const wasm_module_t*, wasm_byte_vec_t* out);
 wasm_module_t* wasm_module_deserialize(wasm_store_t*, const wasm_byte_vec_t*);
// Function Instances
typedef struct wasm_func_t wasm_func_t; void wasm_func_delete( wasm_func_t*); wasm_func_t* wasm_func_copy(const wasm_func_t*);  
typedef wasm_trap_t* (*wasm_func_callback_t)(
  const wasm_val_vec_t* args, wasm_val_vec_t* results);
typedef wasm_trap_t* (*wasm_func_callback_with_env_t)(
  void* env, const wasm_val_vec_t* args, wasm_val_vec_t* results);
 wasm_func_t* wasm_func_new(
  wasm_store_t*, const wasm_functype_t*, wasm_func_callback_t);
 wasm_func_t* wasm_func_new_with_env(
  wasm_store_t*, const wasm_functype_t* type, wasm_func_callback_with_env_t,
  void* env, void (*finalizer)(void*));
 wasm_functype_t* wasm_func_type(const wasm_func_t*);
 size_t wasm_func_param_arity(const wasm_func_t*);
 size_t wasm_func_result_arity(const wasm_func_t*);
 wasm_trap_t* wasm_func_call(
  const wasm_func_t*, const wasm_val_vec_t* args, wasm_val_vec_t* results);
// Global Instances
typedef struct wasm_global_t wasm_global_t; void wasm_global_delete( wasm_global_t*); wasm_global_t* wasm_global_copy(const wasm_global_t*); _Bool wasm_global_same(const wasm_global_t*, const wasm_global_t*);
 wasm_global_t* wasm_global_new(
  wasm_store_t*, const wasm_globaltype_t*, const wasm_val_t*);
 wasm_globaltype_t* wasm_global_type(const wasm_global_t*);
 void wasm_global_get(const wasm_global_t*, wasm_val_t* out);
 void wasm_global_set(wasm_global_t*, const wasm_val_t*);
// Table Instances
typedef struct wasm_table_t wasm_table_t; void wasm_table_delete( wasm_table_t*); wasm_table_t* wasm_table_copy(const wasm_table_t*); _Bool wasm_table_same(const wasm_table_t*, const wasm_table_t*);
typedef uint32_t wasm_table_size_t;
 wasm_table_t* wasm_table_new(
  wasm_store_t*, const wasm_tabletype_t*, wasm_ref_t* init);
 wasm_table_size_t wasm_table_size(const wasm_table_t*);
 _Bool wasm_table_grow(wasm_table_t*, wasm_table_size_t delta, wasm_ref_t* init);
// Memory Instances
typedef struct wasm_memory_t wasm_memory_t; void wasm_memory_delete( wasm_memory_t*); wasm_memory_t* wasm_memory_copy(const wasm_memory_t*); _Bool wasm_memory_same(const wasm_memory_t*, const wasm_memory_t*);
typedef uint32_t wasm_memory_pages_t;
static const size_t MEMORY_PAGE_SIZE = 0x10000;
 wasm_memory_t* wasm_memory_new(wasm_store_t*, const wasm_memorytype_t*);
 wasm_memorytype_t* wasm_memory_type(const wasm_memory_t*);
 byte_t* wasm_memory_data(wasm_memory_t*);
 size_t wasm_memory_data_size(const wasm_memory_t*);
 wasm_memory_pages_t wasm_memory_size(const wasm_memory_t*);
 _Bool wasm_memory_grow(wasm_memory_t*, wasm_memory_pages_t delta);
// Externals
typedef struct wasm_extern_t wasm_extern_t; void wasm_extern_delete( wasm_extern_t*); wasm_extern_t* wasm_extern_copy(const wasm_extern_t*);
typedef struct wasm_extern_vec_t { size_t size; wasm_extern_t ** data; } wasm_extern_vec_t; void wasm_extern_vec_new_empty( wasm_extern_vec_t* out); void wasm_extern_vec_new_uninitialized( wasm_extern_vec_t* out, size_t); void wasm_extern_vec_new( wasm_extern_vec_t* out, size_t, wasm_extern_t * const[]); void wasm_extern_vec_copy( wasm_extern_vec_t* out, const wasm_extern_vec_t*); void wasm_extern_vec_delete( wasm_extern_vec_t*);
 wasm_externkind_t wasm_extern_kind(const wasm_extern_t*);
 wasm_externtype_t* wasm_extern_type(const wasm_extern_t*);
 wasm_extern_t* wasm_func_as_extern(wasm_func_t*);
 wasm_extern_t* wasm_global_as_extern(wasm_global_t*);
 wasm_extern_t* wasm_table_as_extern(wasm_table_t*);
 wasm_extern_t* wasm_memory_as_extern(wasm_memory_t*);
 wasm_func_t* wasm_extern_as_func(wasm_extern_t*);
 wasm_global_t* wasm_extern_as_global(wasm_extern_t*);
 wasm_table_t* wasm_extern_as_table(wasm_extern_t*);
 wasm_memory_t* wasm_extern_as_memory(wasm_extern_t*);


 /*const wasm_extern_t* wasm_table_as_extern_const(const wasm_table_t*);
 const wasm_extern_t* wasm_memory_as_extern_const(const wasm_memory_t*);
 const wasm_func_t* wasm_extern_as_func_const(const wasm_extern_t*);
 const wasm_global_t* wasm_extern_as_global_const(const wasm_extern_t*);
 const wasm_table_t* wasm_extern_as_table_const(const wasm_extern_t*);
 const wasm_memory_t* wasm_extern_as_memory_const(const wasm_extern_t*);*/

// Module Instances
typedef struct wasm_instance_t wasm_instance_t; void wasm_instance_delete( wasm_instance_t*);
 wasm_instance_t* wasm_instance_new(
  wasm_store_t*, const wasm_module_t*, const wasm_extern_vec_t* imports,
  wasm_trap_t**
);
 void wasm_instance_exports(const wasm_instance_t*, wasm_extern_vec_t* out);



typedef enum wasi_version_t {
    INVALID_VERSION = -1,
    LATEST = 0,
    SNAPSHOT0 = 1,
    SNAPSHOT1 = 2,
    WASIX32V1 = 3,
    WASIX64V1 = 4,
  } wasi_version_t;
  typedef enum wasmer_compiler_t {
    CRANELIFT = 0,
    LLVM = 1,
    SINGLEPASS = 2,
  } wasmer_compiler_t;
  typedef enum wasmer_engine_t {
    UNIVERSAL = 0,
  } wasmer_engine_t;
  typedef enum wasmer_parser_operator_t {
    Unreachable,
    Nop,
    Block,
    Loop,
    If,
    Else,
    Try,
    Catch,
    CatchAll,
    Delegate,
    Throw,
    Rethrow,
    Unwind,
    End,
    Br,
    BrIf,
    BrTable,
    Return,
    Call,
    CallIndirect,
    ReturnCall,
    ReturnCallIndirect,
    Drop,
    Select,
    TypedSelect,
    LocalGet,
    LocalSet,
    LocalTee,
    GlobalGet,
    GlobalSet,
    I32Load,
    I64Load,
    F32Load,
    F64Load,
    I32Load8S,
    I32Load8U,
    I32Load16S,
    I32Load16U,
    I64Load8S,
    I64Load8U,
    I64Load16S,
    I64Load16U,
    I64Load32S,
    I64Load32U,
    I32Store,
    I64Store,
    F32Store,
    F64Store,
    I32Store8,
    I32Store16,
    I64Store8,
    I64Store16,
    I64Store32,
    MemorySize,
    MemoryGrow,
    I32Const,
    I64Const,
    F32Const,
    F64Const,
    RefNull,
    RefIsNull,
    RefFunc,
    I32Eqz,
    I32Eq,
    I32Ne,
    I32LtS,
    I32LtU,
    I32GtS,
    I32GtU,
    I32LeS,
    I32LeU,
    I32GeS,
    I32GeU,
    I64Eqz,
    I64Eq,
    I64Ne,
    I64LtS,
    I64LtU,
    I64GtS,
    I64GtU,
    I64LeS,
    I64LeU,
    I64GeS,
    I64GeU,
    F32Eq,
    F32Ne,
    F32Lt,
    F32Gt,
    F32Le,
    F32Ge,
    F64Eq,
    F64Ne,
    F64Lt,
    F64Gt,
    F64Le,
    F64Ge,
    I32Clz,
    I32Ctz,
    I32Popcnt,
    I32Add,
    I32Sub,
    I32Mul,
    I32DivS,
    I32DivU,
    I32RemS,
    I32RemU,
    I32And,
    I32Or,
    I32Xor,
    I32Shl,
    I32ShrS,
    I32ShrU,
    I32Rotl,
    I32Rotr,
    I64Clz,
    I64Ctz,
    I64Popcnt,
    I64Add,
    I64Sub,
    I64Mul,
    I64DivS,
    I64DivU,
    I64RemS,
    I64RemU,
    I64And,
    I64Or,
    I64Xor,
    I64Shl,
    I64ShrS,
    I64ShrU,
    I64Rotl,
    I64Rotr,
    F32Abs,
    F32Neg,
    F32Ceil,
    F32Floor,
    F32Trunc,
    F32Nearest,
    F32Sqrt,
    F32Add,
    F32Sub,
    F32Mul,
    F32Div,
    F32Min,
    F32Max,
    F32Copysign,
    F64Abs,
    F64Neg,
    F64Ceil,
    F64Floor,
    F64Trunc,
    F64Nearest,
    F64Sqrt,
    F64Add,
    F64Sub,
    F64Mul,
    F64Div,
    F64Min,
    F64Max,
    F64Copysign,
    I32WrapI64,
    I32TruncF32S,
    I32TruncF32U,
    I32TruncF64S,
    I32TruncF64U,
    I64ExtendI32S,
    I64ExtendI32U,
    I64TruncF32S,
    I64TruncF32U,
    I64TruncF64S,
    I64TruncF64U,
    F32ConvertI32S,
    F32ConvertI32U,
    F32ConvertI64S,
    F32ConvertI64U,
    F32DemoteF64,
    F64ConvertI32S,
    F64ConvertI32U,
    F64ConvertI64S,
    F64ConvertI64U,
    F64PromoteF32,
    I32ReinterpretF32,
    I64ReinterpretF64,
    F32ReinterpretI32,
    F64ReinterpretI64,
    I32Extend8S,
    I32Extend16S,
    I64Extend8S,
    I64Extend16S,
    I64Extend32S,
    I32TruncSatF32S,
    I32TruncSatF32U,
    I32TruncSatF64S,
    I32TruncSatF64U,
    I64TruncSatF32S,
    I64TruncSatF32U,
    I64TruncSatF64S,
    I64TruncSatF64U,
    MemoryInit,
    DataDrop,
    MemoryCopy,
    MemoryFill,
    TableInit,
    ElemDrop,
    TableCopy,
    TableFill,
    TableGet,
    TableSet,
    TableGrow,
    TableSize,
    MemoryAtomicNotify,
    MemoryAtomicWait32,
    MemoryAtomicWait64,
    AtomicFence,
    I32AtomicLoad,
    I64AtomicLoad,
    I32AtomicLoad8U,
    I32AtomicLoad16U,
    I64AtomicLoad8U,
    I64AtomicLoad16U,
    I64AtomicLoad32U,
    I32AtomicStore,
    I64AtomicStore,
    I32AtomicStore8,
    I32AtomicStore16,
    I64AtomicStore8,
    I64AtomicStore16,
    I64AtomicStore32,
    I32AtomicRmwAdd,
    I64AtomicRmwAdd,
    I32AtomicRmw8AddU,
    I32AtomicRmw16AddU,
    I64AtomicRmw8AddU,
    I64AtomicRmw16AddU,
    I64AtomicRmw32AddU,
    I32AtomicRmwSub,
    I64AtomicRmwSub,
    I32AtomicRmw8SubU,
    I32AtomicRmw16SubU,
    I64AtomicRmw8SubU,
    I64AtomicRmw16SubU,
    I64AtomicRmw32SubU,
    I32AtomicRmwAnd,
    I64AtomicRmwAnd,
    I32AtomicRmw8AndU,
    I32AtomicRmw16AndU,
    I64AtomicRmw8AndU,
    I64AtomicRmw16AndU,
    I64AtomicRmw32AndU,
    I32AtomicRmwOr,
    I64AtomicRmwOr,
    I32AtomicRmw8OrU,
    I32AtomicRmw16OrU,
    I64AtomicRmw8OrU,
    I64AtomicRmw16OrU,
    I64AtomicRmw32OrU,
    I32AtomicRmwXor,
    I64AtomicRmwXor,
    I32AtomicRmw8XorU,
    I32AtomicRmw16XorU,
    I64AtomicRmw8XorU,
    I64AtomicRmw16XorU,
    I64AtomicRmw32XorU,
    I32AtomicRmwXchg,
    I64AtomicRmwXchg,
    I32AtomicRmw8XchgU,
    I32AtomicRmw16XchgU,
    I64AtomicRmw8XchgU,
    I64AtomicRmw16XchgU,
    I64AtomicRmw32XchgU,
    I32AtomicRmwCmpxchg,
    I64AtomicRmwCmpxchg,
    I32AtomicRmw8CmpxchgU,
    I32AtomicRmw16CmpxchgU,
    I64AtomicRmw8CmpxchgU,
    I64AtomicRmw16CmpxchgU,
    I64AtomicRmw32CmpxchgU,
    V128Load,
    V128Store,
    V128Const,
    I8x16Splat,
    I8x16ExtractLaneS,
    I8x16ExtractLaneU,
    I8x16ReplaceLane,
    I16x8Splat,
    I16x8ExtractLaneS,
    I16x8ExtractLaneU,
    I16x8ReplaceLane,
    I32x4Splat,
    I32x4ExtractLane,
    I32x4ReplaceLane,
    I64x2Splat,
    I64x2ExtractLane,
    I64x2ReplaceLane,
    F32x4Splat,
    F32x4ExtractLane,
    F32x4ReplaceLane,
    F64x2Splat,
    F64x2ExtractLane,
    F64x2ReplaceLane,
    I8x16Eq,
    I8x16Ne,
    I8x16LtS,
    I8x16LtU,
    I8x16GtS,
    I8x16GtU,
    I8x16LeS,
    I8x16LeU,
    I8x16GeS,
    I8x16GeU,
    I16x8Eq,
    I16x8Ne,
    I16x8LtS,
    I16x8LtU,
    I16x8GtS,
    I16x8GtU,
    I16x8LeS,
    I16x8LeU,
    I16x8GeS,
    I16x8GeU,
    I32x4Eq,
    I32x4Ne,
    I32x4LtS,
    I32x4LtU,
    I32x4GtS,
    I32x4GtU,
    I32x4LeS,
    I32x4LeU,
    I32x4GeS,
    I32x4GeU,
    I64x2Eq,
    I64x2Ne,
    I64x2LtS,
    I64x2GtS,
    I64x2LeS,
    I64x2GeS,
    F32x4Eq,
    F32x4Ne,
    F32x4Lt,
    F32x4Gt,
    F32x4Le,
    F32x4Ge,
    F64x2Eq,
    F64x2Ne,
    F64x2Lt,
    F64x2Gt,
    F64x2Le,
    F64x2Ge,
    V128Not,
    V128And,
    V128AndNot,
    V128Or,
    V128Xor,
    V128Bitselect,
    V128AnyTrue,
    I8x16Abs,
    I8x16Neg,
    I8x16AllTrue,
    I8x16Bitmask,
    I8x16Shl,
    I8x16ShrS,
    I8x16ShrU,
    I8x16Add,
    I8x16AddSatS,
    I8x16AddSatU,
    I8x16Sub,
    I8x16SubSatS,
    I8x16SubSatU,
    I8x16MinS,
    I8x16MinU,
    I8x16MaxS,
    I8x16MaxU,
    I8x16Popcnt,
    I16x8Abs,
    I16x8Neg,
    I16x8AllTrue,
    I16x8Bitmask,
    I16x8Shl,
    I16x8ShrS,
    I16x8ShrU,
    I16x8Add,
    I16x8AddSatS,
    I16x8AddSatU,
    I16x8Sub,
    I16x8SubSatS,
    I16x8SubSatU,
    I16x8Mul,
    I16x8MinS,
    I16x8MinU,
    I16x8MaxS,
    I16x8MaxU,
    I16x8ExtAddPairwiseI8x16S,
    I16x8ExtAddPairwiseI8x16U,
    I32x4Abs,
    I32x4Neg,
    I32x4AllTrue,
    I32x4Bitmask,
    I32x4Shl,
    I32x4ShrS,
    I32x4ShrU,
    I32x4Add,
    I32x4Sub,
    I32x4Mul,
    I32x4MinS,
    I32x4MinU,
    I32x4MaxS,
    I32x4MaxU,
    I32x4DotI16x8S,
    I32x4ExtAddPairwiseI16x8S,
    I32x4ExtAddPairwiseI16x8U,
    I64x2Abs,
    I64x2Neg,
    I64x2AllTrue,
    I64x2Bitmask,
    I64x2Shl,
    I64x2ShrS,
    I64x2ShrU,
    I64x2Add,
    I64x2Sub,
    I64x2Mul,
    F32x4Ceil,
    F32x4Floor,
    F32x4Trunc,
    F32x4Nearest,
    F64x2Ceil,
    F64x2Floor,
    F64x2Trunc,
    F64x2Nearest,
    F32x4Abs,
    F32x4Neg,
    F32x4Sqrt,
    F32x4Add,
    F32x4Sub,
    F32x4Mul,
    F32x4Div,
    F32x4Min,
    F32x4Max,
    F32x4PMin,
    F32x4PMax,
    F64x2Abs,
    F64x2Neg,
    F64x2Sqrt,
    F64x2Add,
    F64x2Sub,
    F64x2Mul,
    F64x2Div,
    F64x2Min,
    F64x2Max,
    F64x2PMin,
    F64x2PMax,
    I32x4TruncSatF32x4S,
    I32x4TruncSatF32x4U,
    F32x4ConvertI32x4S,
    F32x4ConvertI32x4U,
    I8x16Swizzle,
    I8x16Shuffle,
    V128Load8Splat,
    V128Load16Splat,
    V128Load32Splat,
    V128Load32Zero,
    V128Load64Splat,
    V128Load64Zero,
    I8x16NarrowI16x8S,
    I8x16NarrowI16x8U,
    I16x8NarrowI32x4S,
    I16x8NarrowI32x4U,
    I16x8ExtendLowI8x16S,
    I16x8ExtendHighI8x16S,
    I16x8ExtendLowI8x16U,
    I16x8ExtendHighI8x16U,
    I32x4ExtendLowI16x8S,
    I32x4ExtendHighI16x8S,
    I32x4ExtendLowI16x8U,
    I32x4ExtendHighI16x8U,
    I64x2ExtendLowI32x4S,
    I64x2ExtendHighI32x4S,
    I64x2ExtendLowI32x4U,
    I64x2ExtendHighI32x4U,
    I16x8ExtMulLowI8x16S,
    I16x8ExtMulHighI8x16S,
    I16x8ExtMulLowI8x16U,
    I16x8ExtMulHighI8x16U,
    I32x4ExtMulLowI16x8S,
    I32x4ExtMulHighI16x8S,
    I32x4ExtMulLowI16x8U,
    I32x4ExtMulHighI16x8U,
    I64x2ExtMulLowI32x4S,
    I64x2ExtMulHighI32x4S,
    I64x2ExtMulLowI32x4U,
    I64x2ExtMulHighI32x4U,
    V128Load8x8S,
    V128Load8x8U,
    V128Load16x4S,
    V128Load16x4U,
    V128Load32x2S,
    V128Load32x2U,
    V128Load8Lane,
    V128Load16Lane,
    V128Load32Lane,
    V128Load64Lane,
    V128Store8Lane,
    V128Store16Lane,
    V128Store32Lane,
    V128Store64Lane,
    I8x16RoundingAverageU,
    I16x8RoundingAverageU,
    I16x8Q15MulrSatS,
    F32x4DemoteF64x2Zero,
    F64x2PromoteLowF32x4,
    F64x2ConvertLowI32x4S,
    F64x2ConvertLowI32x4U,
    I32x4TruncSatF64x2SZero,
    I32x4TruncSatF64x2UZero,
    I8x16RelaxedSwizzle,
    I32x4RelaxedTruncSatF32x4S,
    I32x4RelaxedTruncSatF32x4U,
    I32x4RelaxedTruncSatF64x2SZero,
    I32x4RelaxedTruncSatF64x2UZero,
    F32x4Fma,
    F32x4Fms,
    F64x2Fma,
    F64x2Fms,
    I8x16LaneSelect,
    I16x8LaneSelect,
    I32x4LaneSelect,
    I64x2LaneSelect,
    F32x4RelaxedMin,
    F32x4RelaxedMax,
    F64x2RelaxedMin,
    F64x2RelaxedMax,
    I16x8RelaxedQ15mulrS,
    I16x8DotI8x16I7x16S,
    I32x4DotI8x16I7x16AddS,
    F32x4RelaxedDotBf16x8AddF32x4,
  } wasmer_parser_operator_t;
  typedef struct wasi_config_t wasi_config_t;
  typedef struct wasi_env_t wasi_env_t;
  typedef struct wasmer_cpu_features_t wasmer_cpu_features_t;
  typedef struct wasmer_features_t wasmer_features_t;
  typedef struct wasmer_metering_t wasmer_metering_t;
  typedef struct wasmer_middleware_t wasmer_middleware_t;
  typedef struct wasmer_named_extern_t wasmer_named_extern_t;
  typedef struct wasmer_target_t wasmer_target_t;
  typedef struct wasmer_triple_t wasmer_triple_t;
  typedef struct wasi_filesystem_t {
    const char *ptr;
    uintptr_t size;
  } wasi_filesystem_t;
  typedef struct wasmer_named_extern_vec_t {
    uintptr_t size;
    struct wasmer_named_extern_t **data;
  } wasmer_named_extern_vec_t;
  typedef struct FunctionCEnv {
    void *inner;
  } FunctionCEnv;
  typedef struct wasmer_funcenv_t {
    struct FunctionCEnv inner;
  } wasmer_funcenv_t;
  typedef uint64_t (*wasmer_metering_cost_function_t)(enum wasmer_parser_operator_t wasm_operator);
  void wasi_config_arg(struct wasi_config_t *config, const char *arg);
  void wasi_config_capture_stderr(struct wasi_config_t *config);
  void wasi_config_capture_stdout(struct wasi_config_t *config);
  void wasi_config_env(struct wasi_config_t *config, const char *key, const char *value);
  void wasi_config_inherit_stderr(struct wasi_config_t *config);
  void wasi_config_inherit_stdin(struct wasi_config_t *config);
  void wasi_config_inherit_stdout(struct wasi_config_t *config);
  bool wasi_config_mapdir(struct wasi_config_t *config, const char *alias, const char *dir);
  struct wasi_config_t *wasi_config_new(const char *program_name);
  bool wasi_config_preopen_dir(struct wasi_config_t *config, const char *dir);
  void wasi_env_delete(struct wasi_env_t *state);
  bool wasi_env_initialize_instance(struct wasi_env_t *wasi_env,
                                    wasm_store_t *store,
                                    wasm_instance_t *instance);
  struct wasi_env_t *wasi_env_new(wasm_store_t *store, struct wasi_config_t *config);
  intptr_t wasi_env_read_stderr(struct wasi_env_t *env, char *buffer, uintptr_t buffer_len);
  intptr_t wasi_env_read_stdout(struct wasi_env_t *env, char *buffer, uintptr_t buffer_len);
  void wasi_env_set_memory(struct wasi_env_t *_env, const wasm_memory_t *_memory);
  struct wasi_env_t *wasi_env_with_filesystem(struct wasi_config_t *config,
                                              wasm_store_t *store,
                                              const wasm_module_t *module,
                                              const struct wasi_filesystem_t *fs,
                                              wasm_extern_vec_t *imports,
                                              const char *package);
  void wasi_filesystem_delete(struct wasi_filesystem_t *ptr);
  struct wasi_filesystem_t *wasi_filesystem_init_static_memory(const wasm_byte_vec_t *volume_bytes);
  bool wasi_get_imports(const wasm_store_t *_store,
                        struct wasi_env_t *wasi_env,
                        const wasm_module_t *module,
                        wasm_extern_vec_t *imports);
  wasm_func_t *wasi_get_start_function(wasm_instance_t *instance);
  bool wasi_get_unordered_imports(struct wasi_env_t *wasi_env,
                                  const wasm_module_t *module,
                                  struct wasmer_named_extern_vec_t *imports);
  enum wasi_version_t wasi_get_wasi_version(const wasm_module_t *module);
  void wasm_config_canonicalize_nans(wasm_config_t *config, bool enable);
  void wasm_config_push_middleware(wasm_config_t *config, struct wasmer_middleware_t *middleware);
  void wasm_config_set_compiler(wasm_config_t *config, enum wasmer_compiler_t compiler);
  void wasm_config_set_engine(wasm_config_t *config, enum wasmer_engine_t engine);
  void wasm_config_set_features(wasm_config_t *config, struct wasmer_features_t *features);
  void wasm_config_set_target(wasm_config_t *config, struct wasmer_target_t *target);
  bool wasmer_cpu_features_add(struct wasmer_cpu_features_t *cpu_features,
                               const wasm_name_t *feature);
  void wasmer_cpu_features_delete(struct wasmer_cpu_features_t *_cpu_features);
  struct wasmer_cpu_features_t *wasmer_cpu_features_new(void);
  bool wasmer_features_bulk_memory(struct wasmer_features_t *features, bool enable);
  void wasmer_features_delete(struct wasmer_features_t *_features);
  bool wasmer_features_memory64(struct wasmer_features_t *features, bool enable);
  bool wasmer_features_module_linking(struct wasmer_features_t *features, bool enable);
  bool wasmer_features_multi_memory(struct wasmer_features_t *features, bool enable);
  bool wasmer_features_multi_value(struct wasmer_features_t *features, bool enable);
  struct wasmer_features_t *wasmer_features_new(void);
  bool wasmer_features_reference_types(struct wasmer_features_t *features, bool enable);
  bool wasmer_features_simd(struct wasmer_features_t *features, bool enable);
  bool wasmer_features_tail_call(struct wasmer_features_t *features, bool enable);
  bool wasmer_features_threads(struct wasmer_features_t *features, bool enable);
  void wasmer_funcenv_delete(struct wasmer_funcenv_t *_funcenv);
  struct wasmer_funcenv_t *wasmer_funcenv_new(wasm_store_t *store, void *data);
  bool wasmer_is_compiler_available(enum wasmer_compiler_t compiler);
  bool wasmer_is_engine_available(enum wasmer_engine_t engine);
  bool wasmer_is_headless(void);
  int wasmer_last_error_length(void);
  int wasmer_last_error_message(char *buffer, int length);
  struct wasmer_middleware_t *wasmer_metering_as_middleware(struct wasmer_metering_t *metering);
  void wasmer_metering_delete(struct wasmer_metering_t *_metering);
  uint64_t wasmer_metering_get_remaining_points(wasm_instance_t *instance);
  struct wasmer_metering_t *wasmer_metering_new(uint64_t initial_limit,
                                                wasmer_metering_cost_function_t cost_function);
  bool wasmer_metering_points_are_exhausted(wasm_instance_t *instance);
  void wasmer_metering_set_remaining_points(wasm_instance_t *instance, uint64_t new_limit);
  void wasmer_module_name(const wasm_module_t *module, wasm_name_t *out);
  wasm_module_t *wasmer_module_new(wasm_engine_t *engine, const wasm_byte_vec_t *bytes);
  bool wasmer_module_set_name(wasm_module_t *module, const wasm_name_t *name);
  const wasm_name_t *wasmer_named_extern_module(const struct wasmer_named_extern_t *named_extern);
  const wasm_name_t *wasmer_named_extern_name(const struct wasmer_named_extern_t *named_extern);
  const wasm_extern_t *wasmer_named_extern_unwrap(const struct wasmer_named_extern_t *named_extern);
  void wasmer_named_extern_vec_copy(struct wasmer_named_extern_vec_t *out_ptr,
                                    const struct wasmer_named_extern_vec_t *in_ptr);
  void wasmer_named_extern_vec_delete(struct wasmer_named_extern_vec_t *ptr);
  void wasmer_named_extern_vec_new(struct wasmer_named_extern_vec_t *out,
                                   uintptr_t length,
                                   struct wasmer_named_extern_t *const *init);
  void wasmer_named_extern_vec_new_empty(struct wasmer_named_extern_vec_t *out);
  void wasmer_named_extern_vec_new_uninitialized(struct wasmer_named_extern_vec_t *out,
                                                 uintptr_t length);
  void wasmer_setup_tracing(int verbosity_level, int use_color);
  void wasmer_target_delete(struct wasmer_target_t *_target);
  struct wasmer_target_t *wasmer_target_new(struct wasmer_triple_t *triple,
                                            struct wasmer_cpu_features_t *cpu_features);
  void wasmer_triple_delete(struct wasmer_triple_t *_triple);
  struct wasmer_triple_t *wasmer_triple_new(const wasm_name_t *triple);
  struct wasmer_triple_t *wasmer_triple_new_from_host(void);
  const char *wasmer_version(void);
  uint8_t wasmer_version_major(void);
  uint8_t wasmer_version_minor(void);
  uint8_t wasmer_version_patch(void);
  const char *wasmer_version_pre(void);
  void wat2wasm(const wasm_byte_vec_t *wat, wasm_byte_vec_t *out);
  