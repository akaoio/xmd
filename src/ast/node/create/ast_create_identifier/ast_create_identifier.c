/**
 * @file ast_create_identifier.c
 * @brief Implementation of ast_create_identifier function
 * 
 * This file contains ONLY the ast_create_identifier function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Create AST identifier node
 * @param name Identifier name
 * @param loc Source location
 * @return New identifier node or NULL on error
 */
ast_node* ast_create_identifier(const char* name, source_location loc) {
    if (!name) {
        return NULL;
    }
    
    if (name && strstr(name, "= ")) {
        printf("DEBUG: Creating suspicious identifier: '%s'\n", name);
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_IDENTIFIER;
    node->data.identifier.name = xmd_strdup(name);
    node->location = loc;
    if (!node->data.identifier.name) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    return node;
}
