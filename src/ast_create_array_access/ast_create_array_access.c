/**
 * @file ast_create_array_access.c
 * @brief Create AST node for array access expressions
 * @author XMD Team
 * @date 2025-07-29
 */

#include "../../include/ast_node.h"
#include <stdlib.h>

/**
 * @brief Create array access AST node
 * @param array_expr Array expression to access
 * @param index_expr Index expression for access
 * @param loc Source location
 * @return New AST node or NULL on error
 */
ast_node* ast_create_array_access(ast_node* array_expr, ast_node* index_expr, source_location loc) {
    if (!array_expr || !index_expr) {
        return NULL;
    }
    
    ast_node* node = malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_ARRAY_ACCESS;
    node->location = loc;
    node->data.array_access.array_expr = array_expr;
    node->data.array_access.index_expr = index_expr;
    
    return node;
}