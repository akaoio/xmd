/**
 * @file ast_create_array_access.c
 *
 *
 * @brief Implementation of ast_create_array_access function
 * 
 * This file contains ONLY the ast_create_array_access function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast.h"
#include "utils.h"
/**
 * @brief Create AST array access node
 * @param array_expr Array expression
 * @param index_expr Index expression
 * @param loc Source location
 * @return New array access node or NULL on error
 */
ast_node* ast_create_array_access(ast_node* array_expr, ast_node* index_expr, source_location loc) {
    if (!array_expr || !index_expr) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_ARRAY_ACCESS;
    node->data.array_access.array_expr = array_expr;
    node->data.array_access.index_expr = index_expr;
    node->location = loc;
    return node;
}
