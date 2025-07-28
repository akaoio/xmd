/**
 * @file ast_create_loop.c
 * @brief Create AST loop node
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST loop node
 * @param variable Loop variable name (will be copied)
 * @param iterable Iterable expression (takes ownership)
 * @param loc Source location
 * @return New loop node or NULL on error
 */
ast_node* ast_create_loop(const char* variable, ast_node* iterable, source_location loc) {
    if (!variable || !iterable) {
        return NULL;
    }
    
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_LOOP;
    node->location = loc;
    
    node->data.loop.variable = strdup(variable);
    if (!node->data.loop.variable) {
        free(node);
        return NULL;
    }
    
    node->data.loop.iterable = iterable;
    node->data.loop.body = NULL;
    
    return node;
}