/**
 * @file ast_evaluate_program_node.c
 *
 *
 * @brief Implementation of ast_evaluate_program_node function
 * 
 * This file contains ONLY the ast_evaluate_program_node function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "error.h"
#include "variable.h"
#include "utils/common/common_macros.h"

// Forward declaration for output function
extern int ast_evaluator_append_output(ast_evaluator* evaluator, const char* text);
/**
 * @brief Evaluate program node
 * @param node Program node
 * @param evaluator Evaluator context
 * @return Last statement result or NULL
 */
ast_value* ast_evaluate_program_node(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_PROGRAM, NULL, "ast_evaluate_program_node: Invalid node type");
    
    ast_value* result = NULL;
    for (size_t i = 0; i < node->data.program.statement_count; i++) {
        // Free previous result safely - only if it exists and is not shared
        if (result) {
            ast_value_free(result);
            result = NULL;
        }
        result = ast_evaluate(node->data.program.statements[i], evaluator);
        
        // Append result to output if it produces a value (not just assignments)
        if (result && node->data.program.statements[i]->type != AST_ASSIGNMENT) {
            // Convert result to string for output
            char* result_str = ast_value_to_string(result);
            if (result_str && strlen(result_str) > 0) {
                ast_evaluator_append_output(evaluator, result_str);
                ast_evaluator_append_output(evaluator, "\n");
            }
            XMD_FREE_SAFE(result_str);
        }
        
        if (evaluator->error_message) {
            break;
        }
    }
    
    return result;
}
