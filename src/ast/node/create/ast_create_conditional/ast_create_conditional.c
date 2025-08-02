/**
 * @file ast_create_conditional.c
 *
 *
 * @brief Implementation of ast_create_conditional function
 * 
 * This file contains ONLY the ast_create_conditional function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "variable.h"
/**
 * @brief Create AST conditional node (if/elif/else)
 * @param condition Condition expression (NULL for else)
 * @param loc Source location
 * @return New conditional node or NULL on error
 */
ast_node* ast_create_conditional(ast_node* condition, source_location loc) {
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_CONDITIONAL;
    node->data.conditional.condition = condition;
    node->data.conditional.then_block = NULL;
    node->data.conditional.else_block = NULL;
    node->location = loc;
    return node;
}
