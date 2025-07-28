# Phase 2: Recursive Descent Parser Implementation

## Objectives
Implement a recursive descent parser that converts token streams from lexer_enhanced into AST nodes.

## Components to Create

### 1. Parser Core
- `src/ast_parser/ast_parser.c` - Main parser entry point
- `include/ast_parser.h` - Parser interface and structures

### 2. Expression Parsing (following precedence rules)
- `src/ast_parse_expression/ast_parse_expression.c` - Parse expressions with precedence
- `src/ast_parse_primary/ast_parse_primary.c` - Parse primary expressions (literals, identifiers)
- `src/ast_parse_binary_op/ast_parse_binary_op.c` - Parse binary operations
- `src/ast_parse_function_call/ast_parse_function_call.c` - Parse function calls

### 3. Statement Parsing  
- `src/ast_parse_assignment/ast_parse_assignment.c` - Parse variable assignments
- `src/ast_parse_directive/ast_parse_directive.c` - Parse XMD directives
- `src/ast_parse_conditional/ast_parse_conditional.c` - Parse if/elif/else blocks
- `src/ast_parse_loop/ast_parse_loop.c` - Parse for loops

### 4. Parser State Management
- `src/parser_state_create/parser_state_create.c` - Create parser state
- `src/parser_state_free/parser_state_free.c` - Free parser state
- `src/parser_advance_token/parser_advance_token.c` - Advance to next token
- `src/parser_peek_token/parser_peek_token.c` - Peek at current token

## File Structure (following rules 1-3)
```
src/ast_parser/ast_parser.c
src/ast_parse_expression/ast_parse_expression.c
src/ast_parse_assignment/ast_parse_assignment.c
src/parser_state_create/parser_state_create.c
```

## Tests First (rule 4)
- `test/test_ast_parser.c` - Complete parser testing
- Test expression parsing with proper precedence
- Test all statement types and error conditions

## Grammar to Implement
```
program       -> statement* EOF
statement     -> assignment | directive | conditional | loop
assignment    -> IDENTIFIER ('=' | '+=') expression
expression    -> comparison
comparison    -> term (('==' | '!=' | '<' | '>' | '<=' | '>=') term)*
term          -> factor (('+' | '-') factor)*
factor        -> unary (('*' | '/') unary)*
unary         -> ('!' | '-') unary | primary
primary       -> IDENTIFIER | STRING | NUMBER | BOOLEAN | '(' expression ')' | function_call
function_call -> IDENTIFIER '(' (expression (',' expression)*)? ')'
```

## Error Handling (rule 13)
- Meaningful syntax error messages with source locations
- Recovery strategies for malformed input
- Proper cleanup of partial AST nodes on errors

## Memory Management (rule 14)
- Parser owns tokens temporarily during parsing
- AST nodes have clear ownership (parser creates, caller owns)
- Proper cleanup on parse errors