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
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST function call node
 * @param name Function name
 * @param loc Source location
 * @return New function call node or NULL on error
 */
ast_node* ast_create_function_call(const char* name, source_location loc) {
    XMD_VALIDATE_PTRS_RETVAL(NULL, name);
    
    ast_node* node;
    XMD_AST_CREATE_NODE(node, AST_FUNCTION_CALL, NULL);
    
    XMD_STRDUP_VALIDATED(node->data.function_call.name, name, 
                         ({ XMD_FREE_NULL(node); NULL; }));
    
    node->data.function_call.arguments = NULL;
    node->data.function_call.argument_count = 0;
    node->location = loc;
    
    return node;
}
