/**
 * @file ast_create_yield.c
 * @brief Implementation of ast_create_yield function
 * 
 * This file contains ONLY the ast_create_yield function.
 * One function per file - Genesis principle compliance.
 */

#include "ast_node.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST yield statement node
 * @param value Expression to yield (NULL for bare yield)
 * @param loc Source location
 * @return New yield node or NULL on error
 */
ast_node* ast_create_yield(ast_node* value, source_location loc) {
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_YIELD, NULL);
    
    node->location = loc;
    node->data.yield_stmt.value = value;
    
    return node;
}