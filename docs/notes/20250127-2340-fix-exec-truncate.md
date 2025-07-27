# Fix Exec Command Truncate Issue

## Problem
- Direct `exec` in multiline blocks gets truncated
- `set var = exec` works fine (uses dynamic allocation)
- `print(var)` of exec output also truncated

## Root Cause
In `process_directive()`, exec commands use `process_exec()` which has fixed buffer.
Meanwhile, `process_xmd_content_enhanced()` uses `process_exec_dynamic()` for single-line exec.

## Solution
Update `process_directive()` to use `process_exec_dynamic()` for exec commands.

## Files to Modify
- src/xmd_processor/process_directive/process_directive.c

## Testing
- Test with tree command that produces >32KB output
- Verify all 3 test cases work without truncation