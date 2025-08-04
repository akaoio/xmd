/**
 * @file ast_parse_yield.c
 * @brief Implementation of ast_parse_yield function
 * 
 * This file contains ONLY the ast_parse_yield function.
 * One function per file - Genesis principle compliance.
 * Parses yield statements for generator functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Parse yield statement
 * @param pos Pointer to current parsing position (will be advanced)
 * @return AST node for yield statement or NULL on error
 */
ast_node* ast_parse_yield(const char** pos) {
    XMD_VALIDATE_PTR_RETURN(pos, NULL);
    XMD_VALIDATE_PTR_RETURN(*pos, NULL);
    
    const char* start = *pos;
    
    // Skip whitespace
    while (isspace(**pos)) (*pos)++;
    
    // Expect "yield"
    if (strncmp(*pos, "yield", 5) != 0) {
        return NULL;
    }
    *pos += 5;
    
    // Must be followed by whitespace or end of line (for bare yield)
    if (**pos != '\0' && **pos != '\n' && **pos != '\r' && !isspace(**pos)) {
        return NULL;
    }
    
    // Create yield AST node
    source_location loc = {1, 1, "unknown"};
    ast_node* yield_node;
    XMD_MALLOC_VALIDATED(yield_node, ast_node, 1, NULL);
    
    yield_node->type = AST_YIELD;
    yield_node->location = loc;
    yield_node->data.yield_stmt.value = NULL; // Default to bare yield
    
    // Skip whitespace
    while (isspace(**pos)) (*pos)++;
    
    // Check if there's a value to yield
    if (**pos && **pos != '\n' && **pos != '\r') {
        // Parse the yield value expression
        const char* expr_start = *pos;
        
        // Simple expression parsing - find end of line or statement
        while (**pos && **pos != '\n' && **pos != '\r') {
            (*pos)++;
        }
        
        if (*pos > expr_start) {
            // Create a simple string literal for the yielded value
            size_t expr_len = *pos - expr_start;
            char* expr_str;
            XMD_MALLOC_VALIDATED(expr_str, char, expr_len + 1, NULL);
            strncpy(expr_str, expr_start, expr_len);
            expr_str[expr_len] = '\0';
            
            // Trim trailing whitespace
            char* end = expr_str + expr_len - 1;
            while (end > expr_str && isspace(*end)) {
                *end = '\0';
                end--;
            }
            
            // Create a literal node for the value
            ast_node* value_node;
            XMD_MALLOC_VALIDATED(value_node, ast_node, 1, NULL);
            value_node->type = AST_LITERAL;
            value_node->location = loc;
            value_node->data.literal.type = LITERAL_STRING;
            value_node->data.literal.value.string_value = expr_str;
            
            yield_node->data.yield_stmt.value = value_node;
        }
    }
    
    return yield_node;
}