/**
 * @file ast_evaluate_yield.c
 * @brief Implementation of ast_evaluate_yield function
 * 
 * This file contains ONLY the ast_evaluate_yield function.
 * One function per file - Genesis principle compliance.
 * Evaluates yield statements in generator functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Evaluate yield statement
 * @param node Yield AST node
 * @param evaluator AST evaluator context
 * @return Yielded value or NULL on error
 */
ast_value* ast_evaluate_yield(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_AST_VALIDATE_TYPE(node, AST_YIELD, NULL, "ast_evaluate_yield");
    
    // If there's a value to yield, evaluate it
    if (node->data.yield_stmt.value) {
        ast_value* yielded_value = ast_evaluate(node->data.yield_stmt.value, evaluator);
        if (yielded_value) {
            return yielded_value;
        }
    }
    
    // Bare yield - return empty string for now
    return ast_value_create_string("");
}