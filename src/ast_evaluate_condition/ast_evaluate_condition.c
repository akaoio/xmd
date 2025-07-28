/**
 * @file ast_evaluate_condition.c
 * @brief AST-based condition evaluation implementation
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_evaluator.h"
#include "../../include/ast_parser.h"
#include "../../include/lexer_enhanced.h"

/**
 * @brief Evaluate condition using AST parsing (replaces string-based evaluate_condition)
 * @param condition Condition string to evaluate (e.g., "var == value")
 * @param variables Variable store for variable lookups
 * @return true if condition is true, false otherwise
 */
bool ast_evaluate_condition(const char* condition, store* variables) {
    if (!condition || !variables) {
        return false;
    }
    
    // Tokenize the condition
    token* tokens = lexer_enhanced_tokenize(condition, "condition");
    if (!tokens) {
        return false;
    }
    
    // Parse into AST
    ast_node* ast = ast_parse_program(tokens);
    token_list_free(tokens);
    
    if (!ast || ast->type != AST_PROGRAM || ast->data.program.statement_count == 0) {
        ast_free(ast);
        return false;
    }
    
    // Create temporary processor context for evaluation
    processor_context temp_ctx = {0};
    temp_ctx.variables = variables;
    
    // Create evaluator
    ast_evaluator* evaluator = ast_evaluator_create(variables, &temp_ctx);
    if (!evaluator) {
        ast_free(ast);
        return false;
    }
    
    // Evaluate the expression
    ast_node* expr = ast->data.program.statements[0];
    ast_value* result = ast_evaluate(expr, evaluator);
    
    bool condition_result = false;
    if (result) {
        switch (result->type) {
            case AST_VAL_BOOLEAN:
                condition_result = result->value.boolean_value;
                break;
            case AST_VAL_NUMBER:
                condition_result = (result->value.number_value != 0.0);
                break;
            case AST_VAL_STRING:
                condition_result = (result->value.string_value && 
                                  strlen(result->value.string_value) > 0 &&
                                  strcmp(result->value.string_value, "false") != 0 &&
                                  strcmp(result->value.string_value, "0") != 0);
                break;
            case AST_VAL_NULL:
            default:
                condition_result = false;
                break;
        }
    }
    
    ast_value_free(result);
    ast_evaluator_free(evaluator);
    ast_free(ast);
    
    return condition_result;
}