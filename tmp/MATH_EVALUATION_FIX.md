# Mathematical Expression Evaluation Fix Guide

## Problem Statement

Currently, mathematical expressions like `set sum 2 + 3` parse correctly but don't evaluate to numeric results. Instead, they show output like "true + 3" indicating the evaluation returns boolean success rather than computed values.

## Root Cause Analysis

The AST evaluation system is returning boolean success indicators instead of actual computed values. This happens in the expression evaluation chain where assignments are treated as operations that succeed/fail rather than operations that produce values.

## Fix Implementation Guide

### Step 1: Locate the Binary Operation Evaluator

Search for the function that evaluates binary operations in the AST:
```bash
grep -n "AST_BINARY_OP" src/ast_consolidated.c
grep -n "evaluate.*binary" src/native_xmd_consolidated.c
```

### Step 2: Fix the Evaluation Logic

The evaluation function likely looks like this (broken):
```c
// Current (broken) implementation
case AST_BINARY_OP:
    ast_value* left = ast_evaluate_expression(node->data.binary_op.left, context);
    ast_value* right = ast_evaluate_expression(node->data.binary_op.right, context);
    // Returns success boolean instead of computed value
    return ast_value_create_boolean(true);
```

Fix it to compute actual values:
```c
// Fixed implementation
case AST_BINARY_OP:
    ast_value* left = ast_evaluate_expression(node->data.binary_op.left, context);
    ast_value* right = ast_evaluate_expression(node->data.binary_op.right, context);
    
    // Handle different operations
    switch (node->data.binary_op.op) {
        case BINOP_ADD:
            if (left->type == AST_VALUE_NUMBER && right->type == AST_VALUE_NUMBER) {
                double result = left->data.number + right->data.number;
                return ast_value_create_number(result);
            }
            break;
        case BINOP_SUB:
            if (left->type == AST_VALUE_NUMBER && right->type == AST_VALUE_NUMBER) {
                double result = left->data.number - right->data.number;
                return ast_value_create_number(result);
            }
            break;
        case BINOP_MUL:
            if (left->type == AST_VALUE_NUMBER && right->type == AST_VALUE_NUMBER) {
                double result = left->data.number * right->data.number;
                return ast_value_create_number(result);
            }
            break;
        case BINOP_DIV:
            if (left->type == AST_VALUE_NUMBER && right->type == AST_VALUE_NUMBER) {
                if (right->data.number != 0) {
                    double result = left->data.number / right->data.number;
                    return ast_value_create_number(result);
                }
                // Handle division by zero
                return ast_value_create_null();
            }
            break;
    }
    
    // Fallback for unhandled cases
    return ast_value_create_null();
```

### Step 3: Fix Variable Reference Evaluation

Variables in expressions need to resolve to their stored values:
```c
case AST_IDENTIFIER:
    // Look up variable value
    variable* var = store_get(context->variables, node->data.identifier.name);
    if (var && var->type == VAR_NUMBER) {
        return ast_value_create_number(var->value.number);
    } else if (var && var->type == VAR_STRING) {
        return ast_value_create_string(var->value.string);
    }
    return ast_value_create_null();
```

### Step 4: Fix Output Formatting

The output system should not append "true" for assignments. Find where output is generated:

```c
// In ast_process_xmd_content or similar
if (statement_type == AST_ASSIGNMENT) {
    // Don't append output for assignments
    // Just evaluate and store the result
    ast_evaluate_statement(statement, context);
} else if (statement_type == AST_PRINT || statement_type == AST_OUTPUT) {
    // Only append output for explicit output statements
    ast_value* result = ast_evaluate_statement(statement, context);
    append_output(context, ast_value_to_string(result));
}
```

### Step 5: Test Cases

Create these test cases to verify the fix:

**test_math_basic.xmd**:
```xmd
set x 5
set y 3
set sum x + y
set diff x - y
set prod x * y
set quot x / y
output "Sum: {{sum}}, Diff: {{diff}}, Prod: {{prod}}, Quot: {{quot}}"
```

Expected output:
```
Sum: 8, Diff: 2, Prod: 15, Quot: 1.666667
```

**test_math_complex.xmd**:
```xmd
set a 10
set b 20
set c 30
set result a + b * 2 - c / 3
output "Result: {{result}}"
```

Expected output (with proper operator precedence):
```
Result: 40
```

### Step 6: Debug Strategy

If the fix doesn't work immediately:

1. Add debug prints in the evaluation function:
```c
printf("DEBUG: Evaluating binary op %d with left=%f, right=%f\n", 
       node->data.binary_op.op, left->data.number, right->data.number);
```

2. Check that number parsing works:
```c
printf("DEBUG: Parsed number literal: %f\n", node->data.number.value);
```

3. Verify variable storage:
```c
printf("DEBUG: Stored variable %s with value %f\n", name, value);
```

## Common Pitfalls to Avoid

1. **Type Checking**: Always check that operands are numbers before arithmetic
2. **Memory Management**: Free temporary ast_values after use
3. **Division by Zero**: Handle this edge case gracefully
4. **Variable Resolution**: Ensure variables resolve to their stored values
5. **Output Suppression**: Don't output "true" for assignments

## Success Criteria

When properly fixed:
- `set x 5` should store 5 in x (no output)
- `set sum 2 + 3` should store 5 in sum (no output)
- `output "{{sum}}"` should display "5"
- Complex expressions should follow mathematical precedence

## Architecture Note

This fix maintains the pure AST architecture. The evaluation happens entirely within the AST system without falling back to string manipulation. This aligns with the Genesis directive to use only AST parsing.