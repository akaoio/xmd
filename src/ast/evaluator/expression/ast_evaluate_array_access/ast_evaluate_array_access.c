/**
 * @file ast_evaluate_array_access.c
 * @brief Implementation of ast_evaluate_array_access function
 * 
 * This file contains ONLY the ast_evaluate_array_access function.
 * One function per file - Genesis principle compliance.
 * Handles evaluation of array[index] expressions.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "store.h"
#include "variable.h"
#include "utils/common/common_macros.h"

/**
 * @brief Evaluate array access node (array[index])
 * @param node Array access AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_array_access(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    
    if (node->type != AST_ARRAY_ACCESS) {
        XMD_ERROR_RETURN(NULL, "Expected AST_ARRAY_ACCESS node, got type %d", node->type);
    }
    
    // Evaluate the array expression (should be an identifier or expression that results in an array)
    ast_value* array_value = ast_evaluate(node->data.array_access.array_expr, evaluator);
    if (!array_value) {
        XMD_ERROR_RETURN(NULL, "Failed to evaluate array expression");
    }
    
    // Check if the array expression is an identifier
    if (node->data.array_access.array_expr->type == AST_IDENTIFIER) {
        const char* array_name = node->data.array_access.array_expr->data.identifier.name;
        printf("DEBUG: Array access for variable '%s'\n", array_name);
        
        // Get the actual array variable from store
        variable* array_var = store_get(evaluator->variables, array_name);
        if (!array_var) {
            XMD_FREE_SAFE(array_value);
            XMD_ERROR_RETURN(ast_value_create_string(""), "Array variable '%s' not found", array_name);
        }
        
        // Check if it's actually an array
        if (variable_get_type(array_var) != VAR_ARRAY) {
            XMD_FREE_SAFE(array_value);
            XMD_ERROR_RETURN(ast_value_create_string(""), "Variable '%s' is not an array (type: %d)", array_name, variable_get_type(array_var));
        }
        
        // Evaluate the index expression
        ast_value* index_value = ast_evaluate(node->data.array_access.index_expr, evaluator);
        if (!index_value) {
            XMD_FREE_SAFE(array_value);
            XMD_ERROR_RETURN(ast_value_create_string(""), "Failed to evaluate index expression");
        }
        
        // Convert index to integer
        int index = 0;
        if (index_value->type == AST_VAL_NUMBER) {
            index = (int)index_value->value.number_value;
            printf("DEBUG: Array index evaluated to %d\n", index);
        } else if (index_value->type == AST_VAL_STRING) {
            // Try to parse string as number
            char* endptr;
            double num = strtod(index_value->value.string_value, &endptr);
            if (*endptr == '\0') {
                index = (int)num;
                printf("DEBUG: Array index string '%s' converted to %d\n", 
                       index_value->value.string_value, index);
            } else {
                XMD_FREE_SAFE(array_value);
                XMD_FREE_SAFE(index_value);
                XMD_ERROR_RETURN(ast_value_create_string(""), "Invalid array index: %s", index_value->value.string_value);
            }
        } else {
            XMD_FREE_SAFE(array_value);
            XMD_FREE_SAFE(index_value);
            XMD_ERROR_RETURN(ast_value_create_string(""), "Array index must be a number");
        }
        
        // Get array size for bounds checking
        size_t array_size = variable_array_size(array_var);
        printf("DEBUG: Array size: %zu, accessing index: %d\n", array_size, index);
        
        // Bounds checking
        if (index < 0 || (size_t)index >= array_size) {
            XMD_FREE_SAFE(array_value);
            XMD_FREE_SAFE(index_value);
            XMD_ERROR_RETURN(ast_value_create_string(""), "Array index %d out of bounds (size: %zu)", index, array_size);
        }
        
        // Get the element at the index
        variable* element = variable_array_get(array_var, (size_t)index);
        if (!element) {
            XMD_FREE_SAFE(array_value);
            XMD_FREE_SAFE(index_value);
            XMD_ERROR_RETURN(ast_value_create_string(""), "Failed to get array element at index %d", index);
        }
        
        // Convert the element to an AST value
        ast_value* result = NULL;
        variable_type elem_type = variable_get_type(element);
        printf("DEBUG: Array element at index %d has type %d\n", index, elem_type);
        
        switch (elem_type) {
            case VAR_STRING: {
                const char* str = variable_get_string(element);
                printf("DEBUG: Array element string value: '%s'\n", str ? str : "NULL");
                result = ast_value_create_string(str ? str : "");
                break;
            }
            case VAR_NUMBER: {
                double num = variable_get_number(element);
                printf("DEBUG: Array element number value: %f\n", num);
                result = ast_value_create_number(num);
                break;
            }
            case VAR_BOOLEAN: {
                bool val = variable_get_boolean(element);
                printf("DEBUG: Array element boolean value: %s\n", val ? "true" : "false");
                result = ast_value_create_boolean(val);
                break;
            }
            case VAR_ARRAY:
            case VAR_OBJECT: {
                // Nested arrays/objects - convert to string representation
                const char* str = variable_to_string(element);
                printf("DEBUG: Array element array/object string: '%s'\n", str ? str : "NULL");
                result = ast_value_create_string(str ? str : "[complex]");
                break;
            }
            default: {
                // Fallback to string conversion
                const char* str = variable_to_string(element);
                printf("DEBUG: Array element fallback string: '%s'\n", str ? str : "NULL");
                result = ast_value_create_string(str ? str : "");
                break;
            }
        }
        
        // Clean up
        XMD_FREE_SAFE(array_value);
        XMD_FREE_SAFE(index_value);
        
        return result;
    }
    
    // If not a simple identifier, handle as complex expression
    fprintf(stderr, "WARNING: Complex array expressions not yet fully supported\n");
    XMD_FREE_SAFE(array_value);
    return ast_value_create_string("");
}
