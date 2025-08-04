/**
 * @file ast_parse_destructure.c
 *
 * @brief Implementation of ast_parse_destructure function
 * 
 * This file contains ONLY the ast_parse_destructure function.
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
 * @brief Parse destructuring assignment
 * @param pos Current position in input string
 * @return AST node for destructuring or NULL on error
 * 
 * Parses expressions like:
 * - destructure items first, second, ...rest
 * - destructure user name username, age userage
 */
ast_node* ast_parse_destructure(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    source_location loc = {1, (size_t)(start - start), "unknown"};
    
    // Skip whitespace
    while (isspace(**pos)) (*pos)++;
    
    // Expect "destructure" keyword
    if (strncmp(*pos, "destructure", 11) != 0) {
        return NULL;
    }
    *pos += 11;
    
    // Skip whitespace after "destructure"
    while (isspace(**pos)) (*pos)++;
    
    // Parse source expression first (what we're destructuring from)
    ast_node* source_expr = NULL;
    
    // Find the source expression - it should be the first identifier
    const char* source_start = *pos;
    while (**pos && !isspace(**pos)) (*pos)++;
    
    if (*pos == source_start) {
        return NULL; // No source expression
    }
    
    // Create identifier for source
    size_t source_len = *pos - source_start;
    char* source_name = XMD_MALLOC(source_len + 1);
    if (!source_name) return NULL;
    
    strncpy(source_name, source_start, source_len);
    source_name[source_len] = '\0';
    
    source_expr = ast_create_identifier(source_name, loc);
    XMD_FREE_SAFE(source_name);
    
    if (!source_expr) {
        return NULL;
    }
    
    // Skip whitespace
    while (isspace(**pos)) (*pos)++;
    
    // Parse target variables
    char** target_names = NULL;
    size_t target_count = 0;
    size_t target_capacity = 4;
    char* rest_name = NULL;
    bool is_object = false;
    
    target_names = XMD_MALLOC(target_capacity * sizeof(char*));
    if (!target_names) {
        ast_free(source_expr);
        return NULL;
    }
    
    // Parse target list
    while (**pos && **pos != '\n' && **pos != ',') {
        // Skip whitespace and commas
        while (isspace(**pos) || **pos == ',') (*pos)++;
        if (!**pos || **pos == '\n') break;
        
        // Check for rest parameter
        if (**pos == '.' && *(*pos + 1) == '.' && *(*pos + 2) == '.') {
            *pos += 3;
            while (isspace(**pos)) (*pos)++;
            
            // Parse rest variable name
            const char* rest_start = *pos;
            while (**pos && !isspace(**pos) && **pos != ',' && **pos != '\n') {
                (*pos)++;
            }
            
            if (*pos > rest_start) {
                size_t rest_len = *pos - rest_start;
                rest_name = XMD_MALLOC(rest_len + 1);
                if (rest_name) {
                    strncpy(rest_name, rest_start, rest_len);
                    rest_name[rest_len] = '\0';
                }
            }
            break;
        }
        
        // Parse regular target variable
        const char* target_start = *pos;
        while (**pos && !isspace(**pos) && **pos != ',' && **pos != '\n') {
            (*pos)++;
        }
        
        if (*pos > target_start) {
            // Expand array if needed
            if (target_count >= target_capacity) {
                target_capacity *= 2;
                char** new_targets = XMD_REALLOC(target_names, target_capacity * sizeof(char*));
                if (!new_targets) {
                    // Cleanup and return NULL
                    for (size_t i = 0; i < target_count; i++) {
                        XMD_FREE_SAFE(target_names[i]);
                    }
                    XMD_FREE_SAFE(target_names);
                    XMD_FREE_SAFE(rest_name);
                    ast_free(source_expr);
                    return NULL;
                }
                target_names = new_targets;
            }
            
            size_t target_len = *pos - target_start;
            target_names[target_count] = XMD_MALLOC(target_len + 1);
            if (target_names[target_count]) {
                strncpy(target_names[target_count], target_start, target_len);
                target_names[target_count][target_len] = '\0';
                target_count++;
            }
        }
        
        // Skip whitespace
        while (isspace(**pos)) (*pos)++;
    }
    
    // Determine if this is object destructuring based on pattern
    // Object destructuring has pattern: destructure user name username, age userage
    // Array destructuring has pattern: destructure items first, second, ...rest
    // If we have pairs of names, it's object destructuring
    is_object = (target_count % 2 == 0) && target_count > 0;
    
    // Create destructure node
    ast_node* node = ast_create_destructure(target_names, target_count, source_expr, is_object, rest_name, loc);
    
    // Cleanup on failure
    if (!node) {
        for (size_t i = 0; i < target_count; i++) {
            XMD_FREE_SAFE(target_names[i]);
        }
        XMD_FREE_SAFE(target_names);
        XMD_FREE_SAFE(rest_name);
        ast_free(source_expr);
    }
    
    return node;
}