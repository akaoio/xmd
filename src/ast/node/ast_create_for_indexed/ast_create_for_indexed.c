/**
 * @file ast_create_for_indexed.c
 *
 * @brief Implementation of ast_create_for_indexed function
 * 
 * This file contains ONLY the ast_create_for_indexed function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create for indexed loop AST node (for i, item in array)
 * @param index_var Index variable name
 * @param item_var Item variable name
 * @param array_expr Array expression
 * @param body Loop body
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_for_indexed(const char* index_var, const char* item_var, ast_node* array_expr, ast_node* body, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, index_var, item_var);
    XMD_VALIDATE_PTRS(NULL, array_expr, body);
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) return NULL;
    
    node->data.for_indexed.index_var = xmd_strdup(index_var);
    node->data.for_indexed.item_var = xmd_strdup(item_var);
    if (!node->data.for_indexed.index_var || !node->data.for_indexed.item_var) {
        XMD_FREE_SAFE(node->data.for_indexed.index_var);
        XMD_FREE_SAFE(node->data.for_indexed.item_var);
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    node->type = AST_FOR_INDEXED;
    node->location = loc;
    node->data.for_indexed.array_expr = array_expr;
    node->data.for_indexed.body = body;
    
    return node;
}