/**
 * @file ast_parse_string_literal.c
 *
 *
 * @brief Implementation of ast_parse_string_literal function
 * 
 * This file contains ONLY the ast_parse_string_literal function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
/**
 * @brief Parse string literal "value"
 * @param start Pointer to starting position
 * @param pos Pointer to current position
 * @return String literal AST node or NULL  
 */
ast_node* ast_parse_string_literal(const char** start, const char** pos) {
    if (**start != '"') return NULL;
    
    (*start)++; // Skip opening quote
    const char* value_start = *start;
    // Find closing quote
    while (**start && **start != '"') {
        (*start)++;
    }
    if (**start != '"') {
        return NULL; // Unterminated string
    }
    
    size_t value_len = *start - value_start;
    char* string_value = xmd_malloc(value_len + 1);
    if (!string_value) return NULL;
    strncpy(string_value, value_start, value_len);
    string_value[value_len] = '\0';
    (*start)++; // Skip closing quote
    *pos = *start;
    source_location loc = {1, 1, "input"};
    ast_node* result = ast_create_string_literal(string_value, loc);
    free(string_value);
    return result;
}
