/**
 * @file ast_create_import.c
 * @brief Implementation of ast_create_import function
 * 
 * This file contains ONLY the ast_create_import function.
 * One function per file - Genesis principle compliance.
 * Part of Phase 2 module system implementation.
 */

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST import statement node
 * @param module_path Path to module to import
 * @param loc Source location
 * @return New import node or NULL on error
 */
ast_node* ast_create_import(const char* module_path, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, module_path);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_IMPORT, NULL);
    
    // Duplicate module path string
    XMD_STRDUP_VALIDATED(node->data.import.module_name, module_path, 
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    node->location = loc;
    return node;
}