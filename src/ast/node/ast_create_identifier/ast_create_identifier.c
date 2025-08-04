/**
 * @file ast_create_identifier.c
 * @brief Implementation of ast_create_identifier function
 * 
 * This file contains ONLY the ast_create_identifier function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST identifier node
 * @param name Identifier name
 * @param loc Source location
 * @return New identifier node or NULL on error
 */
ast_node* ast_create_identifier(const char* name, source_location loc) {
    XMD_VALIDATE_PTRS_RETVAL(NULL, name);
    
    if (name && strstr(name, "= ")) {
        XMD_DEBUG("Creating suspicious identifier: '%s'", name);
    }
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_IDENTIFIER, NULL);
    
    XMD_STRDUP_VALIDATED(node->data.identifier.name, name,
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    node->location = loc;
    
    return node;
}
