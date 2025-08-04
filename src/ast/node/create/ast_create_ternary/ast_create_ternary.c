/**
 * @file ast_create_ternary.c
 *
 * @brief Implementation of ast_create_ternary function
 * 
 * This file contains ONLY the ast_create_ternary function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create ternary operator AST node
 * @param condition Condition expression
 * @param true_expr True case expression
 * @param false_expr False case expression
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_ternary(ast_node* condition, ast_node* true_expr, ast_node* false_expr, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, condition, true_expr, false_expr);
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    XMD_NULL_CHECK(node);
    
    node->type = AST_TERNARY;
    node->location = loc;
    
    node->data.ternary.condition = condition;
    node->data.ternary.true_expr = true_expr;
    node->data.ternary.false_expr = false_expr;
    
    return node;
}