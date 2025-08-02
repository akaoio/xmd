# Genesis XMD Array & Object Design Analysis

## Critical Design Points from leader.md

### 1. Arrays - Genesis Design

#### Inline Arrays (PREFERRED):
```xmd
set scores 1, 2, 3
```
- NO square brackets needed
- Comma-separated values
- Equivalent to [1, 2, 3] internally

#### Multiline Arrays:
```xmd
set items
    "pen",
    "book",
    "lamp",
```
- Indentation required
- Commas required between elements
- Trailing comma allowed

#### Array Access:
```xmd
set x matrix[0][1]      # Standard bracket notation
set y get matrix 1 2    # Alternative using get function
```

### 2. Objects - Genesis Design

#### Inline Objects (PREFERRED):
```xmd
set user name "Alice", age 30, active true
```
- NO curly braces
- NO colons
- Key-value pairs separated by space
- Comma between pairs

#### Multiline Objects:
```xmd
set config
    debug true,
    retries 3,
    timeout 1000,
```
- Indentation required
- Commas required between pairs
- Key value format (no colons)

#### CRITICAL DISTINCTION:
```xmd
// Setting multiple variables inline:
set a 1, b 2, c "3"  // Creates 3 separate variables

// Creating an object:
set user name "Alice", age 30  // Creates 1 object with 2 properties
```

The parser must distinguish between:
1. Multiple variable assignments (simple values after commas)
2. Object creation (key-value pairs after commas)

### 3. Key Implementation Requirements

#### Array Implementation:
1. **Parser**: Detect comma-separated values after `set varname`
2. **No brackets** in syntax (Genesis minimal design)
3. Support both inline and multiline formats
4. Elements can be literals, variables, or expressions

#### Object Implementation:
1. **Parser**: Detect key-value pairs (identifier followed by value)
2. **No braces or colons** (Genesis minimal syntax)
3. Distinguish from multiple variable assignment
4. Support nested structures

### 4. My Current Implementation Status

#### ✅ What I Got Right:
- Basic array parsing for numeric values
- Comma-separated syntax recognition
- No brackets in array syntax

#### ❌ What Needs Fixing:
1. **String array parsing**: Must handle quoted strings in comma lists
2. **Object parsing**: Not implemented at all
3. **Array access**: Need to implement `array[index]` syntax
4. **Multiline support**: Need to handle indented array/object definitions

### 5. Parser Logic for Disambiguation

To distinguish between multiple variables and objects:

```c
// After "set" and identifier:
// Look ahead to see if we have:
// 1. Simple value, comma, simple value -> Multiple variables
// 2. Identifier value, comma -> Object (key-value pairs)

bool is_object = false;
// Scan ahead for pattern: identifier followed by non-comma
while (not end of line) {
    if (identifier followed by value not comma) {
        is_object = true;
        break;
    }
}
```

### 6. Genesis Compliance Checklist

- ✅ Arrays use comma separation (no brackets)
- ✅ Minimal syntax approach
- ❌ Objects not implemented (need key-value parsing)
- ❌ Multiline format not supported
- ❌ Array access syntax not implemented
- ✅ Following "no mocks, no stubs" directive

### 7. Test Cases from Genesis Design

```xmd
// Arrays:
set scores 1, 2, 3                    // [1, 2, 3]
set names "Alice", "Bob", "Charlie"   // ["Alice", "Bob", "Charlie"]
set mixed 42, "hello", true           // [42, "hello", true]

// Objects:
set user name "Alice", age 30         // {name: "Alice", age: 30}
set profile name "Linh", scores scores, active true  // Nested object

// Multiple variables (NOT object):
set a 1, b 2, c "3"                   // Creates a=1, b=2, c="3"

// Array access:
print scores[0]                       // Should print 1
set first scores[0]                   // first = 1
```

## Implementation Priority

1. Fix string array parsing (immediate issue)
2. Implement object vs multiple variable disambiguation
3. Add array access syntax
4. Support multiline formats with indentation

The Genesis design is beautifully minimal - no unnecessary syntax, just pure expression of intent.