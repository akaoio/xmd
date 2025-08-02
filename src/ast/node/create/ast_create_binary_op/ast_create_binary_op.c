/**
 * @file ast_create_binary_op.c
 * @brief Implementation of ast_create_binary_op function
 * 
 * This file contains ONLY the ast_create_binary_op function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "variable.h"
/**
 * @brief Create AST binary operation node
 * @param op Operation type
 * @param left Left operand
 * @param right Right operand
 * @param loc Source location
 * @return New binary op node or NULL on error
 */
ast_node* ast_create_binary_op(binary_operator op, ast_node* left, ast_node* right, source_location loc) {
    if (!left || !right) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_BINARY_OP;
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->location = loc;
    return node;
}
