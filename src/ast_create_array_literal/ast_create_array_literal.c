/**
 * @file ast_create_array_literal.c
 * @brief Create AST array literal node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST array literal node
 * @param loc Source location
 * @return New array literal node or NULL on error
 */
ast_node* ast_create_array_literal(source_location loc) {
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_ARRAY_LITERAL;
    node->location = loc;
    
    node->data.array_literal.elements = NULL;
    node->data.array_literal.element_count = 0;
    
    return node;
}