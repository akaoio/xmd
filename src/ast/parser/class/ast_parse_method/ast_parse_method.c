/**
 * @file ast_parse_method_simple.c
 *
 *
 * @brief Implementation of ast_parse_method_simple function
 * 
 * This file contains ONLY the ast_parse_method_simple function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "module.h"
#include "utils.h"
/**
 * @brief Parse a method definition within a class
 * @param pos Pointer to current position (updated)
 * @return Method AST node or NULL
 */
ast_node* ast_parse_method(const char** pos) {
    const char* start = *pos;
    if (!start) return NULL;
    
    // Check for "private" keyword
    bool is_private = false;
    if (strncmp(start, "private ", 8) == 0) {
        is_private = true;
        start += 8;
        while (*start && isspace(*start)) start++;
    }
    // Check for "constructor" keyword
    bool is_constructor = false;
    char* method_name = NULL;
    if (strncmp(start, "constructor", 11) == 0) {
        is_constructor = true;
        start += 11;
        method_name = xmd_strdup("constructor");
    } else {
        // Regular method - find method name
        const char* name_start = start;
        while (*start && !isspace(*start) && *start != '\n') {
            start++;
        }
        
        if (start == name_start) {
            return NULL; // No method name found
        }
        size_t name_len = start - name_start;
        method_name = xmd_malloc(name_len + 1);
        if (method_name) {
            strncpy(method_name, name_start, name_len);
            method_name[name_len] = '\0';
        }
    }
    
    if (!method_name) {
        return NULL;
    }
    
    // Skip whitespace after method name
    while (*start && isspace(*start) && *start != '\n') start++;
    // Parse space-separated parameters (Genesis style, not parentheses)
    // For now, skip parameter parsing until end of line
    while (*start && *start != '\n') {
        start++;
    }
    
    // Check for method body (indented lines following)
    if (*start == '\n') {
        start++; // Skip the newline
        // Check if next line is indented (method body)
        const char* next_line = start;
        int method_body_indent = 0;
        while (*next_line && (*next_line == ' ' || *next_line == '\t')) {
            method_body_indent++;
            next_line++;
        }
        
        if (method_body_indent > 0 && *next_line && *next_line != '\n') {
            printf("DEBUG: Found indented method body for %s (indent: %d)\n", method_name, method_body_indent);
            
            while (*start) {
                // Check if this line starts a new method (less indentation)
                const char* line_start = start;
                int line_indent = 0;
                while (*line_start && (*line_start == ' ' || *line_start == '\t')) {
                    line_indent++;
                    line_start++;
                }
                
                // If we hit a line with less indentation than the method body, or EOF, we're done
                if (*line_start == '\0' || (*line_start != '\n' && line_indent < method_body_indent)) {
                    printf("DEBUG: End of method body - found line with indent %d\n", line_indent);
                    break;
                }
                
                // Skip to next line
                while (*start && *start != '\n') start++;
                if (*start == '\n') start++;
            }
            printf("DEBUG: Method body skipped for %s\n", method_name);
            printf("DEBUG: Position after method body: %.20s\n", start);
        } else {
                // No method body, skip to end of line
            while (*start && *start != '\n') start++;
        }
    }
    
    *pos = start;
    // Create method node
    source_location loc = {1, 1, "input"}; 
    ast_node* method = ast_create_method_def(method_name, is_private, loc);
    XMD_FREE_SAFE(method_name);
    return method;
}
