/**
 * @file ast_create_binary_op.c
 * @brief Implementation of ast_create_binary_op function
 * 
 * This file contains ONLY the ast_create_binary_op function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"

/**
 * @brief Create AST binary operation node
 * @param op Operation type
 * @param left Left operand
 * @param right Right operand
 * @param loc Source location
 * @return New binary op node or NULL on error
 */
ast_node* ast_create_binary_op(binary_operator op, ast_node* left, ast_node* right, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, left, right);
    
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_BINARY_OP;
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    node->location = loc;
    return node;
}
