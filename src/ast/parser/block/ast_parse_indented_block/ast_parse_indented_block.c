/**
 * @file ast_parse_indented_block.c
 * @brief Parse indented block of statements for function bodies
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 */

#include <string.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Parse an indented block of statements
 * @param pos Pointer to current position (should be at newline before indent)
 * @param min_indent Minimum expected indentation level
 * @return Block node containing all indented statements or NULL
 */
ast_node* ast_parse_indented_block(const char** pos, int min_indent) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    
    // Create block node to hold statements
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* block = ast_create_block(loc);
    if (!block) {
        return NULL;
    }
    
    // Parse all indented statements
    while (*start) {
        // Save position in case we need to backtrack
        const char* line_start = start;
        
        // Count indentation
        int indent = 0;
        while (*start == ' ') {
            indent++;
            start++;
        }
        while (*start == '\t') {
            indent += 4;  // Count tabs as 4 spaces
            start++;
        }
        
        // If blank line, skip it
        if (*start == '\n') {
            start++;
            continue;
        }
        
        // If less indented than minimum, we're done with this block
        if (indent < min_indent) {
            // Backtrack to beginning of this line
            start = line_start;
            break;
        }
        
        // If we have content at proper indentation, parse it
        if (*start && *start != '\n') {
            // Parse the statement
            ast_node* stmt = ast_parse_statement(&start);
            if (stmt) {
                ast_add_statement(block, stmt);
            } else {
                // If parsing failed, skip to next line
                while (*start && *start != '\n') {
                    start++;
                }
                if (*start == '\n') {
                    start++;
                }
            }
        }
    }
    
    *pos = start;
    return block;
}