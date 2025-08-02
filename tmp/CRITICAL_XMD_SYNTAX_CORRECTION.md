# CRITICAL XMD Syntax Correction

## URGENT: Team is implementing XMD incorrectly!

Genesis has corrected our misunderstanding of XMD syntax. The team needs to immediately fix the fundamental parsing logic.

## Key Corrections

### 1. Assignment vs Comparison
- **WRONG**: `variable = value` for assignment
- **CORRECT**: `set variable value` for assignment
- **COMPARISON**: `if variable = value` (equals comparison)

### 2. The `=` Operator
- `=` is **ONLY** for comparison, **NEVER** for assignment
- Examples:
  - `if score = 100` → comparison (correct)
  - `score = 100` → this would be a comparison expression, not assignment!
  - `set score 100` → assignment (correct)

### 3. Conditional Syntax
```xmd
if score = 100 then print "Perfect!"
if score <= 90
    return "Excellent" 
elif score <= 70
    return "Good"
else
    return "Try again"
```

### 4. Variable Assignment Examples
```xmd
set made "in Vietnam"
set by "Nguyen Ky Son" 
set age 40
set score 95.5
set active true
set empty null
```

### 5. Function Parameters (space-separated)
```xmd
function greet name
    return "Hello " + name

function add a b
    return a + b
```

### 6. Arrays (comma-separated, no brackets needed)
```xmd
set scores 1, 2, 3
set items "pen", "book", "lamp"
```

### 7. Objects (comma-separated, no braces/colons)
```xmd
set user name "Alice", age 30, active true
set config debug true, retries 3, timeout 1000
```

## Parser Fixes Required

### Fix 1: Assignment Statement Parsing
Current (wrong): Looking for `variable = value`
Correct: Only parse `set variable value` as assignment

### Fix 2: Comparison Operator Parsing  
Current: May be treating `=` as assignment
Correct: `=` is always comparison operator

### Fix 3: Function Definition Parsing
Current: May expect parentheses
Correct: Space-separated parameters without parentheses

### Fix 4: Array/Object Parsing
Current: May expect `[1,2,3]` or `{key: value}`  
Correct: Minimal syntax `1, 2, 3` and `key value, key2 value2`

## Critical Test Cases

```xmd
// Variable assignment (ONLY valid assignment syntax)
set x 5
set y 3  
set sum x + y

// Comparison (using = operator)
if sum = 8
    print "Math works!"

// Function with space-separated params
function multiply a b
    return a * b

set result multiply 4 5

// Array without brackets
set numbers 1, 2, 3, 4, 5

// Object without braces/colons  
set person name "Alice", age 30, city "Hanoi"

// Loop examples
for i in 1 .. 5
    print i
    if i = 3 then break

// While loop
set count 0
while count < 3
    print count
    set count count + 1
```

## Team Action Required

1. **Developer/Developer2**: Fix parser to handle correct XMD syntax
2. **Tester**: Update all test files to use correct syntax  
3. **All**: Stop using `=` for assignment anywhere in code
4. **All**: Use space-separated function parameters, not parentheses

This is a fundamental syntax correction that affects the entire language implementation!