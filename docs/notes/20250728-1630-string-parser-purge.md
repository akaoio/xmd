# Complete String Parser Purge

## Current Status
- ✅ process_set.c replaced with AST-based parsing
- ✅ Complete AST infrastructure implemented and tested
- 🔄 Need to identify and purge ALL remaining string parsing

## String Parsing Locations to Remove

### 1. Expression Evaluation Functions
- `evaluate_concatenation_expression()` - string-based expression parsing
- `parse_array_literal()` - string-based array parsing
- `evaluate_condition()` - string-based condition evaluation

### 2. Process Functions Using String Parsing
- `process_directive.c` - command extraction with strchr/strcmp
- `process_if.c` - condition parsing with string manipulation
- `process_script_block.c` - expression parsing with string operations

### 3. Multiline Processing
- `process_multiline_directive_enhanced.c` - line-by-line string tokenization
- Manual string splitting and directive detection

## AST Replacement Strategy

### Replace with AST Functions
- `evaluate_concatenation_expression()` → `ast_evaluate_expression()`
- `parse_array_literal()` → `ast_parse_array_literal()`
- `evaluate_condition()` → `ast_evaluate_conditional_expression()`
- `process_directive()` → `ast_process_directive()`

### Integration Points
- All string parsing functions must be replaced with AST equivalents
- Maintain same external API for backward compatibility
- Ensure all tests continue to pass after replacement

## Purge Verification
- Grep for `strchr`, `strstr`, `strncmp` in parsing contexts
- Remove all manual string tokenization
- Verify no string manipulation in expression/directive parsing
- Test all functionality after complete removal

## Implementation Order
1. Create AST-based replacements for remaining functions
2. Replace function calls throughout codebase
3. Delete string parsing function files
4. Update includes to remove string parsing headers
5. Verify build and test success