/**
 * @file ast_evaluate_program.c
 * @brief Evaluate AST program and return string output
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include <stdlib.h>
#include "utils/common/common_macros.h"
#include "../../../../../include/ast.h"
#include "../../../../../include/utils.h"

/**
 * @brief Evaluate program AST and return string output
 * @param program Program AST node
 * @param evaluator Evaluator context
 * @return String output (must be freed)
 */
char* ast_evaluate_program(ast_node* program, ast_evaluator* evaluator) {
    if (!program || !evaluator) {
        return xmd_strdup("");
    }
    
    // Evaluate the program node
    ast_value* result = ast_evaluate_program_node(program, evaluator);
    
    // Convert result to string
    char* output = NULL;
    if (result) {
        output = ast_value_to_string(result);
        XMD_FREE_SAFE(result);
    } else {
        output = xmd_strdup("");
    }
    
    return output;
}
