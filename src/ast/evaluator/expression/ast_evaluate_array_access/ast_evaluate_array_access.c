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
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate array access node (array[index])
 * @param node Array access AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_array_access(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_ARRAY_ACCESS, NULL, "ast_evaluate_array_access: Invalid node type");
    
    // Check if the array expression is an identifier (most common case)
    if (node->data.array_access.array_expr->type == AST_IDENTIFIER) {
        const char* array_name = node->data.array_access.array_expr->data.identifier.name;
        
        // Get the actual array variable from store
        variable* array_var = store_get(evaluator->variables, array_name);
        XMD_VALIDATE_PTR_RETURN(array_var, NULL);
        
        // Check if it's actually an array
        if (variable_get_type(array_var) != VAR_ARRAY) {
            XMD_ERROR_RETURN(NULL, "Variable '%s' is not an array (type: %d)", array_name, variable_get_type(array_var));
        }
        
        // Evaluate the index expression
        ast_value* index_value = ast_evaluate(node->data.array_access.index_expr, evaluator);
        XMD_VALIDATE_PTR_RETURN(index_value, NULL);
        
        // Convert index to integer
        int index = 0;
        if (index_value->type == AST_VAL_NUMBER) {
            index = (int)index_value->value.number_value;
        } else if (index_value->type == AST_VAL_STRING) {
            // Try to parse string as number
            char* endptr;
            double num = strtod(index_value->value.string_value, &endptr);
            if (*endptr == '\0') {
                index = (int)num;
            } else {
                XMD_FREE_SAFE(index_value);
                XMD_ERROR_RETURN(NULL, "Invalid array index: %s", index_value->value.string_value);
            }
        } else {
            XMD_FREE_SAFE(index_value);
            XMD_ERROR_RETURN(NULL, "Array index must be a number%s", "");
        }
        
        // Get array size for bounds checking
        size_t array_size = variable_array_size(array_var);
        
        // Bounds checking
        if (index < 0 || (size_t)index >= array_size) {
            XMD_FREE_SAFE(index_value);
            XMD_ERROR_RETURN(NULL, "Array index %d out of bounds (size: %zu)", index, array_size);
        }
        
        // Get the element at the index
        variable* element = variable_array_get(array_var, (size_t)index);
        if (!element) {
            XMD_FREE_SAFE(index_value);
            return NULL;
        }
        
        // Convert the element to an AST value
        ast_value* result = NULL;
        variable_type elem_type = variable_get_type(element);
        
        switch (elem_type) {
            case VAR_STRING: {
                const char* str = variable_get_string(element);
                result = ast_value_create_string(str ? str : "");
                break;
            }
            case VAR_NUMBER: {
                double num = variable_get_number(element);
                result = ast_value_create_number(num);
                break;
            }
            case VAR_BOOLEAN: {
                bool val = variable_get_boolean(element);
                result = ast_value_create_boolean(val);
                break;
            }
            case VAR_ARRAY:
            case VAR_OBJECT: {
                // Nested arrays/objects - convert to string representation
                const char* str = variable_to_string(element);
                result = ast_value_create_string(str ? str : "[complex]");
                break;
            }
            default: {
                // Fallback to string conversion
                const char* str = variable_to_string(element);
                result = ast_value_create_string(str ? str : "");
                break;
            }
        }
        
        // Clean up
        XMD_FREE_SAFE(index_value);
        
        return result;
    }
    
    // If not a simple identifier, handle as complex expression (e.g., function returns array)
    fprintf(stderr, "WARNING: Complex array expressions not yet fully supported\n");
    return NULL;
}
