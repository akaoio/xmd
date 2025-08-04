/**
 * @file ast_add_argument.c
 * @brief Implementation of ast_add_argument function
 * 
 * This file contains ONLY the ast_add_argument function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Add an argument to a directive or function call
 * @param node Directive or function call node
 * @param argument Argument to add
 * @return 0 on success, -1 on error
 */
int ast_add_argument(ast_node* node, ast_node* argument) {
    XMD_VALIDATE_PTRS_RETVAL(-1, node, argument);
    
    // Determine which union member to use
    ast_node*** arguments_ptr;
    size_t* count_ptr;
    if (node->type == AST_DIRECTIVE) {
        arguments_ptr = &node->data.directive.arguments;
        count_ptr = &node->data.directive.argument_count;
    } else if (node->type == AST_FUNCTION_CALL) {
        arguments_ptr = &node->data.function_call.arguments;
        count_ptr = &node->data.function_call.argument_count;
    } else {
        XMD_ERROR_STATUS(-1, "Node type does not support arguments");
    }
    
    size_t old_count = *count_ptr;
    size_t new_count = old_count + 1;
    
    XMD_AST_ARRAY_RESIZE(*arguments_ptr, old_count, new_count, ast_node*, -1);
    
    (*arguments_ptr)[old_count] = argument;
    *count_ptr = new_count;
    return 0;
}
