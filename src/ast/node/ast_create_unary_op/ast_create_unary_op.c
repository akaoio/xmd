/**
 * @file ast_create_unary_op.c
 * @brief Implementation of ast_create_unary_op function
 * 
 * This file contains ONLY the ast_create_unary_op function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST unary operation node
 * @param op Unary operator type
 * @param operand Operand expression
 * @param loc Source location
 * @return New unary op node or NULL on error
 */
ast_node* ast_create_unary_op(unary_operator op, ast_node* operand, source_location loc) {
    XMD_VALIDATE_PTRS_RETVAL(NULL, operand);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_UNARY_OP, NULL);
    
    node->data.unary_op.op = op;
    node->data.unary_op.operand = operand;
    node->location = loc;
    
    return node;
}
