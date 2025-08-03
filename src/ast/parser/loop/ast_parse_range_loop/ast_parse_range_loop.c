/**
 * @file ast_parse_range_loop.c
 *
 * @brief Implementation of ast_parse_range_loop function
 * 
 * This file contains ONLY the ast_parse_range_loop function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "module.h"
#include "variable.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse Genesis range loop: "for i in 1 .. 5"
 * @param pos Pointer to current position
 * @return Loop AST node or NULL
 */
ast_node* ast_parse_range_loop(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    start += 4; // Skip "for "
    
    // Parse variable name
    const char* var_start = start;
    while (*start && !isspace(*start)) {
        start++;
    }
    
    size_t var_len = start - var_start;
    char* var_name = xmd_malloc(var_len + 1);
    XMD_NULL_CHECK(var_name);
    strncpy(var_name, var_start, var_len);
    var_name[var_len] = '\0';
    
    // Skip whitespace and "in"
    while (*start && isspace(*start)) {
        start++;
    }
    if (strncmp(start, "in ", 3) != 0) {
        XMD_FREE_SAFE(var_name);
        return NULL;
    }
    start += 3;
    
    // Find range operator with flexible spacing
    const char* range_pos = strstr(start, "..");
    if (!range_pos) {
        XMD_FREE_SAFE(var_name);
        return NULL;
    }
    
    // Parse start value
    const char* start_str = start;
    while (*start_str && isspace(*start_str)) {
        start_str++;
    }
    const char* start_end = range_pos;
    while (start_end > start_str && isspace(*(start_end-1))) {
        start_end--;
    }
    
    size_t start_num_len = start_end - start_str;
    char start_num_str[32];
    if (start_num_len >= sizeof(start_num_str)) {
        XMD_FREE_SAFE(var_name);
        return NULL;
    }
    strncpy(start_num_str, start_str, start_num_len);
    start_num_str[start_num_len] = '\0';
    
    // Parse end value
    const char* end_str = range_pos + 2;
    while (*end_str && isspace(*end_str)) {
        end_str++;
    }
    const char* end_end = end_str;
    while (*end_end && !isspace(*end_end) && *end_end != '\n') {
        end_end++;
    }
    
    size_t end_num_len = end_end - end_str;
    char end_num_str[32];
    if (end_num_len >= sizeof(end_num_str)) {
        XMD_FREE_SAFE(var_name);
        return NULL;
    }
    strncpy(end_num_str, end_str, end_num_len);
    end_num_str[end_num_len] = '\0';
    
    // Convert to integers
    int start_val = atoi(start_num_str);
    int end_val = atoi(end_num_str);
    
    // Create array literal for range
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* range_array = ast_create_array_literal(loc);
    if (!range_array) {
        XMD_FREE_SAFE(var_name);
        return NULL;
    }
    
    // Generate numbers in range (forward or reverse)
    if (start_val <= end_val) {
        // Forward range: 1..5 = [1,2,3,4,5]
        for (int i = start_val; i <= end_val; i++) {
            ast_node* num = ast_create_number_literal((double)i, loc);
            if (num) {
                ast_add_element(range_array, num);
            }
        }
    } else {
        // Reverse range: 5..1 = [5,4,3,2,1]
        for (int i = start_val; i >= end_val; i--) {
            ast_node* num = ast_create_number_literal((double)i, loc);
            if (num) {
                ast_add_element(range_array, num);
            }
        }
    }
    
    // Update position past range
    *pos = end_end;
    
    // Skip to newline and parse loop body (indented statements)
    while (**pos && **pos != '\n') {
        (*pos)++;
    }
    if (**pos == '\n') {
        (*pos)++; // Skip newline
    }
    
    
    // Parse loop body as block of indented statements
    ast_node* loop_body = NULL;
    if (**pos && (isspace(**pos) && **pos != '\n')) {
        // Has indented content - parse as block
        source_location body_loc = {1, 1, "input"};
        loop_body = ast_create_block(body_loc);
        
        while (**pos) {
            // Skip initial indentation
            const char* line_start = *pos;
            while ((**pos && **pos == ' ') || **pos == '\t') {
                (*pos)++;
            }
            
            // If we hit newline or end, break
            if (!**pos || **pos == '\n') {
                if (**pos == '\n') (*pos)++;
                break;
            }
            
            // Check if this line is indented (loop body content)
            if (*pos > line_start) {
                // Parse this indented statement as part of loop body
                ast_node* stmt = ast_parse_statement(pos);
                if (stmt && loop_body) {
                    ast_add_statement(loop_body, stmt);
                }
            } else {
                // Not indented - exit loop body
                *pos = line_start; // Reset position
                break;
            }
        }
    }
    
    
    // Create loop node
    ast_node* loop = ast_create_loop(var_name, range_array, loc);
    if (loop && loop_body) {
        loop->data.loop.body = loop_body;
    }
    
    XMD_FREE_SAFE(var_name);
    
    return loop;
}
