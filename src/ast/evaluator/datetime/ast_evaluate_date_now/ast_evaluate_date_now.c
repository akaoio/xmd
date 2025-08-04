/**
 * @file ast_evaluate_date_now.c
 *
 * @brief Implementation of ast_evaluate_date_now function
 * 
 * This file contains ONLY the ast_evaluate_date_now function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ast.h"
#include "ast_evaluator.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate Date.now() - returns current timestamp
 * @param node Function call AST node
 * @param evaluator Evaluator context
 * @return AST value with current timestamp or NULL on error
 */
ast_value* ast_evaluate_date_now(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    
    // Get current time as seconds since epoch
    time_t current_time = time(NULL);
    
    // Convert to milliseconds (JavaScript-style timestamp)
    double timestamp_ms = (double)current_time * 1000.0;
    
    return ast_value_create_number(timestamp_ms);
}