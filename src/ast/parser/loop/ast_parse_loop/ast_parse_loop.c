/**
 * @file ast_parse_loop.c
 *
 * @brief Implementation of ast_parse_loop function
 * 
 * This file contains ONLY the ast_parse_loop function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "error.h"
#include "module.h"
#include "performance.h"
#include "token.h"
#include "variable.h"
#include "utils.h"
/**
 * @brief Parse loop statement: for variable in iterable
 * @param pos Pointer to current position (updated)
 * @return Loop AST node or NULL
 */
ast_node* ast_parse_loop(const char** pos) {
    const char* start = *pos;
    
    // Skip "for "
    start += 4;
    while (*start && isspace(*start)) {
        start++;
    }
    
    // Get loop variable name
    const char* var_start = start;
    while (*start && !isspace(*start) && *start != '\n') {
        start++;
    }
    
    size_t var_len = start - var_start;
    if (var_len == 0) {
        printf("[ERROR] ast_parse_loop: Missing loop variable name after 'for'\n");
        // Skip to end of line on error
        while (**pos && **pos != '\n') {
            (*pos)++;
        }
        return NULL;
    }
    
    char* var_name = xmd_malloc(var_len + 1);
    if (!var_name) {
        printf("[ERROR] ast_parse_loop: Memory allocation failed for loop variable\n");
        return NULL;
    }
    strncpy(var_name, var_start, var_len);
    var_name[var_len] = '\0';
    
    // Skip whitespace
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    // Check for "in" keyword
    if (strncmp(start, "in ", 3) != 0) {
        XMD_FREE_SAFE(var_name);
        return NULL;
    }
    
    // Skip "in "
    start += 3;
    
    // Parse iterable expression
    const char* iterable_start = start;
    while (*start && *start != '\n') {
        start++;
    }
    
    size_t iterable_len = start - iterable_start;
    char* iterable_text = xmd_malloc(iterable_len + 1);
    if (!iterable_text) {
        XMD_FREE_SAFE(var_name);
        return NULL;
    }
    
    strncpy(iterable_text, iterable_start, iterable_len);
    iterable_text[iterable_len] = '\0';
    
    // Create array literal from space-separated values
    ast_node* iterable_array = ast_create_array_literal((source_location){1, 1, "input"});
    if (!iterable_array) {
        XMD_FREE_SAFE(iterable_text);
        XMD_FREE_SAFE(var_name);
        return NULL;
    }
    
    // Parse space-separated values
    char* token = strtok(iterable_text, " \t");
    while (token) {
        ast_node* element = NULL;
        if (isdigit(*token) || *token == '-') {
            double val = atof(token);
            element = ast_create_number_literal(val, (source_location){1, 1, "input"});
        } else {
            element = ast_create_string_literal(token, (source_location){1, 1, "input"});
        }
        
        if (element) {
            ast_add_element(iterable_array, element);
        }
        token = strtok(NULL, " \t");
    }
    
    // Create loop node
    source_location loc = {1, 1, "input"};
    ast_node* loop = ast_create_loop(var_name, iterable_array, loc);
    XMD_FREE_SAFE(var_name);
    XMD_FREE_SAFE(iterable_text);
    
    *pos = start;
    return loop;
}
