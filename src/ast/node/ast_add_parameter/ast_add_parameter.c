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
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Add a parameter to a function or method definition
 * @param function Function or method definition node
 * @param parameter Parameter name to add
 * @return 0 on success, -1 on error
 */
int ast_add_parameter(ast_node* function, const char* parameter) {
    XMD_VALIDATE_PTRS_RETVAL(-1, function, parameter);
    
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
        XMD_ERROR_STATUS(-1, "Node type does not support parameters");
    }
    
    size_t old_count = *count_ptr;
    size_t new_count = old_count + 1;
    
    XMD_AST_ARRAY_RESIZE(*parameters_ptr, old_count, new_count, char*, -1);
    
    // Duplicate parameter name for the new slot
    XMD_STRDUP_VALIDATED((*parameters_ptr)[old_count], parameter, -1);
    
    *count_ptr = new_count;
    return 0;
}
