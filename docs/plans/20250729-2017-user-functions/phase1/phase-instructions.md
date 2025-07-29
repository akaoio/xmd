# Phase 1: Core AST Extensions

## Objective
Add basic infrastructure for user-defined functions to the AST system.

## Tasks

### 1. Extend AST Node Types
**File**: `include/ast_node.h`
- Add `AST_FUNCTION_DEF` to `ast_node_type` enum
- Add `function_def` struct to `ast_node_data` union

### 2. Create Function Definition Structure
**New struct in** `include/ast_node.h`:
```c
typedef struct {
    char* name;                    // Function name
    char** parameters;             // Parameter names array
    size_t parameter_count;        // Number of parameters
    ast_node* body;               // Function body (block statement)
} ast_function_def;
```

### 3. Function Storage
**File**: `include/ast_evaluator.h`
- Add function storage to `ast_evaluator` struct
- Create function lookup mechanism

### 4. AST Creation Function
**New file**: `src/ast_create_function_def/ast_create_function_def.c`
- Function to create `AST_FUNCTION_DEF` nodes

### 5. Parser Extension  
**File**: `src/ast_parser/*.c` (identify correct parser file)
- Add parsing for `function name param1 param2` syntax
- Handle function body parsing

### 6. Function Storage/Lookup
**New files**:
- `src/ast_evaluator_register_function/ast_evaluator_register_function.c`
- `src/ast_evaluator_lookup_function/ast_evaluator_lookup_function.c`

### 7. Update Function Call Handler
**File**: `src/ast_evaluate_function_call/ast_evaluate_function_call.c`
- Check for user-defined functions before built-ins
- Call user functions with parameter binding

### 8. Basic Test
**New file**: `test/function/test_user_functions_basic.c`
- Test function definition parsing
- Test function storage and lookup
- Test basic function calls

## Implementation Order
1. AST node extensions
2. Function storage structures  
3. AST creation functions
4. Parser updates
5. Function registration/lookup
6. Function call integration
7. Basic tests

## Success Criteria for Phase 1
- Parse `function add a b` without errors
- Store function in evaluator context
- Look up function by name
- Basic function call resolution works
- Unit tests pass