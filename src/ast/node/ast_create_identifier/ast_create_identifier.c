/**
 * @file ast_create_identifier.c
 * @brief Implementation of ast_create_identifier function
 * 
 * This file contains ONLY the ast_create_identifier function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST identifier node
 * @param name Identifier name
 * @param loc Source location
 * @return New identifier node or NULL on error
 */
ast_node* ast_create_identifier(const char* name, source_location loc) {
    XMD_VALIDATE_PTRS_RETVAL(NULL, name);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_IDENTIFIER, NULL);
    
    node->data.variable_ref.name = xmd_strdup(name);
    if (!node->data.variable_ref.name) {
        xmd_free(node);
        return NULL;
    }
    
    node->location = loc;
    return node;
}
