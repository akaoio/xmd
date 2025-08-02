/**
 * @file ast_parse_if_block_simple.c
 * @brief Implementation of ast_parse_if_block_simple function
 * 
 * This file contains ONLY the ast_parse_if_block_simple function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
/**
 * @brief Parse if block form
 */
ast_node* ast_parse_if_block(const char** pos) {
    const char* start = *pos;
    start += 3; // Skip "if "
    
    // Parse condition until end of line
    const char* condition_start = start;
    while (*start && *start != '\n') start++;
    size_t condition_len = start - condition_start;
    char* condition_text = xmd_malloc(condition_len + 1);
    if (!condition_text) return NULL;
    strncpy(condition_text, condition_start, condition_len);
    condition_text[condition_len] = '\0';
    // Trim whitespace
    char* end = condition_text + condition_len - 1;
    while (end > condition_text && isspace(*end)) *end-- = '\0';
    // Parse condition
    ast_node* condition_expr = ast_parse_comparison_expression(condition_text);
    free(condition_text);
    if (!condition_expr) return NULL;
    // Create conditional node
    source_location loc = {1, 1, "input"};
    ast_node* conditional = ast_create_conditional(condition_expr, loc);
    *pos = start;
    return conditional;
}
