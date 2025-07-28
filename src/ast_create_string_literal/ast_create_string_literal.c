/**
 * @file ast_create_string_literal.c
 * @brief Create AST string literal node
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST string literal node
 * @param value String value (will be copied)
 * @param loc Source location
 * @return New string literal node or NULL on error
 */
ast_node* ast_create_string_literal(const char* value, source_location loc) {
    if (!value) {
        return NULL;
    }
    
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_LITERAL;
    node->location = loc;
    
    node->data.literal.type = LITERAL_STRING;
    node->data.literal.value.string_value = strdup(value);
    if (!node->data.literal.value.string_value) {
        free(node);
        return NULL;
    }
    
    return node;
}