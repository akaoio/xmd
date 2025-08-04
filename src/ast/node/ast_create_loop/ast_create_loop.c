/**
 * @file ast_create_loop.c
 * @brief Implementation of ast_create_loop function
 * 
 * This file contains ONLY the ast_create_loop function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Create AST loop node (for)
 * @param variable Loop variable name
 * @param iterable Expression to iterate over
 * @param loc Source location
 * @return New loop node or NULL on error
 */
ast_node* ast_create_loop(const char* variable, ast_node* iterable, source_location loc) {
    XMD_VALIDATE_PTRS_RETVAL(NULL, variable, iterable);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_LOOP, NULL);
    
    XMD_STRDUP_VALIDATED(node->data.loop.variable, variable,
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    node->data.loop.iterable = iterable;
    node->data.loop.body = NULL;
    node->location = loc;
    
    return node;
}
