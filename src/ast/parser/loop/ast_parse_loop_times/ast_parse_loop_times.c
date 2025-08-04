/**
 * @file ast_parse_loop_times.c
 *
 * @brief Implementation of ast_parse_loop_times function
 * 
 * This file contains ONLY the ast_parse_loop_times function.
 * One function per file - Genesis principle compliance.
 * Parser for "loop N times" syntax.
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "module.h"
#include "variable.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Parse "loop N times" syntax
 * @param pos Pointer to current position
 * @return Loop AST node or NULL
 */
ast_node* ast_parse_loop_times(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    start += 4; // Skip "loop"
    
    // Skip whitespace
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    // Parse the count expression (number or variable)
    const char* expr_start = start;
    ast_node* count_expr = NULL;
    
    // Check if it's a number literal
    if (isdigit(*start)) {
        // Parse numeric literal
        while (*start && isdigit(*start)) {
            start++;
        }
        
        size_t num_len = start - expr_start;
        char num_str[32];
        if (num_len >= sizeof(num_str)) {
            return NULL;
        }
        strncpy(num_str, expr_start, num_len);
        num_str[num_len] = '\0';
        
        int loop_count = atoi(num_str);
        if (loop_count <= 0) {
            return NULL;
        }
        
        // Create number literal node
        count_expr = ast_create_number_literal((double)loop_count, XMD_DEFAULT_SOURCE_LOCATION());
    } else if (isalpha(*start) || *start == '_') {
        // Parse identifier (variable)
        while (*start && (isalnum(*start) || *start == '_')) {
            start++;
        }
        
        size_t var_len = start - expr_start;
        if (var_len == 0) {
            return NULL;
        }
        
        char var_name[256];
        if (var_len >= sizeof(var_name)) {
            return NULL;
        }
        strncpy(var_name, expr_start, var_len);
        var_name[var_len] = '\0';
        
        // Create identifier node for variable reference
        count_expr = ast_create_identifier(var_name, XMD_DEFAULT_SOURCE_LOCATION());
    } else {
        // Invalid count expression
        return NULL;
    }
    
    if (!count_expr) {
        return NULL;
    }
    
    // Skip whitespace
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    // Check for "times" keyword
    if (strncmp(start, "times", 5) != 0) {
        return NULL;
    }
    start += 5;
    
    // Skip to end of line
    while (*start && *start != '\n') {
        start++;
    }
    if (*start == '\n') {
        start++;
    }
    
    // Create loop times node that will generate range at evaluation time
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    
    // Parse loop body (indented statements)
    ast_node* loop_body = NULL;
    if (*start && (isspace(*start) && *start != '\n')) {
        // Has indented content - parse as block
        loop_body = ast_create_block(loc);
        
        while (*start) {
            // Skip initial indentation
            const char* line_start = start;
            while ((*start && *start == ' ') || *start == '\t') {
                start++;
            }
            
            // If we hit newline or end, break
            if (!*start || *start == '\n') {
                if (*start == '\n') start++;
                break;
            }
            
            // Check if this line is indented (loop body content)
            if (start > line_start) {
                // Parse this indented statement as part of loop body
                const char* stmt_pos = start;
                ast_node* stmt = ast_parse_statement(&stmt_pos);
                if (stmt && loop_body) {
                    ast_add_statement(loop_body, stmt);
                }
                start = stmt_pos;
            } else {
                // Not indented - exit loop body
                start = line_start; // Reset position
                break;
            }
        }
    }
    
    // Update position
    *pos = start;
    
    // Create loop times node with count expression
    ast_node* loop = ast_create_loop_times(count_expr, loop_body, loc);
    
    return loop;
}