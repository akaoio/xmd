/**
 * @file ast_evaluate_file_delete.c
 *
 *
 * @brief Implementation of ast_evaluate_file_delete function
 * 
 * This file contains ONLY the ast_evaluate_file_delete function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "variable.h"
/**
 * @brief Evaluate File.delete operation
 * @param node File delete AST node
 * @param evaluator Evaluator context
 * @return Boolean value indicating success
 */
ast_value* ast_evaluate_file_delete(ast_node* node, ast_evaluator* evaluator) {
    if (!node || !evaluator || node->type != AST_FILE_DELETE) {
        return ast_value_create_boolean(false);
    }
    
    const char* file_path = node->data.file_io.file_path;
    if (!file_path) {
        return ast_value_create_boolean(false);
    }
    
    // Delete file using remove() 
    int result = remove(file_path);
    return ast_value_create_boolean(result == 0);
}
