/**
 * @file ast_create_import.h
 * @brief Header for ast_create_import function
 * 
 * Genesis principle compliance: One function per file.
 * Part of Phase 2 module system implementation.
 */

#ifndef AST_CREATE_IMPORT_H
#define AST_CREATE_IMPORT_H

#include "ast_node.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create AST import statement node
 * @param module_path Path to module to import
 * @param loc Source location
 * @return New import node or NULL on error
 */
ast_node* ast_create_import(const char* module_path, source_location loc);

#ifdef __cplusplus
}
#endif

#endif /* AST_CREATE_IMPORT_H */