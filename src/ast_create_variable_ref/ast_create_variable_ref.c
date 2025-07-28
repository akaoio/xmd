/**
 * @file ast_create_variable_ref.c
 * @brief Create AST variable reference node
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST variable reference node
 * @param name Variable name (will be copied)
 * @param loc Source location
 * @return New variable reference node or NULL on error
 */
ast_node* ast_create_variable_ref(const char* name, source_location loc) {
    if (!name) {
        return NULL;
    }
    
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_VARIABLE_REF;
    node->location = loc;
    
    node->data.variable_ref.name = strdup(name);
    if (!node->data.variable_ref.name) {
        free(node);
        return NULL;
    }
    
    return node;
}