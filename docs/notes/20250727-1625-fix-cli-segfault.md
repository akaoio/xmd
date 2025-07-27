# Fix CLI Segfault in Shorthand Processing

**Date:** 2025-07-27 16:25  
**Author:** Claude  
**Status:** Bug fix for segmentation fault in CLI processing

## Problem Analysis

**Segfault occurs in:** `store_destroy()` at line 21
**Root cause:** Invalid pointer (0x1) passed to `store_destroy()`
**Call stack:**
1. `main()` → `cmd_process()` 
2. `cmd_process()` → `cli_process_file()`
3. `cli_process_file()` → `xmd_processor_free()`
4. `xmd_processor_free()` → `xmd_cleanup()`
5. `xmd_cleanup()` → `store_destroy(ctx->global_variables)` ← CRASH

## Root Cause

In `cli_process_file()`, we create TWO separate stores:
1. `var_store = store_create()` (line 77)
2. `xmd_handle = xmd_init()` which creates `ctx->global_variables`

Then we call both:
- `store_destroy(var_store)` 
- `xmd_processor_free(xmd_handle)` → `store_destroy(ctx->global_variables)`

**Problem:** Double cleanup or corrupted pointer in `ctx->global_variables`.

## Solution Strategy

Following INSTRUCTIONS.md Rule 13 (error handling) and Rule 14 (memory management):

1. **Fix memory corruption** in `xmd_init()` or `store_create()`
2. **Add null pointer validation** in `store_destroy()`
3. **Eliminate duplicate store creation** in `cli_process_file()`

## Implementation Plan

1. Add validation to `store_destroy()` 
2. Fix `cli_process_file()` to use single store
3. Test with simple cases first
4. Verify with gdb if needed

Following Rule 2: one function per file, will create separate validation function if needed.