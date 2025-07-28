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
            
        case AST_VAL_ARRAY: {
            variable* array = variable_create_array();
            if (!array) {
                return NULL;
            }
            
            for (size_t i = 0; i < value->value.array_value.element_count; i++) {
                variable* element = ast_value_to_variable(value->value.array_value.elements[i]);
                if (element) {
                    if (!variable_array_add(array, element)) {
                        variable_unref(element);
                        variable_unref(array);
                        return NULL;
                    }
                    variable_unref(element); // Array took reference
                }
            }
            
            return array;
        }
            
        case AST_VAL_NULL:
        default:
            return variable_create_string("");
    }
}