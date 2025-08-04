/**
 * @file ast_evaluate_file_read.c
 *
 *
 * @brief Implementation of ast_evaluate_file_read function
 * 
 * This file contains ONLY the ast_evaluate_file_read function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
#include <stdio.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "variable.h"
#include "utils.h"
/**
 * @brief Evaluate File.read operation
 * @param node File read AST node
 * @param evaluator Evaluator context
 * @return String value with file contents or NULL on error
 */
ast_value* ast_evaluate_file_read(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_FILE_READ, NULL, "ast_evaluate_file_read: Invalid node type");
    
    const char* file_path = node->data.file_io.file_path;
    XMD_VALIDATE_PTR_RETURN(file_path, ast_value_create_string(""));
    
    // Open file for reading
    XMD_FILE_READ_OPEN(file, file_path, ast_value_create_string(""));
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (file_size < 0) {
        XMD_FILE_CLOSE_SAFE(file);
        return ast_value_create_string("");
    }
    
    // Read file contents
    char* content = xmd_malloc(file_size + 1);
    if (!content) {
        XMD_FILE_CLOSE_SAFE(file);
        return ast_value_create_string("");
    }
    
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    XMD_FILE_CLOSE_SAFE(file);
    
    // Create string value
    ast_value* result = ast_value_create_string(content);
    XMD_FREE_SAFE(content);
    return result;
}
