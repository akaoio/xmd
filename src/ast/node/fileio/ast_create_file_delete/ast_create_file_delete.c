/**
 * @file ast_create_file_delete.c
 * @brief Implementation of ast_create_file_delete function
 * 
 * This file contains ONLY the ast_create_file_delete function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Create File.delete node
 * @param file_path Path to file to delete
 * @param loc Source location
 * @return File delete node or NULL
 */
ast_node* ast_create_file_delete(const char* file_path, source_location loc) {
    ast_node* node = xmd_calloc(1, sizeof(ast_node));
    if (!node) {
        return NULL;
    }
    
    node->type = AST_FILE_DELETE;
    node->location = loc;
    node->data.file_io.file_path = xmd_strdup(file_path);
    node->data.file_io.content = NULL;
    return node;
}
