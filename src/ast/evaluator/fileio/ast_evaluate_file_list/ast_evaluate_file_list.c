/**
 * @file ast_evaluate_file_list.c
 *
 *
 * @brief Implementation of ast_evaluate_file_list function
 * 
 * This file contains ONLY the ast_evaluate_file_list function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "performance.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Evaluate File.list operation
 * @param node File list AST node
 * @param evaluator Evaluator context
 * @return Array value containing file list or NULL
 */
ast_value* ast_evaluate_file_list(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_FILE_LIST, NULL, "ast_evaluate_file_list: Invalid node type");
    
    const char* dir_path = node->data.file_io.file_path;
    XMD_VALIDATE_PTR_RETURN(dir_path, ast_value_create_array());
    
    // Create empty array for results
    ast_value* result = ast_value_create_array();
    XMD_VALIDATE_PTR_RETURN(result, NULL);
    
    // Open directory
    DIR* dir = opendir(dir_path);
    if (!dir) {
        return result; // Return empty array if can't open directory
    }
    
    // Read directory entries
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and .. entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // Add filename to array
        ast_value* filename = ast_value_create_string(entry->d_name);
        if (filename) {
            ast_value_array_add(result, filename);
        }
    }
    
    closedir(dir);
    return result;
}
