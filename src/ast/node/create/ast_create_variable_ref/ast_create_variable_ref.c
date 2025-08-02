/**
 * @file ast_create_variable_ref.c
 * @brief Implementation of ast_create_variable_ref function
 * 
 * This file contains ONLY the ast_create_variable_ref function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"
#include "variable_internal.h"

/**
 * @brief Create AST variable reference node
 * @param name Variable name
 * @param loc Source location
 * @return New variable ref node or NULL on error
 */
ast_node* ast_create_variable_ref(const char* name, source_location loc) {
    if (!name) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_VARIABLE_REF;
    node->data.variable_ref.name = xmd_strdup(name);
    node->location = loc;
    
    if (!node->data.variable_ref.name) {
        free(node);
        return NULL;
    }
    
    return node;
}
