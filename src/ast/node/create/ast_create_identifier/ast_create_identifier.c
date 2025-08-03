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
#include "../../../../utils/common/common_macros.h"

/**
 * @brief Create AST identifier node
 * @param name Identifier name
 * @param loc Source location
 * @return New identifier node or NULL on error
 */
ast_node* ast_create_identifier(const char* name, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, name);
    
    if (name && strstr(name, "= ")) {
        XMD_DEBUG("Creating suspicious identifier: '%s'", name);
    }
    
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    memset(node, 0, sizeof(ast_node));
    
    node->type = AST_IDENTIFIER;
    node->data.identifier.name = xmd_strdup(name);
    node->location = loc;
    
    if (!node->data.identifier.name) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    return node;
}
