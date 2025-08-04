/**
 * @file ast_parse_inline_object.h
 * @brief Header for ast_parse_inline_object function
 * 
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_INLINE_OBJECT_H
#define AST_PARSE_INLINE_OBJECT_H

#include "ast.h"

/**
 * @brief Parse inline object syntax: key value, key value, ...
 * @param pos Pointer to current position (updated)
 * @param variable_name The object variable name
 * @return Object literal AST node or NULL on error
 * 
 * XMD Syntax: set user name "Alice", age 30, active true
 * Creates: {name: "Alice", age: 30, active: true}
 */
ast_node* ast_parse_inline_object(const char** pos, const char* variable_name);

#endif /* AST_PARSE_INLINE_OBJECT_H */