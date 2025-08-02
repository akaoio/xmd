/**
 * @file ast_parse_conditional_simple.c
 * @brief Implementation of ast_parse_conditional_simple function
 * 
 * This file contains ONLY the ast_parse_conditional_simple function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <ctype.h>
#include "ast.h"
#include "error.h"
#include "utils.h"
/**
 * @brief Parse conditional statement: if condition then action
 * @param pos Pointer to current position (updated)
 * @return Conditional AST node or NULL
 */
ast_node* ast_parse_conditional(const char** pos) {
    const char* start = *pos;
    
    // Skip "if "
    start += 3;
    while (*start && isspace(*start)) start++;
    // Parse condition expression (e.g., "score = 100")
    const char* condition_start = start;
    // Find " then " keyword to determine where condition ends
    const char* then_pos = strstr(start, " then ");
    if (!then_pos) {
        // Invalid conditional - skip to end of line
        while (**pos && **pos != '\n') (*pos)++;
        return NULL;
    }
    // Extract condition text
    size_t condition_len = then_pos - condition_start;
    char* condition_text = xmd_malloc(condition_len + 1);
    if (!condition_text) return NULL;
    strncpy(condition_text, condition_start, condition_len);
    condition_text[condition_len] = '\0';
    // Parse condition as comparison expression
    ast_node* condition_expr = ast_parse_comparison_expression(condition_text);
    XMD_FREE_SAFE(condition_text);
    if (!condition_expr) {
        // Skip to end of line on parse error
        while (**pos && **pos != '\n') (*pos)++;
        return NULL;
    }
    // Skip to after "then "
    start = then_pos + 6;
    while (*start && isspace(*start) && *start != '\n') start++;
    // Parse the action/statement after "then"
    ast_node* then_stmt = ast_parse_statement(&start);
    // Create conditional node
    source_location loc = {1, 1, "input"};
    ast_node* conditional = ast_create_conditional(condition_expr, loc);
    if (conditional) {
        // Set the then block to the parsed statement
        conditional->data.conditional.then_block = then_stmt;
    } else if (then_stmt) {
        XMD_FREE_SAFE(then_stmt);
    }
    *pos = start;
    return conditional;
}
