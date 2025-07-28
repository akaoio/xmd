/**
 * @file ast_create_function_call.c
 * @brief Create AST function call node
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST function call node
 * @param name Function name (will be copied)
 * @param loc Source location
 * @return New function call node or NULL on error
 */
ast_node* ast_create_function_call(const char* name, source_location loc) {
    if (!name) {
        return NULL;
    }
    
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_FUNCTION_CALL;
    node->location = loc;
    
    node->data.function_call.name = strdup(name);
    if (!node->data.function_call.name) {
        free(node);
        return NULL;
    }
    
    node->data.function_call.arguments = NULL;
    node->data.function_call.argument_count = 0;
    
    return node;
}