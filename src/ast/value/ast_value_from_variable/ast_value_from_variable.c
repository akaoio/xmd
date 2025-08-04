/**
 * @file ast_value_from_variable.c
 * @brief Implementation of ast_value_from_variable function
 * 
 * This file contains ONLY the ast_value_from_variable function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "variable.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Convert variable to ast_value - MISSING FUNCTION
 */
ast_value* ast_value_from_variable(variable* var) {
    XMD_VALIDATE_PTRS(NULL, var);
    
    // Use the XMD_VARIABLE_TYPE_DISPATCH macro to eliminate switch duplication
    XMD_VARIABLE_TYPE_DISPATCH(var,
        // VAR_STRING case
        return ast_value_create_string(var->value.string_value),
        
        // VAR_NUMBER case
        return ast_value_create_number(var->value.number_value),
        
        // VAR_BOOLEAN case
        return ast_value_create_boolean(var->value.boolean_value),
        
        // VAR_ARRAY case
        {
            // Create array ast_value
            ast_value* array_val = ast_value_create_array();
            if (!array_val) return NULL;
            
            array_val->value.array_value.element_count = var->value.array_value->count;
            array_val->value.array_value.elements = xmd_calloc(var->value.array_value->count, sizeof(ast_value*));
            for (size_t i = 0; i < var->value.array_value->count; i++) {
                array_val->value.array_value.elements[i] = ast_value_from_variable(var->value.array_value->items[i]);
            }
            return array_val;
        },
        
        // VAR_OBJECT case
        return ast_value_create_string(""),
        
        // VAR_NULL case  
        return ast_value_create_string(""),
        
        // default case
        return ast_value_create_string("")
    );
}
