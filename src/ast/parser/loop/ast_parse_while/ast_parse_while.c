/**
 * @file ast_parse_while.c
 *
 * @brief Implementation of ast_parse_while function
 * 
 * This file contains ONLY the ast_parse_while function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "ast.h"
#include "variable.h"
#include "utils.h"
#include "utils/common/common_macros.h"
/**
 * @brief Parse while loop statement: while condition
 * @param pos Pointer to current position
 * @return While loop AST node or NULL
 */
ast_node* ast_parse_while(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    // Skip "while "
    start += 6;
    while (*start && isspace(*start)) {
        start++;
    }
    
    // Parse condition until end of line
    const char* condition_start = start;
    while (*start && *start != '\n') {
        start++;
    }
    
    size_t condition_len = start - condition_start;
    if (condition_len == 0) {
        return NULL;
    }
    
    // Create condition expression from string
    char* condition_str;
    XMD_MALLOC_SAFE(condition_str, char[condition_len + 1], NULL, "ast_parse_while: Failed to allocate condition string");
    strncpy(condition_str, condition_start, condition_len);
    condition_str[condition_len] = '\0';
    
    // Trim trailing whitespace
    char* end = condition_str + condition_len - 1;
    while (end > condition_str && isspace(*end)) {
        *end = '\0';
        end--;
    }
    
    // Parse the condition as a comparison or simple expression
    ast_node* condition_node = NULL;
    if (strstr(condition_str, " < ") || strstr(condition_str, " > ") || 
        strstr(condition_str, " <= ") || strstr(condition_str, " >= ") ||
        strstr(condition_str, " == ") || strstr(condition_str, " = ") || 
        strstr(condition_str, " != ")) {
        condition_node = ast_parse_comparison_expression(condition_str);
    } else {
        // Simple expression or variable
        const char* expr_pos = condition_str;
        condition_node = ast_parse_expression(&expr_pos);
    }
    
    XMD_FREE_SAFE(condition_str);
    
    if (!condition_node) {
        return NULL;
    }
    
    // Create while loop node (using loop structure with condition as iterable)
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* while_node = ast_create_loop("", condition_node, loc); // Empty var name for while
    
    // Move past newline
    if (*start == '\n') {
        start++;
    }
    
    // Parse the loop body (indented statements)
    ast_node* body = ast_create_block(loc);
    if (body) {
        // Parse all indented lines
        while (*start) {
            // Check for indentation
            const char* line_start = start;
            int indent_count = 0;
            while (*line_start == ' ' || *line_start == '\t') {
                indent_count++;
                line_start++;
            }
            
            // If not indented or empty line, break
            if (indent_count == 0 || *line_start == '\n') {
                break;
            }
            
            // Parse the statement
            const char* stmt_pos = line_start;
            ast_node* stmt = ast_parse_statement(&stmt_pos);
            if (stmt) {
                ast_add_statement(body, stmt);
                start = stmt_pos;
                
                // Skip to next line
                while (*start && *start != '\n') {
                    start++;
                }
                if (*start == '\n') {
                    start++;
                }
            } else {
                break;
            }
        }
        
        // Attach body to while loop
        while_node->data.loop.body = body;
    }
    
    *pos = start;
    return while_node;
}
