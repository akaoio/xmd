/**
 * @file ast_create_spread.c
 *
 * @brief Implementation of ast_create_spread function
 * 
 * This file contains ONLY the ast_create_spread function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Create spread operator AST node
 * @param expression Expression to spread
 * @param in_array true if spreading in array context
 * @param in_object true if spreading in object context
 * @param loc Source location
 * @return AST node or NULL on failure
 */
ast_node* ast_create_spread(ast_node* expression, bool in_array, bool in_object, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, expression);
    
    ast_node* node = XMD_CALLOC(1, sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_SPREAD;
    node->location = loc;
    node->data.spread.expression = expression;
    node->data.spread.in_array = in_array;
    node->data.spread.in_object = in_object;
    
    return node;
}