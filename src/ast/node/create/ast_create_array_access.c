/**
 * @file ast_create_array_access.c
 * @brief Create array access AST node
 * 
 * This file contains ONLY the ast_create_array_access function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create array access AST node
 * @param array_expr Array expression
 * @param index_expr Index expression
 * @param loc Source location
 * @return AST node or NULL on failure
 */
ast_node* ast_create_array_access(ast_node* array_expr, ast_node* index_expr, source_location loc) {
    XMD_NULL_CHECK(array_expr);
    XMD_NULL_CHECK(index_expr);
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_ARRAY_ACCESS;
    node->location = loc;
    node->data.array_access.array_expr = array_expr;
    node->data.array_access.index_expr = index_expr;
    
    return node;
}