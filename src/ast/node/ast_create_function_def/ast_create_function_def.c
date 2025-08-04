/**
 * @file ast_create_function_def.c
 * @brief Implementation of ast_create_function_def function
 * 
 * This file contains ONLY the ast_create_function_def function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST function definition node
 * @param name Function name
 * @param is_async Whether function is async
 * @param loc Source location
 * @return New function definition node or NULL on error
 */
ast_node* ast_create_function_def(const char* name, bool is_async, source_location loc) {
    XMD_VALIDATE_PTRS_RETVAL(NULL, name);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_FUNCTION_DEF, NULL);
    
    node->data.function_def.name = xmd_strdup(name);
    if (!node->data.function_def.name) {
        xmd_free(node);
        return NULL;
    }
    
    node->data.function_def.is_async = is_async;
    node->data.function_def.parameters = NULL;
    node->data.function_def.parameter_count = 0;
    node->data.function_def.body = NULL;
    node->location = loc;
    
    return node;
}
