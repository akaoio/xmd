/**
 * @file ast_create_file_read.c
 * @brief Implementation of ast_create_file_read function
 * 
 * This file contains ONLY the ast_create_file_read function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create File.read node
 * @param file_path Path to file to read
 * @param loc Source location
 * @return File read node or NULL
 */
ast_node* ast_create_file_read(const char* file_path, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, file_path);
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_FILE_READ;
    node->location = loc;
    node->data.file_io.file_path = xmd_strdup(file_path);
    node->data.file_io.content = NULL;
    return node;
}
