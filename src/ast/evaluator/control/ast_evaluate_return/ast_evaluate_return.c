/**
 * @file ast_evaluate_return.c
 * @brief Implementation of ast_evaluate_return function
 * 
 * This file contains ONLY the ast_evaluate_return function.
 * One function per file - Genesis principle compliance.
 */

#include <stdlib.h>
#include "ast.h"
#include "ast_node.h"
#include "ast_evaluator.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Evaluate return statement
 * @param node Return statement AST node
 * @param evaluator Evaluator context
 * @return Return value or NULL
 */
ast_value* ast_evaluate_return(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_RETURN, NULL, "ast_evaluate_return: Invalid node type");
    
    // Evaluate return value if present
    ast_value* return_value = NULL;
    if (node->data.return_stmt.value) {
        return_value = ast_evaluate(node->data.return_stmt.value, evaluator);
    }
    
    // Set return value in evaluator context
    if (evaluator->return_value) {
        ast_value_free(evaluator->return_value);
    }
    evaluator->return_value = return_value;
    evaluator->should_return = true;
    
    // Return the value to signal return encountered
    return return_value;
}