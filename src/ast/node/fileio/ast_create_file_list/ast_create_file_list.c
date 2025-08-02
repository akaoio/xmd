/**
 * @file ast_create_file_list.c
 * @brief Implementation of ast_create_file_list function
 * 
 * This file contains ONLY the ast_create_file_list function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Create File.list node
 * @param directory_path Path to directory to list
 * @param loc Source location
 * @return File list node or NULL
 */
ast_node* ast_create_file_list(const char* directory_path, source_location loc) {
    ast_node* node = xmd_calloc(1, sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_FILE_LIST;
    node->location = loc;
    node->data.file_io.file_path = xmd_strdup(directory_path);
    node->data.file_io.content = NULL;
    return node;
}
