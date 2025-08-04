
/**
 * @file ast_evaluator_create.c
 * @brief Implementation of ast_evaluator_create function
 * 
 * This file contains ONLY the ast_evaluator_create function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdlib.h>
#include "utils/common/common_macros.h"
#include "ast_evaluator.h"
#include "ast_node.h"
#include "error.h"
#include "store.h"
#include "variable.h"
#include "xmd_processor_internal.h"

/**
 * @brief Create and initialize AST evaluator
 * @param variables Variable store
 * @param ctx Processor context
 * @return New evaluator or NULL on error
 */
ast_evaluator* ast_evaluator_create(store* variables, processor_context* ctx) {
    XMD_CREATE_VALIDATED(evaluator, ast_evaluator, sizeof(ast_evaluator), NULL);
    
    evaluator->variables = variables ? variables : store_create();
    evaluator->functions = store_create();  // Create functions store
    evaluator->ctx = ctx;
    evaluator->output_buffer = NULL;
    evaluator->output_size = 0;
    evaluator->output_capacity = 0;
    evaluator->has_error = false;
    evaluator->error_message = NULL;
    evaluator->in_statement_context = false;
    
    // Initialize control flow members
    evaluator->return_value = NULL;
    evaluator->should_return = false;
    
    return evaluator;
}
