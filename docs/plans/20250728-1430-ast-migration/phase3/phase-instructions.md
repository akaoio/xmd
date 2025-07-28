# Phase 3: Complete String Parser Purge

## Objective
Completely remove and purge all string-based parsing functions identified in the codebase, replacing them with AST-based implementations.

## Priority Order (High to Low Impact)

### 1. Core Expression/Condition Functions (CRITICAL)
- `evaluate_condition()` → `ast_evaluate_condition()`
- `evaluate_concatenation_expression()` → `ast_evaluate_expression()`
- `parse_array_literal()` → `ast_parse_array_literal()`

### 2. Directive Processing Functions (HIGH)
- `process_directive()` → Already done, but verify complete replacement
- `process_for()` → `ast_process_for()`
- `process_print_function()` → `ast_process_function_call()`
- `process_cmd_function()` → `ast_process_function_call()`

### 3. Variable/Template Substitution (HIGH)
- `substitute_variables()` → `ast_substitute_variables()`
- Template extraction functions → AST-based template parser

### 4. Content Processing (MEDIUM)
- `process_xmd_content_*()` → AST-based content processor
- `process_multiline_directive_enhanced()` → AST-based multiline processor

### 5. Utility and Validation (LOW)
- `xmd_validate_syntax()` → AST-based validator
- `is_multiline_directive()` → AST-based detection

## Implementation Strategy

### Step 1: Replace Core Functions
Create AST-based replacements for critical parsing functions first:
- `src/ast_evaluate_condition/ast_evaluate_condition.c`
- `src/ast_parse_array_literal/ast_parse_array_literal.c`
- Update all callers to use AST functions

### Step 2: Replace Process Functions
- Extend existing AST directive processor
- Create AST-based loop and function processors
- Replace all process_* function calls

### Step 3: Replace Variable Substitution
- Create AST-based variable reference parser
- Replace template variable substitution with AST

### Step 4: Purge Files
- Delete all string parsing function files
- Remove includes and references
- Update CMakeLists.txt to remove deleted files

## File Structure (following rules 1-3)
```
src/ast_evaluate_condition/ast_evaluate_condition.c
src/ast_parse_array_literal/ast_parse_array_literal.c
src/ast_process_for/ast_process_for.c
src/ast_substitute_variables/ast_substitute_variables.c
```

## Tests (rule 4)
- Extend existing AST parser tests
- Verify all XMD processor tests still pass
- Add tests for new AST functions

## Verification Strategy
- Grep for `strchr`, `strstr`, `strncmp` in parsing contexts
- Ensure no manual string tokenization remains
- All tests pass after string parser removal
- Build succeeds with all string parsing files deleted