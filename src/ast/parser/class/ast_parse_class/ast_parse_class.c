/**
 * @file ast_parse_class.c
 * @brief Implementation of ast_parse_class function
 * 
 * This file contains ONLY the ast_parse_class function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "module.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse class definition
 * Format: class ClassName [extends ParentClass]
 */
ast_node* ast_parse_class(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    
    const char* start = *pos;
    
    // Skip "class "
    start += 6;
    while (*start && isspace(*start)) start++;
    
    // Get class name
    const char* name_start = start;
    while (*start && (isalnum(*start) || *start == '_')) {
        start++;
    }
    size_t name_len = start - name_start;
    if (name_len == 0) {
        XMD_ERROR_RETURN(NULL, "ast_parse_class: Missing class name after 'class' keyword");
    }
    
    char* class_name;
    XMD_MALLOC_DYNAMIC(class_name, name_len + 1, NULL);
    strncpy(class_name, name_start, name_len);
    class_name[name_len] = '\0';
    
    // Check for extends
    while (*start && isspace(*start) && *start != '\n') start++;
    char* parent_class = NULL;
    if (strncmp(start, "extends ", 8) == 0) {
        start += 8;
        while (*start && isspace(*start)) start++;
        
        const char* parent_start = start;
        while (*start && (isalnum(*start) || *start == '_')) {
            start++;
        }
        size_t parent_len = start - parent_start;
        if (parent_len > 0) {
            XMD_MALLOC_DYNAMIC(parent_class, parent_len + 1, NULL);
            strncpy(parent_class, parent_start, parent_len);
            parent_class[parent_len] = '\0';
        }
    }
    
    // Create class definition node
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* class_def = ast_create_class_def(class_name, parent_class, loc);
    XMD_FREE_SAFE(class_name);
    XMD_FREE_SAFE(parent_class);
    
    // Check for class body (indented lines following)
    if (*start == '\n') {
        start++; // Skip the newline
        
        // Check if next line is indented (class body)
        const char* next_line = start;
        while (*next_line && (*next_line == ' ' || *next_line == '\t')) {
            next_line++;
        }
        
        if (next_line > start && *next_line && *next_line != '\n') {
            // Found indented content - parse as class body
            
            // Parse each indented line as a method or constructor
            while (*start) {
                
                if (*start == '\n') {
                    start++; // Skip newline
                    continue;
                }
                
                // Check if this line is indented (part of class body)
                const char* line_check = start;
                int indent_count = 0;
                while (*line_check && (*line_check == ' ' || *line_check == '\t')) {
                    indent_count++;
                    line_check++;
                }
                
                // If line has no indentation or is empty, end of class body
                if (indent_count == 0 || *line_check == '\n' || *line_check == '\0') {
                    break;
                }
                
                // Skip the indentation to get to content
                start = line_check;
                
                // Parse method or constructor
                ast_node* method = ast_parse_method(&start);
                if (method) {
                    ast_add_method(class_def, method);
                } else {
                    // Skip unrecognized content to next line
                    while (*start && *start != '\n') start++;
                    if (*start == '\n') start++;
                }
            }
        }
    } else {
        // No class body, skip to end of line
        while (*start && *start != '\n') {
            start++;
        }
    }
    
    *pos = start;
    return class_def;
}
