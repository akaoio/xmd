/**
 * @file ast_parse_await.c
 *
 * @brief Implementation of ast_parse_await function
 * 
 * This file contains ONLY the ast_parse_await function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "utils/common/validation_macros.h"
#include "utils/common/common_macros.h"

/**
 * @brief Parse await expression
 * @param pos Pointer to current position in input
 * @return AST node or NULL on error
 */
ast_node* ast_parse_await(const char** pos) {
    XMD_VALIDATE_PARAMS_2(NULL, pos, *pos);
    
    const char* start = *pos;
    
    // Check for 'await' keyword
    if (strncmp(start, "await", 5) != 0 || (start[5] && !isspace(start[5]))) {
        return NULL;
    }
    
    // Skip 'await' keyword
    *pos += 5;
    while (**pos && isspace(**pos)) (*pos)++;
    
    source_location loc = {1, start - *pos, "input"};
    
    // Parse expression to await
    ast_node* expression = ast_parse_expression(pos);
    if (!expression) {
        return NULL;
    }
    
    return ast_create_await(expression, loc);
}