/**
 * @file ast_create_function_call.c
 * @brief Implementation of ast_create_function_call function
 * 
 * This file contains ONLY the ast_create_function_call function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"
/**
 * @brief Create AST function call node
 * @param name Function name
 * @param loc Source location
 * @return New function call node or NULL on error
 */
ast_node* ast_create_function_call(const char* name, source_location loc) {
    if (!name) {
        return NULL;
    }
    
    ast_node* node = xmd_malloc(sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_FUNCTION_CALL;
    node->data.function_call.name = xmd_strdup(name);
    node->data.function_call.arguments = NULL;
    node->data.function_call.argument_count = 0;
    node->location = loc;
    if (!node->data.function_call.name) {
        free(node);
        return NULL;
    }
    return node;
}
