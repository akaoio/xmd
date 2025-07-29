# XMD Functions Tutorial: From Basics to Advanced

This tutorial will guide you through creating and using user-defined functions in XMD, from simple examples to advanced patterns.

## Table of Contents

1. [Introduction](#introduction)
2. [Your First Function](#your-first-function)
3. [Function Parameters](#function-parameters)
4. [Return Values](#return-values)
5. [Function Scope](#function-scope)
6. [Shell-Style Syntax](#shell-style-syntax)
7. [Practical Applications](#practical-applications)
8. [Advanced Patterns](#advanced-patterns)
9. [Best Practices](#best-practices)
10. [Troubleshooting](#troubleshooting)

## Introduction

XMD functions use a natural, shell-inspired syntax that makes them easy to write and read. Unlike traditional programming languages, XMD functions avoid unnecessary punctuation and follow mobile-friendly design principles.

### Why Functions?

- **Reusability**: Write once, use everywhere
- **Organization**: Keep content modular and maintainable
- **Abstraction**: Hide complex logic behind simple interfaces
- **Consistency**: Ensure uniform output across your content

## Your First Function

Let's start with the simplest possible function:

```xmd
<!-- Define a function -->



<!-- Use the function -->

```

**Output:**
```
Hello, World!
```

### Breaking It Down

1. `function sayHello` - Declares a function named "sayHello"
2. `return "Hello, World!"` - Specifies what the function returns
3. `sayHello` - Calls the function (note: no parentheses needed!)

## Function Parameters

Functions become powerful when they accept parameters:

```xmd
<!-- Function with one parameter -->



<!-- Use with different values -->
- 
- 
- 
```

**Output:**
```
- Hello, Alice!
- Hello, Bob!
- Hello, World!
```

### Multiple Parameters

```xmd
<!-- Function with multiple parameters -->




```

**Output:**
```
Alice is 25 years old and lives in New York
```

### Parameter Best Practices

- Use descriptive names: `calculateTax amount rate` not `calc a r`
- Keep parameter count reasonable (2-4 is ideal)
- Order parameters logically (most important first)

## Return Values

Functions can return different types of data:

### String Returns

```xmd




```

### Number Returns

```xmd



The sum is: 
```

### Conditional Returns

```xmd



- Alice (25): 
- Bob (16): 
```

### No Return (Empty Functions)

```xmd
<!-- Function that doesn't explicitly return anything -->


<!-- This returns null/empty -->
Result: ""
```

## Function Scope

Functions create their own local scope for parameters:

```xmd
<!-- Set a global variable -->


<!-- Function that uses parameter with same name -->



Global name: Global Alice
Function result: 
Global name after: Global Alice
```

**Output:**
```
Global name: Global Alice
Function result: Hello, Local Bob!
Global name after: Global Alice
```

The global variable remains unchanged!

## Shell-Style Syntax

XMD's shell-style syntax makes functions feel natural:

### Traditional vs XMD Syntax

**Traditional Programming:**
```javascript
function greet(name, time) {
    return "Good " + time + ", " + name + "!";
}
greet("Alice", "morning");
```

**XMD Shell-Style:**
```xmd




```

### Why Shell-Style?

- **Mobile-friendly**: Less punctuation to type
- **Natural reading**: Flows like English
- **Familiar**: Similar to command-line tools
- **Accessible**: Lower barrier to entry

### Quoted Parameters

Use quotes for parameters with spaces:

```xmd






```

## Practical Applications

### Content Generation

```xmd





This is the blog post content...
```

### Data Formatting

```xmd






Price: 
Discount: 
```

### HTML Generation

```xmd






Visit  for more info.
This is  information.
```

### Calculations

```xmd






Circle area (r=5): 
Rectangle area (10×8): 
```

## Advanced Patterns

### Function Composition

```xmd









<!-- Compose functions -->

```

**Output:**
```
Result: 20
```

### Template Functions

```xmd




```

### Conditional Logic

```xmd






```

### Working with Arrays

```xmd








Shopping list:



```

## Best Practices

### 1. Function Naming

**Good:**
```xmd



```

**Avoid:**
```xmd



```

### 2. Parameter Organization

**Logical order:**
```xmd
<!-- Most important parameter first -->


```

### 3. Documentation

```xmd
<!-- 
Function: calculateMonthlyPayment
Purpose: Calculate monthly loan payment
Parameters:
  - principal: Loan amount in dollars
  - rate: Annual interest rate (as decimal)
  - years: Loan term in years
Returns: Monthly payment amount
-->


```

### 4. Error Handling

```xmd





```

### 5. Consistent Style

- Use consistent naming conventions
- Keep function bodies simple
- Use descriptive parameter names
- Add documentation for complex functions

## Troubleshooting

### Common Issues

**1. Function Not Found**
```xmd
<!-- Error: my_function is not defined -->

```

**Solution:** Make sure the function is defined before use:
```xmd




```

**2. Parameter Count Mismatch**
```xmd
<!-- Function expects 2 parameters -->



<!-- Error: Only providing 1 parameter -->

```

**Solution:** Provide all required parameters:
```xmd

```

**3. Scope Issues**
```xmd
<!-- This won't work - trying to access local variable globally -->





Value: test  <!-- local_var is not accessible here -->
```

**Solution:** Return values instead of relying on side effects:
```xmd




Value: 
```

### Debugging Tips

1. **Test functions in isolation** before using them in complex contexts
2. **Use simple return values** first, then add complexity
3. **Check parameter types** - ensure strings are quoted properly
4. **Verify function names** - XMD is case-sensitive

### Performance Considerations

- Functions are evaluated each time they're called
- Complex functions in loops can be slow
- Consider caching results for expensive operations:

```xmd
<!-- Cache expensive calculation -->


<!-- Use cached result multiple times -->
Result 1: 
Result 2: 
```

## Next Steps

Now that you understand XMD functions, try:

1. **Create utility functions** for your common content patterns
2. **Build a function library** for your project
3. **Experiment with composition** to build complex behaviors
4. **Share functions** across your team for consistency

### Further Reading

- [Function Examples](function-examples.md) - Real-world function patterns
- [XMD API Reference](../api/functions.md) - Complete function reference
- [Advanced XMD](advanced-xmd.md) - Complex XMD patterns and techniques

---

**Happy function writing!** 🚀

The shell-style syntax makes XMD functions a joy to use. Start simple, build up complexity gradually, and soon you'll be creating sophisticated content generation systems with ease.