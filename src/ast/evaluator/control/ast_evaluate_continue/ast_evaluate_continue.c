
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

/**
 * @brief Evaluate continue statement  
 * @param node Continue statement node
 * @param evaluator Evaluator context
 * @return NULL (continue statements don't return values)
 */
ast_value* ast_evaluate_continue(ast_node* node, ast_evaluator* evaluator) {
    if (!node || !evaluator || node->type != AST_CONTINUE) {
        return NULL;
    }
    
    // DEVELOPER ENHANCEMENT: Enhanced continue statement signaling
    // Improved loop context handling with proper continue signaling
    evaluator->has_error = true;
    if (evaluator->error_message) {
        free(evaluator->error_message);
    }
    evaluator->error_message = xmd_strdup("__CONTINUE__");
    printf("DEBUG: Continue statement executed - signaling next iteration\n");
    return ast_value_create_string("");
}
