/**
 * @file ast_parse_return.c
 * @brief Implementation of ast_parse_return function
 * 
 * This file contains ONLY the ast_parse_return function.
 * One function per file - Genesis principle compliance.
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "ast.h"
#include "ast_node.h"
#include "ast_parser.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Parse return statement: return expression
 * @param pos Pointer to current position in input
 * @return Return statement AST node or NULL
 */
ast_node* ast_parse_return(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    
    // Skip "return"
    start += 6;
    
    // Skip whitespace after "return"
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    *pos = start;
    
    // Check if there's a return value
    ast_node* value = NULL;
    if (*start && *start != '\n') {
        // Parse the return expression
        value = ast_parse_expression(pos);
    }
    
    // Skip to end of line
    while (**pos && **pos != '\n') {
        (*pos)++;
    }
    if (**pos == '\n') {
        (*pos)++;
    }
    
    // Create the return node
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    return ast_create_return(value, loc);
}