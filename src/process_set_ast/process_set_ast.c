/**
 * @file process_set_ast.c
 * @brief Replace string-based process_set with AST evaluation
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
 * @brief Replace string-based process_set with AST evaluation
 * @param args Arguments for set directive
 * @param ctx Processor context  
 * @param output Buffer to store output
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_set_ast(const char* args, processor_context* ctx, char* output, size_t output_size) {
    if (!args || !ctx || !output || output_size == 0) {
        if (output && output_size > 0) {
            output[0] = '\0';
        }
        return -1;
    }
    
    // Check if we should execute this block
    if (!should_execute_block(ctx)) {
        output[0] = '\0';
        return 0;
    }
    
    // Tokenize the assignment string
    token* tokens = lexer_enhanced_tokenize(args, "set_directive");
    if (!tokens) {
        output[0] = '\0';
        return -1;
    }
    
    // Parse into AST
    ast_node* ast = ast_parse_program(tokens);
    token_list_free(tokens);
    
    if (!ast) {
        output[0] = '\0';
        return -1;
    }
    
    // Create evaluator
    ast_evaluator* evaluator = ast_evaluator_create(ctx->variables, ctx);
    if (!evaluator) {
        ast_free(ast);
        output[0] = '\0';
        return -1;
    }
    
    // Evaluate AST (should be assignment statement)
    int result = 0;
    if (ast->type == AST_PROGRAM && ast->data.program.statement_count > 0) {
        ast_node* stmt = ast->data.program.statements[0];
        if (stmt->type == AST_ASSIGNMENT) {
            result = ast_evaluate_assignment(stmt, evaluator);
        } else {
            // Just evaluate as expression for now
            ast_value* val = ast_evaluate(stmt, evaluator);
            if (val) {
                ast_value_free(val);
            } else {
                result = -1;
            }
        }
    }
    
    ast_evaluator_free(evaluator);
    ast_free(ast);
    
    output[0] = '\0';
    return result;
}