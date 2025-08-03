/**
 * @file ast_evaluate_file_exists.c
 *
 *
 * @brief Implementation of ast_evaluate_file_exists function
 * 
 * This file contains ONLY the ast_evaluate_file_exists function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "variable.h"
#include "utils/common/common_macros.h"
/**
 * @brief Evaluate File.exists operation
 * @param node File exists AST node
 * @param evaluator Evaluator context
 * @return Boolean value indicating if file exists
 */
ast_value* ast_evaluate_file_exists(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(ast_value_create_boolean(false), node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_FILE_EXISTS, ast_value_create_boolean(false), "ast_evaluate_file_exists: Invalid node type");
    
    const char* file_path = node->data.file_io.file_path;
    if (!file_path) {
        return ast_value_create_boolean(false);
    }
    
    // Try to open file for reading
    FILE* file = fopen(file_path, "r");
    if (file) {
        fclose(file);
        return ast_value_create_boolean(true);
    }
    return ast_value_create_boolean(false);
}
