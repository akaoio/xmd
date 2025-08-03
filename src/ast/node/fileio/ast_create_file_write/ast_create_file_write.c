/**
 * @file ast_create_file_write.c
 * @brief Implementation of ast_create_file_write function
 * 
 * This file contains ONLY the ast_create_file_write function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"

/**
 * @brief Create File.write node
 * @param file_path Path to file to write
 * @param content Content to write
 * @param loc Source location
 * @return File write node or NULL
 */
ast_node* ast_create_file_write(const char* file_path, const char* content, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, file_path, content);
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_FILE_WRITE;
    node->location = loc;
    node->data.file_io.file_path = xmd_strdup(file_path);
    node->data.file_io.content = NULL; // Content should be stored as an AST node, not a string
    return node;
}