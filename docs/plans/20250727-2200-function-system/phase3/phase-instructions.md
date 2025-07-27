# Phase 3: Function Execution Engine

## Objective
Implement function call resolution, execution, and return value handling.

## Function Call Syntax
```javascript
// Simple calls
greet("World")
add(5, 3)

// Nested calls
print(greet("XMD"))
cmd("echo " + add(2, 3))

// Variable usage
set result = add(x, y)
print(result)
```

## Components to Build

### 1. Function Call Parser
- **File**: `src/function/parse_function_call/parse_function_call.c`
- **Purpose**: Parse function call syntax and extract arguments
- **Handle**: `func()`, `func(arg)`, `func(a, b, c)`

### 2. Argument Evaluator
- **File**: `src/function/evaluate_arguments/evaluate_arguments.c`
- **Purpose**: Evaluate arguments before passing to function
- **Handle**: Variables, strings, numbers, nested calls

### 3. Function Executor
- **File**: `src/function/execute_function/execute_function.c`
- **Purpose**: Execute user-defined function with arguments
- **Process**: Create scope, bind parameters, execute body, return result

### 4. Scope Manager
- **File**: `src/function/scope_manager/scope_manager.c`
- **Purpose**: Manage local variable scope during function execution
- **Operations**: create_scope, bind_parameter, resolve_variable, destroy_scope

### 5. Return Value Handler
- **File**: `src/function/return_handler/return_handler.c`
- **Purpose**: Handle function return statements and values
- **Support**: `return value;`, `return "string";`, `return variable;`

## Function Call Processor
- **File**: `src/xmd_processor/process_function_call/process_function_call.c`
- **Purpose**: Main entry point for function call processing
- **Integration**: Modify `process_directive.c` to recognize function calls

## Execution Flow
1. Parse function call → extract name and arguments
2. Lookup function in registry → get function definition
3. Evaluate arguments → resolve variables and expressions
4. Create local scope → bind parameters to arguments
5. Execute function body → process XMD directives in function context
6. Handle return → extract return value and cleanup scope
7. Return result → substitute function call with result

## Advanced Features
- **Recursion**: Support for recursive function calls
- **Nested Calls**: Functions calling other functions
- **Error Handling**: Meaningful errors for missing functions/parameters
- **Type Coercion**: Automatic string/number conversion

## Success Criteria
- Function calls resolve correctly
- Parameters passed accurately
- Return values work properly
- Local scope isolated from global
- Recursive calls supported
- Performance acceptable for reasonable nesting

## Error Handling
- Function not found
- Wrong number of arguments
- Invalid argument types
- Stack overflow (deep recursion)
- Runtime errors in function body

## Dependencies
- Phase 1: Multiline output fixed
- Phase 2: Function definitions working
- Existing variable system
- Existing directive processing