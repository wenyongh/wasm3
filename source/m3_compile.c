#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef const char * M3Result;
struct M3Environment; typedef struct M3Environment * IM3Environment;
struct M3Runtime; typedef struct M3Runtime * IM3Runtime;
struct M3Module; typedef struct M3Module * IM3Module;
struct M3Function; typedef struct M3Function * IM3Function;
typedef struct M3ErrorInfo
{
    M3Result result;
    IM3Runtime runtime;
    IM3Module module;
    IM3Function function;
    const char * file;
    uint32_t line;
    const char * message;
}
M3ErrorInfo;
typedef struct M3StackInfo
{
    void * startAddr;
    int32_t stackSize;
}
M3StackInfo;
enum
{
    c_m3Type_none = 0,
    c_m3Type_i32 = 1,
    c_m3Type_i64 = 2,
    c_m3Type_f32 = 3,
    c_m3Type_f64 = 4,
    c_m3Type_void,
    c_m3Type_ptr,
    c_m3Type_trap,
    c_m3Type_runtime
};
typedef struct M3ImportInfo
{
    const char * moduleUtf8;
    const char * fieldUtf8;
}
M3ImportInfo;
typedef M3ImportInfo * IM3ImportInfo;
extern M3Result m3Err_none;
extern M3Result m3Err_typeListOverflow;
extern M3Result m3Err_mallocFailed;
extern M3Result m3Err_incompatibleWasmVersion;
extern M3Result m3Err_wasmMalformed;
extern M3Result m3Err_misorderedWasmSection;
extern M3Result m3Err_wasmUnderrun;
extern M3Result m3Err_wasmOverrun;
extern M3Result m3Err_wasmMissingInitExpr;
extern M3Result m3Err_lebOverflow;
extern M3Result m3Err_missingUTF8;
extern M3Result m3Err_wasmSectionUnderrun;
extern M3Result m3Err_wasmSectionOverrun;
extern M3Result m3Err_invalidTypeId;
extern M3Result m3Err_tooManyMemorySections;
extern M3Result m3Err_moduleAlreadyLinked;
extern M3Result m3Err_functionLookupFailed;
extern M3Result m3Err_functionImportMissing;
extern M3Result m3Err_noCompiler;
extern M3Result m3Err_unknownOpcode;
extern M3Result m3Err_functionStackOverflow;
extern M3Result m3Err_functionStackUnderrun;
extern M3Result m3Err_mallocFailedCodePage;
extern M3Result m3Err_settingImmutableGlobal;
extern M3Result m3Err_optimizerFailed;
extern M3Result m3Err_missingCompiledCode;
extern M3Result m3Err_wasmMemoryOverflow;
extern M3Result m3Err_globalMemoryNotAllocated;
extern M3Result m3Err_globaIndexOutOfBounds;
extern M3Result m3Err_trapOutOfBoundsMemoryAccess;
extern M3Result m3Err_trapDivisionByZero;
extern M3Result m3Err_trapIntegerOverflow;
extern M3Result m3Err_trapIntegerConversion;
extern M3Result m3Err_trapIndirectCallTypeMismatch;
extern M3Result m3Err_trapTableIndexOutOfRange;
extern M3Result m3Err_trapExit;
extern M3Result m3Err_trapAbort;
extern M3Result m3Err_trapUnreachable;
extern M3Result m3Err_trapStackOverflow;
IM3Environment m3_NewEnvironment (void);
void m3_FreeEnvironment (IM3Environment i_environment);
IM3Runtime m3_NewRuntime (IM3Environment io_environment,
                          uint32_t i_stackSizeInBytes,
                          M3StackInfo * i_nativeStackInfo);
void m3_FreeRuntime (IM3Runtime i_runtime);
const uint8_t * m3_GetMemory (IM3Runtime i_runtime,
                              uint32_t * o_memorySizeInBytes,
                              uint32_t i_memoryIndex);
M3Result m3_ParseModule (IM3Environment i_environment,
                         IM3Module * o_module,
                         const uint8_t * const i_wasmBytes,
                         uint32_t i_numWasmBytes);
void m3_FreeModule (IM3Module i_module);
M3Result m3_LoadModule (IM3Runtime io_runtime, IM3Module io_module);
typedef const void * (* M3RawCall) (IM3Runtime runtime, uint64_t * _sp, void * _mem);
M3Result m3_LinkRawFunction (IM3Module io_module,
                             const char * const i_moduleName,
                             const char * const i_functionName,
                             const char * const i_signature,
                             M3RawCall i_function);
M3Result m3_FindFunction (IM3Function * o_function,
                          IM3Runtime i_runtime,
                          const char * const i_functionName);
M3Result m3_Call (IM3Function i_function);
M3Result m3_CallWithArgs (IM3Function i_function, uint32_t i_argc, const char * const * i_argv);
void m3_GetErrorInfo (IM3Runtime i_runtime, M3ErrorInfo* info);
void m3_ResetErrorInfo (IM3Runtime i_runtime);
void m3_PrintRuntimeInfo (IM3Runtime i_runtime);
void m3_PrintM3Info (void);
void m3_PrintProfilerInfo (void);
typedef double f64;
typedef float f32;
typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint8_t u8;
typedef int8_t i8;
typedef const void * m3ret_t;
typedef const void * voidptr_t;
typedef const char * cstr_t;
typedef const char * const ccstr_t;
typedef const u8 * bytes_t;
typedef const u8 * const cbytes_t;
typedef i64 m3reg_t;
typedef u64 * m3stack_t;
typedef
const void * const cvptr_t;
typedef void * code_t;
typedef code_t const * pc_t;
typedef struct M3MemoryHeader
{
    IM3Runtime runtime;
    void * maxStack;
    size_t length;
}
M3MemoryHeader;
typedef struct M3CodePageHeader
{
    struct M3CodePage * next;
    u32 lineIndex;
    u32 numLines;
    u32 sequence;
    u32 usageCount;
}
M3CodePageHeader;
static const char * const c_waTypes [] = { "nil", "i32", "i64", "f32", "f64", "void", "void *" };
static const char * const c_waCompactTypes [] = { "0", "i", "I", "f", "F", "v", "*" };

M3Result m3Error (M3Result i_result, IM3Runtime i_runtime, IM3Module i_module, IM3Function i_function,
                  const char * const i_file, u32 i_lineNum, const char * const i_errorMessage, ...);

void m3Abort (const char* message);
void m3NotImplemented (void);
void m3Yield (void);
M3Result m3Malloc (void ** o_ptr, size_t i_size);
void * m3Realloc (void * i_ptr, size_t i_newSize, size_t i_oldSize);
void m3Free_impl (void * o_ptr);
M3Result NormalizeType (u8 * o_type, i8 i_convolutedWasmType);
bool IsIntType (u8 i_wasmType);
bool IsFpType (u8 i_wasmType);
bool Is64BitType (u8 i_m3Type);
u32 SizeOfType (u8 i_m3Type);
M3Result Read_u64 (u64 * o_value, const u8 ** io_bytes, cbytes_t i_end);
M3Result Read_u32 (u32 * o_value, const u8 ** io_bytes, cbytes_t i_end);
M3Result Read_f64 (f64 * o_value, bytes_t * io_bytes, cbytes_t i_end);
M3Result Read_f32 (f32 * o_value, bytes_t * io_bytes, cbytes_t i_end);
M3Result Read_u8 (u8 * o_value, const u8 ** io_bytes, cbytes_t i_end);
M3Result ReadLebUnsigned (u64 * o_value, u32 i_maxNumBits, bytes_t * io_bytes, cbytes_t i_end);
M3Result ReadLebSigned (i64 * o_value, u32 i_maxNumBits, bytes_t * io_bytes, cbytes_t i_end);
M3Result ReadLEB_u32 (u32 * o_value, bytes_t* io_bytes, cbytes_t i_end);
M3Result ReadLEB_u7 (u8 * o_value, bytes_t * io_bytes, cbytes_t i_end);
M3Result ReadLEB_i7 (i8 * o_value, bytes_t * io_bytes, cbytes_t i_end);
M3Result ReadLEB_i32 (i32 * o_value, bytes_t * io_bytes, cbytes_t i_end);
M3Result ReadLEB_i64 (i64 * o_value, bytes_t * io_bytes, cbytes_t i_end);
M3Result Read_utf8 (cstr_t * o_utf8, bytes_t * io_bytes, cbytes_t i_end);
size_t SPrintArg (char * o_string, size_t i_n, m3stack_t i_sp, u8 i_type);
void ReportError (IM3Runtime io_runtime, IM3Module i_module, IM3Function i_function, ccstr_t i_errorMessage, ccstr_t i_file, u32 i_lineNum);
typedef struct M3CodePage
{
    M3CodePageHeader info;
    code_t code [1];
}
M3CodePage;
typedef M3CodePage * IM3CodePage;
IM3CodePage NewCodePage (u32 i_minNumLines);
void FreeCodePages (IM3CodePage i_page);
u32 NumFreeLines (IM3CodePage i_page);
pc_t GetPageStartPC (IM3CodePage i_page);
pc_t GetPagePC (IM3CodePage i_page);
void EmitWord64_impl (IM3CodePage i_page, u64 i_word);
void EmitWord_impl (IM3CodePage i_page, void* i_word);
void PushCodePage (IM3CodePage * i_list, IM3CodePage i_codePage);
IM3CodePage PopCodePage (IM3CodePage * i_list);
typedef m3ret_t ( * IM3Operation) (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);

static inline u32
rotl32(u32 n, unsigned c) {
    const unsigned mask = CHAR_BIT * sizeof(n) - 1;
    c &= mask & 31;
    return (n << c) | (n >> ((-c) & mask));
}
static inline u32
rotr32(u32 n, unsigned c) {
    const unsigned mask = CHAR_BIT * sizeof(n) - 1;
    c &= mask & 31;
    return (n >> c) | (n << ((-c) & mask));
}
static inline u64
rotl64(u64 n, unsigned c) {
    const unsigned mask = CHAR_BIT * sizeof(n) - 1;
    c &= mask & 63;
    return (n << c) | (n >> ((-c) & mask));
}
static inline u64
rotr64(u64 n, unsigned c) {
    const unsigned mask = CHAR_BIT * sizeof(n) - 1;
    c &= mask & 63;
    return (n >> c) | (n << ((-c) & mask));
}
static inline f32
min_f32(f32 a, f32 b) {
    if (__builtin_expect(!!(isnan(a) || isnan(b)), 0)) return NAN;
    if (__builtin_expect(!!(a == 0 && a == b), 0)) return signbit(a) ? a : b;
    return a > b ? b : a;
}
static inline f32
max_f32(f32 a, f32 b) {
    if (__builtin_expect(!!(isnan(a) || isnan(b)), 0)) return NAN;
    if (__builtin_expect(!!(a == 0 && a == b), 0)) return signbit(a) ? b : a;
    return a > b ? a : b;
}
static inline f64
min_f64(f64 a, f64 b) {
    if (__builtin_expect(!!(isnan(a) || isnan(b)), 0)) return NAN;
    if (__builtin_expect(!!(a == 0 && a == b), 0)) return signbit(a) ? a : b;
    return a > b ? b : a;
}
static inline f64
max_f64(f64 a, f64 b) {
    if (__builtin_expect(!!(isnan(a) || isnan(b)), 0)) return NAN;
    if (__builtin_expect(!!(a == 0 && a == b), 0)) return signbit(a) ? b : a;
    return a > b ? a : b;
}

static inline m3ret_t
Call (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    m3Yield ();
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}
 
static inline m3ret_t
op_i32_Equal_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) == (((i32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Equal_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) == (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Equal_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) == (((i64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Equal_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) == (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_NotEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) != (((i32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_NotEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) != (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_NotEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) != (((i64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_NotEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) != (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_LessThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i32) _r0)) < (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_LessThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) < (((i32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_LessThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) < (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_LessThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i64) _r0)) < (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_LessThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) < (((i64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_LessThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) < (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_GreaterThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i32) _r0)) > (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_GreaterThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) > (((i32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_GreaterThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) > (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_GreaterThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i64) _r0)) > (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_GreaterThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) > (((i64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_GreaterThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) > (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_LessThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i32) _r0)) <= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_LessThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) <= (((i32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_LessThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) <= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_LessThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i64) _r0)) <= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_LessThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) <= (((i64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_LessThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) <= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_GreaterThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i32) _r0)) >= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_GreaterThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) >= (((i32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_GreaterThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) >= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_GreaterThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i64) _r0)) >= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_GreaterThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) >= (((i64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_GreaterThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) >= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_LessThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((u32) _r0)) < (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_LessThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) < (((u32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_LessThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) < (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_LessThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((u64) _r0)) < (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_LessThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) < (((u64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_LessThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) < (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_GreaterThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((u32) _r0)) > (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_GreaterThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) > (((u32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_GreaterThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) > (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_GreaterThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((u64) _r0)) > (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_GreaterThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) > (((u64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_GreaterThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) > (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_LessThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((u32) _r0)) <= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_LessThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) <= (((u32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_LessThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) <= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_LessThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((u64) _r0)) <= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_LessThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) <= (((u64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_LessThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) <= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_GreaterThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((u32) _r0)) >= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_GreaterThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) >= (((u32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_GreaterThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) >= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_GreaterThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((u64) _r0)) >= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_GreaterThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) >= (((u64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_GreaterThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) >= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Equal_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) == (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Equal_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) == (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Equal_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) == (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Equal_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) == (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_NotEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) != (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_NotEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) != (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_NotEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) != (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_NotEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) != (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_LessThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((f32) _fp0)) < (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_LessThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) < (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_LessThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) < (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_LessThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((f64) _fp0)) < (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_LessThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) < (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_LessThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) < (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_GreaterThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((f32) _fp0)) > (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_GreaterThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) > (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_GreaterThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) > (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_GreaterThan_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((f64) _fp0)) > (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_GreaterThan_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) > (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_GreaterThan_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) > (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_LessThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((f32) _fp0)) <= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_LessThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) <= (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_LessThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) <= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_LessThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((f64) _fp0)) <= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_LessThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) <= (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_LessThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) <= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_GreaterThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((f32) _fp0)) >= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_GreaterThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) >= (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_GreaterThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) >= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_GreaterThanOrEqual_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((f64) _fp0)) >= (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_GreaterThanOrEqual_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) >= (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_GreaterThanOrEqual_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) >= (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_Add_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) + (((i32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Add_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) + (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Add_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) + (((i64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Add_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) + (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_Multiply_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) * (((i32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Multiply_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) * (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Multiply_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) * (((i64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Multiply_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) * (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_Subtract_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i32) _r0)) - (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Subtract_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) - (((i32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Subtract_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) - (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Subtract_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((((i64) _r0)) - (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Subtract_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) - (((i64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Subtract_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) - (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_ShiftLeft_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((((u32) _r0))) << ((u32)((operand)) % 32));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_ShiftLeft_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand)) << ((u32)((((u32) _r0))) % 32));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_ShiftLeft_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand1)) << ((u32)((operand2)) % 32));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_ShiftLeft_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((((u64) _r0))) << ((u64)((operand)) % 64));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_ShiftLeft_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand)) << ((u64)((((u64) _r0))) % 64));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_ShiftLeft_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand1)) << ((u64)((operand2)) % 64));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_ShiftRight_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((((i32) _r0))) >> ((u32)((operand)) % 32));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_ShiftRight_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand)) >> ((u32)((((i32) _r0))) % 32));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_ShiftRight_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand1)) >> ((u32)((operand2)) % 32));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_ShiftRight_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((((i64) _r0))) >> ((u64)((operand)) % 64));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_ShiftRight_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand)) >> ((u64)((((i64) _r0))) % 64));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_ShiftRight_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand1)) >> ((u64)((operand2)) % 64));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_ShiftRight_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((((u32) _r0))) >> ((u32)((operand)) % 32));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_ShiftRight_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand)) >> ((u32)((((u32) _r0))) % 32));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_ShiftRight_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand1)) >> ((u32)((operand2)) % 32));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_ShiftRight_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((((u64) _r0))) >> ((u64)((operand)) % 64));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_ShiftRight_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand)) >> ((u64)((((u64) _r0))) % 64));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_ShiftRight_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand1)) >> ((u64)((operand2)) % 64));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_And_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) & (((u64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_And_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) & (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Or_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) | (((u64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Or_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) | (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Xor_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) ^ (((u64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Xor_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand1) ^ (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Add_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand) + (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Add_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand1) + (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Add_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand) + (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Add_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand1) + (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Multiply_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand) * (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Multiply_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand1) * (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Multiply_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand) * (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Multiply_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand1) * (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Subtract_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((((f32) _fp0)) - (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Subtract_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand) - (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Subtract_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand1) - (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Subtract_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((((f64) _fp0)) - (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Subtract_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand) - (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Subtract_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand1) - (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Divide_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((((f32) _fp0)) / (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Divide_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand) / (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Divide_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand1) / (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Divide_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((((f64) _fp0)) / (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Divide_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand) / (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Divide_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ((operand1) / (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_Rotl_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotl32((((u32) _r0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Rotl_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotl32((operand), (((u32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Rotl_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotl32((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_Rotr_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotr32((((u32) _r0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Rotr_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotr32((operand), (((u32) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Rotr_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotr32((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Rotl_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotl64((((u64) _r0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Rotl_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotl64((operand), (((u64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Rotl_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotl64((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Rotr_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotr64((((u64) _r0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Rotr_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotr64((operand), (((u64) _r0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Rotr_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = rotr64((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_Divide_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = ((u32) _r0) / operand;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Divide_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(((u32) _r0) == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand / ((u32) _r0);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Divide_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand2 == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand1 / operand2;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_Divide_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = ((i32) _r0) / operand;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Divide_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(((i32) _r0) == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand / ((i32) _r0);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Divide_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand2 == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand1 / operand2;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Divide_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = ((u64) _r0) / operand;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Divide_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(((u64) _r0) == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand / ((u64) _r0);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Divide_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand2 == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand1 / operand2;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_Divide_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = ((i64) _r0) / operand;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Divide_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(((i64) _r0) == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand / ((i64) _r0);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Divide_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand2 == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand1 / operand2;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_Remainder_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = ((u32) _r0) % operand;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Remainder_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(((u32) _r0) == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand % ((u32) _r0);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Remainder_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand2 = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 operand1 = * (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand2 == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand1 % operand2;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_Remainder_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = ((i32) _r0) % operand;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Remainder_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(((i32) _r0) == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand % ((i32) _r0);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Remainder_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand2 == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand1 % operand2;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Remainder_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = ((u64) _r0) % operand;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Remainder_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(((u64) _r0) == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand % ((u64) _r0);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Remainder_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand2 = * (u64 *) (_sp + * ((i32 *) _pc++));
    u64 operand1 = * (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand2 == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand1 % operand2;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_Remainder_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = ((i64) _r0) % operand;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Remainder_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(((i64) _r0) == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand % ((i64) _r0);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Remainder_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(operand2 == 0), 0))
        return m3Err_trapDivisionByZero;
    (_r0) = operand1 % operand2;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Min_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = min_f32((((f32) _fp0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Min_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = min_f32((operand), (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Min_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = min_f32((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Max_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = max_f32((((f32) _fp0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Max_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = max_f32((operand), (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Max_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = max_f32((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Min_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = min_f64((((f64) _fp0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Min_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = min_f64((operand), (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Min_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = min_f64((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Max_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = max_f64((((f64) _fp0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Max_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = max_f64((operand), (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Max_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = max_f64((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_CopySign_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = copysignf((((f32) _fp0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_CopySign_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = copysignf((operand), (((f32) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_CopySign_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = copysignf((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_CopySign_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = copysign((((f64) _fp0)), (operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_CopySign_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = copysign((operand), (((f64) _fp0)));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_CopySign_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = copysign((operand1), (operand2));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Abs_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = fabsf((f32) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Abs_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = fabsf(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Abs_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = fabs((f64) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Abs_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = fabs(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Ceil_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = ceilf((f32) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Ceil_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ceilf(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Ceil_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = ceil((f64) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Ceil_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = ceil(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Floor_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = floorf((f32) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Floor_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = floorf(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Floor_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = floor((f64) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Floor_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = floor(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Trunc_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = truncf((f32) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Trunc_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = truncf(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Trunc_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = trunc((f64) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Trunc_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = trunc(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Sqrt_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = sqrtf((f32) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Sqrt_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = sqrtf(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Sqrt_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = sqrt((f64) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Sqrt_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = sqrt(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Nearest_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = rintf((f32) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Nearest_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = rintf(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Nearest_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = rint((f64) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Nearest_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = rint(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Negate_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = -((f32) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Negate_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 operand = * (f32 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = -(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Negate_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_fp0)) = -((f64) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Negate_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 operand = * (f64 *) (_sp + * ((i32 *) _pc++));
    ((_fp0)) = -(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_EqualToZero_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_r0)) = (((i32) _r0) == 0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_EqualToZero_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) == 0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_EqualToZero_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_r0)) = (((i64) _r0) == 0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_EqualToZero_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 operand = * (i64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) == 0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_Clz_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_r0)) = ((((u32) _r0) == 0) ? 32 : __builtin_clz((u32) _r0));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Clz_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand) == 0) ? 32 : __builtin_clz(operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Clz_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_r0)) = ((((u64) _r0) == 0) ? 64 : __builtin_clzll((u64) _r0));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Clz_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand) == 0) ? 64 : __builtin_clzll(operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_Ctz_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_r0)) = ((((u32) _r0) == 0) ? 32 : __builtin_ctz((u32) _r0));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Ctz_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand) == 0) ? 32 : __builtin_ctz(operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Ctz_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_r0)) = ((((u64) _r0) == 0) ? 64 : __builtin_ctzll((u64) _r0));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Ctz_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = (((operand) == 0) ? 64 : __builtin_ctzll(operand));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_Popcnt_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_r0)) = __builtin_popcount((u32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Popcnt_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = __builtin_popcount(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Popcnt_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_r0)) = __builtin_popcountll((u64) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Popcnt_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u64 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = __builtin_popcountll(operand);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_Wrap_i64_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ((_r0)) = (((i32) _r0) & 0x00000000ffffffff);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Wrap_i64_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 operand = * (i32 *) (_sp + * ((i32 *) _pc++));
    ((_r0)) = ((operand) & 0x00000000ffffffff);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_Trunc_f32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    if (__builtin_expect(!!(isnan((f32) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f32) _fp0 <= -2147483904.0f || (f32) _fp0 >= 2147483648.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (i32)(f32) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Trunc_f32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * stack = (f32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -2147483904.0f || (* stack) >= 2147483648.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (i32)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Trunc_f32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 * dest = (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((f32) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f32) _fp0 <= -2147483904.0f || (f32) _fp0 >= 2147483648.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (i32)(f32) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Trunc_f32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * stack = (f32 *) (_sp + * ((i32 *) _pc++));
    i32 * dest = (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -2147483904.0f || (* stack) >= 2147483648.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (i32)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_Trunc_f32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    if (__builtin_expect(!!(isnan((f32) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f32) _fp0 <= -1.0f || (f32) _fp0 >= 4294967296.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (u32)(f32) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Trunc_f32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * stack = (f32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -1.0f || (* stack) >= 4294967296.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (u32)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Trunc_f32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 * dest = (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((f32) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f32) _fp0 <= -1.0f || (f32) _fp0 >= 4294967296.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (u32)(f32) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Trunc_f32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * stack = (f32 *) (_sp + * ((i32 *) _pc++));
    u32 * dest = (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -1.0f || (* stack) >= 4294967296.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (u32)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_Trunc_f64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    if (__builtin_expect(!!(isnan((f64) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f64) _fp0 <= -2147483649.0 || (f64) _fp0 >= 2147483648.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (i32)(f64) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Trunc_f64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * stack = (f64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -2147483649.0 || (* stack) >= 2147483648.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (i32)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Trunc_f64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 * dest = (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((f64) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f64) _fp0 <= -2147483649.0 || (f64) _fp0 >= 2147483648.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (i32)(f64) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Trunc_f64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * stack = (f64 *) (_sp + * ((i32 *) _pc++));
    i32 * dest = (i32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -2147483649.0 || (* stack) >= 2147483648.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (i32)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u32_Trunc_f64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    if (__builtin_expect(!!(isnan((f64) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f64) _fp0 <= -1.0 || (f64) _fp0 >= 4294967296.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (u32)(f64) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Trunc_f64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * stack = (f64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -1.0 || (* stack) >= 4294967296.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (u32)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Trunc_f64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 * dest = (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((f64) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f64) _fp0 <= -1.0 || (f64) _fp0 >= 4294967296.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (u32)(f64) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u32_Trunc_f64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * stack = (f64 *) (_sp + * ((i32 *) _pc++));
    u32 * dest = (u32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -1.0 || (* stack) >= 4294967296.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (u32)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_Trunc_f32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    if (__builtin_expect(!!(isnan((f32) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f32) _fp0 <= -9223373136366403584.0f || (f32) _fp0 >= 9223372036854775808.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (i64)(f32) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Trunc_f32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * stack = (f32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -9223373136366403584.0f || (* stack) >= 9223372036854775808.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (i64)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Trunc_f32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 * dest = (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((f32) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f32) _fp0 <= -9223373136366403584.0f || (f32) _fp0 >= 9223372036854775808.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (i64)(f32) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Trunc_f32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * stack = (f32 *) (_sp + * ((i32 *) _pc++));
    i64 * dest = (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -9223373136366403584.0f || (* stack) >= 9223372036854775808.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (i64)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Trunc_f32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    if (__builtin_expect(!!(isnan((f32) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f32) _fp0 <= -1.0f || (f32) _fp0 >= 18446744073709551616.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (u64)(f32) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Trunc_f32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * stack = (f32 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -1.0f || (* stack) >= 18446744073709551616.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (u64)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Trunc_f32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 * dest = (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((f32) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f32) _fp0 <= -1.0f || (f32) _fp0 >= 18446744073709551616.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (u64)(f32) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Trunc_f32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * stack = (f32 *) (_sp + * ((i32 *) _pc++));
    u64 * dest = (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -1.0f || (* stack) >= 18446744073709551616.0f), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (u64)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_Trunc_f64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    if (__builtin_expect(!!(isnan((f64) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f64) _fp0 <= -9223372036854777856.0 || (f64) _fp0 >= 9223372036854775808.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (i64)(f64) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Trunc_f64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * stack = (f64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -9223372036854777856.0 || (* stack) >= 9223372036854775808.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (i64)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Trunc_f64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 * dest = (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((f64) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f64) _fp0 <= -9223372036854777856.0 || (f64) _fp0 >= 9223372036854775808.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (i64)(f64) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Trunc_f64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * stack = (f64 *) (_sp + * ((i32 *) _pc++));
    i64 * dest = (i64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -9223372036854777856.0 || (* stack) >= 9223372036854775808.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (i64)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_u64_Trunc_f64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    if (__builtin_expect(!!(isnan((f64) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f64) _fp0 <= -1.0 || (f64) _fp0 >= 18446744073709551616.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (u64)(f64) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Trunc_f64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * stack = (f64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -1.0 || (* stack) >= 18446744073709551616.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (_r0) = (u64)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Trunc_f64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 * dest = (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((f64) _fp0)), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((f64) _fp0 <= -1.0 || (f64) _fp0 >= 18446744073709551616.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (u64)(f64) _fp0;;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_u64_Trunc_f64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * stack = (f64 *) (_sp + * ((i32 *) _pc++));
    u64 * dest = (u64 *) (_sp + * ((i32 *) _pc++));
    if (__builtin_expect(!!(isnan((* stack))), 0)) {
        return m3Err_trapIntegerConversion;
    }
    if (__builtin_expect(!!((* stack) <= -1.0 || (* stack) >= 18446744073709551616.0), 0)) {
        return m3Err_trapIntegerOverflow;
    } (* dest) = (u64)(* stack);;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_Extend_i32_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _r0 = (i64) ((i32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Extend_i32_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 from = * (i32 *) (_sp + * ((i32 *) _pc++));
    _r0 = (i64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_Extend_u32_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _r0 = (i64) ((u32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Extend_u32_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 from = * (u32 *) (_sp + * ((i32 *) _pc++));
    _r0 = (i64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Demote_f64_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f32) ((f64) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Demote_f64_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 from = * (f64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f32) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Promote_f32_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f64) ((f32) _fp0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Promote_f32_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 from = * (f32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Convert_i32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f64) ((i32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_i32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f64 *) (_sp + * ((i32 *) _pc++)) = (f64) ((i32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_i32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 from = * (i32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_i32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 from = * (i32 *) (_sp + * ((i32 *) _pc++));
    * (f64 *) (_sp + * ((i32 *) _pc++)) = (f64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Convert_u32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f64) ((u32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_u32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f64 *) (_sp + * ((i32 *) _pc++)) = (f64) ((u32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_u32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 from = * (u32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_u32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 from = * (u32 *) (_sp + * ((i32 *) _pc++));
    * (f64 *) (_sp + * ((i32 *) _pc++)) = (f64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Convert_i64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f64) ((i64) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_i64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f64 *) (_sp + * ((i32 *) _pc++)) = (f64) ((i64) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_i64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 from = * (i64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_i64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 from = * (i64 *) (_sp + * ((i32 *) _pc++));
    * (f64 *) (_sp + * ((i32 *) _pc++)) = (f64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Convert_u64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f64) ((u64) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_u64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f64 *) (_sp + * ((i32 *) _pc++)) = (f64) ((u64) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_u64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 from = * (u64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Convert_u64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 from = * (u64 *) (_sp + * ((i32 *) _pc++));
    * (f64 *) (_sp + * ((i32 *) _pc++)) = (f64) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Convert_i32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f32) ((i32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_i32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f32 *) (_sp + * ((i32 *) _pc++)) = (f32) ((i32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_i32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 from = * (i32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f32) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_i32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 from = * (i32 *) (_sp + * ((i32 *) _pc++));
    * (f32 *) (_sp + * ((i32 *) _pc++)) = (f32) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Convert_u32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f32) ((u32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_u32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f32 *) (_sp + * ((i32 *) _pc++)) = (f32) ((u32) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_u32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 from = * (u32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f32) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_u32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 from = * (u32 *) (_sp + * ((i32 *) _pc++));
    * (f32 *) (_sp + * ((i32 *) _pc++)) = (f32) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Convert_i64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f32) ((i64) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_i64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f32 *) (_sp + * ((i32 *) _pc++)) = (f32) ((i64) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_i64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 from = * (i64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f32) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_i64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 from = * (i64 *) (_sp + * ((i32 *) _pc++));
    * (f32 *) (_sp + * ((i32 *) _pc++)) = (f32) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Convert_u64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = (f32) ((u64) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_u64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f32 *) (_sp + * ((i32 *) _pc++)) = (f32) ((u64) _r0);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_u64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 from = * (u64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (f32) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Convert_u64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 from = * (u64 *) (_sp + * ((i32 *) _pc++));
    * (f32 *) (_sp + * ((i32 *) _pc++)) = (f32) (from);
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_Reinterpret_f32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        f32 c;
        i32 t;
    } u;
    u.c = (f32) _fp0;
    _r0 = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Reinterpret_f32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        f32 c;
        i32 t;
    } u;
    u.c = * (f32 *) (_sp + * ((i32 *) _pc++));
    _r0 = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Reinterpret_f32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        f32 c;
        i32 t;
    } u;
    u.c = (f32) _fp0;
    * (i32 *) (_sp + * ((i32 *) _pc++)) = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i32_Reinterpret_f32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        f32 c;
        i32 t;
    } u;
    u.c = * (f32 *) (_sp + * ((i32 *) _pc++));
    * (i32 *) (_sp + * ((i32 *) _pc++)) = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_Reinterpret_f64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        f64 c;
        i64 t;
    } u;
    u.c = (f64) _fp0;
    _r0 = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Reinterpret_f64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        f64 c;
        i64 t;
    } u;
    u.c = * (f64 *) (_sp + * ((i32 *) _pc++));
    _r0 = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Reinterpret_f64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        f64 c;
        i64 t;
    } u;
    u.c = (f64) _fp0;
    * (i64 *) (_sp + * ((i32 *) _pc++)) = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_i64_Reinterpret_f64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        f64 c;
        i64 t;
    } u;
    u.c = * (f64 *) (_sp + * ((i32 *) _pc++));
    * (i64 *) (_sp + * ((i32 *) _pc++)) = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f32_Reinterpret_i32_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        i32 c;
        f32 t;
    } u;
    u.c = (i32) _r0;
    _fp0 = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Reinterpret_i32_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        i32 c;
        f32 t;
    } u;
    u.c = * (i32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Reinterpret_i32_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        i32 c;
        f32 t;
    } u;
    u.c = (i32) _r0;
    * (f32 *) (_sp + * ((i32 *) _pc++)) = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f32_Reinterpret_i32_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        i32 c;
        f32 t;
    } u;
    u.c = * (i32 *) (_sp + * ((i32 *) _pc++));
    * (f32 *) (_sp + * ((i32 *) _pc++)) = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_f64_Reinterpret_i64_r_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        i64 c;
        f64 t;
    } u;
    u.c = (i64) _r0;
    _fp0 = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Reinterpret_i64_r_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        i64 c;
        f64 t;
    } u;
    u.c = * (i64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Reinterpret_i64_s_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        i64 c;
        f64 t;
    } u;
    u.c = (i64) _r0;
    * (f64 *) (_sp + * ((i32 *) _pc++)) = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_f64_Reinterpret_i64_s_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    union {
        i64 c;
        f64 t;
    } u;
    u.c = * (i64 *) (_sp + * ((i32 *) _pc++));
    * (f64 *) (_sp + * ((i32 *) _pc++)) = u.t;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}
m3ret_t op_Loop (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_If_r (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_If_s (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);

static inline m3ret_t
op_Select_i32_rss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    _r0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_i32_srs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand2 = (i32) _r0;
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    _r0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_i32_ssr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = (i32) _r0;
    _r0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_i32_sss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand2 = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 operand1 = * (i32 *) (_sp + * ((i32 *) _pc++));
    _r0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_Select_i64_rss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    _r0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_i64_srs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = * (i32 *) (_sp + * ((i32 *) _pc++));
    i64 operand2 = (i64) _r0;
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    _r0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_i64_ssr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = * (i32 *) (_sp + * ((i32 *) _pc++));
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = (i64) _r0;
    _r0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_i64_sss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = * (i32 *) (_sp + * ((i32 *) _pc++));
    i64 operand2 = * (i64 *) (_sp + * ((i32 *) _pc++));
    i64 operand1 = * (i64 *) (_sp + * ((i32 *) _pc++));
    _r0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_Select_f32_rss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_f32_rrs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    f32 operand2 = (f32) _fp0;
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_f32_rsr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = (f32) _fp0;
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_Select_f32_sss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) * (i32 *) (_sp + * ((i32 *) _pc++));
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_f32_srs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) * (i32 *) (_sp + * ((i32 *) _pc++));
    f32 operand2 = (f32) _fp0;
    f32 operand1 = * (f32 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_f32_ssr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) * (i32 *) (_sp + * ((i32 *) _pc++));
    f32 operand2 = * (f32 *) (_sp + * ((i32 *) _pc++));
    f32 operand1 = (f32) _fp0;
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_Select_f64_rss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_f64_rrs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    f64 operand2 = (f64) _fp0;
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_f64_rsr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = (f64) _fp0;
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_Select_f64_sss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) * (i32 *) (_sp + * ((i32 *) _pc++));
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_f64_srs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) * (i32 *) (_sp + * ((i32 *) _pc++));
    f64 operand2 = (f64) _fp0;
    f64 operand1 = * (f64 *) (_sp + * ((i32 *) _pc++));
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
} 

static inline m3ret_t
op_Select_f64_ssr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) * (i32 *) (_sp + * ((i32 *) _pc++));
    f64 operand2 = * (f64 *) (_sp + * ((i32 *) _pc++));
    f64 operand1 = (f64) _fp0;
    _fp0 = (condition) ? operand1 : operand2;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_Return (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ;
    return NULL;
}

static inline m3ret_t
op_Branch (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    return ((IM3Operation)(* (pc_t)* _pc))( (pc_t)* _pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_Bridge (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    return ((IM3Operation)(* (pc_t)* _pc))( (pc_t)* _pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_BranchIf_r (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    pc_t branch = * ((pc_t *) _pc++);
    if (condition)
    {
        return ((IM3Operation)(* (pc_t)branch))( (pc_t)branch + 1, _sp, _mem, _r0, _fp0);
    }
    else return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_BranchIf_s (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = * (i32 *) (_sp + * ((i32 *) _pc++));
    pc_t branch = * ((pc_t *) _pc++);
    if (condition)
    {
        return ((IM3Operation)(* (pc_t)branch))( (pc_t)branch + 1, _sp, _mem, _r0, _fp0);
    }
    else return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_BranchIf_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    i32 value = * (i32 *) (_sp + * ((i32 *) _pc++));
    pc_t branch = * ((pc_t *) _pc++);
    if (condition) {
        _r0 = value;
        return ((IM3Operation)(* (pc_t)branch))( (pc_t)branch + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_BranchIf_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    pc_t branch = * ((pc_t *) _pc++);
    if (condition) {
        _r0 = value;
        return ((IM3Operation)(* (pc_t)branch))( (pc_t)branch + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i32_BranchIf_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 value = * (i32 *) (_sp + * ((i32 *) _pc++));
    pc_t branch = * ((pc_t *) _pc++);
    if (condition) {
        _r0 = value;
        return ((IM3Operation)(* (pc_t)branch))( (pc_t)branch + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_i64_BranchIf_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) * (i32 *) (_sp + * ((i32 *) _pc++));
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    pc_t branch = * ((pc_t *) _pc++);
    if (condition) {
        _r0 = value;
        return ((IM3Operation)(* (pc_t)branch))( (pc_t)branch + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}
m3ret_t op_BranchTable (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);

static inline m3ret_t
op_ContinueLoop (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    void * loopId = * ((void * *) _pc++);
    return loopId;
}

static inline m3ret_t
op_ContinueLoopIf (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    void * loopId = * ((void * *) _pc++);
    if (condition)
    {
        return loopId;
    }
    else return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}
m3ret_t op_Compile (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_Call (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_CallIndirect (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_CallRawFunction (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_Entry (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_MemCurrent (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_MemGrow (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);

static inline m3ret_t
op_Const (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 constant = * ((u64 *) _pc++);
    * (u64 *) (_sp + * ((i32 *) _pc++)) = constant;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_Unreachable (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    return m3Err_trapUnreachable;
}

static inline m3ret_t
op_End (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    ;
    return 0;
}
m3ret_t op_GetGlobal (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetGlobal_i32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetGlobal_i64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);

static inline m3ret_t
op_SetGlobal_s32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 * global = * ((u32 * *) _pc++);
    * global = * (u32 *) (_sp + * ((i32 *) _pc++));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_SetGlobal_s64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 * global = * ((u64 * *) _pc++);
    * global = * (u64 *) (_sp + * ((i32 *) _pc++));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_SetGlobal_f32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * global = * ((f32 * *) _pc++);
    * global = _fp0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

static inline m3ret_t
op_SetGlobal_f64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * global = * ((f64 * *) _pc++);
    * global = _fp0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}
m3ret_t op_CopySlot_32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_PreserveCopySlot_32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_CopySlot_64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_PreserveCopySlot_64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetRegister_i32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetSlot_i32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_PreserveSetSlot_i32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetRegister_i64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetSlot_i64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_PreserveSetSlot_i64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetRegister_f32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetSlot_f32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_PreserveSetSlot_f32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetRegister_f64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_SetSlot_f64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);
m3ret_t op_PreserveSetSlot_f64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0);

static inline m3ret_t
op_f32_Load_f32_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f32) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f32 value;
        memcpy(&value, src8, sizeof(value));
        _fp0 = (f32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_f32_Load_f32_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f32) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f32 value;
        memcpy(&value, src8, sizeof(value));
        _fp0 = (f32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_f64_Load_f64_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f64) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f64 value;
        memcpy(&value, src8, sizeof(value));
        _fp0 = (f64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_f64_Load_f64_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f64) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f64 value;
        memcpy(&value, src8, sizeof(value));
        _fp0 = (f64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i32_Load_i8_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i8) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i8 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Load_i8_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i8) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i8 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i32_Load_u8_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Load_u8_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i32_Load_i16_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Load_i16_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i32_Load_u16_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u16) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u16 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Load_u16_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u16) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u16 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i32_Load_i32_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Load_i32_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i32)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Load_i8_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i8) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i8 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Load_i8_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i8) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i8 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Load_u8_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Load_u8_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Load_i16_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Load_i16_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Load_u16_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u16) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u16 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Load_u16_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u16) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u16 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Load_i32_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Load_i32_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Load_u32_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u32) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u32 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Load_u32_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u32) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u32 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Load_i64_r(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 offset = * ((u32 *) _pc++);
    u64 operand = (u32) _r0;
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i64) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i64 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Load_i64_s(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i64) <= _mem->length), 1)) {
        u8* src8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i64 value;
        memcpy(&value, src8, sizeof(value));
        _r0 = (i64)value;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_f32_Store_f32_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f32 val = (f32) _fp0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_f32_Store_f32_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 value = * (f32 *) (_sp + * ((i32 *) _pc++));
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f32 val = (f32) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_f32_Store_f32_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 value = * (f32 *) (_sp + * ((i32 *) _pc++));
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f32 val = (f32) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_f32_Store_f32_rr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f32 val = (f32) _fp0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_f64_Store_f64_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f64) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f64 val = (f64) _fp0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_f64_Store_f64_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 value = * (f64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f64) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f64 val = (f64) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_f64_Store_f64_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 value = * (f64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f64) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f64 val = (f64) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_f64_Store_f64_rr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (f64) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        f64 val = (f64) _fp0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i32_Store_u8_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 val = (u8) _r0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Store_u8_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 value = * (i32 *) (_sp + * ((i32 *) _pc++));
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 val = (u8) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Store_u8_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 value = * (i32 *) (_sp + * ((i32 *) _pc++));
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 val = (u8) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i32_Store_i16_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 val = (i16) _r0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Store_i16_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 value = * (i32 *) (_sp + * ((i32 *) _pc++));
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 val = (i16) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Store_i16_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 value = * (i32 *) (_sp + * ((i32 *) _pc++));
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 val = (i16) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i32_Store_i32_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 val = (i32) _r0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Store_i32_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 value = * (i32 *) (_sp + * ((i32 *) _pc++));
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 val = (i32) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i32_Store_i32_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 value = * (i32 *) (_sp + * ((i32 *) _pc++));
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 val = (i32) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Store_u8_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 val = (u8) _r0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Store_u8_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 val = (u8) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Store_u8_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (u8) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        u8 val = (u8) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Store_i16_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 val = (i16) _r0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Store_i16_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 val = (i16) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Store_i16_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i16) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i16 val = (i16) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Store_i32_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 val = (i32) _r0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Store_i32_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 val = (i32) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Store_i32_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i32) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i32 val = (i32) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

static inline m3ret_t
op_i64_Store_i64_rs(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i64) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i64 val = (i64) _r0;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Store_i64_sr(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = (u32) _r0;
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i64) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i64 val = (i64) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
} 

static inline m3ret_t
op_i64_Store_i64_ss(pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 value = * (i64 *) (_sp + * ((i32 *) _pc++));
    u64 operand = * (u32 *) (_sp + * ((i32 *) _pc++));
    u32 offset = * ((u32 *) _pc++);
    operand += offset;
    if (__builtin_expect(!!(operand + sizeof (i64) <= _mem->length), 1)) {
        u8* mem8 = (u8*)((M3MemoryHeader*)(_mem)+1) + operand;
        i64 val = (i64) value;
        memcpy(mem8, &val, sizeof(val));
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        return m3Err_trapOutOfBoundsMemoryAccess;
}

enum
{
    c_waOp_block = 0x02,
    c_waOp_loop = 0x03,
    c_waOp_if = 0x04,
    c_waOp_else = 0x05,
    c_waOp_end = 0x0b,
    c_waOp_branch = 0x0c,
    c_waOp_branchTable = 0x0e,
    c_waOp_branchIf = 0x0d,
    c_waOp_call = 0x10,
    c_waOp_getLocal = 0x20,
    c_waOp_setLocal = 0x21,
    c_waOp_teeLocal = 0x22,
};
typedef struct M3BranchPatch
{
    struct M3BranchPatch * next;
    pc_t * location;
}
M3BranchPatch;
typedef M3BranchPatch * IM3BranchPatch;
typedef struct M3CompilationScope
{
    struct M3CompilationScope * outer;
    pc_t pc;
    IM3BranchPatch patches;
    i32 depth;
    i16 initStackIndex;
    u8 type;
    u8 opcode;
    bool isPolymorphic;
}
M3CompilationScope;
typedef M3CompilationScope * IM3CompilationScope;
static const u16 c_m3RegisterUnallocated = 0;
typedef struct
{
    IM3Runtime runtime;
    IM3Module module;
    bytes_t wasm;
    bytes_t wasmEnd;
    M3CompilationScope block;
    IM3Function function;
    IM3CodePage page;
    IM3BranchPatch releasedPatches;
    u32 numEmits;
    u32 numOpcodes;
    u16 firstSlotIndex;
    u16 stackIndex;
    u16 firstConstSlotIndex;
    u16 constSlotIndex;
    u64 constants [60];
    u16 wasmStack [2000];
    u8 typeStack [2000];
    u8 m3Slots [2000];
    u16 numAllocatedExecSlots;
    u16 regStackIndexPlusOne [2];
    u8 previousOpcode;
}
M3Compilation;
typedef M3Compilation * IM3Compilation;
typedef M3Result (* M3Compiler) (IM3Compilation, u8);
typedef struct M3OpInfo
{
    i8 stackOffset;
    u8 type;
    IM3Operation operations [4];
    M3Compiler compiler;
}
M3OpInfo;
typedef const M3OpInfo * IM3OpInfo;
extern const M3OpInfo c_operations [];
bool IsRegisterAllocated (IM3Compilation o, u32 i_register);
bool IsRegisterLocation (i16 i_location);
bool IsFpRegisterLocation (i16 i_location);
bool IsIntRegisterLocation (i16 i_location);
bool IsStackPolymorphic (IM3Compilation o);
M3Result EmitOp (IM3Compilation o, IM3Operation i_operation);
void EmitConstant (IM3Compilation o, const u64 immediate);
M3Result Push (IM3Compilation o, u8 i_waType, i16 i_location);
void EmitPointer (IM3Compilation o, const void * const i_immediate);
M3Result CompileBlock (IM3Compilation io, u8 i_blockType, u8 i_blockOpcode);
M3Result Compile_BlockStatements (IM3Compilation io);
M3Result Compile_Function (IM3Function io_function);
bool PeekNextOpcode (IM3Compilation o, u8 i_opcode);
u16 GetMaxExecSlot (IM3Compilation o);
typedef struct M3FuncType
{
    u32 numArgs;
    u8 argTypes [31];
    u8 returnType;
}
M3FuncType;
typedef M3FuncType * IM3FuncType;
void PrintFuncTypeSignature (IM3FuncType i_funcType);
typedef struct M3Function
{
    struct M3Module * module;
    M3ImportInfo import;
    bytes_t wasm;
    bytes_t wasmEnd;
    cstr_t name;
    IM3FuncType funcType;
    IM3Operation callOp;
    pc_t compiled;
    u32 hits;
    u16 maxStackSlots;
    u16 numLocals;
    u16 numConstants;
    void * constants;
}
M3Function;
typedef M3Function * IM3Function;
cstr_t GetFunctionImportModuleName (IM3Function i_function);
cstr_t GetFunctionName (IM3Function i_function);
u32 GetFunctionNumArgs (IM3Function i_function);
u32 GetFunctionNumReturns (IM3Function i_function);
u8 GetFunctionReturnType (IM3Function i_function);
u32 GetFunctionNumArgsAndLocals (IM3Function i_function);
cstr_t SPrintFunctionArgList (IM3Function i_function, m3stack_t i_sp);
typedef struct M3MemoryInfo
{
    u32 initPages;
    u32 maxPages;
}
M3MemoryInfo;
typedef struct M3Memory
{
    M3MemoryHeader * mallocated;
    u32 numPages;
    u32 maxPages;
}
M3Memory;
typedef M3Memory * IM3Memory;
typedef struct M3DataSegment
{
    const u8 * initExpr;
    const u8 * data;
    u32 initExprSize;
    u32 memoryRegion;
    u32 size;
}
M3DataSegment;
void FreeImportInfo (M3ImportInfo * i_info);
typedef struct M3Global
{
    M3ImportInfo import;
    union
    {
        i64 intValue;
        f64 f64Value;
        f32 f32Value;
    };
    bytes_t initExpr;
    u32 initExprSize;
    u8 type;
    bool imported;
    bool isMutable;
}
M3Global;
typedef M3Global * IM3Global;
typedef struct M3Module
{
    struct M3Runtime * runtime;
    cstr_t name;
    u32 numFuncTypes;
    M3FuncType * funcTypes;
    u32 numImports;
    IM3Function * imports;
    u32 numFunctions;
    M3Function * functions;
    i32 startFunction;
    u32 numDataSegments;
    M3DataSegment * dataSegments;
    u32 importedGlobals;
    u32 numGlobals;
    M3Global * globals;
    u32 numElementSegments;
    bytes_t elementSection;
    bytes_t elementSectionEnd;
    IM3Function * table0;
    u32 table0Size;
    M3MemoryInfo memoryInfo;
    bool memoryImported;
    struct M3Module * next;
}
M3Module;
typedef M3Module * IM3Module;
M3Result Module_AddGlobal (IM3Module io_module, IM3Global * o_global, u8 i_type, bool i_mutable, bool i_isImported);
M3Result Module_AddFunction (IM3Module io_module, u32 i_typeIndex, IM3ImportInfo i_importInfo );
IM3Function Module_GetFunction (IM3Module i_module, u32 i_functionIndex);
typedef struct M3Environment
{
    u32 dummy;
}
M3Environment;
typedef M3Environment * IM3Environment;
typedef struct M3Runtime
{
    M3Compilation compilation;
    IM3Environment environment;
    M3CodePage * pagesOpen;
    M3CodePage * pagesFull;
    u32 numCodePages;
    u32 numActiveCodePages;
    IM3Module modules;
    void * stack;
    u32 stackSize;
    u32 numStackSlots;
    u32 argc;
    ccstr_t * argv;
    M3Result runtimeError;
    M3Memory memory;
    u32 memoryLimit;
    M3ErrorInfo error;
    char error_message[256];
    i32 exit_code;
}
M3Runtime;
typedef M3Runtime * IM3Runtime;
void InitRuntime (IM3Runtime io_runtime, u32 i_stackSizeInBytes);
void ReleaseRuntime (IM3Runtime io_runtime);
M3Result ResizeMemory (IM3Runtime io_runtime, u32 i_numPages);
typedef void * (* ModuleVisitor) (IM3Module i_module, void * i_info);
void * ForEachModule (IM3Runtime i_runtime, ModuleVisitor i_visitor, void * i_info);
void * v_FindFunction (IM3Module i_module, const char * const i_name);
IM3CodePage AcquireCodePage (IM3Runtime io_runtime);
IM3CodePage AcquireCodePageWithCapacity (IM3Runtime io_runtime, u32 i_slotCount);
void ReleaseCodePage (IM3Runtime io_runtime, IM3CodePage i_codePage);
M3Result m3Error (M3Result i_result, IM3Runtime i_runtime, IM3Module i_module, IM3Function i_function, const char * const i_file, u32 i_lineNum, const char * const i_errorMessage, ...);
M3Result BridgeToNewPageIfNecessary (IM3Compilation o);
M3Result EnsureCodePageNumLines (IM3Compilation o, u32 i_numLines);
M3Result EmitOp (IM3Compilation o, IM3Operation i_operation);
void EmitConstant (IM3Compilation o, const u64 i_immediate);
void EmitConstant64 (IM3Compilation o, const u64 i_const);
void EmitSlotOffset (IM3Compilation o, const i32 i_offset);
void EmitPointer (IM3Compilation o, const void * const i_pointer);
void * ReservePointer (IM3Compilation o);
pc_t GetPC (IM3Compilation o);
void dump_type_stack (IM3Compilation o);
void log_opcode (IM3Compilation o, u8 i_opcode);
const char * get_indention_string (IM3Compilation o);
void emit_stack_dump (IM3Compilation o);
void log_emit (IM3Compilation o, IM3Operation i_operation);

static const IM3Operation c_setSetOps [] = {
    NULL,
    op_SetSlot_i32,
    op_SetSlot_i64,
    op_SetSlot_f32,
    op_SetSlot_f64
};

void ReleaseCompilationCodePage (IM3Compilation o)
{
    ReleaseCodePage (o->runtime, o->page);
}

bool IsStackPolymorphic (IM3Compilation o)
{
    return o->block.isPolymorphic;
}

bool IsRegisterLocation (i16 i_location)
{
    return (i_location >= 2000 + 1);
}

bool IsFpRegisterLocation (i16 i_location)
{
    return (i_location == 2000 + 2);
}

bool IsIntRegisterLocation (i16 i_location)
{
    return (i_location == 2000 + 1);
}

i16 GetStackTopIndex (IM3Compilation o)
{
    return o->stackIndex - 1;
}

u8 GetStackTopTypeAtOffset (IM3Compilation o, u16 i_offset)
{
    u8 type = c_m3Type_none;
    ++i_offset;
    if (o->stackIndex >= i_offset)
        type = o->typeStack [o->stackIndex - i_offset];
    return type;
}

u8 GetStackTopType (IM3Compilation o)
{
    return GetStackTopTypeAtOffset (o, 0);
}

u8 GetStackBottomType (IM3Compilation o, u16 i_offset)
{
    u8 type = c_m3Type_none;
    if (i_offset < o->stackIndex)
        type = o->typeStack [i_offset];
    return type;
}

u8 GetBlockType (IM3Compilation o)
{
    return o->block.type;
}

bool BlockHasType (IM3Compilation o)
{
    return GetBlockType (o) != c_m3Type_none;
}

i16 GetNumBlockValues (IM3Compilation o)
{
    return o->stackIndex - o->block.initStackIndex;
}

bool IsStackTopInRegister (IM3Compilation o)
{
    i16 i = GetStackTopIndex (o);
    if (i >= 0) {
        return (o->wasmStack [i] >= 2000 + 1);
    }
    else
        return false;
}

bool IsStackTopInSlot (IM3Compilation o)
{
    return ! IsStackTopInRegister (o);
}

static const u16 c_slotUnused = 0xffff;

u16 GetStackTopSlotIndex (IM3Compilation o)
{
    i16 i = GetStackTopIndex (o);
    u16 slot = c_slotUnused;
    if (i >= 0)
        slot = o->wasmStack [i];
    return slot;
}

bool IsValidSlot (u16 i_slot)
{
    return (i_slot < 2000);
}

bool IsStackTopMinus1InRegister (IM3Compilation o)
{
    i16 i = GetStackTopIndex (o);
    if (i > 0) {
        return (o->wasmStack [i - 1] >= 2000 + 1);
    }
    else
        return false;
}

void MarkSlotAllocated (IM3Compilation o, u16 i_slot)
{
    o->m3Slots [i_slot] = 1;
    o->numAllocatedExecSlots++;
}

bool AllocateSlot (IM3Compilation o, u16 * o_execSlot)
{
    bool found = false;
    i16 i = o->firstSlotIndex;

    while (i < 2000) {
        if (o->m3Slots [i] == 0) {
            MarkSlotAllocated (o, i);
            * o_execSlot = i;
            found = true;
            break;
        }
        ++i;
    }
    return found;
}

M3Result IncrementSlotUsageCount (IM3Compilation o, u16 i_slot)
{
    M3Result result = m3Err_none;
    if (o->m3Slots [i_slot] < 0xFF)
    {
        o->m3Slots [i_slot]++;
    }
    else
        result = "slot usage count overflow";
    return result;
}

void DeallocateSlot (IM3Compilation o, i16 i_slotIndex)
{
    if (-- o->m3Slots [i_slotIndex] == 0)
         o->numAllocatedExecSlots--;
}

bool IsRegisterAllocated (IM3Compilation o, u32 i_register)
{
    return (o->regStackIndexPlusOne [i_register] != c_m3RegisterUnallocated);
}

bool IsRegisterTypeAllocated (IM3Compilation o, u8 i_type)
{
    return IsRegisterAllocated (o, IsFpType (i_type));
}

void AllocateRegister (IM3Compilation o, u32 i_register, u16 i_stackIndex)
{
    o->regStackIndexPlusOne [i_register] = i_stackIndex + 1;
}

void DeallocateRegister (IM3Compilation o, u32 i_register)
{
    o->regStackIndexPlusOne [i_register] = c_m3RegisterUnallocated;
}

u16 GetRegisterStackIndex (IM3Compilation o, u32 i_register)
{
    return o->regStackIndexPlusOne [i_register] - 1;
}

u16 GetMaxExecSlot (IM3Compilation o)
{
    u16 i = o->firstSlotIndex;
    u32 allocated = o->numAllocatedExecSlots;

    while (i < 2000) {
        if (allocated == 0)
            break;
        if (o->m3Slots [i])
            --allocated;
        ++i;
    }
    return i;
}

M3Result PreserveRegisterIfOccupied (IM3Compilation o, u8 i_registerType)
{
    M3Result result = m3Err_none;
    u32 regSelect = IsFpType (i_registerType);

    if (IsRegisterAllocated (o, regSelect)) {
        u16 stackIndex = GetRegisterStackIndex (o, regSelect);
        DeallocateRegister (o, regSelect);
        u16 slot;
        if (AllocateSlot (o, & slot)) {
            o->wasmStack [stackIndex] = slot;
            u8 type = o->typeStack [stackIndex];
            result = EmitOp (o, c_setSetOps [type]);
            if (result) { goto _catch; }
            EmitSlotOffset (o, slot);
        }
        else {
            result = m3Err_functionStackOverflow;
            goto _catch;
        }
    }
_catch:
    return result;
}

M3Result PreserveRegisters (IM3Compilation o)
{
    M3Result result;
    result = PreserveRegisterIfOccupied (o, c_m3Type_f64);
    if (result) { goto _catch; }
    result = PreserveRegisterIfOccupied (o, c_m3Type_i64);
    if (result) { goto _catch; }
_catch:
    return result;
}

M3Result PreserveNonTopRegisters (IM3Compilation o)
{
    M3Result result = m3Err_none;
    i16 stackTop = GetStackTopIndex (o);

    if (stackTop >= 0) {
        if (IsRegisterAllocated (o, 0)) {
            if (GetRegisterStackIndex (o, 0) != stackTop) {
                result = PreserveRegisterIfOccupied (o, c_m3Type_i64);
                if (result) { goto _catch; }
            }
        }

        if (IsRegisterAllocated (o, 1)) {
            if (GetRegisterStackIndex (o, 1) != stackTop) {
                result = PreserveRegisterIfOccupied (o, c_m3Type_f64);
                if (result) { goto _catch; }
            }
        }
    }
    _catch:
    return result;
}

M3Result Push (IM3Compilation o, u8 i_m3Type, i16 i_location)
{
    M3Result result = m3Err_none;
    u16 stackIndex = o->stackIndex++;

    if (stackIndex < 2000) {
        if (o->function) {
            if (stackIndex > o->function->maxStackSlots)
                o->function->maxStackSlots = stackIndex;
        }
        o->wasmStack [stackIndex] = i_location;
        o->typeStack [stackIndex] = i_m3Type;
        if (IsRegisterLocation (i_location)) {
            u32 regSelect = IsFpRegisterLocation (i_location);
            AllocateRegister (o, regSelect, stackIndex);
        }
    }
    else
        result = m3Err_functionStackOverflow;
    return result;
}

M3Result PushRegister (IM3Compilation o, u8 i_m3Type)
{
    i16 location = IsFpType (i_m3Type) ? 2000 + 2 : 2000 + 1;
    return Push (o, i_m3Type, location);
}

M3Result Pop (IM3Compilation o)
{
    M3Result result = m3Err_none;
    if (o->stackIndex > o->block.initStackIndex) {
        o->stackIndex--;
        i16 location = o->wasmStack [o->stackIndex];
        if (IsRegisterLocation (location)) {
            u32 regSelect = IsFpRegisterLocation (location);
            DeallocateRegister (o, regSelect);
        }
        else if (location >= o->firstSlotIndex) {
            DeallocateSlot (o, location);
        }
    }
    else if (! IsStackPolymorphic (o))
        result = m3Err_functionStackUnderrun;
    return result;
}

M3Result UnwindBlockStack (IM3Compilation o)
{
    M3Result result = m3Err_none;
    i16 initStackIndex = o->block.initStackIndex;
    u32 popCount = 0;

    while (o->stackIndex > initStackIndex) {
        result = Pop (o);
        if (result) { goto _catch; }
        ++popCount;
    }
    if (popCount) {}

    _catch:
    return result;
}

M3Result _PushAllocatedSlotAndEmit (IM3Compilation o, u8 i_m3Type, bool i_doEmit)
{
    M3Result result = m3Err_none;
    u16 slot;

    if (AllocateSlot (o, & slot)) {
        result = Push (o, i_m3Type, slot);
        if (result) { goto _catch; }
        if (i_doEmit)
            EmitSlotOffset (o, slot);
    }
    else
        result = m3Err_functionStackOverflow;
    _catch:
    return result;
}

M3Result PushAllocatedSlotAndEmit (IM3Compilation o, u8 i_m3Type)
{
    return _PushAllocatedSlotAndEmit (o, i_m3Type, true);
}

M3Result PushAllocatedSlot (IM3Compilation o, u8 i_m3Type)
{
    return _PushAllocatedSlotAndEmit (o, i_m3Type, false);
}

M3Result PushConst (IM3Compilation o, u64 i_word, u8 i_m3Type)
{
    M3Result result = m3Err_none;
    i16 location = -1;
    u32 numConstants = o->constSlotIndex - o->firstConstSlotIndex;

    for (u32 i = 0; i < numConstants; ++i) {
        if (o->constants [i] == i_word) {
            location = o->firstConstSlotIndex + i;
            result = Push (o, i_m3Type, location);
            if (result) { goto _catch; }
            break;
        }
    }

    if (location < 0) {
        if (o->constSlotIndex < o->firstSlotIndex) {
            o->constants [numConstants] = i_word;
            location = o->constSlotIndex++;
            result = Push (o, i_m3Type, location);
            if (result) { goto _catch; }
        }
        else {
            result = EmitOp (o, op_Const);
            if (result) { goto _catch; }
            EmitConstant64 (o, i_word);
            result = PushAllocatedSlotAndEmit (o, i_m3Type);
            if (result) { goto _catch; }
        }
    }
    _catch:
    return result;
}

M3Result EmitTopSlotAndPop (IM3Compilation o)
{
    if (IsStackTopInSlot (o))
        EmitSlotOffset (o, GetStackTopSlotIndex (o));
    return Pop (o);
}

M3Result AddTrapRecord (IM3Compilation o)
{
    M3Result result = m3Err_none;
    if (o->function) {}
    return result;
}

M3Result AcquirePatch (IM3Compilation o, IM3BranchPatch * o_patch)
{
    M3Result result = m3Err_none;
    IM3BranchPatch patch = o->releasedPatches;
    if (patch) {
        o->releasedPatches = patch->next;
        patch->next = NULL;
    }
    else {
        result = m3Malloc ((void **) & patch, sizeof (M3BranchPatch) * (1));
        if (result) { goto _catch; }
    }
    * o_patch = patch;
    _catch:
    return result;
}

bool PatchBranches (IM3Compilation o)
{
    bool didPatch = false;
    M3CompilationScope * block = & o->block;
    pc_t pc = GetPC (o);
    IM3BranchPatch patches = block->patches;
    IM3BranchPatch endPatch = patches;
    while (patches) {
        * (patches->location) = pc;
        endPatch = patches;
        patches = patches->next;
    }
    if (block->patches) {
        endPatch->next = o->releasedPatches;
        o->releasedPatches = block->patches;
        block->patches = NULL;
        didPatch = true;
    }
    return didPatch;
}

M3Result CopyTopSlot (IM3Compilation o, u16 i_destSlot)
{
    M3Result result = m3Err_none;
    IM3Operation op;
    u8 type = GetStackTopType (o);
    if (IsStackTopInRegister (o)) {
        op = c_setSetOps [type];
    }
    else
        op = Is64BitType (type) ? op_CopySlot_64 : op_CopySlot_32;
    result = EmitOp (o, op);
    if (result) { goto _catch; }
    EmitSlotOffset (o, i_destSlot);
    if (IsStackTopInSlot (o))
        EmitSlotOffset (o, GetStackTopSlotIndex (o));
    _catch:
    return result;
}

M3Result PreservedCopyTopSlot (IM3Compilation o, u16 i_destSlot, u16 i_preserveSlot)
{
    M3Result result = m3Err_none;
    IM3Operation op;
    u8 type = GetStackTopType (o);
    if (IsStackTopInRegister (o)) {
        const IM3Operation c_preserveSetSlot [] = {
            NULL,
            op_PreserveSetSlot_i32,
            op_PreserveSetSlot_i64,
            op_PreserveSetSlot_f32,
            op_PreserveSetSlot_f64
        };
        op = c_preserveSetSlot [type];
    }
    else
        op = Is64BitType (type) ? op_PreserveCopySlot_64 : op_PreserveCopySlot_32;
    result = EmitOp (o, op);
    if (result) { goto _catch; }
    EmitSlotOffset (o, i_destSlot);
    if (IsStackTopInSlot (o))
        EmitSlotOffset (o, GetStackTopSlotIndex (o));
    EmitSlotOffset (o, i_preserveSlot);
    _catch:
    return result;
}

M3Result MoveStackTopToRegister (IM3Compilation o)
{
    M3Result result = m3Err_none;
    if (IsStackTopInSlot (o)) {
        u8 type = GetStackTopType (o);
        static const IM3Operation setRegisterOps [] = {
            NULL,
            op_SetRegister_i32,
            op_SetRegister_i64,
            op_SetRegister_f32,
            op_SetRegister_f64
        };
        IM3Operation op = setRegisterOps [type];
        result = EmitOp (o, op);
        if (result) { goto _catch; }
        result = EmitTopSlotAndPop (o);
        if (result) { goto _catch; }
        result = PushRegister (o, type); 
        if (result) { goto _catch; }
    }
_catch:
    return result;
}

M3Result ReturnStackTop (IM3Compilation o)
{
    M3Result result = m3Err_none;
    i16 top = GetStackTopIndex (o);
    if (top >= 0)
    {
        const u16 returnSlot = 0;
        if (o->wasmStack [top] != returnSlot)
            CopyTopSlot (o, returnSlot);
    }
    else if (! IsStackPolymorphic (o))
        result = m3Err_functionStackUnderrun;
    return result;
}

M3Result FindReferencedLocalWithinCurrentBlock (IM3Compilation o, u16 * o_preservedSlotIndex, u32 i_localIndex)
{
    M3Result result = m3Err_none;
    IM3CompilationScope scope = & o->block;
    i16 startIndex = scope->initStackIndex;
    while (scope->opcode == c_waOp_block) {
        scope = scope->outer;
        if (! scope)
            break;
        startIndex = scope->initStackIndex;
    }
    * o_preservedSlotIndex = (u16) i_localIndex;
    for (u32 i = startIndex; i < o->stackIndex; ++i) {
        if (o->wasmStack [i] == i_localIndex) {
            if (* o_preservedSlotIndex == i_localIndex) {
                if (! AllocateSlot (o, o_preservedSlotIndex)) {
                        result = m3Err_functionStackOverflow;
                        goto _catch;
                }
            }
            else {
                result = IncrementSlotUsageCount (o, * o_preservedSlotIndex);
                if (result) { goto _catch; }
            }
            o->wasmStack [i] = * o_preservedSlotIndex;
        }
    }
_catch:
    return result;
}

M3Result GetBlockScope (IM3Compilation o, IM3CompilationScope * o_scope, i32 i_depth)
{
    IM3CompilationScope scope = & o->block;
    while (i_depth--) {
        scope = scope->outer;
        if (! scope)
            return "invalid block depth";
    }
    * o_scope = scope;
    return m3Err_none;
}

M3Result Compile_Const_i32 (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    i32 value;
    result = ReadLEB_i32 (& value, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }
    result = PushConst (o, value, c_m3Type_i32);
    if (result) { goto _catch; }
_catch:
    return result;
}

M3Result Compile_Const_i64 (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    i64 value;
    result = ReadLEB_i64 (& value, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }
    result = PushConst (o, value, c_m3Type_i64);
    if (result) { goto _catch; }
_catch:
    return result;
}

M3Result Compile_Const_f32 (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    f32 value;
    result = Read_f32 (& value, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }
    union { u64 u; f32 f; } union64;
    union64.f = value;
    result = PushConst (o, union64.u, c_m3Type_f32);
    if (result) { goto _catch; }
_catch:
    return result;
}

M3Result Compile_Const_f64 (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    f64 value;
    result = Read_f64 (& value, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }
    union { u64 u; f64 f; } union64;
    union64.f = value;
    result = PushConst (o, union64.u, c_m3Type_f64);
    if (result) { goto _catch; }
_catch:
    return result;
}

M3Result Compile_Return (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    bool hasReturn = GetFunctionNumReturns (o->function);
    if (hasReturn) {
        result = ReturnStackTop (o);
        if (result) { goto _catch; }
        result = Pop (o);
        if (result) { goto _catch; }
    }
    result = EmitOp (o, op_Return);
    if (result) { goto _catch; }
    o->block.isPolymorphic = true;
_catch:
    return result;
}

M3Result Compile_End (IM3Compilation o, u8 i_opcode)
{
    M3Result result = m3Err_none;
    if (o->block.depth == 0) {
        u8 valueType = o->block.type;
        if (valueType) {
            if (IsStackTopInRegister (o))
                PatchBranches (o);

            result = ReturnStackTop (o);
            if (result) { goto _catch; }
        }
        else
            PatchBranches (o);

        result = EmitOp (o, op_Return);
        if (result) { goto _catch; }
        result = UnwindBlockStack (o);
        if (result) { goto _catch; }

        if (valueType) {
            if (PatchBranches (o)) {
                result = PushRegister (o, valueType);
                if (result) { goto _catch; }

                ReturnStackTop (o);

                result = EmitOp (o, op_Return);
                if (result) { goto _catch; }
            }
        }
    }
_catch:
    return result;
}

M3Result Compile_SetLocal (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    u32 localSlot;
    result = ReadLEB_u32 (& localSlot, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }
    if (localSlot < GetFunctionNumArgsAndLocals (o->function)) {
        u16 preserveSlot;
        result = FindReferencedLocalWithinCurrentBlock (o, & preserveSlot, localSlot);
        if (result) { goto _catch; }
        if (preserveSlot == localSlot) {
            result = CopyTopSlot (o, localSlot);
            if (result) { goto _catch; }
        }
        else {
            result = PreservedCopyTopSlot (o, localSlot, preserveSlot);
            if (result) { goto _catch; }
        }
        if (i_opcode != c_waOp_teeLocal) {
            result = Pop (o);
            if (result) { goto _catch; }
        }
    }
    else {
        result = "local index out of bounds"; goto _catch; }
_catch:
    return result;
}

M3Result Compile_GetLocal (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    {
        u32 localIndex;
        result = ReadLEB_u32 (& localIndex, & o->wasm, o->wasmEnd);
        if (result) { goto _catch; }

        u8 type = o->typeStack [localIndex];

        result = Push (o, type, localIndex);
        if (result) { goto _catch; }
    } _catch:
    return result;
}

M3Result Compile_GetGlobal (IM3Compilation o, M3Global * i_global)
{
    M3Result result;
    result = EmitOp (o, op_GetGlobal);
    if (result) { goto _catch; }

    EmitPointer (o, & i_global->intValue);
    result = PushAllocatedSlotAndEmit (o, i_global->type);
    if (result) { goto _catch; }

_catch:
    return result;
}

M3Result Compile_SetGlobal (IM3Compilation o, M3Global * i_global)
{
    M3Result result = m3Err_none;
    if (i_global->isMutable) {
        IM3Operation op;
        u8 type = GetStackTopType (o);
        if (IsStackTopInRegister (o)) {
            const IM3Operation c_setGlobalOps [] = {
                NULL,
                op_SetGlobal_i32,
                op_SetGlobal_i64,
                op_SetGlobal_f32,
                op_SetGlobal_f64
            };
            op = c_setGlobalOps [type];
        }
        else
            op = Is64BitType (type) ? op_SetGlobal_s64 : op_SetGlobal_s32;

        result = EmitOp (o, op);
        if (result) { goto _catch; }

        EmitPointer (o, & i_global->intValue);
        if (IsStackTopInSlot (o))
            EmitSlotOffset (o, GetStackTopSlotIndex (o));

        result = Pop (o);
        if (result) { goto _catch; }
    }
    else
        result = m3Err_settingImmutableGlobal;
_catch:
    return result;
}

M3Result Compile_GetSetGlobal (IM3Compilation o, u8 i_opcode)
{
    M3Result result = m3Err_none;
    u32 globalIndex;
    result = ReadLEB_u32 (& globalIndex, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }

    if (globalIndex < o->module->numGlobals) {
        if (o->module->globals) {
            M3Global * global = & o->module->globals [globalIndex];
            result = (i_opcode == 0x23) ? Compile_GetGlobal (o, global) : Compile_SetGlobal (o, global);
        }
        else
            result = m3Error (m3Err_globalMemoryNotAllocated, o->runtime, o->module, NULL,
                              "m3_compile.c", 946, "module '%s' is missing global memory", o->module->name);
    }
    else
        result = m3Error (m3Err_globaIndexOutOfBounds, o->runtime, o->module, NULL, "m3_compile.c", 948, "");
_catch:
    return result;
}

M3Result Compile_Branch (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    u32 depth;
    result = ReadLEB_u32 (& depth, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }

    IM3CompilationScope scope;
    result = GetBlockScope (o, & scope, depth);
    if (result) { goto _catch; }

    IM3Operation op;
    if (scope->opcode == c_waOp_loop) {
        if (i_opcode == c_waOp_branchIf) {
            result = MoveStackTopToRegister (o);
            if (result) { goto _catch; }

            op = op_ContinueLoopIf;

            result = Pop (o);
            if (result) { goto _catch; }
        }
        else {
            op = op_ContinueLoop;
            o->block.isPolymorphic = true;
        }

        result = EmitOp (o, op);
        if (result) { goto _catch; }

        EmitPointer (o, scope->pc);
    }
    else {
        u16 conditionSlot = c_slotUnused;
        u16 valueSlot = c_slotUnused;
        u8 valueType = scope->type;
        if (i_opcode == c_waOp_branchIf) {
            bool conditionInRegister = IsStackTopInRegister (o);
            op = conditionInRegister ? op_BranchIf_r : op_BranchIf_s;
            conditionSlot = GetStackTopSlotIndex (o);

            result = Pop (o);
            if (result) { goto _catch; }

            if (IsFpType (valueType)) {
                result = MoveStackTopToRegister (o);
                if (result) { goto _catch; }
            }
            else if (IsIntType (valueType)) {
                if (IsStackTopInSlot (o)) {
                    valueSlot = GetStackTopSlotIndex (o);
                    const IM3Operation ifOps [2][2] = {
                        { op_i32_BranchIf_ss, op_i32_BranchIf_rs },
                        { op_i64_BranchIf_ss, op_i64_BranchIf_rs }
                    };
                    op = ifOps [valueType - c_m3Type_i32] [conditionInRegister];
                }
            }
        }
        else {
            op = op_Branch;
            if (valueType != c_m3Type_none && ! IsStackPolymorphic (o)) {
                result = MoveStackTopToRegister (o);
                if (result) { goto _catch; }
            }
            o->block.isPolymorphic = true;
        }

        result = EmitOp (o, op);
        if (result) { goto _catch; }

        if (IsValidSlot (conditionSlot))
            EmitSlotOffset (o, conditionSlot);
        if (IsValidSlot (valueSlot))
            EmitSlotOffset (o, valueSlot);
        IM3BranchPatch patch;

        result = AcquirePatch (o, & patch);
        if (result) { goto _catch; }

        patch->location = (pc_t *) ReservePointer (o);
        patch->next = scope->patches;
        scope->patches = patch;
    }
_catch:
    return result;
}

M3Result Compile_BranchTable (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    {
        u32 targetCount;
        result = ReadLEB_u32 (& targetCount, & o->wasm, o->wasmEnd);
        if (result) { goto _catch; }
        result = PreserveRegisterIfOccupied (o, c_m3Type_i64);
        if (result) { goto _catch; }

        u16 slot = GetStackTopSlotIndex (o);

        result = Pop (o);
        if (result) { goto _catch; }

        if (GetNumBlockValues (o) > 0) {
            result = MoveStackTopToRegister (o);
            if (result) { goto _catch; }
        }
        u32 numCodeLines = targetCount + 4;

        result = EnsureCodePageNumLines (o, numCodeLines);
        if (result) { goto _catch; }
        result = EmitOp (o, op_BranchTable);
        if (result) { goto _catch; }

        EmitSlotOffset (o, slot);
        EmitConstant (o, targetCount);
        ++targetCount;
        for (u32 i = 0; i < targetCount; ++i) {
            u32 target;
            result = ReadLEB_u32 (& target, & o->wasm, o->wasmEnd);
            if (result) { goto _catch; }

            IM3CompilationScope scope;
            result = GetBlockScope (o, & scope, target);
            if (result) { goto _catch; }

            if (scope->opcode == c_waOp_loop) {
                IM3CodePage continueOpPage = AcquireCodePage (o->runtime);
                if (continueOpPage) {
                    pc_t startPC = GetPagePC (continueOpPage);
                    EmitPointer (o, startPC);
                    IM3CodePage savedPage = o->page;
                    o->page = continueOpPage;

                    result = EmitOp (o, op_ContinueLoop);
                    if (result) { goto _catch; }

                    EmitPointer (o, scope->pc);
                    ReleaseCompilationCodePage (o);
                    o->page = savedPage;
                }
                else {
                    result = m3Err_mallocFailedCodePage;
                    goto _catch;
                }
            }
            else {
                IM3BranchPatch patch;
                result = AcquirePatch (o, & patch);
                if (result) { goto _catch; }

                patch->location = (pc_t *) ReservePointer (o);
                patch->next = scope->patches;
                scope->patches = patch;
            }
        }
        o->block.isPolymorphic = true;
    }
_catch:
    return result;
}

M3Result CompileCallArgsReturn (IM3Compilation o, u16 * o_stackOffset, IM3FuncType i_type, bool i_isIndirect)
{
    M3Result result = m3Err_none;
    {
        u16 execTop = GetMaxExecSlot (o);
        if (execTop == 0)
            execTop = 1;
        * o_stackOffset = execTop;
        u32 numArgs = i_type->numArgs + i_isIndirect;
        u16 argTop = execTop + numArgs;
        while (numArgs--) {
            result = CopyTopSlot (o, --argTop);
            if (result) { goto _catch; }
            result = Pop (o);
            if (result) { goto _catch; }
        }
        i32 numReturns = i_type->returnType ? 1 : 0;
        if (numReturns) {
            MarkSlotAllocated (o, execTop);
            result = Push (o, i_type->returnType, execTop);
            if (result) { goto _catch; }
        }
    } _catch:
    return result;
}

M3Result Compile_Call (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    {
        u32 functionIndex;
        result = ReadLEB_u32 (& functionIndex, & o->wasm, o->wasmEnd);
        if (result) { goto _catch; }
        IM3Function function = Module_GetFunction (o->module, functionIndex);
        if (function) {
            if (function->module) {
                u16 slotTop;
                result = CompileCallArgsReturn (o, & slotTop, function->funcType, false);
                if (result) { goto _catch; }

                IM3Operation op;
                const void * operand;
                if (function->compiled) {
                    op = op_Call;
                    operand = function->compiled;
                }
                else {
                    op = op_Compile;
                    operand = function;
                }

                result = EmitOp (o, op);
                if (result) { goto _catch; }

                EmitPointer (o, operand);
                EmitSlotOffset (o, slotTop);
            }
            else {
                result = m3Error (m3Err_functionImportMissing, o->runtime, o->module, NULL,
                                  "m3_compile.c", 1197, "'%s.%s'",
                                  GetFunctionImportModuleName (function),
                                  GetFunctionName (function));
            }
        }
        else
            result = m3Err_functionLookupFailed;
    } _catch:
    return result;
}

M3Result Compile_CallIndirect (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    u32 typeIndex;
    result = ReadLEB_u32 (& typeIndex, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }

    i8 reserved;
    result = ReadLEB_i7 (& reserved, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }

    if (typeIndex < o->module->numFuncTypes) {
        u16 execTop;
        IM3FuncType type = & o->module->funcTypes [typeIndex];
        result = CompileCallArgsReturn (o, & execTop, type, true);
        if (result) { goto _catch; }

        result = EmitOp (o, op_CallIndirect);
        if (result) { goto _catch; }

        EmitPointer (o, o->module);
        EmitPointer (o, type);
        EmitSlotOffset (o, execTop);
    }
    else {
        result = "function type index out of range";
        goto _catch;
    }
_catch:
    return result;
}

M3Result Compile_Memory_Current (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    i8 reserved;
    result = ReadLEB_i7 (& reserved, & o->wasm, o->wasmEnd);
    if (result) { goto _catch; }

    result = EmitOp (o, op_MemCurrent);
    if (result) { goto _catch; }

    result = PushRegister (o, c_m3Type_i32);
    if (result) { goto _catch; }

_catch:
    return result;
}

M3Result Compile_Memory_Grow (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    i8 reserved;
    {
        result = ReadLEB_i7 (& reserved, & o->wasm, o->wasmEnd);
        if (result) { goto _catch; }
    }
    {
        result = MoveStackTopToRegister (o);
        if (result) { goto _catch; }
    }
    {
        result = Pop (o);
        if (result) { goto _catch; }
    }
    {
        result = EmitOp (o, op_MemGrow);
        if (result) { goto _catch; }
    }
    {
        result = PushRegister (o, c_m3Type_i32);
        if (result) { goto _catch; }
    }
_catch:
    return result;
}

M3Result ReadBlockType (IM3Compilation o, u8 * o_blockType)
{
    M3Result result;
    i8 type;
    {
        result = ReadLEB_i7 (& type, & o->wasm, o->wasmEnd);
        if (result) { goto _catch; }
    }
    {
        result = NormalizeType (o_blockType, type);
        if (result) { goto _catch; }
    }
    if (* o_blockType) {}
_catch:
    return result;
}

M3Result PreserveArgsAndLocals (IM3Compilation o)
{
    M3Result result = m3Err_none;
    if (o->stackIndex > o->firstSlotIndex) {
        u32 numArgsAndLocals = GetFunctionNumArgsAndLocals (o->function);
        for (u32 i = 0; i < numArgsAndLocals; ++i) {
            u16 preservedSlotIndex;
            {
                result = FindReferencedLocalWithinCurrentBlock (o, & preservedSlotIndex, i);
                if (result) { goto _catch; }
            }
            if (preservedSlotIndex != i) {
                u8 type = GetStackBottomType (o, i);
                IM3Operation op = Is64BitType (type) ? op_CopySlot_64 : op_CopySlot_32;
                EmitOp (o, op);
                EmitSlotOffset (o, preservedSlotIndex);
                EmitSlotOffset (o, i);
            }
        }
    }
_catch:
    return result;
}

M3Result Compile_LoopOrBlock (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    {
        result = PreserveRegisters (o);
        if (result) { goto _catch; }
    }
    {
        result = PreserveArgsAndLocals (o);
        if (result) { goto _catch; }
    }
    u8 blockType;
    {
        result = ReadBlockType (o, & blockType);
        if (result) { goto _catch; }
    }
    if (i_opcode == c_waOp_loop)
    {
        result = EmitOp (o, op_Loop);
        if (result) { goto _catch; }
    }
    {
        result = CompileBlock (o, blockType, i_opcode);
        if (result) { goto _catch; }
    }
_catch:
    return result;
}

M3Result CompileElseBlock (IM3Compilation o, pc_t * o_startPC, u8 i_blockType)
{
    M3Result result;
    IM3CodePage elsePage = AcquireCodePage (o->runtime);
    if (elsePage) {
        * o_startPC = GetPagePC (elsePage);
        IM3CodePage savedPage = o->page;
        o->page = elsePage;
        {
            result = CompileBlock (o, i_blockType, c_waOp_else);
            if (result) { goto _catch; }
        }
        {
            result = EmitOp (o, op_Branch);
            if (result) { goto _catch; }
        }
        EmitPointer (o, GetPagePC (savedPage));
        ReleaseCompilationCodePage (o);
        o->page = savedPage;
    }
    else result = m3Err_mallocFailedCodePage;
_catch:
    return result;
}

M3Result Compile_If (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    {
        {
            result = PreserveNonTopRegisters (o);
            if (result) { goto _catch; }
        }
        {
            result = PreserveArgsAndLocals (o);
            if (result) { goto _catch; }
        }
        IM3Operation op = IsStackTopInRegister (o) ? op_If_r : op_If_s;
        {
            result = EmitOp (o, op);
            if (result) { goto _catch; }
        }
        {
            result = EmitTopSlotAndPop (o);
            if (result) { goto _catch; }
        }
        i32 stackIndex = o->stackIndex;
        pc_t * pc = (pc_t *) ReservePointer (o);
        u8 blockType;
        {
            result = ReadBlockType (o, & blockType);
            if (result) { goto _catch; }
        }
        {
            result = CompileBlock (o, blockType, i_opcode);
            if (result) { goto _catch; }
        }
        if (o->previousOpcode == c_waOp_else) {
            if (blockType && o->stackIndex > stackIndex) {
                {
                    result = Pop (o);
                    if (result) { goto _catch; }
                }
            }
            {
                result = CompileElseBlock (o, pc, blockType);
                if (result) { goto _catch; }
            }
        }
        else * pc = GetPC (o);
    } _catch:
    return result;
}

M3Result Compile_Select (IM3Compilation o, u8 i_opcode)
{
    static const IM3Operation intSelectOps [2] [4] = {
        { op_Select_i32_rss, op_Select_i32_srs, op_Select_i32_ssr, op_Select_i32_sss },
        { op_Select_i64_rss, op_Select_i64_srs, op_Select_i64_ssr, op_Select_i64_sss }
    };
    static const IM3Operation fpSelectOps [2] [2] [3] = {
        {
            { op_Select_f32_sss, op_Select_f32_srs, op_Select_f32_ssr },
            { op_Select_f32_rss, op_Select_f32_rrs, op_Select_f32_rsr }
        },
        {
            { op_Select_f64_sss, op_Select_f64_srs, op_Select_f64_ssr },
            { op_Select_f64_rss, op_Select_f64_rrs, op_Select_f64_rsr }
        }
    };
    M3Result result = m3Err_none;
    u16 slots [3] = { c_slotUnused, c_slotUnused, c_slotUnused };
    u8 type = GetStackTopTypeAtOffset (o, 1);
    IM3Operation op = NULL;
    if (IsFpType (type)) {
        bool selectorInReg = IsStackTopInRegister (o);
        slots [0] = GetStackTopSlotIndex (o);
        {
            result = Pop (o);
            if (result) { goto _catch; }
        }
        u32 opIndex = 0;
        for (u32 i = 1; i <= 2; ++i) {
            if (IsStackTopInRegister (o))
                opIndex = i;
            else
                slots [i] = GetStackTopSlotIndex (o);
            {
                result = Pop (o);
                if (result) { goto _catch; }
            }
        }
        if (opIndex == 0)
        {
            result = PreserveRegisterIfOccupied (o, type);
            if (result) { goto _catch; }
        }
        op = fpSelectOps [type - c_m3Type_f32] [selectorInReg] [opIndex];
    }
    else if (IsIntType (type)) {
        u32 opIndex = 3;
        for (u32 i = 0; i < 3; ++i) {
            if (IsStackTopInRegister (o))
                opIndex = i;
            else
                slots [i] = GetStackTopSlotIndex (o);
            {
                result = Pop (o);
                if (result) { goto _catch; }
            }
        }
        if (opIndex == 3)
        {
            result = PreserveRegisterIfOccupied (o, type);
            if (result) { goto _catch; }
        }
        op = intSelectOps [type - c_m3Type_i32] [opIndex];
    }
    else if (! IsStackPolymorphic (o)) {
        result = m3Err_functionStackUnderrun; goto _catch; }
    EmitOp (o, op);
    for (u32 i = 0; i < 3; i++) {
        if (IsValidSlot (slots [i]))
            EmitSlotOffset (o, slots [i]);
    }
    {
        result = PushRegister (o, type);
        if (result) { goto _catch; }
    }
_catch:
    return result;
}

M3Result Compile_Drop (IM3Compilation o, u8 i_opcode)
{
    return Pop (o);
}

M3Result Compile_Nop (IM3Compilation o, u8 i_opcode)
{
    return m3Err_none;
}

M3Result Compile_Unreachable (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    {
        result = AddTrapRecord (o);
        if (result) { goto _catch; }
    }
    {
        result = EmitOp (o, op_Unreachable);
        if (result) { goto _catch; }
    }
    o->block.isPolymorphic = true;
_catch:
    return result;
}

M3Result Compile_Operator (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    const M3OpInfo * op = & c_operations [i_opcode];
    IM3Operation operation;
    if (IsFpType (GetStackTopType (o)) && IsIntType (op->type)) {
        {
            result = PreserveRegisterIfOccupied (o, op->type);
            if (result) { goto _catch; }
        }
    }
    if (op->stackOffset == 0) {
        if (IsStackTopInRegister (o)) {
            operation = op->operations [0];
        }
        else {
            {
                result = PreserveRegisterIfOccupied (o, op->type);
                if (result) { goto _catch; }
            }
            operation = op->operations [1];
        }
    }
    else {
        if (IsStackTopInRegister (o)) {
            operation = op->operations [0];
            if (IsStackTopMinus1InRegister (o)) {
                operation = op->operations [3];
            }
        }
        else if (IsStackTopMinus1InRegister (o)) {
            operation = op->operations [1];
            if (! operation)
                operation = op->operations [0];
        }
        else {
            {
                result = PreserveRegisterIfOccupied (o, op->type);
                if (result) { goto _catch; }
            }
            operation = op->operations [2];
        }
    }
    if (operation) {
        {
            result = EmitOp (o, operation);
            if (result) { goto _catch; }
        }
        {
            result = EmitTopSlotAndPop (o);
            if (result) { goto _catch; }
        }
        if (op->stackOffset < 0)
        {
            result = EmitTopSlotAndPop (o);
            if (result) { goto _catch; }
        }
        if (op->type != c_m3Type_none)
        {
            result = PushRegister (o, op->type);
            if (result) { goto _catch; }
        }
    }
    else {
        result = m3Error ("no operation found for opcode", o->runtime, o->module,
                          NULL, "m3_compile.c", 1575, "");
    }
_catch:
    return result;
}

M3Result Compile_Convert (IM3Compilation o, u8 i_opcode)
{
    M3Result result = m3Err_none;
    const M3OpInfo * opInfo = & c_operations [i_opcode];
    bool destInSlot = IsRegisterTypeAllocated (o, opInfo->type);
    bool sourceInSlot = IsStackTopInSlot (o);
    IM3Operation op = opInfo->operations [destInSlot * 2 + sourceInSlot];
    {
        result = EmitOp (o, op);
        if (result) { goto _catch; }
    }
    {
        result = EmitTopSlotAndPop (o);
        if (result) { goto _catch; }
    }
    if (destInSlot)
    {
        result = PushAllocatedSlotAndEmit (o, opInfo->type);
        if (result) { goto _catch; }
    }
    else
    {
        result = PushRegister (o, opInfo->type);
        if (result) { goto _catch; }
    }
_catch:
    return result;
}

M3Result Compile_Load_Store (IM3Compilation o, u8 i_opcode)
{
    M3Result result;
    {
        u32 alignHint, memoryOffset;
        {
            result = ReadLEB_u32 (& alignHint, & o->wasm, o->wasmEnd);
            if (result) { goto _catch; }
        }
        {
            result = ReadLEB_u32 (& memoryOffset, & o->wasm, o->wasmEnd);
            if (result) { goto _catch; }
        }
        const M3OpInfo * op = & c_operations [i_opcode];
        if (IsFpType (op->type)) {
            result = PreserveRegisterIfOccupied (o, c_m3Type_f64);
            if (result) { goto _catch; }
        }
        {
            result = Compile_Operator (o, i_opcode);
            if (result) { goto _catch; }
        }
        EmitConstant (o, memoryOffset);
    }
_catch:
    return result;
}

const M3OpInfo c_operations [] =
{
    { 0, c_m3Type_none, { op_Unreachable, NULL, NULL, NULL }, Compile_Unreachable },
    { 0, c_m3Type_none, { NULL, NULL, NULL, NULL }, Compile_Nop },
    { 0, c_m3Type_none, { NULL, NULL, NULL, NULL }, Compile_LoopOrBlock },
    { 0, c_m3Type_none, { op_Loop, NULL, NULL, NULL }, Compile_LoopOrBlock },
    { -1, c_m3Type_none, { NULL, NULL, NULL, NULL }, Compile_If },
    { 0, c_m3Type_none, { NULL, NULL, NULL, NULL }, Compile_Nop },
    { 0 }, { 0 }, { 0 }, { 0 }, { 0 },
    { 0, c_m3Type_none, { NULL, NULL, NULL, NULL }, Compile_End },
    { 0, c_m3Type_none, { op_Branch, NULL, NULL, NULL }, Compile_Branch },
    { -1, c_m3Type_none, { op_BranchIf_r, op_BranchIf_s }, Compile_Branch },
    { -1, c_m3Type_none, { op_BranchTable, NULL, NULL, NULL }, Compile_BranchTable },
    { 0, (u8)-1, { op_Return, NULL, NULL, NULL }, Compile_Return },
    { 0, (u8)-1, { op_Call, NULL, NULL, NULL }, Compile_Call },
    { 0, (u8)-1, { op_CallIndirect, NULL, NULL, NULL }, Compile_CallIndirect },
    { 0, (u8)-1, { NULL, NULL, NULL, NULL }, Compile_Call },
    { 0, (u8)-1, { NULL, NULL, NULL, NULL }, Compile_CallIndirect },
    { 0 }, { 0 },
    { 0 }, { 0 }, { 0 }, { 0 },
    { -1, c_m3Type_none, { NULL, NULL, NULL, NULL }, Compile_Drop },
    { -2, (u8)-1, { NULL, NULL, NULL, NULL }, Compile_Select },
    { 0 }, { 0 }, { 0 }, { 0 },
    { 1, (u8)-1, { NULL, NULL, NULL, NULL }, Compile_GetLocal },
    { 1, c_m3Type_none, { NULL, NULL, NULL, NULL }, Compile_SetLocal },
    { 0, (u8)-1, { NULL, NULL, NULL, NULL }, Compile_SetLocal },
    { 1, c_m3Type_none, { op_GetGlobal, NULL, NULL, NULL }, Compile_GetSetGlobal },
    { 1, c_m3Type_none, { NULL, NULL, NULL, NULL }, Compile_GetSetGlobal },
    { 0 }, { 0 }, { 0 },
    { 0, c_m3Type_i32, { op_i32_Load_i32_r, op_i32_Load_i32_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i64, { op_i64_Load_i64_r, op_i64_Load_i64_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_f32, { op_f32_Load_f32_r, op_f32_Load_f32_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_f64, { op_f64_Load_f64_r, op_f64_Load_f64_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i32, { op_i32_Load_i8_r, op_i32_Load_i8_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i32, { op_i32_Load_u8_r, op_i32_Load_u8_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i32, { op_i32_Load_i16_r, op_i32_Load_i16_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i32, { op_i32_Load_u16_r, op_i32_Load_u16_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i64, { op_i64_Load_i8_r, op_i64_Load_i8_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i64, { op_i64_Load_u8_r, op_i64_Load_u8_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i64, { op_i64_Load_i16_r, op_i64_Load_i16_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i64, { op_i64_Load_u16_r, op_i64_Load_u16_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i64, { op_i64_Load_i32_r, op_i64_Load_i32_s, NULL, NULL }, Compile_Load_Store },
    { 0, c_m3Type_i64, { op_i64_Load_u32_r, op_i64_Load_u32_s, NULL, NULL }, Compile_Load_Store },
    { -2, c_m3Type_none, { op_i32_Store_i32_rs, op_i32_Store_i32_sr, op_i32_Store_i32_ss, NULL }, Compile_Load_Store },
    { -2, c_m3Type_none, { op_i64_Store_i64_rs, op_i64_Store_i64_sr, op_i64_Store_i64_ss, NULL }, Compile_Load_Store },
    { -2, c_m3Type_none, { op_f32_Store_f32_rs, op_f32_Store_f32_sr, op_f32_Store_f32_ss, op_f32_Store_f32_rr }, Compile_Load_Store },
    { -2, c_m3Type_none, { op_f64_Store_f64_rs, op_f64_Store_f64_sr, op_f64_Store_f64_ss, op_f64_Store_f64_rr }, Compile_Load_Store },
    { -2, c_m3Type_none, { op_i32_Store_u8_rs, op_i32_Store_u8_sr, op_i32_Store_u8_ss, NULL }, Compile_Load_Store },
    { -2, c_m3Type_none, { op_i32_Store_i16_rs, op_i32_Store_i16_sr, op_i32_Store_i16_ss, NULL }, Compile_Load_Store },
    { -2, c_m3Type_none, { op_i64_Store_u8_rs, op_i64_Store_u8_sr, op_i64_Store_u8_ss, NULL }, Compile_Load_Store },
    { -2, c_m3Type_none, { op_i64_Store_i16_rs, op_i64_Store_i16_sr, op_i64_Store_i16_ss, NULL }, Compile_Load_Store },
    { -2, c_m3Type_none, { op_i64_Store_i32_rs, op_i64_Store_i32_sr, op_i64_Store_i32_ss, NULL }, Compile_Load_Store },
    { 1, c_m3Type_i32, { op_MemCurrent, NULL, NULL, NULL }, Compile_Memory_Current },
    { 1, c_m3Type_i32, { op_MemGrow, NULL, NULL, NULL }, Compile_Memory_Grow },
    { 1, c_m3Type_i32, { NULL, NULL, NULL, NULL }, Compile_Const_i32 },
    { 1, c_m3Type_i64, { NULL, NULL, NULL, NULL }, Compile_Const_i64 },
    { 1, c_m3Type_f32, { NULL, NULL, NULL, NULL }, Compile_Const_f32 },
    { 1, c_m3Type_f64, { NULL, NULL, NULL, NULL }, Compile_Const_f64 },
    { 0, c_m3Type_i32, { op_i32_EqualToZero_r, op_i32_EqualToZero_s, NULL, NULL } },
    { -1, c_m3Type_i32, { op_i32_Equal_rs, NULL, op_i32_Equal_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_NotEqual_rs, NULL, op_i32_NotEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_LessThan_rs, op_i32_LessThan_sr, op_i32_LessThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_LessThan_rs, op_u32_LessThan_sr, op_u32_LessThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_GreaterThan_rs, op_i32_GreaterThan_sr, op_i32_GreaterThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_GreaterThan_rs, op_u32_GreaterThan_sr, op_u32_GreaterThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_LessThanOrEqual_rs, op_i32_LessThanOrEqual_sr, op_i32_LessThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_LessThanOrEqual_rs, op_u32_LessThanOrEqual_sr, op_u32_LessThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_GreaterThanOrEqual_rs, op_i32_GreaterThanOrEqual_sr, op_i32_GreaterThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_GreaterThanOrEqual_rs, op_u32_GreaterThanOrEqual_sr, op_u32_GreaterThanOrEqual_ss, NULL } },
    { 0, c_m3Type_i32, { op_i64_EqualToZero_r, op_i64_EqualToZero_s, NULL, NULL } },
    { -1, c_m3Type_i32, { op_i64_Equal_rs, NULL, op_i64_Equal_ss, NULL } },
    { -1, c_m3Type_i32, { op_i64_NotEqual_rs, NULL, op_i64_NotEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_i64_LessThan_rs, op_i64_LessThan_sr, op_i64_LessThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_u64_LessThan_rs, op_u64_LessThan_sr, op_u64_LessThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_i64_GreaterThan_rs, op_i64_GreaterThan_sr, op_i64_GreaterThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_u64_GreaterThan_rs, op_u64_GreaterThan_sr, op_u64_GreaterThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_i64_LessThanOrEqual_rs, op_i64_LessThanOrEqual_sr, op_i64_LessThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_u64_LessThanOrEqual_rs, op_u64_LessThanOrEqual_sr, op_u64_LessThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_i64_GreaterThanOrEqual_rs, op_i64_GreaterThanOrEqual_sr, op_i64_GreaterThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_u64_GreaterThanOrEqual_rs, op_u64_GreaterThanOrEqual_sr, op_u64_GreaterThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_f32_Equal_rs, NULL, op_f32_Equal_ss, NULL } },
    { -1, c_m3Type_i32, { op_f32_NotEqual_rs, NULL, op_f32_NotEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_f32_LessThan_rs, op_f32_LessThan_sr, op_f32_LessThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_f32_GreaterThan_rs, op_f32_GreaterThan_sr, op_f32_GreaterThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_f32_LessThanOrEqual_rs, op_f32_LessThanOrEqual_sr, op_f32_LessThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_f32_GreaterThanOrEqual_rs, op_f32_GreaterThanOrEqual_sr, op_f32_GreaterThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_f64_Equal_rs, NULL, op_f64_Equal_ss, NULL } },
    { -1, c_m3Type_i32, { op_f64_NotEqual_rs, NULL, op_f64_NotEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_f64_LessThan_rs, op_f64_LessThan_sr, op_f64_LessThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_f64_GreaterThan_rs, op_f64_GreaterThan_sr, op_f64_GreaterThan_ss, NULL } },
    { -1, c_m3Type_i32, { op_f64_LessThanOrEqual_rs, op_f64_LessThanOrEqual_sr, op_f64_LessThanOrEqual_ss, NULL } },
    { -1, c_m3Type_i32, { op_f64_GreaterThanOrEqual_rs, op_f64_GreaterThanOrEqual_sr, op_f64_GreaterThanOrEqual_ss, NULL } },
    { 0, c_m3Type_i32, { op_u32_Clz_r, op_u32_Clz_s, NULL, NULL } },
    { 0, c_m3Type_i32, { op_u32_Ctz_r, op_u32_Ctz_s, NULL, NULL } },
    { 0, c_m3Type_i32, { op_u32_Popcnt_r, op_u32_Popcnt_s, NULL, NULL } },
    { -1, c_m3Type_i32, { op_i32_Add_rs, NULL, op_i32_Add_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_Subtract_rs, op_i32_Subtract_sr, op_i32_Subtract_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_Multiply_rs, NULL, op_i32_Multiply_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_Divide_rs, op_i32_Divide_sr, op_i32_Divide_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_Divide_rs, op_u32_Divide_sr, op_u32_Divide_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_Remainder_rs, op_i32_Remainder_sr, op_i32_Remainder_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_Remainder_rs, op_u32_Remainder_sr, op_u32_Remainder_ss, NULL } },
    { -1, c_m3Type_i32, { op_u64_And_rs, NULL, op_u64_And_ss, NULL } },
    { -1, c_m3Type_i32, { op_u64_Or_rs, NULL, op_u64_Or_ss, NULL } },
    { -1, c_m3Type_i32, { op_u64_Xor_rs, NULL, op_u64_Xor_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_ShiftLeft_rs, op_u32_ShiftLeft_sr, op_u32_ShiftLeft_ss, NULL } },
    { -1, c_m3Type_i32, { op_i32_ShiftRight_rs, op_i32_ShiftRight_sr, op_i32_ShiftRight_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_ShiftRight_rs, op_u32_ShiftRight_sr, op_u32_ShiftRight_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_Rotl_rs, op_u32_Rotl_sr, op_u32_Rotl_ss, NULL } },
    { -1, c_m3Type_i32, { op_u32_Rotr_rs, op_u32_Rotr_sr, op_u32_Rotr_ss, NULL } },
    { 0, c_m3Type_i64, { op_u64_Clz_r, op_u64_Clz_s, NULL, NULL } },
    { 0, c_m3Type_i64, { op_u64_Ctz_r, op_u64_Ctz_s, NULL, NULL } },
    { 0, c_m3Type_i64, { op_u64_Popcnt_r, op_u64_Popcnt_s, NULL, NULL } },
    { -1, c_m3Type_i64, { op_i64_Add_rs, NULL, op_i64_Add_ss, NULL } },
    { -1, c_m3Type_i64, { op_i64_Subtract_rs, op_i64_Subtract_sr, op_i64_Subtract_ss, NULL } },
    { -1, c_m3Type_i64, { op_i64_Multiply_rs, NULL, op_i64_Multiply_ss, NULL } },
    { -1, c_m3Type_i64, { op_i64_Divide_rs, op_i64_Divide_sr, op_i64_Divide_ss, NULL } },
    { -1, c_m3Type_i64, { op_u64_Divide_rs, op_u64_Divide_sr, op_u64_Divide_ss, NULL } },
    { -1, c_m3Type_i64, { op_i64_Remainder_rs, op_i64_Remainder_sr, op_i64_Remainder_ss, NULL } },
    { -1, c_m3Type_i64, { op_u64_Remainder_rs, op_u64_Remainder_sr, op_u64_Remainder_ss, NULL } },
    { -1, c_m3Type_i64, { op_u64_And_rs, NULL, op_u64_And_ss, NULL } },
    { -1, c_m3Type_i64, { op_u64_Or_rs, NULL, op_u64_Or_ss, NULL } },
    { -1, c_m3Type_i64, { op_u64_Xor_rs, NULL, op_u64_Xor_ss, NULL } },
    { -1, c_m3Type_i64, { op_u64_ShiftLeft_rs, op_u64_ShiftLeft_sr, op_u64_ShiftLeft_ss, NULL } },
    { -1, c_m3Type_i64, { op_i64_ShiftRight_rs, op_i64_ShiftRight_sr, op_i64_ShiftRight_ss, NULL } },
    { -1, c_m3Type_i64, { op_u64_ShiftRight_rs, op_u64_ShiftRight_sr, op_u64_ShiftRight_ss, NULL } },
    { -1, c_m3Type_i64, { op_u64_Rotl_rs, op_u64_Rotl_sr, op_u64_Rotl_ss, NULL } },
    { -1, c_m3Type_i64, { op_u64_Rotr_rs, op_u64_Rotr_sr, op_u64_Rotr_ss, NULL } },
    { 0, c_m3Type_f32, { op_f32_Abs_r, op_f32_Abs_s, NULL, NULL } },
    { 0, c_m3Type_f32, { op_f32_Negate_r, op_f32_Negate_s, NULL, NULL } },
    { 0, c_m3Type_f32, { op_f32_Ceil_r, op_f32_Ceil_s, NULL, NULL } },
    { 0, c_m3Type_f32, { op_f32_Floor_r, op_f32_Floor_s, NULL, NULL } },
    { 0, c_m3Type_f32, { op_f32_Trunc_r, op_f32_Trunc_s, NULL, NULL } },
    { 0, c_m3Type_f32, { op_f32_Nearest_r, op_f32_Nearest_s, NULL, NULL } },
    { 0, c_m3Type_f32, { op_f32_Sqrt_r, op_f32_Sqrt_s, NULL, NULL } },
    { -1, c_m3Type_f32, { op_f32_Add_rs, NULL, op_f32_Add_ss, NULL } },
    { -1, c_m3Type_f32, { op_f32_Subtract_rs, op_f32_Subtract_sr, op_f32_Subtract_ss, NULL } },
    { -1, c_m3Type_f32, { op_f32_Multiply_rs, NULL, op_f32_Multiply_ss, NULL } },
    { -1, c_m3Type_f32, { op_f32_Divide_rs, op_f32_Divide_sr, op_f32_Divide_ss, NULL } },
    { -1, c_m3Type_f32, { op_f32_Min_rs, NULL, op_f32_Min_ss, NULL } },
    { -1, c_m3Type_f32, { op_f32_Max_rs, NULL, op_f32_Max_ss, NULL } },
    { -1, c_m3Type_f32, { op_f32_CopySign_rs, op_f32_CopySign_sr, op_f32_CopySign_ss, NULL } },
    { 0, c_m3Type_f64, { op_f64_Abs_r, op_f64_Abs_s, NULL, NULL } },
    { 0, c_m3Type_f64, { op_f64_Negate_r, op_f64_Negate_s, NULL, NULL } },
    { 0, c_m3Type_f64, { op_f64_Ceil_r, op_f64_Ceil_s, NULL, NULL } },
    { 0, c_m3Type_f64, { op_f64_Floor_r, op_f64_Floor_s, NULL, NULL } },
    { 0, c_m3Type_f64, { op_f64_Trunc_r, op_f64_Trunc_s, NULL, NULL } },
    { 0, c_m3Type_f64, { op_f64_Nearest_r, op_f64_Nearest_s, NULL, NULL } },
    { 0, c_m3Type_f64, { op_f64_Sqrt_r, op_f64_Sqrt_s, NULL, NULL } },
    { -1, c_m3Type_f64, { op_f64_Add_rs, NULL, op_f64_Add_ss, NULL } },
    { -1, c_m3Type_f64, { op_f64_Subtract_rs, op_f64_Subtract_sr, op_f64_Subtract_ss, NULL } },
    { -1, c_m3Type_f64, { op_f64_Multiply_rs, NULL, op_f64_Multiply_ss, NULL } },
    { -1, c_m3Type_f64, { op_f64_Divide_rs, op_f64_Divide_sr, op_f64_Divide_ss, NULL } },
    { -1, c_m3Type_f64, { op_f64_Min_rs, NULL, op_f64_Min_ss, NULL } },
    { -1, c_m3Type_f64, { op_f64_Max_rs, NULL, op_f64_Max_ss, NULL } },
    { -1, c_m3Type_f64, { op_f64_CopySign_rs, op_f64_CopySign_sr, op_f64_CopySign_ss, NULL } },
    { 0, c_m3Type_i32, { op_i32_Wrap_i64_r, op_i32_Wrap_i64_s, NULL, NULL } },
    { 0, c_m3Type_i32, { op_i32_Trunc_f32_r_r, op_i32_Trunc_f32_r_s, op_i32_Trunc_f32_s_r, op_i32_Trunc_f32_s_s }, Compile_Convert },
    { 0, c_m3Type_i32, { op_u32_Trunc_f32_r_r, op_u32_Trunc_f32_r_s, op_u32_Trunc_f32_s_r, op_u32_Trunc_f32_s_s }, Compile_Convert },
    { 0, c_m3Type_i32, { op_i32_Trunc_f64_r_r, op_i32_Trunc_f64_r_s, op_i32_Trunc_f64_s_r, op_i32_Trunc_f64_s_s }, Compile_Convert },
    { 0, c_m3Type_i32, { op_u32_Trunc_f64_r_r, op_u32_Trunc_f64_r_s, op_u32_Trunc_f64_s_r, op_u32_Trunc_f64_s_s }, Compile_Convert },
    { 0, c_m3Type_i64, { op_i64_Extend_i32_r, op_i64_Extend_i32_s, NULL, NULL } },
    { 0, c_m3Type_i64, { op_i64_Extend_u32_r, op_i64_Extend_u32_s, NULL, NULL } },
    { 0, c_m3Type_i64, { op_i64_Trunc_f32_r_r, op_i64_Trunc_f32_r_s, op_i64_Trunc_f32_s_r, op_i64_Trunc_f32_s_s }, Compile_Convert },
    { 0, c_m3Type_i64, { op_u64_Trunc_f32_r_r, op_u64_Trunc_f32_r_s, op_u64_Trunc_f32_s_r, op_u64_Trunc_f32_s_s }, Compile_Convert },
    { 0, c_m3Type_i64, { op_i64_Trunc_f64_r_r, op_i64_Trunc_f64_r_s, op_i64_Trunc_f64_s_r, op_i64_Trunc_f64_s_s }, Compile_Convert },
    { 0, c_m3Type_i64, { op_u64_Trunc_f64_r_r, op_u64_Trunc_f64_r_s, op_u64_Trunc_f64_s_r, op_u64_Trunc_f64_s_s }, Compile_Convert },
    { 0, c_m3Type_f32, { op_f32_Convert_i32_r_r, op_f32_Convert_i32_r_s, op_f32_Convert_i32_s_r, op_f32_Convert_i32_s_s }, Compile_Convert },
    { 0, c_m3Type_f32, { op_f32_Convert_u32_r_r, op_f32_Convert_u32_r_s, op_f32_Convert_u32_s_r, op_f32_Convert_u32_s_s }, Compile_Convert },
    { 0, c_m3Type_f32, { op_f32_Convert_i64_r_r, op_f32_Convert_i64_r_s, op_f32_Convert_i64_s_r, op_f32_Convert_i64_s_s }, Compile_Convert },
    { 0, c_m3Type_f32, { op_f32_Convert_u64_r_r, op_f32_Convert_u64_r_s, op_f32_Convert_u64_s_r, op_f32_Convert_u64_s_s }, Compile_Convert },
    { 0, c_m3Type_f32, { op_f32_Demote_f64_r, op_f32_Demote_f64_s, NULL, NULL } },
    { 0, c_m3Type_f64, { op_f64_Convert_i32_r_r, op_f64_Convert_i32_r_s, op_f64_Convert_i32_s_r, op_f64_Convert_i32_s_s }, Compile_Convert },
    { 0, c_m3Type_f64, { op_f64_Convert_u32_r_r, op_f64_Convert_u32_r_s, op_f64_Convert_u32_s_r, op_f64_Convert_u32_s_s }, Compile_Convert },
    { 0, c_m3Type_f64, { op_f64_Convert_i64_r_r, op_f64_Convert_i64_r_s, op_f64_Convert_i64_s_r, op_f64_Convert_i64_s_s }, Compile_Convert },
    { 0, c_m3Type_f64, { op_f64_Convert_u64_r_r, op_f64_Convert_u64_r_s, op_f64_Convert_u64_s_r, op_f64_Convert_u64_s_s }, Compile_Convert },
    { 0, c_m3Type_f64, { op_f64_Promote_f32_r, op_f64_Promote_f32_s, NULL, NULL } },
    { 0, c_m3Type_i32, { op_i32_Reinterpret_f32_r_r, op_i32_Reinterpret_f32_r_s, op_i32_Reinterpret_f32_s_r, op_i32_Reinterpret_f32_s_s }, Compile_Convert },
    { 0, c_m3Type_i64, { op_i64_Reinterpret_f64_r_r, op_i64_Reinterpret_f64_r_s, op_i64_Reinterpret_f64_s_r, op_i64_Reinterpret_f64_s_s }, Compile_Convert },
    { 0, c_m3Type_f32, { op_f32_Reinterpret_i32_r_r, op_f32_Reinterpret_i32_r_s, op_f32_Reinterpret_i32_s_r, op_f32_Reinterpret_i32_s_s }, Compile_Convert },
    { 0, c_m3Type_f64, { op_f64_Reinterpret_i64_r_r, op_f64_Reinterpret_i64_r_s, op_f64_Reinterpret_i64_s_r, op_f64_Reinterpret_i64_s_s }, Compile_Convert },
    { 0, c_m3Type_void }
};

M3Result Compile_BlockStatements (IM3Compilation o)
{
    M3Result result = m3Err_none;
    while (o->wasm < o->wasmEnd) { emit_stack_dump (o);
        u8 opcode = * (o->wasm++); log_opcode (o, opcode);
        const M3OpInfo * op = & c_operations [opcode];
        M3Compiler compiler = op->compiler;
        if (! compiler)
            compiler = Compile_Operator;
        if (compiler)
            result = (* compiler) (o, opcode);
        else
            result = m3Err_noCompiler;
        o->previousOpcode = opcode;
        if (o->stackIndex > 2000)
            result = m3Err_functionStackOverflow;
        if (result)
            break;
        if (opcode == c_waOp_end || opcode == c_waOp_else)
            break;
    }
    return result;
}

M3Result ValidateBlockEnd (IM3Compilation o, bool * o_copyStackTopToRegister)
{
    M3Result result = m3Err_none;
    * o_copyStackTopToRegister = false;
    if (o->block.type != c_m3Type_none) {
        if (IsStackPolymorphic (o)) {
            {
                result = UnwindBlockStack (o);
                if (result) { goto _catch; }
            }
            {
                result = PushRegister (o, o->block.type);
                if (result) { goto _catch; }
            }
        }
        else {
            i16 initStackIndex = o->block.initStackIndex;
            if (o->block.depth > 0 && initStackIndex != o->stackIndex) {
                if (o->stackIndex == initStackIndex + 1) {
                    * o_copyStackTopToRegister = IsStackTopInSlot (o);
                }
                else {
                    result = "unexpected block stack offset";
                    goto _catch;
                }
            }
        }
    }
    else {
        result = UnwindBlockStack (o);
        if (result) { goto _catch; }
    }
_catch:
    return result;
}

M3Result CompileBlock (IM3Compilation o, u8 i_blockType, u8 i_blockOpcode)
{
    M3Result result;
    M3CompilationScope outerScope = o->block;
    M3CompilationScope * block = & o->block;
    block->outer = & outerScope;
    block->pc = GetPagePC (o->page);
    block->patches = NULL;
    block->type = i_blockType;
    block->initStackIndex = o->stackIndex;
    block->depth ++;
    block->opcode = i_blockOpcode;
    {
        result = Compile_BlockStatements (o);
        if (result) { goto _catch; }
    }
    bool moveStackTopToRegister;
    {
        result = ValidateBlockEnd (o, & moveStackTopToRegister);
        if (result) { goto _catch; }
    }
    if (moveStackTopToRegister) {
        result = MoveStackTopToRegister (o);
        if (result) { goto _catch; }
    }
    PatchBranches (o);
    o->block = outerScope;
_catch:
    return result;
}

M3Result CompileLocals (IM3Compilation o)
{
    M3Result result;
    u32 numLocalBlocks;
    {
        result = ReadLEB_u32 (& numLocalBlocks, & o->wasm, o->wasmEnd);
        if (result) { goto _catch; }
    }
    for (u32 l = 0; l < numLocalBlocks; ++l) {
        u32 varCount;
        i8 waType;
        u8 localType;
        {
            result = ReadLEB_u32 (& varCount, & o->wasm, o->wasmEnd);
            if (result) { goto _catch; }
        }
        {
            result = ReadLEB_i7 (& waType, & o->wasm, o->wasmEnd);
            if (result) { goto _catch; }
        }
        {
            result = NormalizeType (& localType, waType);
            if (result) { goto _catch; }
        }
        while (varCount--) {
            result = PushAllocatedSlot (o, localType);
            if (result) { goto _catch; }
        }
    }
_catch:
    return result;
}

M3Result Compile_ReserveConstants (IM3Compilation o)
{
    M3Result result = m3Err_none;
    u32 numConstants = 0;
    bytes_t wa = o->wasm;
    while (wa < o->wasmEnd) {
        u8 code = * wa++;
        if (code >= 0x41 && code <= 0x44)
            ++numConstants;
    }
    o->firstSlotIndex = o->firstConstSlotIndex = o->constSlotIndex = o->stackIndex;
    numConstants = (((numConstants) < (60)) ? (numConstants) : (60));
    u32 freeSlots = 2000 - o->constSlotIndex;
    if (numConstants <= freeSlots)
        o->firstSlotIndex += numConstants;
    else
        result = m3Err_functionStackOverflow;
    return result;
}

void SetupCompilation (IM3Compilation o)
{
    IM3BranchPatch patches = o->releasedPatches;
    memset (o, 0x0, sizeof (M3Compilation));
    o->releasedPatches = patches;
}

M3Result Compile_Function (IM3Function io_function)
{
    M3Result result = m3Err_none;
    IM3Runtime runtime = io_function->module->runtime;
    IM3Compilation o = & runtime->compilation;
    SetupCompilation (o);
    o->runtime = runtime;
    o->module = io_function->module;
    o->wasm = io_function->wasm;
    o->wasmEnd = io_function->wasmEnd;
    o->page = AcquireCodePage (runtime);

    if (o->page) {
        pc_t pc = GetPagePC (o->page);
        o->block.type = GetFunctionReturnType (io_function);
        o->function = io_function;
        M3FuncType * ft = io_function->funcType;

        for (u32 i = 0; i < GetFunctionNumArgs (io_function); ++i) {
            u8 type = ft->argTypes [i];
            {
                result = PushAllocatedSlot (o, type);
                if (result) { goto _catch; }
            }
        }
        {
            result = CompileLocals (o);
            if (result) { goto _catch; }
        }
        {
            result = Compile_ReserveConstants (o);
            if (result) { goto _catch; }
        }
        o->function->maxStackSlots = o->firstSlotIndex;
        o->numAllocatedExecSlots = 0;
        o->block.initStackIndex = o->stackIndex;
        {
            result = EmitOp (o, op_Entry);
            if (result) { goto _catch; }
        }
        EmitPointer (o, io_function);
        {
            result = Compile_BlockStatements (o);
            if (result) { goto _catch; }
        }
        io_function->compiled = pc;
        u32 numConstants = o->constSlotIndex - o->firstConstSlotIndex;
        io_function->numConstants = numConstants;
        if (numConstants) {
            {
                result = m3Malloc ((void **) & io_function->constants, sizeof (u64) * (numConstants));
                if (result) { goto _catch; }
            }
            memcpy (io_function->constants, o->constants, sizeof (u64) * numConstants);
        }
    }
    else {
        result = m3Err_mallocFailedCodePage;
        goto _catch;
    }

_catch:
    ReleaseCompilationCodePage (o);
    return result;
}
