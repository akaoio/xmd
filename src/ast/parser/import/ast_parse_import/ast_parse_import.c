/**
 * @file ast_parse_import.c
 * @brief Implementation of ast_parse_import function
 * 
 * This file contains ONLY the ast_parse_import function.
 * One function per file - Genesis principle compliance.
 * Part of Phase 2 module system implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast_parser.h"
#include "ast_node.h"
#include "ast.h"
#include "utils.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Parse import statement
 * @param pos Pointer to current position in source (will be updated)
 * @return Import AST node or NULL on error
 */
ast_node* ast_parse_import(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    
    // Skip "import" keyword (6 characters)
    if (strncmp(start, "import", 6) != 0) {
        XMD_ERROR_RETURN(NULL, "ast_parse_import: Expected 'import' keyword%s", "");
    }
    start += 6;
    
    // Skip whitespace after "import"
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    // Parse module path - expect quoted string
    if (*start != '"') {
        XMD_ERROR_RETURN(NULL, "ast_parse_import: Expected quoted module path after 'import'%s", "");
    }
    start++; // Skip opening quote
    
    // Find closing quote and extract module path
    const char* path_start = start;
    while (*start && *start != '"' && *start != '\n') {
        start++;
    }
    
    if (*start != '"') {
        XMD_ERROR_RETURN(NULL, "ast_parse_import: Unterminated module path string%s", "");
    }
    
    // Extract module path
    size_t path_len = start - path_start;
    char* module_path;
    XMD_MALLOC_VALIDATED(module_path, char, path_len + 1, NULL);
    
    strncpy(module_path, path_start, path_len);
    module_path[path_len] = '\0';
    
    start++; // Skip closing quote
    
    // Skip any trailing whitespace
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    // Update position
    *pos = start;
    
    // Create import AST node
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* import_node = ast_create_import(module_path, loc);
    
    // Free temporary path string (ast_create_import should copy it)
    XMD_FREE_NULL(module_path);
    
    return import_node;
}