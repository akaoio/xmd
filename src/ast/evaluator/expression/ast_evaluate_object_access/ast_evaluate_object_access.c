/**
 * @file ast_evaluate_object_access.c
 * @brief Implementation of ast_evaluate_object_access function
 * 
 * This file contains ONLY the ast_evaluate_object_access function.
 * One function per file - Genesis principle compliance.
 * Handles evaluation of obj.property expressions.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../../../include/ast.h"
#include "../../../../../include/utils.h"
#include "../../../../utils/common/common_macros.h"

// Forward declarations
ast_value* ast_evaluate(ast_node* node, ast_evaluator* evaluator);
ast_value* ast_value_create_string(const char* str);
ast_value* ast_value_create_number(double num);
ast_value* ast_value_create_boolean(bool val);

/**
 * @brief Evaluate object access node (obj.property)
 * @param node Object access AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_object_access(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    
    if (node->type != AST_OBJECT_ACCESS) {
        XMD_ERROR_RETURN(NULL, "Expected AST_OBJECT_ACCESS node, got type %d", node->type);
    }
    
    // Evaluate the object expression (should be an identifier or expression that results in an object)
    ast_value* object_value = ast_evaluate(node->data.object_access.object_expr, evaluator);
    if (!object_value) {
        XMD_ERROR_RETURN(NULL, "Failed to evaluate object expression");
    }
    
    // Check if the object expression is an identifier
    if (node->data.object_access.object_expr->type == AST_IDENTIFIER) {
        const char* object_name = node->data.object_access.object_expr->data.identifier.name;
        const char* property_name = node->data.object_access.property_name;
        
        
        // Get the actual object variable from store
        variable* object_var = store_get(evaluator->variables, object_name);
        if (!object_var) {
            XMD_FREE_SAFE(object_value);
            XMD_ERROR_RETURN(ast_value_create_string(""), "Object variable '%s' not found", object_name);
        }
        
        // Check if it's actually an object
        if (variable_get_type(object_var) != VAR_OBJECT) {
            XMD_FREE_SAFE(object_value);
            XMD_ERROR_RETURN(ast_value_create_string(""), "Variable '%s' is not an object (type: %d)", 
                           object_name, variable_get_type(object_var));
        }
        
        // Get the property from the object
        variable* property_var = variable_object_get(object_var, property_name);
        if (!property_var) {
            XMD_FREE_SAFE(object_value);
            XMD_ERROR_RETURN(ast_value_create_string(""), "Property '%s' not found in object '%s'", 
                           property_name, object_name);
        }
        
        // Convert the property to an AST value
        ast_value* result = NULL;
        variable_type prop_type = variable_get_type(property_var);
        
        switch (prop_type) {
            case VAR_STRING: {
                const char* str = variable_get_string(property_var);
                result = ast_value_create_string(str ? str : "");
                break;
            }
            case VAR_NUMBER: {
                double num = variable_get_number(property_var);
                result = ast_value_create_number(num);
                break;
            }
            case VAR_BOOLEAN: {
                bool val = variable_get_boolean(property_var);
                result = ast_value_create_boolean(val);
                break;
            }
            case VAR_ARRAY:
            case VAR_OBJECT: {
                // Nested objects/arrays - convert to string representation
                const char* str = variable_to_string(property_var);
                result = ast_value_create_string(str ? str : "[complex]");
                break;
            }
            default: {
                // Fallback to string conversion
                const char* str = variable_to_string(property_var);
                result = ast_value_create_string(str ? str : "");
                break;
            }
        }
        
        // Clean up
        XMD_FREE_SAFE(object_value);
        
        return result;
    }
    
    // If not a simple identifier, handle as complex expression
    fprintf(stderr, "WARNING: Complex object expressions not yet fully supported\n");
    XMD_FREE_SAFE(object_value);
    return ast_value_create_string("");
}
