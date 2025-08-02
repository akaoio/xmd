/**
 * @file ast_add_parameter.c
 * @brief Implementation of ast_add_parameter function
 * 
 * This file contains ONLY the ast_add_parameter function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "module.h"
#include "utils.h"
#include "variable.h"
/**
 * @brief Add a parameter to a function or method definition
 * @param function Function or method definition node
 * @param parameter Parameter name to add
 * @return 0 on success, -1 on error
 */
int ast_add_parameter(ast_node* function, const char* parameter) {
    if (!function || !parameter) {
        return -1;
    }
    
    // Determine which union member to use
    char*** parameters_ptr;
    size_t* count_ptr;
    if (function->type == AST_FUNCTION_DEF) {
        parameters_ptr = &function->data.function_def.parameters;
        count_ptr = &function->data.function_def.parameter_count;
    } else if (function->type == AST_METHOD_DEF) {
        parameters_ptr = &function->data.method_def.parameters;
        count_ptr = &function->data.method_def.parameter_count;
    } else {
        return -1;
    }
    
    // Reallocate array
    char** new_parameters = xmd_realloc(*parameters_ptr,
                                      (*count_ptr + 1) * sizeof(char*));
    if (!new_parameters) {
        return -1;
    }
    
    // Duplicate parameter name
    char* param_copy = xmd_strdup(parameter);
    if (!param_copy) {
        // Free the new array if strdup fails
        if (*count_ptr == 0) {
            XMD_FREE_SAFE(new_parameters);
        }
        return -1;
    }
    
    *parameters_ptr = new_parameters;
    (*parameters_ptr)[*count_ptr] = param_copy;
    (*count_ptr)++;
    return 0;
}
