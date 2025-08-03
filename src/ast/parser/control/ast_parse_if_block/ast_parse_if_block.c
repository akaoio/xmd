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
#include "ast.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse if block form
 */
ast_node* ast_parse_if_block(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    const char* start = *pos;
    start += 3; // Skip "if "
    
    // Parse condition until end of line
    const char* condition_start = start;
    while (*start && *start != '\n') start++;
    size_t condition_len = start - condition_start;
    char* condition_text;
    XMD_MALLOC_SAFE(condition_text, char[condition_len + 1], NULL, "ast_parse_if_block: Memory allocation failed");
    strncpy(condition_text, condition_start, condition_len);
    condition_text[condition_len] = '\0';
    // Trim whitespace
    char* end = condition_text + condition_len - 1;
    while (end > condition_text && isspace(*end)) *end-- = '\0';
    // Parse condition
    ast_node* condition_expr = ast_parse_comparison_expression(condition_text);
    XMD_FREE_SAFE(condition_text);
    if (!condition_expr) return NULL;
    // Create conditional node
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* conditional = ast_create_conditional(condition_expr, loc);
    
    // Move past newline
    if (*start == '\n') {
        start++;
    }
    
    // Parse the then block (indented statements)
    ast_node* then_block = ast_create_block(loc);
    if (then_block) {
        // Check for indentation
        const char* body_start = start;
        while (*body_start == ' ' || *body_start == '\t') {
            body_start++;
        }
        
        // If there's indented content, parse it
        if (body_start > start && *body_start && *body_start != '\n') {
            // Parse the indented statement
            const char* stmt_pos = body_start;
            ast_node* stmt = ast_parse_statement(&stmt_pos);
            if (stmt) {
                ast_add_statement(then_block, stmt);
                start = stmt_pos;
            }
        }
        
        // Attach then block to conditional
        conditional->data.conditional.then_block = then_block;
    }
    
    *pos = start;
    return conditional;
}
