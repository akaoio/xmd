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
#include "ast.h"
#include "error.h"
#include "module.h"
#include "performance.h"
#include "token.h"
#include "variable.h"
#include "../../../../../utils/common/common_macros.h"
#include "utils.h"
/**
 * @brief Parse loop statement: for variable in iterable
 * @param pos Pointer to current position (updated)
 * @return Loop AST node or NULL
 */
ast_node* ast_parse_loop(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
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
    
    char* var_name;
    XMD_MALLOC_DYNAMIC(var_name, var_len + 1, NULL);
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
    char* iterable_text;
    XMD_MALLOC_DYNAMIC(iterable_text, iterable_len + 1, NULL);
    
    strncpy(iterable_text, iterable_start, iterable_len);
    iterable_text[iterable_len] = '\0';
    
    // Create array literal from space-separated values
    ast_node* iterable_array = ast_create_array_literal((source_location){1, 1, "input"});
    if (!iterable_array) {
        XMD_FREE_SAFE(iterable_text);
        XMD_FREE_SAFE(var_name);
        return NULL;
    }
    
    // Check if this is a range loop (e.g., "1 .. 5") - Pure XMD syntax
    char* range_pos = strstr(iterable_text, " .. ");
    if (range_pos) {
        // Parse range loop
        *range_pos = '\0';  // Split at ".."
        double start_val = atof(iterable_text);
        double end_val = atof(range_pos + 4);  // Skip " .. "
        
        // Create elements for the range
        for (int i = (int)start_val; i <= (int)end_val; i++) {
            ast_node* element = ast_create_number_literal((double)i, (source_location){1, 1, "input"});
            if (element) {
                ast_add_element(iterable_array, element);
            }
        }
    } else {
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
    }
    
    // Create loop node
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* loop = ast_create_loop(var_name, iterable_array, loc);
    XMD_FREE_SAFE(var_name);
    XMD_FREE_SAFE(iterable_text);
    
    // Move to next line for body parsing
    if (*start == '\n') {
        start++;
    }
    
    // Parse loop body (indented statements)
    ast_node* body = ast_create_block(loc);
    if (body) {
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
                ast_add_statement(body, stmt);
                start = stmt_pos;
            }
        }
        
        // Attach body to loop
        loop->data.loop.body = body;
    }
    
    *pos = start;
    return loop;
}
