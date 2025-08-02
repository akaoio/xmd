# XMD Language Feature Implementation Roadmap

## Current System Status (2025-07-31)

### ✅ Working Components
- **Build System**: 100% compilation success
- **Runtime**: Basic file processing without crashes
- **AST Parser**: Real implementation in `ast_consolidated.c`
- **Variable Storage**: Basic `set` command and {{varname}} substitution
- **Expression Parsing**: Mathematical expressions parse but don't evaluate

### ⚠️ Partially Working
- **Math Evaluation**: Expressions like `2 + 3` parse but show as "true + 3"
- **Output Formatting**: Shows "true" for successful assignments
- **Variable Substitution**: {{varname}} works but needs refinement

### ❌ Not Implemented
- **Conditionals**: `if/elif/else` statements with `=` comparison
- **Functions**: Function definitions with space-separated parameters
- **Classes**: Object-oriented programming features
- **Import/Export**: Module system
- **Advanced Features**: Formal logic, async/await, generators

## Implementation Phases

### Phase 1: Core Language Fundamentals (IMMEDIATE PRIORITY)
**Goal**: Implement correct XMD syntax per Genesis specification

#### 1.1 Fix Assignment vs Comparison Understanding
- **CRITICAL**: `=` is COMPARISON operator, NOT assignment!
- **Assignment**: Only `set variable value` syntax
- **Comparison**: `if score = 90` means "if score equals 90"
- **Parser Fix**: Ensure `=` always parsed as comparison in expressions

#### 1.2 Fix Binary Operation Evaluation  
- **File**: `src/ast_consolidated.c`
- **Function**: `ast_evaluate_binary_op()`
- **Issue**: Currently returns boolean instead of computed value
- **Solution**: Implement proper arithmetic operations for BINOP_ADD, BINOP_SUB, etc.

#### 1.3 Fix Assignment Parsing
- **Syntax**: `set variable value` (no `=` sign in assignments!)
- **Examples**:
  - `set name "Alice"` (correct)
  - `name = "Alice"` (WRONG - this would be comparison!)

#### 1.4 Test Cases
```xmd
set x 5
set y 3
set sum x + y
if sum = 8
    print "Correct calculation!"
else
    print "Math is broken"
```

### Phase 2: Control Flow Implementation (1-2 days)

#### 2.1 Conditional Statements
- **Syntax**: `if score = 90` (single `=` is COMPARISON, not assignment!)
- **Key Understanding**: In XMD, `=` is ONLY for comparison, NOT for setting values
- **Assignment**: Use `set variable value` ONLY
- **Comparison**: Use `=` for equality, `<=`, `>=`, `<`, `>` for other comparisons
- **Components**:
  - Add AST_CONDITIONAL node type
  - Implement `ast_parse_conditional()` parser with `=` as comparison operator
  - Implement `ast_evaluate_conditional()` evaluator
  - Support `elif` and `else` chains

#### 2.2 Loop Constructs
- **For Loops**: `for i in 1..5` and `for item in list`
- **While Loops**: `while count < 10`
- **Components**:
  - Add AST_LOOP node type
  - Implement range iterators
  - Add break/continue support

### Phase 3: Function System (2-3 days)

#### 3.1 Function Definitions
- **Syntax**: `function greet name` (space-separated parameters)
- **Components**:
  - Enhance AST_FUNCTION_DEF implementation
  - Create function symbol table
  - Implement parameter binding
  - Add return statement support

#### 3.2 Function Calls
- **Syntax**: `greet "Alice"` (space-separated arguments)
- **Components**:
  - Enhance AST_FUNCTION_CALL implementation
  - Implement call stack management
  - Add argument evaluation and passing

#### 3.3 Built-in Functions
- String manipulation: `uppercase`, `lowercase`, `trim`
- List operations: `length`, `append`, `remove`
- Math functions: `sqrt`, `pow`, `round`

### Phase 4: Advanced Data Types (2-3 days)

#### 4.1 Lists/Arrays
- **Syntax**: `[1, 2, 3]` and `list[0]`
- **Operations**: `append`, `remove`, `slice`
- **Iteration**: `for item in list`

#### 4.2 Objects/Dictionaries
- **Syntax**: `{name: "Alice", age: 30}`
- **Access**: `person.name` or `person["name"]`
- **Modification**: `person.age = 31`

### Phase 5: Class System (3-4 days)

#### 5.1 Class Definitions
```xmd
class Person
  constructor name age
    set this.name name
    set this.age age
  
  method greet
    return "Hello, I'm {{this.name}}"
```

#### 5.2 Inheritance
```xmd
class Student extends Person
  constructor name age grade
    super name age
    set this.grade grade
```

### Phase 6: Module System (2-3 days)

#### 6.1 Import/Export
- **Export**: `export function calculate`, `export class MyClass`
- **Import**: `import calculate from "./math.xmd"`
- **Import All**: `import * as math from "./math.xmd"`

#### 6.2 Module Resolution
- Relative paths: `./module.xmd`, `../lib/module.xmd`
- Module cache to prevent duplicate loading
- Circular dependency detection

### Phase 7: Advanced Features (1 week)

#### 7.1 Async/Await
```xmd
async function fetchData url
  set response await http.get url
  return response.json()
```

#### 7.2 Error Handling
```xmd
try
  set result riskyOperation()
catch error
  print "Error: {{error.message}}"
finally
  cleanup()
```

#### 7.3 Generators
```xmd
function* fibonacci
  set a 0
  set b 1
  while true
    yield a
    set temp a + b
    set a b
    set b temp
```

### Phase 8: Formal Logic Features (Optional)

#### 8.1 Axioms and Theorems
```xmd
axiom "identity" all x: x = x
theorem "reflexivity" 
  prove all x: x = x
  by axiom "identity"
```

## Technical Architecture

### AST Node Types Required
- [x] AST_PROGRAM
- [x] AST_ASSIGNMENT
- [x] AST_BINARY_OP
- [x] AST_IDENTIFIER
- [x] AST_NUMBER
- [x] AST_STRING
- [ ] AST_CONDITIONAL (if/elif/else)
- [ ] AST_LOOP (for/while)
- [x] AST_FUNCTION_DEF
- [x] AST_FUNCTION_CALL
- [x] AST_RETURN
- [x] AST_ARRAY_LITERAL
- [x] AST_ARRAY_ACCESS
- [ ] AST_OBJECT_LITERAL
- [ ] AST_MEMBER_ACCESS
- [ ] AST_CLASS_DEF
- [ ] AST_METHOD_DEF
- [ ] AST_IMPORT
- [ ] AST_EXPORT
- [ ] AST_TRY_CATCH
- [ ] AST_ASYNC
- [ ] AST_AWAIT
- [ ] AST_YIELD

### Parser Functions Required
- [x] ast_parse_program()
- [x] ast_parse_statement()
- [x] ast_parse_expression()
- [x] ast_parse_assignment()
- [ ] ast_parse_conditional()
- [ ] ast_parse_loop()
- [x] ast_parse_function_def()
- [x] ast_parse_function_call()
- [ ] ast_parse_class()
- [ ] ast_parse_import()
- [ ] ast_parse_try_catch()

### Evaluator Functions Required
- [x] ast_evaluate()
- [x] ast_evaluate_assignment()
- [x] ast_evaluate_expression()
- [ ] ast_evaluate_binary_op() (needs fix)
- [ ] ast_evaluate_conditional()
- [ ] ast_evaluate_loop()
- [x] ast_evaluate_function_call()
- [ ] ast_evaluate_class_instantiation()
- [ ] ast_evaluate_method_call()

## Testing Strategy

### Unit Tests
- Test each AST node type creation
- Test parsing of each language construct
- Test evaluation of each operation

### Integration Tests
- Complex expressions with multiple operations
- Nested control structures
- Function calls within expressions
- Class inheritance chains

### Example Test Programs
1. **Calculator**: Math expressions and functions
2. **Todo List**: Classes, arrays, and methods
3. **Web Server**: Async/await and error handling
4. **Math Library**: Module system and exports

## Success Metrics

1. **Phase 1 Success**: `set result 2 + 3` produces `result = 5`
2. **Phase 2 Success**: Conditional and loop examples from Genesis spec work
3. **Phase 3 Success**: Function definition and calling works
4. **Phase 4 Success**: Lists and objects fully functional
5. **Phase 5 Success**: Classes with inheritance work
6. **Phase 6 Success**: Module import/export operational
7. **Phase 7 Success**: Async/await examples execute
8. **Phase 8 Success**: Formal logic proofs validate

## Next Immediate Steps

1. **Fix Binary Operation Evaluation** (ast_evaluate_binary_op)
2. **Fix Output Formatting** (suppress "true" for assignments)
3. **Test Mathematical Expressions** thoroughly
4. **Begin Conditional Implementation** (if/elif/else)

---
**Architect Note**: This roadmap prioritizes fixing the current partial implementations before adding new features. The mathematical expression evaluation is the most critical immediate fix, as it's partially working but not computing results. Once expressions work properly, we can build the rest of the language features on a solid foundation.