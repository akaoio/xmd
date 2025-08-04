/**
 * @file ast_create_loop_refactored.c
 * @brief Implementation of ast_create_loop function (REFACTORED)
 * 
 * This file contains ONLY the ast_create_loop function.
 * One function per file - Genesis principle compliance.
 * REFACTORED to use AST_CREATE_NODE macro for reduced duplication
 */

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "ast_macros.h"
#include "utils.h"
#include "variable.h"
#include "utils/common/common_macros.h"

/**
 * @brief Create AST loop node (for)
 * @param variable Loop variable name
 * @param iterable Expression to iterate over
 * @param loc Source location
 * @return New loop node or NULL on error
 */
ast_node* ast_create_loop(const char* variable, ast_node* iterable, source_location loc) {
    // Use macro with validation
    AST_CREATE_NODE_VALIDATED(node, AST_LOOP, loc, variable && iterable);
    
    // Set loop-specific fields
    AST_SET_STRING_FIELD(node, data.loop.variable, variable);
    node->data.loop.iterable = iterable;
    node->data.loop.body = NULL;
    
    return node;
}