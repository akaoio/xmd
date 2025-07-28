/**
 * @file ast_create_binary_op.c
 * @brief Create AST binary operation node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Create AST binary operation node
 * @param op Binary operator
 * @param left Left operand (takes ownership)
 * @param right Right operand (takes ownership)
 * @param loc Source location
 * @return New binary operation node or NULL on error
 */
ast_node* ast_create_binary_op(binary_operator op, ast_node* left, ast_node* right, source_location loc) {
    if (!left || !right) {
        return NULL;
    }
    
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    node->type = AST_BINARY_OP;
    node->location = loc;
    
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    
    return node;
}