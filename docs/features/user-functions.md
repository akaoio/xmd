# User-Defined Functions in XMD

XMD now supports user-defined functions with shell-style syntax, following the design principles of mobile-first, minimal punctuation programming.

## Overview

User-defined functions in XMD use a natural, shell-inspired syntax that avoids traditional programming punctuation like parentheses in function definitions. This makes XMD more accessible and easier to type on mobile devices.

## Function Definition Syntax

Functions are defined using the `function` keyword followed by the function name and parameters:

```xmd


```

### Key Features:

- **Shell-style syntax**: No parentheses around parameters
- **Natural language**: Parameters separated by spaces
- **Mobile-friendly**: Minimal punctuation required
- **Indented bodies**: Function body follows indentation-based structure (future enhancement)

## Function Call Syntax

Functions can be called using shell-style syntax within XMD directives:

```xmd



```

The system automatically transforms these shell-style calls to proper function calls internally.

## Examples

### Simple Arithmetic Function

```xmd



The double of 5 is: 
```

### Multi-Parameter Function

```xmd






Calculate:  +  = 
```

### String Processing Function

```xmd





```

## Function Scope

Functions create their own local scope:

- Parameters shadow global variables of the same name
- Function parameters are only accessible within the function
- Global variables remain unchanged after function execution

```xmd





Global x: global
Function result: 
Global x after: global
```

Output:
```
Global x: global
Function result: local: parameter
Global x after: global
```

## Return Statements

Functions can return values using the `return` keyword:

```xmd





```

If no return statement is provided, functions return null.

## Integration with Built-in Functions

User-defined functions work seamlessly with XMD's built-in functions:

```xmd




Numbers: 
```

## Current Limitations

1. **Indented Bodies**: Currently functions must be defined with explicit return statements. Future versions will support indented function bodies.

2. **Recursion**: Recursive function calls are supported but should be used carefully to avoid infinite loops.

3. **Closure Support**: Functions currently have limited closure support - they can access parameters but not outer scope variables.

## Implementation Details

The user-defined functions feature is built on XMD's AST (Abstract Syntax Tree) system:

1. **Function Registration**: Functions are stored in the evaluator context
2. **Shell Transformation**: Shell-style calls are transformed to AST-compatible syntax
3. **Scope Management**: Local scopes are created for parameter binding
4. **Return Handling**: Return statements immediately exit function execution

## Testing

The implementation includes comprehensive tests:

- Basic function infrastructure tests
- Shell-style transformation tests
- Function evaluation and scope tests
- Multi-parameter function tests

Run tests with:
```bash
make test_user_functions_basic
./test_shell_transformation
```

## Future Enhancements

Planned improvements include:

1. **Indented Function Bodies**: Support for multi-line, indented function definitions
2. **Enhanced Closure Support**: Access to outer scope variables
3. **Function Composition**: Better support for function composition and chaining
4. **Documentation Integration**: Automatic function documentation generation

## Design Philosophy

User-defined functions in XMD follow the core design principles:

- **Shell-style**: Familiar to users of command-line interfaces
- **Mobile-first**: Easy to type on mobile keyboards
- **Minimal punctuation**: Reduces cognitive load
- **Natural language**: Reads like English
- **Progressive enhancement**: Works with existing XMD features

This implementation provides a solid foundation for user-defined functions while maintaining XMD's commitment to simplicity and accessibility.