/**
 * @file ast_create_conditional.c
 * @brief Create AST conditional node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST conditional node
 * @param condition Condition expression (takes ownership, can be NULL for else)
 * @param loc Source location
 * @return New conditional node or NULL on error
 */
ast_node* ast_create_conditional(ast_node* condition, source_location loc) {
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_CONDITIONAL;
    node->location = loc;
    
    node->data.conditional.condition = condition;
    node->data.conditional.then_block = NULL;
    node->data.conditional.else_block = NULL;
    
    return node;
}