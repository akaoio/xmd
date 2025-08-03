/**
 * @file ast_create_file_exists.c
 * @brief Implementation of ast_create_file_exists function
 * 
 * This file contains ONLY the ast_create_file_exists function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "utils.h"
#include "variable.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Create File.exists node
 * @param file_path Path to check for existence
 * @param loc Source location
 * @return File exists node or NULL
 */
ast_node* ast_create_file_exists(const char* file_path, source_location loc) {
    XMD_CREATE_VALIDATED(node, ast_node, sizeof(ast_node), NULL);
    
    node->type = AST_FILE_EXISTS;
    node->location = loc;
    node->data.file_io.file_path = xmd_strdup(file_path);
    node->data.file_io.content = NULL;
    return node;
}
