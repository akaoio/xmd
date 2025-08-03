/**
 * @file ast_value_to_variable.c
 *
 * @brief Implementation of ast_value_to_variable function
 * 
 * This file contains ONLY the ast_value_to_variable function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "variable.h"
#include "utils.h"
/**
 * @brief Convert AST value to variable
 * @param value AST value to convert
 * @return Variable or NULL on error
 */
variable* ast_value_to_variable(ast_value* value) {
    if (!value) {
        return NULL;
    }
    
    switch (value->type) {
        case AST_VAL_STRING:
            return variable_create_string(value->value.string_value);
            
        case AST_VAL_NUMBER:
            return variable_create_number(value->value.number_value);
            
        case AST_VAL_BOOLEAN:
            return variable_create_boolean(value->value.boolean_value);
            
        case AST_VAL_ARRAY: {
            // Create array variable
            variable* array_var = variable_create_array();
            if (!array_var) {
                return NULL;
            }
            
            // Convert each ast_value element to variable and add to array
            for (size_t i = 0; i < value->value.array_value.element_count; i++) {
                variable* elem_var = ast_value_to_variable(value->value.array_value.elements[i]);
                if (!elem_var) {
                    variable_unref(array_var);
                    return NULL;
                }
                
                if (!variable_array_add(array_var, elem_var)) {
                    variable_unref(elem_var);
                    variable_unref(array_var);
                    return NULL;
                }
                
                // Release our reference since array now owns it
                variable_unref(elem_var);
            }
            return array_var;
        }
        
        default:
            return NULL;
    }
}
