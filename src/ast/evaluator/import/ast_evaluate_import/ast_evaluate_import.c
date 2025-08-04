/**
 * @file ast_evaluate_import.c
 * @brief Implementation of ast_evaluate_import function
 * 
 * This file contains ONLY the ast_evaluate_import function.
 * One function per file - Genesis principle compliance.
 * Part of Phase 2 module system implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "module.h"
#include "store.h"
#include "variable.h"
#include "utils.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate import statement - basic file-based implementation
 * @param node Import AST node
 * @param evaluator Evaluator context
 * @return Empty string value (imports don't produce output)
 * 
 * Basic implementation that loads and evaluates XMD files.
 * Supports simple file imports with variable sharing.
 */
ast_value* ast_evaluate_import(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_IMPORT, NULL, "ast_evaluate_import: Invalid node type");
    
    // Validate module path
    XMD_VALIDATE_STRING_RETVAL(node->data.import.module_name, NULL);
    
    const char* module_name = node->data.import.module_name;
    
    // Build potential file paths
    char import_path[1024];
    FILE* import_file = NULL;
    
    // Try different extensions and paths
    const char* extensions[] = {".xmd", ".xm", ""};
    const char* search_paths[] = {"./", "../", "./"};
    
    for (int i = 0; i < 3 && !import_file; i++) {
        for (int j = 0; j < 3 && !import_file; j++) {
            snprintf(import_path, sizeof(import_path), "%s%s%s", 
                     search_paths[i], module_name, extensions[j]);
            import_file = fopen(import_path, "r");
        }
    }
    
    // If file not found, log warning but don't fail
    if (!import_file) {
        fprintf(stderr, "Warning: Import module '%s' not found in search paths\n", module_name);
        return ast_value_create_string("");
    }
    
    // Read file content
    fseek(import_file, 0, SEEK_END);
    long file_size = ftell(import_file);
    fseek(import_file, 0, SEEK_SET);
    
    if (file_size <= 0 || file_size > 1048576) { // 1MB limit
        fclose(import_file);
        fprintf(stderr, "Warning: Import file '%s' is empty or too large\n", import_path);
        return ast_value_create_string("");
    }
    
    char* content = xmd_malloc(file_size + 1);
    if (!content) {
        fclose(import_file);
        return ast_value_create_string("");
    }
    
    size_t read_size = fread(content, 1, file_size, import_file);
    content[read_size] = '\0';
    fclose(import_file);
    
    // Process the imported content in current evaluator context
    // This allows imported variables to be available in current scope
    extern char* ast_process_xmd_content(const char* content, store* variables);
    char* output = ast_process_xmd_content(content, evaluator->variables);
    XMD_FREE_SAFE(output);
    
    XMD_FREE_SAFE(content);
    
    return ast_value_create_string("");
}