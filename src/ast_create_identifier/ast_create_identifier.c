/**
 * @file ast_create_identifier.c
 * @brief Create AST identifier node
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST identifier node
 * @param name Identifier name (will be copied)
 * @param loc Source location
 * @return New identifier node or NULL on error
 */
ast_node* ast_create_identifier(const char* name, source_location loc) {
    if (!name) {
        return NULL;
    }
    
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_IDENTIFIER;
    node->location = loc;
    
    node->data.identifier.name = strdup(name);
    if (!node->data.identifier.name) {
        free(node);
        return NULL;
    }
    
    return node;
}