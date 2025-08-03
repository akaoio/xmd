/**
 * @file ast_create_function_call.c
 * @brief Implementation of ast_create_function_call function
 * 
 * This file contains ONLY the ast_create_function_call function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"

/**
 * @brief Create AST function call node
 * @param name Function name
 * @param loc Source location
 * @return New function call node or NULL on error
 */
ast_node* ast_create_function_call(const char* name, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, name);
    
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    memset(node, 0, sizeof(ast_node));
    
    node->type = AST_FUNCTION_CALL;
    node->data.function_call.name = xmd_strdup(name);
    node->data.function_call.arguments = NULL;
    node->data.function_call.argument_count = 0;
    node->location = loc;
    
    if (!node->data.function_call.name) {
        XMD_FREE_SAFE(node);
        return NULL;
    }
    
    return node;
}
