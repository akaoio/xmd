/**
 * @file ast_evaluate_spread.c
 *
 * @brief Implementation of ast_evaluate_spread function
 * 
 * This file contains ONLY the ast_evaluate_spread function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ast_evaluator.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate spread operator
 * @param node Spread AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_spread(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_SPREAD, NULL, "ast_evaluate_spread: Invalid node type");
    
    // Evaluate the expression to spread
    ast_value* source = ast_evaluate(node->data.spread.expression, evaluator);
    if (!source) {
        return NULL;
    }
    
    // Handle array spreading
    if (node->data.spread.in_array) {
        if (source->type == AST_VAL_ARRAY) {
            // Create a new array containing all elements from source
            ast_value* result = ast_value_create_array();
            if (!result) {
                ast_value_free(source);
                return NULL;
            }
            
            // Copy all elements from source array
            for (size_t i = 0; i < source->value.array_value.element_count; i++) {
                ast_value* element = source->value.array_value.elements[i];
                if (element) {
                    // Create a copy of the element
                    ast_value* element_copy = NULL;
                    switch (element->type) {
                        case AST_VAL_STRING:
                            element_copy = ast_value_create_string(element->value.string_value);
                            break;
                        case AST_VAL_NUMBER:
                            element_copy = ast_value_create_number(element->value.number_value);
                            break;
                        case AST_VAL_BOOLEAN:
                            element_copy = ast_value_create_boolean(element->value.boolean_value);
                            break;
                        case AST_VAL_NULL:
                            element_copy = calloc(1, sizeof(ast_value));
                            if (element_copy) element_copy->type = AST_VAL_NULL;
                            break;
                        case AST_VAL_ARRAY:
                            // For nested arrays, we'd need recursive copying
                            // For now, create a placeholder
                            element_copy = ast_value_create_string("[array]");
                            break;
                    }
                    
                    if (element_copy) {
                        ast_value_array_add(result, element_copy);
                    }
                }
            }
            
            ast_value_free(source);
            return result;
        } else {
            // Non-array values become single-element arrays when spread
            ast_value* result = ast_value_create_array();
            if (result) {
                ast_value_array_add(result, source);
                return result;
            }
        }
    }
    
    // Handle object spreading
    if (node->data.spread.in_object) {
        // For object spreading, we would need to return object properties
        // This is complex and would require object AST values
        // For now, return the source as-is
        return source;
    }
    
    // Fallback: return source unchanged
    return source;
}