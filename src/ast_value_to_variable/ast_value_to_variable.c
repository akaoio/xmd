/**
 * @file ast_value_to_variable.c
 * @brief Convert AST value to variable
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <stdio.h>
#include "../../include/ast_evaluator.h"

/**
 * @brief Convert AST value to variable
 * @param value AST value
 * @return Variable or NULL on error
 */
variable* ast_value_to_variable(ast_value* value) {
    if (!value) {
        return NULL;
    }
    
    switch (value->type) {
        case AST_VAL_STRING:
            return variable_create_string(value->value.string_value);
            
        case AST_VAL_NUMBER: {
            // Convert number to string representation
            char num_str[64];
            snprintf(num_str, sizeof(num_str), "%.10g", value->value.number_value);
            return variable_create_string(num_str);
        }
        
        case AST_VAL_BOOLEAN:
            return variable_create_string(value->value.boolean_value ? "true" : "false");
            
        case AST_VAL_NULL:
        default:
            return variable_create_string("");
    }
}