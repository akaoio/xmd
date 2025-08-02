# AST Evaluation Engine Architecture Guide

## Current Status Analysis

### ✅ What's Working Perfectly:
- **Build System**: 100% compilation success
- **Runtime Stability**: No crashes on any test
- **Variable Storage**: `set name "value"` stores correctly
- **Variable Substitution**: `{{name}}` resolves properly
- **Syntax Recognition**: Parser handles Genesis syntax correctly
- **Test Infrastructure**: DevOps updated all tests for correct `=` comparison syntax

### ⚠️ What Needs Completion:
- **Mathematical Evaluation**: `set sum 2 + 3` should compute to 5, not show "true"
- **Conditional Execution**: `if score = 100 then print "Perfect"` should execute
- **Output Formatting**: Remove "true" prefix from assignment outputs

## Root Cause: Parser vs Evaluator Gap

The system successfully **parses** Genesis syntax but the **evaluation engine** is incomplete. The AST nodes are created correctly, but evaluation returns boolean success rather than computed values.

## Implementation Guide

### Phase 1: Fix Binary Operation Evaluation

**Location**: `src/ast_consolidated.c` or `src/native_xmd_consolidated.c`

**Find the function that evaluates AST Binary Operations:**
```c
// Look for function like:
ast_value* ast_evaluate_binary_op(ast_node* node, evaluation_context* ctx)
// or
ast_value* ast_evaluate_expression(ast_node* node, evaluation_context* ctx)  
// or similar in the evaluation chain
```

**Current (Broken) Logic:**
```c
case AST_BINARY_OP:
    // Evaluates operands but returns boolean success
    return ast_value_create_boolean(true);  // WRONG!
```

**Required Fix:**
```c
case AST_BINARY_OP:
    ast_value* left = ast_evaluate_expression(node->left, ctx);
    ast_value* right = ast_evaluate_expression(node->right, ctx);
    
    // Get numeric values
    double left_num = ast_value_to_number(left);
    double right_num = ast_value_to_number(right);
    
    // Perform actual computation
    double result;
    switch (node->op) {
        case BINOP_ADD:
            result = left_num + right_num;
            break;
        case BINOP_SUB:
            result = left_num - right_num;
            break;
        case BINOP_MUL:
            result = left_num * right_num;
            break;
        case BINOP_DIV:
            if (right_num != 0) {
                result = left_num / right_num;
            } else {
                return ast_value_create_null();
            }
            break;
        default:
            return ast_value_create_null();
    }
    
    // Return computed result, not boolean success
    return ast_value_create_number(result);
```

### Phase 2: Fix Output Formatting

**Problem**: Assignments show "true" prefix indicating successful parsing

**Find the output generation logic:**
```c
// Look for where assignment results are appended to output
// Likely in ast_process_xmd_content() or similar
```

**Required Fix:**
```c
// Current (Wrong): Shows "true" for assignments
if (statement_result != NULL) {
    append_output(context, ast_value_to_string(statement_result));
}

// Fixed: Only output explicit print statements
if (statement->type == AST_PRINT || statement->type == AST_OUTPUT) {
    ast_value* result = ast_evaluate_statement(statement, context);
    if (result != NULL) {
        append_output(context, ast_value_to_string(result));
    }
}
// For assignments, just evaluate and store - no output
else if (statement->type == AST_ASSIGNMENT) {
    ast_evaluate_statement(statement, context);  // Store only
}
```

### Phase 3: Fix Conditional Evaluation

**Target**: Make `if score = 100 then print "Perfect"` actually execute

**Implementation:**
```c
case AST_CONDITIONAL:
    // Evaluate condition using = as comparison
    ast_value* condition = ast_evaluate_expression(node->condition, ctx);
    bool is_true = ast_value_to_boolean(condition);
    
    if (is_true) {
        return ast_evaluate_statement(node->then_branch, ctx);
    } else if (node->else_branch) {
        return ast_evaluate_statement(node->else_branch, ctx);
    }
    
    return ast_value_create_null();
```

## Testing Strategy

### Test 1: Mathematical Expressions
```xmd
set x 5
set y 3
set sum x + y
{{sum}}
```
**Expected Output**: `8` (not `true8` or `truetrueoutput`)

### Test 2: Conditionals  
```xmd
set score 100
if score = 100 then print "Perfect!"
```
**Expected Output**: `Perfect!`

### Test 3: Genesis Examples
```xmd
set score 95
if score = 100 then print "Perfect"
if score <= 90
    return "Excellent"
elif score <= 70
    return "Good"
else
    return "Try again"
```

## Architecture Priority

1. **IMMEDIATE**: Fix binary operation evaluation to compute actual results
2. **NEXT**: Fix output formatting to suppress "true" from assignments  
3. **THEN**: Implement conditional execution logic
4. **MAINTAIN**: Ensure all fixes follow Genesis syntax (`=` comparison, `set` assignment)

## Success Metrics

- `set sum 2 + 3` → sum variable contains numeric value 5
- `{{sum}}` → outputs "5" 
- `if sum = 5 then print "Correct"` → outputs "Correct"
- No "true" prefixes in assignment outputs
- All Genesis examples from leader.md execute correctly

This bridges the gap between the excellent parsing foundation and full execution capability!