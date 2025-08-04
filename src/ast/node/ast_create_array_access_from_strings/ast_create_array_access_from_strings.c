/**
 * @file ast_create_array_access_from_strings.c
 * @brief Implementation of ast_create_array_access_from_strings function
 * 
 * This file contains ONLY the ast_create_array_access_from_strings function.
 * One function per file - Genesis principle compliance.
 */

#include "ast_node.h"
#include "utils.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create AST array access node from strings
 * @param array_name Name of the array variable
 * @param index_str String representation of the index
 * @param loc Source location
 * @return New array access node or NULL on error
 */
ast_node* ast_create_array_access_from_strings(const char* array_name, const char* index_str, source_location loc) {
    XMD_VALIDATE_PTRS(NULL, array_name, index_str);

    // Create array expression (identifier)
    ast_node* array_expr = ast_create_identifier(array_name, loc);
    if (!array_expr) return NULL;

    // Parse index expression
    ast_node* index_expr = NULL;
    
    // Try to parse as number first
    char* endptr;
    double num_val = strtod(index_str, &endptr);
    if (*endptr == '\0') {
        // It's a number
        index_expr = ast_create_number_literal(num_val, loc);
    } else {
        // It's an identifier or more complex expression
        index_expr = ast_create_identifier(index_str, loc);
    }

    if (!index_expr) {
        ast_free(array_expr);
        return NULL;
    }

    // Create array access node
    return ast_create_array_access(array_expr, index_expr, loc);
}