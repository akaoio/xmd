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
/**
 * @brief Convert variable to ast_value - MISSING FUNCTION
 */
ast_value* ast_value_from_variable(variable* var) {
    if (!var) return NULL;
    
    switch (var->type) {
        case VAR_STRING:
            return ast_value_create_string(var->value.string_value);
        case VAR_NUMBER:
            return ast_value_create_number(var->value.number_value);
        case VAR_BOOLEAN:
            return ast_value_create_boolean(var->value.boolean_value);
        case VAR_ARRAY: {
            // Create array ast_value
            ast_value* array_val = ast_value_create_array();
            if (!array_val) return NULL;
            
            array_val->value.array_value.element_count = var->value.array_value->count;
            array_val->value.array_value.elements = xmd_calloc(var->value.array_value->count, sizeof(ast_value*));
            for (size_t i = 0; i < var->value.array_value->count; i++) {
                array_val->value.array_value.elements[i] = ast_value_from_variable(var->value.array_value->items[i]);
            }
            return array_val;
        }
        default:
            return ast_value_create_string("");
    }
}
