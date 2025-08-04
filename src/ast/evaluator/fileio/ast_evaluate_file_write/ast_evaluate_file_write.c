/**
 * @file ast_evaluate_file_write.c
 *
 *
 * @brief Implementation of ast_evaluate_file_write function
 * 
 * This file contains ONLY the ast_evaluate_file_write function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
#include <string.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "variable.h"
/**
 * @brief Evaluate File.write operation
 * @param node File write AST node
 * @param evaluator Evaluator context
 * @return Boolean value indicating success
 */
ast_value* ast_evaluate_file_write(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_FILE_WRITE, NULL, "ast_evaluate_file_write: Invalid node type");
    
    const char* file_path = node->data.file_io.file_path;
    if (!file_path || !node->data.file_io.content) {
        return ast_value_create_boolean(false);
    }
    
    // Evaluate content expression
    ast_value* content_value = ast_evaluate(node->data.file_io.content, evaluator);
    XMD_VALIDATE_PTR_RETURN(content_value, ast_value_create_boolean(false));
    
    // Convert content to string
    const char* content_str = "";
    if (content_value->type == AST_VAL_STRING) {
        content_str = content_value->value.string_value;
    } else if (content_value->type == AST_VAL_NUMBER) {
        // Convert number to string
        char number_buf[64];
        snprintf(number_buf, sizeof(number_buf), "%.0f", content_value->value.number_value);
        content_str = number_buf;
    } else if (content_value->type == AST_VAL_BOOLEAN) {
        content_str = content_value->value.boolean_value ? "true" : "false";
    }
    
    // Write to file
    FILE* file = fopen(file_path, "w");
    if (!file) {
        XMD_FREE_SAFE(content_value);
        return ast_value_create_boolean(false);
    }
    
    size_t bytes_written = fwrite(content_str, 1, strlen(content_str), file);
    XMD_FILE_CLOSE_SAFE(file);
    bool success = (bytes_written == strlen(content_str));
    XMD_FREE_SAFE(content_value);
    return ast_value_create_boolean(success);
}
