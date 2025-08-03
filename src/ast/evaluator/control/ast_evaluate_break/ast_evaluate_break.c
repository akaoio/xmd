
/**
 * @file ast_evaluate_break.c
 * @brief Implementation of ast_evaluate_break function
 * 
 * This file contains ONLY the ast_evaluate_break function.
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

/**
 * @brief Evaluate break statement
 * @param node Break statement node
 * @param evaluator Evaluator context
 * @return NULL (break statements don't return values)
 */
ast_value* ast_evaluate_break(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_BREAK, NULL, "ast_evaluate_break: Invalid node type");
    
    // DEVELOPER ENHANCEMENT: Enhanced break statement signaling
    // Improved loop context handling with proper break signaling
    evaluator->has_error = true;
    if (evaluator->error_message) {
        XMD_FREE_SAFE(evaluator->error_message);
    }
    evaluator->error_message = xmd_strdup("__BREAK__");
    return ast_value_create_string("");
}
