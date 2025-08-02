/**
 * @file ast_process_xmd_content.c
 * @brief Main AST-based XMD content processor
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Main entry point for AST-based XMD processing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/utils.h"
#include "../../include/store.h"
#include "../../include/ast_parser.h"
#include "../../include/ast_evaluator.h"
#include "../../include/ast_node.h"

/**
 * @brief Process XMD content using AST system
 * @param input Input markdown content
 * @param variables Variable store for evaluation
 * @return Processed output string (must be freed)
 */
char* ast_process_xmd_content(const char* input, store* variables) {
    if (!input) {
        return NULL;
    }
    
    // REAL IMPLEMENTATION - NO MORE STUBS!
    // Parse and evaluate XMD content using full AST system
    
    // Create AST evaluator context with proper parameters
    ast_evaluator* evaluator = ast_evaluator_create(variables, NULL);
    if (!evaluator) {
        return xmd_strdup(input); // Fallback to original if evaluator fails
    }
    
    // Parse the input as XMD program
    ast_node* program = ast_parse_program(input);
    
    if (!program) {
        // If parsing fails, return original input
        ast_evaluator_free(evaluator);
        return xmd_strdup(input);
    }
    
    // Evaluate the AST
    ast_value* result = ast_evaluate(program, evaluator);
    
    // Get the output from evaluator's output buffer or from result
    char* output = NULL;
    if (evaluator->output_buffer && evaluator->output_size > 0) {
        // Use accumulated output from evaluator
        output = xmd_strdup(evaluator->output_buffer);
    } else if (result) {
        // Convert result to string if no accumulated output
        output = ast_value_to_string(result);
    } else {
        // Fallback to empty string
        output = xmd_strdup("");
    }
    
    // Clean up
    if (result) {
        ast_value_free(result);
    }
    ast_free(program);
    ast_evaluator_free(evaluator);
    
    return output;
}
