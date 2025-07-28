/**
 * @file ast_evaluate_concatenation_expression.c
 * @brief AST-based concatenation expression evaluation
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_evaluator.h"
#include "../../include/ast_parser.h"
#include "../../include/lexer_enhanced.h"
#include "../../include/xmd_processor_internal.h"

/**
 * @brief Evaluate concatenation expression using AST
 * @param expr Expression to evaluate (e.g., "- " + item + "\n")
 * @param ctx Processor context for variable lookups
 * @return Evaluated string result or NULL on error (caller must free)
 */
char* ast_evaluate_concatenation_expression(const char* expr, processor_context* ctx) {
    if (!expr || !ctx) {
        return NULL;
    }
    
    // Tokenize the expression
    token* tokens = lexer_enhanced_tokenize(expr, "concat_expression");
    if (!tokens) {
        return NULL;
    }
    
    // Parse into AST
    ast_node* ast = ast_parse_program(tokens);
    token_list_free(tokens);
    
    if (!ast || ast->type != AST_PROGRAM || ast->data.program.statement_count == 0) {
        ast_free(ast);
        return NULL;
    }
    
    // Create evaluator
    ast_evaluator* evaluator = ast_evaluator_create(ctx->variables, ctx);
    if (!evaluator) {
        ast_free(ast);
        return NULL;
    }
    
    // Evaluate the expression
    ast_node* expr_node = ast->data.program.statements[0];
    ast_value* result = ast_evaluate(expr_node, evaluator);
    
    char* result_str = NULL;
    if (result) {
        if (result->type == AST_VAL_STRING && result->value.string_value) {
            result_str = strdup(result->value.string_value);
        } else if (result->type == AST_VAL_NUMBER) {
            result_str = malloc(64);
            if (result_str) {
                snprintf(result_str, 64, "%.15g", result->value.number_value);
            }
        } else if (result->type == AST_VAL_BOOLEAN) {
            result_str = strdup(result->value.boolean_value ? "true" : "false");
        } else {
            result_str = strdup("");
        }
        ast_value_free(result);
    }
    
    ast_evaluator_free(evaluator);
    ast_free(ast);
    
    return result_str;
}