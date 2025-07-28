/**
 * @file ast_create_boolean_literal.c
 * @brief Create AST boolean literal node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST boolean literal node
 * @param value Boolean value
 * @param loc Source location
 * @return New boolean literal node or NULL on error
 */
ast_node* ast_create_boolean_literal(bool value, source_location loc) {
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_LITERAL;
    node->location = loc;
    
    node->data.literal.type = LITERAL_BOOLEAN;
    node->data.literal.value.boolean_value = value;
    
    return node;
}