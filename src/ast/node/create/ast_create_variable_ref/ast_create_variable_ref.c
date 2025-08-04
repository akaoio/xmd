/**
 * @file ast_create_variable_ref.c
 * @brief Implementation of ast_create_variable_ref function
 * 
 * This file contains ONLY the ast_create_variable_ref function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST variable reference node
 * @param variable_name Name of variable to reference
 * @param loc Source location
 * @return New variable reference node or NULL on error
 */
ast_node* ast_create_variable_ref(const char* variable_name, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, variable_name);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_IDENTIFIER, NULL);
    
    XMD_STRDUP_VALIDATED(node->data.identifier.name, variable_name,
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    node->location = loc;
    return node;
}