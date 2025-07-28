# AST Migration Plan Overview

## Objective
Replace all string-based parsing in XMD with proper Abstract Syntax Tree (AST) parsing architecture.

## Current State
- String manipulation using strchr, strstr, strncmp throughout codebase
- Direct text processing in process_set.c, process_directive.c, etc.
- Error-prone pattern matching without proper syntax validation
- Limited extensibility for new language features

## Target State  
- Full AST-based parsing with lexer → parser → interpreter pipeline
- Proper error handling with source location tracking
- Type-safe node structures following one-function-per-file rule
- Complete removal of string-based parsing code

## Phases
1. **Phase 1**: Core AST Infrastructure (ast_node, lexer_enhanced)
2. **Phase 2**: Parser Implementation (recursive descent)
3. **Phase 3**: AST Interpreter/Evaluator
4. **Phase 4**: Migration of Existing Components
5. **Phase 5**: String Parser Purge
6. **Phase 6**: Testing and Documentation

## Success Criteria
- All XMD directives parsed through AST
- Zero string-based parsing remaining
- Full test coverage maintained
- Performance equivalent or better
- Clean architecture following dev rules