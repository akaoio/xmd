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
#include "../../../utils/common/validation_macros.h"

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
    
    XMD_ALLOC_CHECK(node, ast_node);
    XMD_STRDUP_CHECK(node->data.for_indexed.index_var, index_var);
    XMD_STRDUP_CHECK(node->data.for_indexed.item_var, item_var);
    
    node->type = AST_FOR_INDEXED;
    node->location = loc;
    node->data.for_indexed.array_expr = array_expr;
    node->data.for_indexed.body = body;
    
    return node;
}