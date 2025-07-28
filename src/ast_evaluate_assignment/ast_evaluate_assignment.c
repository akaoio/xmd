/**
 * @file ast_evaluate_assignment.c
 * @brief Evaluate assignment statement
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include "../../include/ast_evaluator.h"

/**
 * @brief Evaluate assignment statement
 * @param node Assignment AST node
 * @param evaluator Evaluator context
 * @return 0 on success, -1 on error
 */
int ast_evaluate_assignment(ast_node* node, ast_evaluator* evaluator) {
    if (!node || !evaluator || node->type != AST_ASSIGNMENT) {
        return -1;
    }
    
    // Evaluate the right-hand side
    ast_value* value = ast_evaluate(node->data.assignment.value, evaluator);
    if (!value) {
        return -1;
    }
    
    // Convert AST value to variable
    variable* var = ast_value_to_variable(value);
    ast_value_free(value);
    
    if (!var) {
        return -1;
    }
    
    // Handle assignment operators
    if (node->data.assignment.op == BINOP_ASSIGN) {
        // Simple assignment: var = value
        store_set(evaluator->variables, node->data.assignment.variable, var);
    } else if (node->data.assignment.op == BINOP_ASSIGN_ADD) {
        // Append assignment: var += value
        variable* existing = store_get(evaluator->variables, node->data.assignment.variable);
        if (existing && existing->type == VAR_STRING && var->type == VAR_STRING) {
            // String concatenation
            size_t new_len = strlen(existing->value.string_value) + strlen(var->value.string_value) + 1;
            char* new_value = malloc(new_len);
            if (new_value) {
                snprintf(new_value, new_len, "%s%s", existing->value.string_value, var->value.string_value);
                variable* concat_var = variable_create_string(new_value);
                if (concat_var) {
                    store_set(evaluator->variables, node->data.assignment.variable, concat_var);
                    variable_unref(concat_var);
                }
                free(new_value);
            }
        } else {
            // Just set the new value if types don't match or existing doesn't exist
            store_set(evaluator->variables, node->data.assignment.variable, var);
        }
    }
    
    variable_unref(var);
    return 0;
}