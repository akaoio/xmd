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
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Evaluate File.delete operation
 * @param node File delete AST node
 * @param evaluator Evaluator context
 * @return Boolean value indicating success
 */
ast_value* ast_evaluate_file_delete(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(ast_value_create_boolean(false), node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_FILE_DELETE, ast_value_create_boolean(false), "ast_evaluate_file_delete: Invalid node type");
    
    const char* file_path = node->data.file_io.file_path;
    XMD_VALIDATE_PTR_RETURN(file_path, ast_value_create_boolean(false));
    
    // Delete file using remove() 
    int result = remove(file_path);
    return ast_value_create_boolean(result == 0);
}
