/**
 * @file ast_create_loop_times.c
 *
 * @brief Implementation of ast_create_loop_times function
 * 
 * This file contains ONLY the ast_create_loop_times function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create loop N times AST node
 * @param count_expr Number of iterations expression
 * @param body Loop body
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_loop_times(ast_node* count_expr, ast_node* body, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, count_expr, body);
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_LOOP_TIMES;
    node->location = loc;
    node->data.loop_times.count_expr = count_expr;
    node->data.loop_times.body = body;
    
    return node;
}