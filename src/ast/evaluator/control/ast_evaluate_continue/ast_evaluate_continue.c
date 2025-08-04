
/**
 * @file ast_evaluate_continue.c
 * @brief Implementation of ast_evaluate_continue function
 * 
 * This file contains ONLY the ast_evaluate_continue function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "error.h"
#include "utils.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate continue statement  
 * @param node Continue statement node
 * @param evaluator Evaluator context
 * @return NULL (continue statements don't return values)
 */
ast_value* ast_evaluate_continue(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_CONTINUE, NULL, "ast_evaluate_continue: Invalid node type");
    
    // ENHANCED: Continue statement using control flow macro pattern
    // Set continue signal using consolidated error handling
    evaluator->has_error = true;
    XMD_CLEANUP_RESOURCE(evaluator->error_message, xmd_free);
    evaluator->error_message = xmd_strdup("__CONTINUE__");
    XMD_VALIDATE_PTR_RETURN(evaluator->error_message, NULL);
    return ast_value_create_string("");
}
