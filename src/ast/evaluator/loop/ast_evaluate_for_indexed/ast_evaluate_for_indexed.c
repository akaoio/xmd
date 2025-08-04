/**
 * @file ast_evaluate_for_indexed.c
 *
 * @brief Implementation of ast_evaluate_for_indexed function
 * 
 * This file contains ONLY the ast_evaluate_for_indexed function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate for indexed loop (for i, item in array)
 * @param node For indexed AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_for_indexed(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_FOR_INDEXED, NULL, "ast_evaluate_for_indexed: Invalid node type");
    
    // Evaluate array expression
    ast_value* array_val = ast_evaluate(node->data.for_indexed.array_expr, evaluator);
    if (!array_val || array_val->type != AST_VAL_ARRAY) {
        XMD_FREE_SAFE(array_val);
        XMD_ERROR_RETURN(NULL, "For indexed requires an array%s", "");
    }
    
    ast_value* result = NULL;
    
    // Iterate over array elements with index
    for (size_t i = 0; i < array_val->value.array_value.element_count; i++) {
        // Set index variable
        variable* index_var = variable_create_number((double)i);
        if (index_var) {
            store_set(evaluator->variables, node->data.for_indexed.index_var, index_var);
            variable_unref(index_var);
        }
        
        // Set item variable
        ast_value* element = array_val->value.array_value.elements[i];
        if (element) {
            variable* item_var = ast_value_to_variable(element);
            if (item_var) {
                store_set(evaluator->variables, node->data.for_indexed.item_var, item_var);
                variable_unref(item_var);
            }
        }
        
        // Execute body
        XMD_FREE_SAFE(result);
        result = ast_evaluate(node->data.for_indexed.body, evaluator);
        
        // Check for break/continue
        if (evaluator->has_error) {
            break;
        }
    }
    
    XMD_FREE_SAFE(array_val);
    return result;
}