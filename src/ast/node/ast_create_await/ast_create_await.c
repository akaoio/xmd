/**
 * @file ast_create_await.c
 *
 * @brief Implementation of ast_create_await function
 * 
 * This file contains ONLY the ast_create_await function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create await expression AST node
 * @param expression Expression to await
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_await(ast_node* expression, source_location loc) {
    XMD_VALIDATE_PARAMS_1(NULL, expression);
    
    ast_node* node;
    XMD_MALLOC_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_AWAIT;
    node->location = loc;
    node->data.await.expression = expression;
    
    return node;
}