/**
 * @file ast_parse_number_literal.c
 *
 *
 * @brief Implementation of ast_parse_number_literal function
 * 
 * This file contains ONLY the ast_parse_number_literal function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "utils/common/common_macros.h"
/**
 * @brief Parse number literal
 * @param start Pointer to starting position
 * @param pos Pointer to current position
 * @return Number literal AST node or NULL
 */
ast_node* ast_parse_number_literal(const char** start, const char** pos) {
    if (!start || !*start || !pos) return NULL;
    const char* num_start = *start;
    
    // Handle negative numbers
    if (**start == '-') {
        (*start)++;
    }
    // Parse digits
    while (**start && isdigit(**start)) {
        (*start)++;
    }
    
    // Handle decimal point
    if (**start == '.') {
        (*start)++;
        while (**start && isdigit(**start)) {
            (*start)++;
        }
    }
    
    size_t num_len = *start - num_start;
    char* num_str;
    XMD_MALLOC_SAFE(num_str, char[num_len + 1], NULL, "ast_parse_number_literal: Memory allocation failed");
    strncpy(num_str, num_start, num_len);
    num_str[num_len] = '\0';
    double value = atof(num_str);
    XMD_FREE_SAFE(num_str);
    *pos = *start;
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    return ast_create_number_literal(value, loc);
}
