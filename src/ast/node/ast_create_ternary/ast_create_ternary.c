/**
 * @file ast_create_ternary.c
 * @brief Implementation of ast_create_ternary function
 * 
 * This file contains ONLY the ast_create_ternary function.
 * One function per file - Genesis principle compliance.
 * Creates ternary operator AST nodes (condition ? true_expr : false_expr)
 */

#include <stdlib.h>
#include "ast.h"
#include "utils.h"
#include "../../../utils/common/common_macros.h"
#include "../../../utils/common/validation_macros.h"

/**
 * @brief Create ternary operator AST node
 * @param condition Condition expression to evaluate
 * @param true_expr Expression to return if condition is true
 * @param false_expr Expression to return if condition is false
 * @param loc Source location
 * @return New ternary AST node or NULL on error
 */
ast_node* ast_create_ternary(ast_node* condition, ast_node* true_expr, ast_node* false_expr, source_location loc) {
    XMD_VALIDATE_PARAMS_3(NULL, condition, true_expr, false_expr);
    
    ast_node* node;
    XMD_MALLOC_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_TERNARY;
    node->location = loc;
    node->data.ternary.condition = condition;
    node->data.ternary.true_expr = true_expr;
    node->data.ternary.false_expr = false_expr;
    
    return node;
}