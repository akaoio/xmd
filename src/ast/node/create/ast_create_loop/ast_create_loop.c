/**
 * @file ast_create_loop.c
 * @brief Implementation of ast_create_loop function
 * 
 * This file contains ONLY the ast_create_loop function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"
/**
 * @brief Create AST loop node (for)
 * @param variable Loop variable name
 * @param iterable Expression to iterate over
 * @param loc Source location
 * @return New loop node or NULL on error
 */
ast_node* ast_create_loop(const char* variable, ast_node* iterable, source_location loc) {
    if (!variable || !iterable) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_LOOP;
    node->data.loop.variable = xmd_strdup(variable);
    node->data.loop.iterable = iterable;
    node->data.loop.body = NULL;
    node->location = loc;
    if (!node->data.loop.variable) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    return node;
}
