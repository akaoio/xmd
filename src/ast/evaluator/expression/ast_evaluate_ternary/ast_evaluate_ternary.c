/**
 * @file ast_evaluate_ternary.c
 * @brief Implementation of ast_evaluate_ternary function
 * 
 * This file contains ONLY the ast_evaluate_ternary function.
 * One function per file - Genesis principle compliance.
 * Evaluates ternary operator expressions (condition ? true_expr : false_expr)
 */

#include <stdbool.h>
#include "ast.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Evaluate ternary operator AST node
 * @param node Ternary AST node to evaluate
 * @param evaluator AST evaluator context
 * @return Result value or NULL on error
 */
ast_value* ast_evaluate_ternary(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_AST_VALIDATE_TYPE(node, AST_TERNARY, NULL, "ast_evaluate_ternary");
    
    // Evaluate condition
    ast_value* condition_val = ast_evaluate(node->data.ternary.condition, evaluator);
    XMD_VALIDATE_PTR_RETURN(condition_val, NULL);
    
    // Convert condition to boolean
    bool is_true = false;
    XMD_VARIABLE_TYPE_DISPATCH(condition_val,
        /* string */ is_true = (condition_val->value.string_value && strlen(condition_val->value.string_value) > 0),
        /* number */ is_true = (condition_val->value.number_value != 0.0),
        /* boolean */ is_true = condition_val->value.boolean_value,
        /* array */ is_true = (condition_val->value.array_value.element_count > 0),
        /* object */ is_true = true, // Objects are always truthy
        /* null */ is_true = false,
        /* default */ is_true = false
    );
    
    ast_value_free(condition_val);
    
    // Evaluate appropriate branch
    if (is_true) {
        return ast_evaluate(node->data.ternary.true_expr, evaluator);
    } else {
        return ast_evaluate(node->data.ternary.false_expr, evaluator);
    }
}