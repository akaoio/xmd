/**
 * @file ast_evaluator_create.c
 * @brief Create AST evaluator
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_evaluator.h"

/**
 * @brief Create AST evaluator
 * @param variables Variable store
 * @param ctx Processor context
 * @return Evaluator or NULL on error
 */
ast_evaluator* ast_evaluator_create(store* variables, processor_context* ctx) {
    if (!variables || !ctx) {
        return NULL;
    }
    
    ast_evaluator* evaluator = malloc(sizeof(ast_evaluator));
    if (!evaluator) {
        return NULL;
    }
    
    evaluator->variables = variables;
    evaluator->ctx = ctx;
    evaluator->output_buffer = NULL;
    evaluator->output_size = 0;
    evaluator->has_error = false;
    evaluator->error_message = NULL;
    evaluator->in_statement_context = false;
    
    return evaluator;
}