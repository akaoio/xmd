/**
 * @file ast_parse_spread.c
 *
 * @brief Implementation of ast_parse_spread function
 * 
 * This file contains ONLY the ast_parse_spread function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "ast_parser.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Parse spread operator
 * @param pos Current position in input string
 * @return AST node for spread or NULL on error
 * 
 * Parses expressions like:
 * - ...items (in array context)
 * - ...user (in object context)
 */
ast_node* ast_parse_spread(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    source_location loc = {1, (size_t)(start - start), "unknown"};
    
    // Skip whitespace
    while (isspace(**pos)) (*pos)++;
    
    // Expect "..." prefix
    if (**pos != '.' || *(*pos + 1) != '.' || *(*pos + 2) != '.') {
        return NULL;
    }
    *pos += 3;
    
    // Skip whitespace after "..."
    while (isspace(**pos)) (*pos)++;
    
    // Parse the expression to spread
    const char* expr_start = *pos;
    while (**pos && !isspace(**pos) && **pos != ',' && **pos != '\n' && **pos != ')' && **pos != ']') {
        (*pos)++;
    }
    
    if (*pos == expr_start) {
        return NULL; // No expression after spread operator
    }
    
    // Create identifier for the expression to spread
    size_t expr_len = *pos - expr_start;
    char* expr_name = XMD_MALLOC(expr_len + 1);
    if (!expr_name) return NULL;
    
    strncpy(expr_name, expr_start, expr_len);
    expr_name[expr_len] = '\0';
    
    ast_node* expression = ast_create_identifier(expr_name, loc);
    XMD_FREE_SAFE(expr_name);
    
    if (!expression) {
        return NULL;
    }
    
    // Determine context based on surrounding syntax
    // This is a simplified approach - in a full parser, context would be passed down
    bool in_array = false;
    bool in_object = false;
    
    // Look ahead for context clues
    const char* lookahead = *pos;
    while (isspace(*lookahead)) lookahead++;
    
    if (*lookahead == ',' || *lookahead == ']' || *lookahead == '\n') {
        // Likely in array context
        in_array = true;
    } else {
        // Default to object context
        in_object = true;
    }
    
    // Create spread node
    ast_node* node = ast_create_spread(expression, in_array, in_object, loc);
    
    if (!node) {
        ast_free(expression);
    }
    
    return node;
}