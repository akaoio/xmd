/**
 * @file ast_create_spread.c
 * @brief Implementation of ast_create_spread function
 * 
 * This file contains ONLY the ast_create_spread function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Create spread AST node
 * @param expression Expression to spread
 * @param in_array Whether spread is in array context
 * @param in_object Whether spread is in object context  
 * @param loc Source location
 * @return AST node or NULL on error
 */
ast_node* ast_create_spread(ast_node* expression, bool in_array, bool in_object, source_location loc) {
    // For now, return a stub implementation
    // This is a complex feature that would need full implementation
    return NULL; // Stub implementation
}