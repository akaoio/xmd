# XMD SYNTAX GUIDE
*The Pure Natural Language Programming Syntax*

## Philosophy

XMD is designed to be "the purest language closest to human natural language." Unlike traditional programming languages, XMD uses natural language concepts for operations.

## Core Syntax Rules

### 1. Assignment vs Comparison

**CRITICAL DISTINCTION:**

- `set` = Assignment (action)
- `=` = Comparison (equality check)

```xmd
# Assignment (setting a value)
set x 5
set name "Alice"
set result true

# Comparison (checking equality) 
if x = 5
    print "x equals 5"
end

if name = "Alice"
    print "Hello Alice!"
end
```

### 2. Variable Declaration

Use `set` keyword followed by variable name and value:

```xmd
set age 25
set message "Hello World"
set isActive true
set items [1, 2, 3]
set user {name: "John", age: 30}
```

### 3. Conditional Statements

Use `if` with single `=` for comparison:

```xmd
# Basic if statement
if x = 10
    print "x is ten"

# If-else structure  
if age = 18
    print "Adult"
else
    print "Minor"

# Multiple conditions
if score = 100
    print "Perfect!"
elif score <= 90
    print "Excellent!"
else
    print "Good job!"
```

### 4. Comparison Operators

```xmd
if x = 5      # Equal to
if x != 5     # Not equal to
if x < 5      # Less than
if x > 5      # Greater than
if x <= 5     # Less than or equal
if x >= 5     # Greater than or equal
```

### 5. Loops

#### For Loop

**Range Loop:**
```xmd
for i in 1 .. 5
    print i

for i in min .. max
    print i
```

**Array Iteration:**
```xmd
for item in items
    print item
```

**Loop with Index:**
```xmd
for i, name in names
    print i + ": " + name
```

**Repeat N Times:**
```xmd
loop 100 times
    print "I am sorry..."
```

#### While Loop
```xmd
set counter 0
while counter < 10
    print counter
    set counter counter + 1
end
```

### 6. Functions

```xmd
# Function definition
function greet name
    print "Hello " + name

# Function call
greet "Alice"
```

### 7. Print Statements

```xmd
print "Simple text"
print variable_name
print "Hello " + name
```

## XMD vs Other Languages

| Operation | XMD | Other Languages |
|-----------|-----|----------------|
| Assignment | `set x 5` | `x = 5` |
| Comparison | `if x = 5` | `if x == 5` |
| Function | `function name param` | `function name(param)` |
| Loop | `for i in 1 .. 5` | `for i in range(1, 6)` |

## Important Notes

### ❌ What NOT to Use

```xmd
# WRONG - These are NOT XMD syntax:
x = 5           # NO assignment with =
if x == 5       # NO double equals  
x += 1          # NO compound assignment
```

### ✅ Correct XMD Syntax

```xmd
# CORRECT - Pure XMD way:
set x 5         # Assignment with 'set'
if x = 5        # Comparison with single =
set x x + 1     # Explicit reassignment
```

## Complete Example

```xmd
# XMD Program Example
set name "XMD Language"
set version 1.0
set features ["natural", "pure", "beautiful"]

print "Welcome to " + name

if version = 1.0
    print "First release!"

for feature in features
    print "Feature: " + feature

function calculate a b
    set result a + b
    print "Result: " + result

calculate 10, 20
```

## Design Principles

1. **Natural Language**: `set` and `=` mirror human speech
2. **Explicit Actions**: `set` makes assignment clear and intentional  
3. **Pure Syntax**: No confusing `==` vs `=` distinction
4. **Readable Code**: Code reads like English sentences

---

*"Although not the most powerful language, but it is the one that is purest and closest to human natural language."* - Nguyen Ky Son