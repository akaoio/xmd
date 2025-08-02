# XMD MODULAR ARCHITECTURE DESIGN
**Genesis Leader Authority**: 2025-08-01 16:55
**Principle**: 1 function → 1 file → 1 directory

## 🚨 CRITICAL VIOLATION ANALYSIS

### Current Violations
- `src/ast_consolidated.c`: 186KB, 141 functions (SEVERE VIOLATION)
- `src/variable.c`: 34KB, ~30 functions (VIOLATION)
- `src/systems_consolidated.c`: 31KB (VIOLATION)
- `src/native_xmd_consolidated.c`: 28KB (VIOLATION)

### Root Cause
Previous consolidation violated core isolation principle, creating maintenance nightmare.

## 🎯 NEW MODULAR STRUCTURE

### Directory Organization
```
src/
├── ast/
│   ├── parser/
│   │   ├── program/
│   │   │   └── ast_parse_program.c
│   │   ├── statement/
│   │   │   ├── ast_parse_statement_simple.c
│   │   │   └── ast_parse_statement_block.c
│   │   ├── expression/
│   │   │   ├── ast_parse_expression_simple.c
│   │   │   ├── ast_parse_binary_expression.c
│   │   │   └── ast_parse_comparison_expression.c
│   │   ├── assignment/
│   │   │   └── ast_parse_assignment_simple.c
│   │   ├── control/
│   │   │   ├── ast_parse_if_then_simple.c
│   │   │   ├── ast_parse_elif_simple.c
│   │   │   └── ast_parse_else_simple.c
│   │   ├── loop/
│   │   │   ├── ast_parse_loop_simple.c
│   │   │   ├── ast_parse_while_simple.c
│   │   │   └── ast_parse_range_loop.c
│   │   └── literal/
│   │       ├── ast_parse_string_literal.c
│   │       ├── ast_parse_number_literal.c
│   │       └── ast_parse_boolean_literal.c
│   ├── evaluator/
│   │   ├── program/
│   │   │   └── ast_evaluate_program.c
│   │   ├── statement/
│   │   │   └── ast_evaluate_statement.c
│   │   ├── expression/
│   │   │   ├── ast_evaluate_expression.c
│   │   │   └── ast_evaluate_binary_op.c
│   │   ├── assignment/
│   │   │   └── ast_evaluate_assignment.c
│   │   ├── control/
│   │   │   └── ast_evaluate_conditional.c
│   │   ├── loop/
│   │   │   ├── ast_evaluate_loop.c
│   │   │   └── ast_evaluate_while_loop.c
│   │   └── function/
│   │       └── ast_evaluate_function_call.c
│   ├── node/
│   │   ├── create/
│   │   │   ├── ast_create_program.c
│   │   │   ├── ast_create_assignment.c
│   │   │   └── ast_create_binary_op.c
│   │   └── free/
│   │       └── ast_free.c
│   └── value/
│       ├── ast_value_create_string.c
│       ├── ast_value_create_number.c
│       ├── ast_value_to_string.c
│       └── ast_value_free.c
├── variable/
│   ├── create/
│   │   ├── variable_create_string.c
│   │   ├── variable_create_number.c
│   │   └── variable_create_array.c
│   ├── operations/
│   │   ├── variable_copy.c
│   │   ├── variable_equals.c
│   │   └── variable_to_string.c
│   └── memory/
│       ├── variable_ref.c
│       └── variable_unref.c
├── lexer/
│   ├── core/
│   │   ├── lexer_create.c
│   │   ├── lexer_advance.c
│   │   └── lexer_free.c
│   └── token/
│       ├── lexer_next_token.c
│       └── lexer_peek_token.c
└── main.c
```

## 📏 NAMING CONVENTIONS

### File Names
- **Pattern**: `module_action_target.c`
- **Examples**:
  - `ast_parse_program.c` (module: ast, action: parse, target: program)
  - `variable_create_string.c` (module: variable, action: create, target: string)

### Function Names (must match file name)
- **One function per file**: Function name = file name without .c
- **Example**: `ast_parse_program.c` contains ONLY `ast_parse_program()` function

### Directory Structure
- **Depth limit**: Maximum 4 levels deep
- **Grouping**: By module → by action type → by specific target
- **Example**: `src/ast/parser/expression/` contains all expression parsing functions

## 🔧 REFACTORING PROCESS

### Phase 1: Test Coverage (Systems Engineer - 2 hours)
1. Create comprehensive test suite for current functionality
2. Validate all features work before refactoring
3. Create regression test framework

### Phase 2: AST Module Refactoring (Developer - 4 hours)
1. Create new directory structure
2. Extract each function to its own file
3. Update includes and build system
4. Run tests after each extraction

### Phase 3: Other Modules (Team - 8 hours)
1. Variable module refactoring
2. Lexer module refactoring
3. Native XMD module refactoring
4. Remaining consolidated files

## ✅ SUCCESS CRITERIA

### Compliance Metrics
- **File size**: No file larger than 2KB (approximately 50 lines)
- **Function count**: Exactly 1 function per file
- **Directory depth**: Maximum 4 levels
- **Build success**: 100% maintained throughout
- **Test coverage**: All tests pass after each refactoring step

### Quality Standards
- **Memory safety**: Zero leaks (valgrind clean)
- **Documentation**: Each file has header comment
- **Error handling**: Consistent across all functions
- **Performance**: No degradation from modularization

## 🚨 ENFORCEMENT

### Genesis Leader Authority
- **REJECT** any PR with multiple functions in one file
- **REJECT** any consolidated or monolithic files
- **REQUIRE** test-driven refactoring approach
- **MONITOR** continuous build and test success

### Team Responsibilities
- **Systems Engineer**: Test coverage and validation
- **Developer**: Implementation following this design
- **Genesis Leader**: Architecture compliance monitoring

---

**GENESIS DECREE**: This architecture is now LAW. No deviations permitted. Every function gets its own file. Period.