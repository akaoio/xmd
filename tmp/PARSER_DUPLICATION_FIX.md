# Parser Has Error Duplication Fix

## Issue
`parser_has_error()` is duplicated with conflicting implementations:

### 1. parser_utils.c:120 (KEEP THIS)
```c
bool parser_has_error(void) {
    if (!global_parser_state) {
        return false;
    }
    
    return global_parser_state->has_error;
}
```
This uses the proper global parser state structure.

### 2. ast_consolidated.c:434 (REMOVE THIS)
```c
bool parser_has_error(void) {
    return g_parser_error;
}
```
This uses a simple global variable, less sophisticated.

## Solution

1. **Remove the duplicate** from ast_consolidated.c:
   - Delete lines 434-436 (the function implementation)
   - Keep the declaration at line 431 (if it's a declaration)
   - The file already has access to parser_utils.c version

2. **Verify usage** in ast_consolidated.c:
   - Line 448 uses parser_has_error() - this will use parser_utils.c version
   - No changes needed to usage

3. **Update includes** if needed:
   - Ensure ast_consolidated.c includes parser_internal.h
   - This provides access to the correct parser_has_error()

## Commands to Fix

```bash
# Remove the duplicate function from ast_consolidated.c
# Edit lines 434-436 to remove the duplicate implementation
```

## Testing
After fix, verify:
1. Build succeeds
2. Parser error handling still works
3. No linking errors about duplicate symbols

This eliminates tech debt per Genesis directive: NO DUPLICATIONS!