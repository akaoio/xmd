/**
 * @file ast_parse_else_simple.c
 * @brief Implementation of ast_parse_else_simple function
 * 
 * This file contains ONLY the ast_parse_else_simple function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "ast_parser.h"
#include "utils/common/common_macros.h"
/**
 * @brief Parse else statement
 * @param pos Pointer to current position
 * @return Conditional AST node or NULL
 */
ast_node* ast_parse_else(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    // Skip "else"
    start += 4;
    // Skip to end of line
    while (*start && *start != '\n') {
        start++;
    }
    
    // Create conditional node with NULL condition (indicates else)
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* else_node = ast_create_conditional(NULL, loc);
    *pos = start;
    return else_node;
}
