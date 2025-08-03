/**
 * @file ast_parse_identifier_or_array.c
 * @brief Implementation of ast_parse_identifier_or_array function
 * 
 * This file contains ONLY the ast_parse_identifier_or_array function.
 * One function per file - Genesis principle compliance.
 * Detects array[index] syntax and creates appropriate AST nodes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"  
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Parse identifier or array access (array[index])
 * @param identifier_str The identifier string to parse
 * @param loc Source location for AST nodes
 * @return AST node (identifier or array access)
 */
ast_node* ast_parse_identifier_or_array(const char* identifier_str, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, identifier_str);
    
    
    // Look for bracket to detect array access
    const char* bracket_pos = strchr(identifier_str, '[');
    if (!bracket_pos) {
        // No bracket, just a regular identifier
        return ast_create_identifier(identifier_str, loc);
    }
    
    // Find the closing bracket
    const char* close_bracket = strchr(bracket_pos, ']');
    if (!close_bracket) {
        return ast_create_identifier(identifier_str, loc);
    }
    
    // Extract array name (before '[')
    size_t array_name_len = bracket_pos - identifier_str;
    char* array_name;
    XMD_MALLOC_SAFE(array_name, char[array_name_len + 1], NULL, "ast_parse_identifier_or_array: Failed to allocate array name");
    strncpy(array_name, identifier_str, array_name_len);
    array_name[array_name_len] = '\0';
    
    // Extract index (between '[' and ']')
    size_t index_len = close_bracket - bracket_pos - 1;
    char* index_str = xmd_malloc(index_len + 1);
    if (!index_str) {
        XMD_FREE_SAFE(array_name);
        return NULL;
    }
    strncpy(index_str, bracket_pos + 1, index_len);
    index_str[index_len] = '\0';
    
    
    // Create array expression (identifier)
    ast_node* array_expr = ast_create_identifier(array_name, loc);
    if (!array_expr) {
        XMD_FREE_SAFE(array_name);
        XMD_FREE_SAFE(index_str);
        return NULL;
    }
    
    // Create index expression
    ast_node* index_expr = NULL;
    if (isdigit(index_str[0]) || (index_str[0] == '-' && isdigit(index_str[1]))) {
        // Numeric index
        double index_val = atof(index_str);
        index_expr = ast_create_number_literal(index_val, loc);
    } else {
        // Variable index
        index_expr = ast_create_identifier(index_str, loc);
    }
    
    if (!index_expr) {
        XMD_FREE_SAFE(array_expr);
        XMD_FREE_SAFE(array_name);
        XMD_FREE_SAFE(index_str);
        return NULL;
    }
    
    // Create array access node
    ast_node* result = ast_create_array_access(array_expr, index_expr, loc);
    if (result) {
    } else {
        XMD_FREE_SAFE(array_expr);
        XMD_FREE_SAFE(index_expr);
    }
    
    XMD_FREE_SAFE(array_name);
    XMD_FREE_SAFE(index_str);
    return result;
}
