/**
 * @file ast_parse_try_catch.h
 * @brief Header for ast_parse_try_catch function
 * 
 * This file contains ONLY the ast_parse_try_catch function declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_AST_PARSE_TRY_CATCH_H
#define XMD_AST_PARSE_TRY_CATCH_H

#include "../../../../../../include/ast.h"

/**
 * @brief Parse try-catch statement
 * @param pos Pointer to current position in input (will be advanced)
 * @return Try-catch AST node or NULL on error
 */
ast_node* ast_parse_try_catch(const char** pos);

#endif /* XMD_AST_PARSE_TRY_CATCH_H */