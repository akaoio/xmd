/**
 * @file ast_parse_import.h
 * @brief Header for ast_parse_import function
 * 
 * Genesis principle compliance: One function per file.
 * Part of Phase 2 module system implementation.
 */

#ifndef AST_PARSE_IMPORT_H
#define AST_PARSE_IMPORT_H

#include "ast_node.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Parse import statement
 * @param pos Pointer to current position in source (will be updated)
 * @return Import AST node or NULL on error
 */
ast_node* ast_parse_import(const char** pos);

#ifdef __cplusplus
}
#endif

#endif /* AST_PARSE_IMPORT_H */