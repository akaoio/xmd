/**
 * @file ast_add_argument.c
 * @brief Add argument to AST function call or directive node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_node.h"

/**
 * @brief Add argument to AST node (function call or directive)
 * @param node Target node
 * @param argument Argument to add (takes ownership)
 * @return 0 on success, -1 on error
 */
int ast_add_argument(ast_node* node, ast_node* argument) {
    if (!node || !argument) {
        return -1;
    }
    
    if (node->type == AST_FUNCTION_CALL) {
        size_t new_count = node->data.function_call.argument_count + 1;
        ast_node** new_args = realloc(node->data.function_call.arguments, 
                                      new_count * sizeof(ast_node*));
        if (!new_args) {
            return -1;
        }
        
        new_args[node->data.function_call.argument_count] = argument;
        node->data.function_call.arguments = new_args;
        node->data.function_call.argument_count = new_count;
        return 0;
    }
    
    if (node->type == AST_DIRECTIVE) {
        size_t new_count = node->data.directive.argument_count + 1;
        ast_node** new_args = realloc(node->data.directive.arguments, 
                                      new_count * sizeof(ast_node*));
        if (!new_args) {
            return -1;
        }
        
        new_args[node->data.directive.argument_count] = argument;
        node->data.directive.arguments = new_args;
        node->data.directive.argument_count = new_count;
        return 0;
    }
    
    return -1;
}