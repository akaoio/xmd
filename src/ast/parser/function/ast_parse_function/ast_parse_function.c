/**
 * @file ast_parse_function.c
 *
 * @brief Implementation of ast_parse_function function
 * 
 * This file contains ONLY the ast_parse_function function.
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
#include "error.h"
#include "module.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse function definition: function name param1 param2
 * @param pos Pointer to current position
 * @return Function definition AST node or NULL
 */
ast_node* ast_parse_function(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    const char* start = *pos;
    
    // Skip "function "
    start += 9;
    while (*start && isspace(*start)) {
        start++;
    }
    
    // Get function name
    const char* name_start = start;
    while (*start && !isspace(*start) && *start != '\n') {
        start++;
    }
    
    size_t name_len = start - name_start;
    if (name_len == 0) {
        // Skip to end of line on error
        while (**pos && **pos != '\n') {
            (*pos)++;
        }
        return NULL;
    }
    
    char* func_name;
    XMD_MALLOC_SAFE(func_name, char[name_len + 1], NULL, "ast_parse_function: Failed to allocate function name");
    if (!func_name) {
        return NULL;
    }
    strncpy(func_name, name_start, name_len);
    func_name[name_len] = '\0';
    
    // Create function definition node
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* func_def = ast_create_function_def(func_name, false, loc);
    free(func_name);
    
    if (!func_def) {
        return NULL;
    }
    
    // Parse space-separated parameters
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    while (*start && *start != '\n') {
        // Get parameter name
        const char* param_start = start;
        while (*start && !isspace(*start) && *start != '\n') {
            start++;
        }
        
        if (start > param_start) {
            size_t param_len = start - param_start;
            char* param_name = xmd_malloc(param_len + 1);
            if (param_name) {
                strncpy(param_name, param_start, param_len);
                param_name[param_len] = '\0';
                ast_add_parameter(func_def, param_name);
                free(param_name);
            }
        }
        
        // Skip whitespace
        while (*start && isspace(*start) && *start != '\n') {
            start++;
        }
    }
    
    printf("DEBUG: Parsed function definition with %zu parameters\n", 
           func_def->data.function_def.parameter_count);
    
    // Check if there's a function body (indented lines following)
    if (*start == '\n') {
        start++; // Skip the newline
        
        // Check if next line is indented (function body)
        const char* next_line = start;
        while (*next_line && (*next_line == ' ' || *next_line == '\t')) {
            next_line++;
        }
        
        if (next_line > start && *next_line && *next_line != '\n') {
            // Found indented content - parse as function body
            printf("DEBUG: Found indented function body\n");
            
            // Parse the indented block as function body
            source_location body_loc = {1, 1, "input"};
            ast_node* body = ast_create_block(body_loc);
            if (body) {
                // Parse each indented line as a statement
                while (*start) {
                    if (*start == '\n') {
                        start++; // Skip newline
                        continue;
                    }
                    
                    // Check if this line is indented (part of function body)
                    const char* line_check = start;
                    int indent_count = 0;
                    while (*line_check && (*line_check == ' ' || *line_check == '\t')) {
                        indent_count++;
                        line_check++;
                    }
                    
                    // If line has no indentation or is empty, end of function body
                    if (indent_count == 0 || *line_check == '\n' || *line_check == '\0') {
                        break;
                    }
                    
                    // Skip the indentation to get to content
                    start = line_check;
                    
                    // Parse the line as a statement
                    const char* line_start = start;
                    while (*start && *start != '\n') {
                        start++;
                    }
                    
                    if (start > line_start) {
                        size_t line_len = start - line_start;
                        char* line_content = xmd_malloc(line_len + 1);
                        if (line_content) {
                            strncpy(line_content, line_start, line_len);
                            line_content[line_len] = '\0';
                            
                            printf("DEBUG: Parsing function body line: '%s'\n", line_content);
                            
                            // Check if this is a return statement
                            const char* trimmed = line_content;
                            while (*trimmed && isspace(*trimmed)) {
                                trimmed++;
                            }
                            
                            if (strncmp(trimmed, "return ", 7) == 0) {
                                // Parse return statement
                                printf("DEBUG: Found return statement in function body\n");
                                const char* return_expr = trimmed + 7;
                                while (*return_expr && isspace(*return_expr)) {
                                    return_expr++;
                                }
                                
                                // Parse the return expression
                                const char* expr_pos = return_expr;
                                ast_node* return_value = ast_parse_expression(&expr_pos);
                                if (return_value) {
                                    // Create return statement node
                                    source_location ret_loc = {1, 1, "input"};
                                    ast_node* return_stmt = ast_create_return(return_value, ret_loc);
                                    if (return_stmt) {
                                        ast_add_statement(body, return_stmt);
                                        printf("DEBUG: Return statement added to function body\n");
                                    }
                                } else {
                                    printf("DEBUG: Failed to parse return expression: %s\n", return_expr);
                                }
                            } else {
                                // Parse as general statement
                                const char* stmt_pos = trimmed;
                                ast_node* stmt = ast_parse_statement(&stmt_pos);
                                if (stmt) {
                                    ast_add_statement(body, stmt);
                                    printf("DEBUG: Statement added to function body\n");
                                }
                            }
                            free(line_content);
                        }
                    }
                    
                    if (*start == '\n') {
                        start++; // Skip newline
                    }
                }
                
                func_def->data.function_def.body = body;
                printf("DEBUG: Function body parsed successfully\n");
            }
        }
    }
    
    *pos = start;
    return func_def;
}
