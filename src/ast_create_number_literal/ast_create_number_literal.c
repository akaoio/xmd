/**
 * @file ast_create_number_literal.c
 * @brief Create AST number literal node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST number literal node
 * @param value Number value
 * @param loc Source location
 * @return New number literal node or NULL on error
 */
ast_node* ast_create_number_literal(double value, source_location loc) {
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_LITERAL;
    node->location = loc;
    
    node->data.literal.type = LITERAL_NUMBER;
    node->data.literal.value.number_value = value;
    
    return node;
}