/**
 * @file ast_parse_generator_function.h
 * @brief Header for ast_parse_generator_function function
 * 
 * Genesis principle compliance: one function per file per directory
 */

#ifndef AST_PARSE_GENERATOR_FUNCTION_H
#define AST_PARSE_GENERATOR_FUNCTION_H

#include "ast.h"

/**
 * @brief Parse generator function definition (function* name ...)
 * @param pos Pointer to current parsing position (will be advanced)
 * @return AST node for generator function or NULL on error
 */
ast_node* ast_parse_generator_function(const char** pos);

#endif // AST_PARSE_GENERATOR_FUNCTION_H