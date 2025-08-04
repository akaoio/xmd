/**
 * @file ast_create_for_range.c
 *
 * @brief Implementation of ast_create_for_range function
 * 
 * This file contains ONLY the ast_create_for_range function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create for range loop AST node (for i in 1..5)
 * @param variable Loop variable name
 * @param start_expr Start value expression
 * @param end_expr End value expression
 * @param body Loop body
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_for_range(const char* variable, ast_node* start_expr, ast_node* end_expr, ast_node* body, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, variable, start_expr);
    XMD_VALIDATE_PTRS(NULL, end_expr, body);
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) return NULL;
    
    node->data.for_range.variable = xmd_strdup(variable);
    if (!node->data.for_range.variable) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    node->type = AST_FOR_RANGE;
    node->location = loc;
    node->data.for_range.start_expr = start_expr;
    node->data.for_range.end_expr = end_expr;
    node->data.for_range.body = body;
    
    return node;
}