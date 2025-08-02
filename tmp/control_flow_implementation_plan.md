# Control Flow Implementation Plan

## Status: EMERGENCY REDESIGN - Waiting for Developer2 Parser Redesign

### CRITICAL DISCOVERY:
Parser fundamentally misunderstands Genesis syntax. Current parser treats ALL commas as arrays - WRONG!

### Genesis Control Flow Syntax (Correct):
1. **If/Then Forms**:
   - Single line: `if score = 100 then print "Wowww"`
   - Block form: `if score <= 90` + indented block
   - Comparison: Use `=` not `==`

2. **Range Loops**:
   - Correct: `for i in 1 .. 5` (spaces around ..)
   - Range: `for i in min .. max`

3. **Break/Continue**:
   - With then: `if i = 4 then break`
   - Block form: `if condition` + `break` on next line

4. **Multiple Variables**:
   - Pattern 1: `set a 1, b 2, c "3"` → creates THREE variables (not array)
   - Must work in loops for proper iteration

### Missing Evaluation Functions to Implement:

1. **ast_evaluate_loop(ast_node* node, ast_evaluator* evaluator)**
   - Handle AST_LOOP nodes
   - Support range syntax: `for i in 1..5`
   - Support space-separated values: `for item in apple orange banana`
   - Set loop variable in evaluator context
   - Execute loop body for each iteration
   - Handle break/continue statements

2. **ast_evaluate_while_loop(ast_node* node, ast_evaluator* evaluator)**
   - Handle AST_WHILE_LOOP nodes
   - Evaluate condition expression
   - Execute body while condition is true
   - Safety limit to prevent infinite loops (1000 iterations max)
   - Support variable increment in body
   - Handle break/continue statements

3. **ast_evaluate_break(ast_node* node, ast_evaluator* evaluator)**
   - Handle AST_BREAK nodes
   - Signal loop exit via error mechanism or context flag
   - Clean up loop context
   - Return appropriate value to interrupt loop

4. **ast_evaluate_continue(ast_node* node, ast_evaluator* evaluator)**
   - Handle AST_CONTINUE nodes
   - Signal skip to next iteration
   - Clean up current iteration context
   - Return appropriate value to continue loop

### Integration Points:

1. Add cases to main ast_evaluate() switch statement:
   ```c
   case AST_LOOP:
       return ast_evaluate_loop(node, evaluator);
   case AST_WHILE_LOOP:
       return ast_evaluate_while_loop(node, evaluator);
   case AST_BREAK:
       return ast_evaluate_break(node, evaluator);
   case AST_CONTINUE:
       return ast_evaluate_continue(node, evaluator);
   ```

2. Loop context tracking:
   - Add loop_depth counter to evaluator
   - Track current loop for break/continue
   - Restore context after loop completion

### Testing Strategy:
- Use test_control_flow.xmd for validation
- Test range loops, while loops, break/continue
- Verify integration with function calls when available
- Test nested loops and complex control flow

### Coordination Note:
Following Orchestrator's sequential plan - waiting for Developer2 to complete function implementation first to avoid conflicts.