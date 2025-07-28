/**
 * @file ast_create_unary_op.c
 * @brief Create AST unary operation node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST unary operation node
 * @param op Unary operator
 * @param operand Operand (takes ownership)
 * @param loc Source location
 * @return New unary operation node or NULL on error
 */
ast_node* ast_create_unary_op(unary_operator op, ast_node* operand, source_location loc) {
    if (!operand) {
        return NULL;
    }
    
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_UNARY_OP;
    node->location = loc;
    
    node->data.unary_op.op = op;
    node->data.unary_op.operand = operand;
    
    return node;
}