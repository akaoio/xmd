# XMD Runtime Crash Analysis - 2025-07-31

## Commands That Work (No Crash)
- `./build/xmd version` ✅ - Returns version info successfully
- `./build/xmd --help` ✅ - Shows usage information
- `./build/xmd -h` ✅ - Shows help

## Commands That Crash (Segfault)
- `./build/xmd process test_minimal.xmd` ❌ - Aborted
- `./build/xmd config` ❌ - Aborted
- `echo "Hello" | ./build/xmd` ❌ - Aborted
- `./build/xmd process <any_file>` ❌ - All file processing crashes

## Crash Pattern Analysis
1. **Static commands work**: version, help (no file processing)
2. **All processing crashes**: Any command that processes content fails
3. **File vs stdin irrelevant**: Both file input and stdin crash
4. **Crash is immediate**: Happens before any processing begins

## Hypothesis
The crash occurs in the initialization of the processor or file handling system, not in AST parsing specifically. The version/help commands bypass the processing pipeline entirely.

## Test Files Attempted
- `test_minimal.xmd` (just "Hello World") - Crash
- `test_debug.xmd` (XMD directives) - Crash
- `test_ast_math.xmd` (math expressions) - Crash
- stdin input - Crash

## Updated Analysis After Team "Fixes"

**Team Claims vs Reality:**
- Team claims: Runtime crisis resolved, minimal main.c works
- Reality: System still crashes on all `process` commands

**Current main.c Analysis (Post-Fix):**
- ✅ `print_version()` works (calls `xmd_get_version()`)
- ✅ `print_usage()` works (no library calls)
- ❌ `cmd_process_simple()` crashes (calls library functions)

**Crash Location Analysis:**
The crash occurs in `cmd_process_simple()` at one of these calls:
1. `xmd_config_create_default()` (line 34)
2. `xmd_processor_create()` (line 40)
3. `xmd_process_file()` (line 47)

**Critical Finding:**
The "minimal main.c" is not the issue. The crash is in the XMD library functions themselves, likely in processor initialization or the pure AST system implementation.

## Next Steps
1. Debug library function crashes (xmd_processor_create, xmd_process_file)
2. Test individual library functions in isolation
3. The AST system or processor implementation has fundamental runtime issues