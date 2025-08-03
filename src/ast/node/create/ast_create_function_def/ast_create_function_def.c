/**
 * @file ast_create_function_def.c
 * @brief Implementation of ast_create_function_def function
 * 
 * This file contains ONLY the ast_create_function_def function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"

/**
 * @brief Create AST function definition node
 * @param name Function name
 * @param is_async Whether function is async
 * @param loc Source location
 * @return New function def node or NULL on error
 */
ast_node* ast_create_function_def(const char* name, bool is_async, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, name);
    
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_FUNCTION_DEF;
    node->location = loc;
    memset(&node->data, 0, sizeof(node->data));
    
    node->data.function_def.name = xmd_strdup(name);
    if (!node->data.function_def.name) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    node->data.function_def.parameters = NULL;
    node->data.function_def.parameter_count = 0;
    node->data.function_def.body = NULL;
    node->data.function_def.is_async = is_async;
    
    return node;
}
