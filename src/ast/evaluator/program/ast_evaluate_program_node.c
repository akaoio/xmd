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
        XMD_FREE_SAFE(result);
        result = ast_evaluate(node->data.program.statements[i], evaluator);
        
        // If the result is a string literal (plain text), append it to output
        if (result && result->type == AST_VAL_STRING && 
            node->data.program.statements[i]->type == AST_LITERAL &&
            node->data.program.statements[i]->data.literal.type == LITERAL_STRING) {
            ast_evaluator_append_output(evaluator, result->value.string_value);
            ast_evaluator_append_output(evaluator, "\n");
        }
        
        if (evaluator->error_message) {
            break;
        }
    }
    
    return result;
}
