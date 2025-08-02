/**
 * @file ast_create_unary_op.c
 * @brief Implementation of ast_create_unary_op function
 * 
 * This file contains ONLY the ast_create_unary_op function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Create AST unary operation node
 * @param op Unary operator type
 * @param operand Operand expression
 * @param loc Source location
 * @return New unary op node or NULL on error
 */
ast_node* ast_create_unary_op(unary_operator op, ast_node* operand, source_location loc) {
    if (!operand) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_UNARY_OP;
    node->data.unary_op.op = op;
    node->data.unary_op.operand = operand;
    node->location = loc;
    return node;
}
