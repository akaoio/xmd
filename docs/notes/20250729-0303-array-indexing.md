# Array Indexing Implementation

**Date:** 2025-07-29 03:03
**Author:** XMD Team
**Topic:** Array Indexing Feature Implementation

## Overview

Implementing array indexing syntax `variable[index]` to allow accessing individual elements of arrays in XMD expressions.

## Requirements

- Support syntax: `variable[index]` where index is a number (0-based indexing)
- Support in assignments: `set element = array[0]`
- Support in expressions: `array[0] + " - " + array[1]`
- Proper error handling for out-of-bounds access
- Integration with existing AST parser and evaluator

## AST Changes Required

1. **New AST Node Type**: `AST_ARRAY_ACCESS`
   - Fields: array_expr (ast_node*), index_expr (ast_node*)

2. **Parser Enhancement**: 
   - Modify primary expression parsing to handle `[` after identifiers
   - Parse index expression between `[` and `]`

3. **Evaluator Enhancement**:
   - Add evaluation case for AST_ARRAY_ACCESS
   - Support variable lookup and array element access
   - Return appropriate ast_value for accessed element

## Implementation Strategy

1. Add AST_ARRAY_ACCESS to ast_node_type enum
2. Add array_access struct to ast_node union
3. Add ast_create_array_access function
4. Enhance ast_parse_primary to handle array indexing syntax
5. Add evaluation case in ast_evaluate
6. Create comprehensive tests

## Test Cases

- Basic indexing: arr[0], arr[1]
- Expression indexing: arr[i+1], arr[len-1] 
- Nested arrays: matrix[0][1]
- Out of bounds: arr[100] (should handle gracefully)
- Invalid types: string[0] (should error appropriately)

## Files to Modify

- include/ast_node.h - Add AST_ARRAY_ACCESS type and struct
- src/ast_node/ast_node.c - Add creation function
- src/ast_parse_primary/ast_parse_primary.c - Parse array access
- src/ast_evaluate/ast_evaluate.c - Evaluate array access
- test/ast_parser/test_ast_parser.c - Add indexing tests