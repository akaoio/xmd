/**
 * @file ast_evaluate_block.c
 * @brief Implementation of ast_evaluate_block function
 * 
 * This file contains ONLY the ast_evaluate_block function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "utils/common/common_macros.h"
#include "ast_evaluator.h"
#include "ast_node.h"
#include "error.h"
#include "variable.h"

/**
 * @brief Evaluate block node
 * @param node Block AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_block(ast_node* node, ast_evaluator* evaluator) {
    if (!node || node->type != AST_BLOCK || !evaluator) {
        return NULL;
    }
    
    ast_value* result = NULL;
    
    // Evaluate each statement in the block
    for (size_t i = 0; i < node->data.block.statement_count; i++) {
        ast_node* stmt = node->data.block.statements[i];
        if (!stmt) continue;
        
        // Free previous result
        if (result) {
            XMD_FREE_SAFE(result);
        }
        
        // Evaluate statement
        result = ast_evaluate(stmt, evaluator);
        
        if (evaluator->has_error) {
            break;
        }
    }
    
    return result;
}