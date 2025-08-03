# 🎯 XMD Showcase Examples

This directory contains demonstration files showcasing XMD's capabilities.

## 📁 Demo Files

### 🌟 Basic Examples
- **`hello_world.xmd`** - Your first XMD program
- **`functions_demo.xmd`** - Function definitions and calls
- **`loops_demo.xmd`** - All types of loops (for, while, ranges)
- **`conditionals_demo.xmd`** - If/else logic and comparisons
- **`data_structures.xmd`** - Arrays, objects, and data processing

## 🚀 How to Run

```bash
# Run individual examples
./xmd process showcase/hello_world.xmd
./xmd process showcase/functions_demo.xmd
./xmd process showcase/loops_demo.xmd

# Run all examples
for file in showcase/*.xmd; do
    echo "=== Running $file ==="
    ./xmd process "$file"
    echo ""
done
```

## 📖 What You'll Learn

### Hello World (`hello_world.xmd`)
- Basic variable assignment
- String concatenation
- Print statements
- Variable persistence

**Expected Output:**
```
Hello, World!
Welcome to XMD v2.0.0-consolidation
The most beautiful programming language!
Hello, World! from XMD
```

### Functions Demo (`functions_demo.xmd`)
- Function definition with parameters
- Multi-parameter functions
- Parameterless functions
- Function composition
- Return values

**Expected Output:**
```
Hello, Alice!
15 + 25 = 40
7 × 8 = 56
Current timestamp: 2025-08-03
Functions working: Hello, Developer!
```

### Loops Demo (`loops_demo.xmd`)
- Range loops (`for i in 1..5`)
- Array iteration
- While loops
- Nested structures
- Counter operations

**Expected Output:**
```
=== Range Loops ===
Count: 1
Count: 2
Count: 3
Count: 4
Count: 5

=== Array Loops ===
I like apple
I like banana
I like cherry

=== While Loops ===
Countdown: 3
Countdown: 2
Countdown: 1
Blast off! 🚀
...
```

### Conditionals Demo (`conditionals_demo.xmd`)
- If/elif/else statements
- Logical operators (and, or)
- Comparison operators
- Nested conditions
- Practical examples

### Data Structures (`data_structures.xmd`)
- Array creation and access
- Object properties
- Mixed data types
- Data processing patterns
- Statistical calculations

## 🎯 Next Steps

1. **Experiment**: Modify these examples to see how XMD responds
2. **Create**: Write your own XMD programs based on these patterns
3. **Learn**: Study the syntax and structure used in each example
4. **Build**: Create more complex applications using these building blocks

## 💡 Tips for Learning

- Start with `hello_world.xmd` to understand basics
- Each example builds on previous concepts
- Try modifying variables and seeing the results
- Experiment with different data types and operations

---

**🚀 Happy coding with XMD - the most beautiful programming language!**