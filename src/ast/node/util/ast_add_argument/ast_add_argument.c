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
/**
 * @brief Add an argument to a directive or function call
 * @param node Directive or function call node
 * @param argument Argument to add
 * @return 0 on success, -1 on error
 */
int ast_add_argument(ast_node* node, ast_node* argument) {
    if (!node || !argument) {
        return -1;
    }
    
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
        return -1;
    }
    
    // Reallocate array
    ast_node** new_arguments = xmd_realloc(*arguments_ptr,
                                         (*count_ptr + 1) * sizeof(ast_node*));
    if (!new_arguments) {
        return -1;
    }
    
    *arguments_ptr = new_arguments;
    (*arguments_ptr)[*count_ptr] = argument;
    (*count_ptr)++;
    return 0;
}
