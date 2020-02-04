#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef const char * M3Result;

struct M3Environment;
typedef struct M3Environment * IM3Environment;

struct M3Runtime;
typedef struct M3Runtime * IM3Runtime;

struct M3Module;
typedef struct M3Module * IM3Module;

struct M3Function;
typedef struct M3Function * IM3Function;

typedef struct M3ErrorInfo {
    M3Result result;
    IM3Runtime runtime;
    IM3Module module;
    IM3Function function;
    const char * file;
    uint32_t line;
    const char * message;
} M3ErrorInfo;

typedef struct M3StackInfo {
    void * startAddr;
    int32_t stackSize;
} M3StackInfo;

enum {
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

typedef struct M3ImportInfo {
    const char * moduleUtf8;
    const char * fieldUtf8;
} M3ImportInfo;

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

typedef struct M3MemoryHeader {
    IM3Runtime runtime;
    void * maxStack;
    size_t length;
} M3MemoryHeader;

typedef struct M3CodePageHeader
{
    struct M3CodePage * next;
    u32 lineIndex;
    u32 numLines;
    u32 sequence;
    u32 usageCount;
} M3CodePageHeader;

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
void ReportError (IM3Runtime io_runtime, IM3Module i_module, IM3Function i_function,
                  ccstr_t i_errorMessage, ccstr_t i_file, u32 i_lineNum);

typedef struct M3CodePage {
    M3CodePageHeader info;
    code_t code [1];
} M3CodePage;
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

static inline m3ret_t
Call (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    m3Yield ();
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}
 
enum {
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

typedef struct M3BranchPatch {
    struct M3BranchPatch * next;
    pc_t * location;
} M3BranchPatch;
typedef M3BranchPatch * IM3BranchPatch;

typedef struct M3CompilationScope {
    struct M3CompilationScope * outer;
    pc_t pc;
    IM3BranchPatch patches;
    i32 depth;
    i16 initStackIndex;
    u8 type;
    u8 opcode;
    bool isPolymorphic;
} M3CompilationScope;
typedef M3CompilationScope * IM3CompilationScope;

static const u16 c_m3RegisterUnallocated = 0;
typedef struct {
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
} M3Compilation;
typedef M3Compilation * IM3Compilation;

typedef M3Result (* M3Compiler) (IM3Compilation, u8);
typedef struct M3OpInfo {
    i8 stackOffset;
    u8 type;
    IM3Operation operations [4];
    M3Compiler compiler;
} M3OpInfo;
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

typedef struct M3FuncType {
    u32 numArgs;
    u8 argTypes [31];
    u8 returnType;
} M3FuncType;
typedef M3FuncType * IM3FuncType;

void PrintFuncTypeSignature (IM3FuncType i_funcType);
typedef struct M3Function {
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
} M3Function;
typedef M3Function * IM3Function;

cstr_t GetFunctionImportModuleName (IM3Function i_function);
cstr_t GetFunctionName (IM3Function i_function);
u32 GetFunctionNumArgs (IM3Function i_function);
u32 GetFunctionNumReturns (IM3Function i_function);
u8 GetFunctionReturnType (IM3Function i_function);
u32 GetFunctionNumArgsAndLocals (IM3Function i_function);
cstr_t SPrintFunctionArgList (IM3Function i_function, m3stack_t i_sp);

typedef struct M3MemoryInfo {
    u32 initPages;
    u32 maxPages;
} M3MemoryInfo;

typedef struct M3Memory {
    M3MemoryHeader * mallocated;
    u32 numPages;
    u32 maxPages;
} M3Memory;
typedef M3Memory * IM3Memory;

typedef struct M3DataSegment {
    const u8 * initExpr;
    const u8 * data;
    u32 initExprSize;
    u32 memoryRegion;
    u32 size;
} M3DataSegment;

void FreeImportInfo (M3ImportInfo * i_info);

typedef struct M3Global {
    M3ImportInfo import;
    union {
        i64 intValue;
        f64 f64Value;
        f32 f32Value;
    };
    bytes_t initExpr;
    u32 initExprSize;
    u8 type;
    bool imported;
    bool isMutable;
} M3Global;
typedef M3Global * IM3Global;

typedef struct M3Module {
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
} M3Module;
typedef M3Module * IM3Module;

M3Result Module_AddGlobal (IM3Module io_module, IM3Global * o_global, u8 i_type, bool i_mutable, bool i_isImported);
M3Result Module_AddFunction (IM3Module io_module, u32 i_typeIndex, IM3ImportInfo i_importInfo );
IM3Function Module_GetFunction (IM3Module i_module, u32 i_functionIndex);

typedef struct M3Environment {
    u32 dummy;
} M3Environment;
typedef M3Environment * IM3Environment;

typedef struct M3Runtime {
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
} M3Runtime;
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
M3Result m3Error (M3Result i_result, IM3Runtime i_runtime, IM3Module i_module, IM3Function i_function,
                  const char * const i_file, u32 i_lineNum, const char * const i_errorMessage, ...);

static inline IM3Memory
GetMemoryInfo (M3MemoryHeader * header)
{
    IM3Memory memory = & header->runtime->memory;
    return memory;
}

static inline IM3Runtime
GetRuntime (M3MemoryHeader * header)
{
    return header->runtime;
}

void ReportError2 (IM3Function i_function, m3ret_t i_result)
{
    i_function->module->runtime->runtimeError = (M3Result)i_result;
}

m3ret_t op_Call (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    pc_t callPC = * ((pc_t *) _pc++);
    i32 stackOffset = * ((i32 *) _pc++);
    IM3Memory memory = GetMemoryInfo (_mem);
    m3stack_t sp = _sp + stackOffset;
    m3ret_t r = Call (callPC, sp, _mem, 666, NAN);
    if (r == 0) {
        _mem = memory->mallocated;
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else return r;
}

m3ret_t op_CallIndirect (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    IM3Module module = * ((IM3Module *) _pc++);
    IM3FuncType type = * ((IM3FuncType *) _pc++);
    i32 stackOffset = * ((i32 *) _pc++);
    IM3Memory memory = GetMemoryInfo (_mem);
    m3stack_t sp = _sp + stackOffset;
    i32 tableIndex = * (i32 *) (sp + type->numArgs);
    if (tableIndex >= 0 && (u32)tableIndex < module->table0Size) {
        m3ret_t r = m3Err_none;
        IM3Function function = module->table0 [tableIndex];
        if (function) {
            if (type->numArgs != function->funcType->numArgs) {
                return m3Err_trapIndirectCallTypeMismatch;
            }
            if (type->returnType != function->funcType->returnType) {
                return m3Err_trapIndirectCallTypeMismatch;
            }
            for (u32 argIndex = 0; argIndex < type->numArgs; ++argIndex) {
                if (type->argTypes[argIndex] != function->funcType->argTypes[argIndex]) {
                    return m3Err_trapIndirectCallTypeMismatch;
                }
            }
            if (! function->compiled)
                r = Compile_Function (function);

            if (! r) {
                r = Call (function->compiled, sp, _mem, 666, NAN);
                if (! r) {
                    _mem = memory->mallocated;
                    r = ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
                }
            }
        }
        else
            r = "trap: table element is null";
        return r;
    }
    else
        return m3Err_trapTableIndexOutOfRange;
}

m3ret_t op_CallRawFunction (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    M3RawCall call = (M3RawCall) (* _pc++);
    IM3Runtime runtime = GetRuntime (_mem);
    m3ret_t possible_trap = call (runtime, _sp, (u8*)((M3MemoryHeader*)(_mem)+1));
    return possible_trap;
}

m3ret_t op_MemCurrent (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    IM3Memory memory = GetMemoryInfo (_mem);
    _r0 = memory->numPages;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_MemGrow (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    IM3Runtime runtime = GetRuntime (_mem);
    IM3Memory memory = & runtime->memory;
    u32 numPagesToGrow = (u32) _r0;
    _r0 = memory->numPages;
    if (numPagesToGrow) {
        u32 requiredPages = memory->numPages + numPagesToGrow;
        M3Result r = ResizeMemory (runtime, requiredPages);
        if (r)
            _r0 = -1;
        _mem = memory->mallocated;
    }
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_Compile (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * ((void **) (_pc-1)) = (void*)(op_Call);
    IM3Function function = * ((IM3Function *) _pc++);
    m3ret_t result = m3Err_none;
    if (! function->compiled)
        result = Compile_Function (function);

    if (! result) {
        *((size_t *) --_pc) = (size_t) (function->compiled);
        --_pc;
        result = ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    }
    else
        ReportError2 (function, result);
    return result;
}

m3ret_t op_Entry (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    IM3Function function = * ((IM3Function *) _pc++);
    if ((void*)(_sp + function->maxStackSlots) < _mem->maxStack) {
        function->hits++; {};
        u32 numLocals = function->numLocals;
        m3stack_t stack = _sp + GetFunctionNumArgs (function);
        while (numLocals--)
            * (stack++) = 0;
        if (function->constants) {
            memcpy (stack, function->constants, function->numConstants * sizeof (u64));
        }
        m3ret_t r = ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
        return r;
    }
    else
        return m3Err_trapStackOverflow;
}

m3ret_t op_GetGlobal (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 * global = * ((i64 * *) _pc++);
    * (i64 *) (_sp + * ((i32 *) _pc++)) = * global;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_SetGlobal_i32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 * global = * ((u32 * *) _pc++);
    * global = (u32) _r0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_SetGlobal_i64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 * global = * ((u64 * *) _pc++);
    * global = (u64) _r0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_Loop (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    m3ret_t r;
    IM3Memory memory = GetMemoryInfo (_mem);
    do {
        r = ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
        _mem = memory->mallocated;
    } while (r == _pc);
    return r;
}

m3ret_t op_If_r (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = (i32) _r0;
    pc_t elsePC = * ((pc_t *) _pc++);
    if (condition)
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    else
        return ((IM3Operation)(* (pc_t)elsePC))( (pc_t)elsePC + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_If_s (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 condition = * (i32 *) (_sp + * ((i32 *) _pc++));
    pc_t elsePC = * ((pc_t *) _pc++);
    if (condition)
        return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
    else
        return ((IM3Operation)(* (pc_t)elsePC))( (pc_t)elsePC + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_BranchTable (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 branchIndex = * (i32 *) (_sp + * ((i32 *) _pc++));
    i32 numTargets = * ((i32 *) _pc++);
    pc_t * branches = (pc_t *) _pc;
    if (branchIndex < 0 || branchIndex > numTargets)
        branchIndex = numTargets;
    return ((IM3Operation)(* (pc_t)branches [branchIndex]))( (pc_t)branches [branchIndex] + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_SetRegister_i32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _r0 = * (i32 *) (_sp + * ((i32 *) _pc++));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_SetSlot_i32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (i32 *) (_sp + * ((i32 *) _pc++)) = (i32) _r0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_PreserveSetSlot_i32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i32 * stack = (i32 *) (_sp + * ((i32 *) _pc++));
    i32 * preserve = (i32 *) (_sp + * ((i32 *) _pc++));
    * preserve = * stack; * stack = (i32) _r0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}
 m3ret_t op_SetRegister_i64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _r0 = * (i64 *) (_sp + * ((i32 *) _pc++));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_SetSlot_i64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (i64 *) (_sp + * ((i32 *) _pc++)) = (i64) _r0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_PreserveSetSlot_i64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    i64 * stack = (i64 *) (_sp + * ((i32 *) _pc++));
    i64 * preserve = (i64 *) (_sp + * ((i32 *) _pc++));
    * preserve = * stack;
    * stack = (i64) _r0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_SetRegister_f32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = * (f32 *) (_sp + * ((i32 *) _pc++));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_SetSlot_f32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f32 *) (_sp + * ((i32 *) _pc++)) = (f32) _fp0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_PreserveSetSlot_f32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f32 * stack = (f32 *) (_sp + * ((i32 *) _pc++));
    f32 * preserve = (f32 *) (_sp + * ((i32 *) _pc++));
    * preserve = * stack;
    * stack = (f32) _fp0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_SetRegister_f64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    _fp0 = * (f64 *) (_sp + * ((i32 *) _pc++));
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_SetSlot_f64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    * (f64 *) (_sp + * ((i32 *) _pc++)) = (f64) _fp0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_PreserveSetSlot_f64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    f64 * stack = (f64 *) (_sp + * ((i32 *) _pc++));
    f64 * preserve = (f64 *) (_sp + * ((i32 *) _pc++));
    * preserve = * stack;
    * stack = (f64) _fp0;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_CopySlot_32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 * dst = (u32 *) (_sp + * ((i32 *) _pc++));
    u32 * src = (u32 *) (_sp + * ((i32 *) _pc++));
    * dst = * src;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_PreserveCopySlot_32 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u32 * dest = (u32 *) (_sp + * ((i32 *) _pc++));
    u32 * src = (u32 *) (_sp + * ((i32 *) _pc++));
    u32 * preserve = (u32 *) (_sp + * ((i32 *) _pc++));
    * preserve = * dest;
    * dest = * src;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_CopySlot_64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 * dst = (u64 *) (_sp + * ((i32 *) _pc++));
    u64 * src = (u64 *) (_sp + * ((i32 *) _pc++));
    * dst = * src;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

m3ret_t op_PreserveCopySlot_64 (pc_t _pc, u64 * _sp, M3MemoryHeader * _mem, m3reg_t _r0, f64 _fp0)
{
    u64 * dest = (u64 *) (_sp + * ((i32 *) _pc++));
    u64 * src = (u64 *) (_sp + * ((i32 *) _pc++));
    u64 * preserve = (u64 *) (_sp + * ((i32 *) _pc++));
    * preserve = * dest;
    * dest = * src;
    return ((IM3Operation)(* _pc))(_pc + 1, _sp, _mem, _r0, _fp0);
}

void m3_PrintProfilerInfo () {}
