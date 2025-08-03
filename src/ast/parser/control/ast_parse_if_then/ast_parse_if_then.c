/**
 * @file ast_parse_if_then.c
 *
 * @brief Implementation of ast_parse_if_then function
 * 
 * This file contains ONLY the ast_parse_if_then function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse if-then single line (Genesis syntax)
 * @param pos Pointer to current position
 * @return Conditional AST node or NULL
 */
ast_node* ast_parse_if_then(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    
    // Skip "if "
    start += 3;
    
    const char* then_pos = strstr(start, " then ");
    if (!then_pos) {
        return NULL;
    }
    
    // Extract condition
    size_t condition_len = then_pos - start;
    char* condition_text;
    XMD_MALLOC_SAFE(condition_text, char[condition_len + 1], NULL, "ast_parse_if_then: Failed to allocate condition text");
    
    strncpy(condition_text, start, condition_len);
    condition_text[condition_len] = '\0';
    
    // Parse condition
    ast_node* condition_expr = ast_parse_comparison_expression(condition_text);
    XMD_FREE_SAFE(condition_text);
    
    if (!condition_expr) {
        return NULL;
    }
    
    // Skip to after "then "
    start = then_pos + 6;
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    // Parse action after "then"
    ast_node* then_stmt = ast_parse_statement(&start);
    
    // Create conditional node
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* conditional = ast_create_conditional(condition_expr, loc);
    
    if (conditional) {
        conditional->data.conditional.then_block = then_stmt;
    } else if (then_stmt) {
        XMD_FREE_SAFE(then_stmt);
    }
    
    *pos = start;
    return conditional;
}
