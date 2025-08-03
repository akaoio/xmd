/**
 * @file ast_parse_statement.c
 *
 * @brief Implementation of ast_parse_statement function
 * 
 * This file contains ONLY the ast_parse_statement function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "ast.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse a single statement
 * @param pos Pointer to current position in input
 * @return AST statement node or NULL
 */
ast_node* ast_parse_statement(const char** pos) {
    if (!pos || !*pos) {
        XMD_ERROR_RETURN(NULL, "ast_parse_statement: NULL position pointer provided");
    }
    
    // DEBUG: ast_parse_statement ENTRY - disabled after successful loop fix
    const char* start = *pos;
    // Skip whitespace
    while (*start && isspace(*start) && *start != '\n') {
        start++;
    }
    
    if (!*start || *start == '\n') {
        XMD_ERROR_RETURN(NULL, "ast_parse_statement: Empty statement or newline-only input");
    }
    
    *pos = start;
    
    // CONTROL FLOW PARSING
    // Check for IF statements (Genesis if/then syntax)
    if (strncmp(start, "if ", 3) == 0) {
        const char* then_pos = strstr(start + 3, " then ");
        if (then_pos) {
            // Single line: "if condition then action"
            return ast_parse_if_then(pos);
        } else {
            // Block form
            return ast_parse_if_block(pos);
        }
    }
    
    // Check for ELIF statements
    if (strncmp(start, "elif ", 5) == 0) {
        return ast_parse_elif(pos);
    }
    
    // Check for ELSE statements
    if (strncmp(start, "else", 4) == 0 && (start[4] == '\0' || isspace(start[4]) || start[4] == '\n')) {
        return ast_parse_else(pos);
    }
    
    // Check for WHILE loops
    if (strncmp(start, "while ", 6) == 0) {
        return ast_parse_while(pos);
    }
    
    // Check for FOR loops (enhanced with range support)
    if (strncmp(start, "for ", 4) == 0) {
        // Check for range syntax first
        const char* line_end = start;
        while (*line_end && *line_end != '\n') {
            line_end++;
        }
        
        const char* range_pos = strstr(start, "..");
        if (range_pos && range_pos < line_end) {
            // Range loop syntax detected - use specialized parser
            return ast_parse_range_loop(pos);
        } else {
            // Use general loop parser
            return ast_parse_loop(pos);
        }
    }
    
    // Check for BREAK statements
    if (strncmp(start, "break", 5) == 0 && (start[5] == '\0' || isspace(start[5]) || start[5] == '\n')) {
        *pos = start + 5;
        while (**pos && **pos != '\n') {
            (*pos)++;
        }
        if (**pos == '\n') {
            (*pos)++;
        }
        source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
        return ast_create_break_statement(loc);
    }
    
    // Check for CONTINUE statements
    if (strncmp(start, "continue", 8) == 0 && (start[8] == '\0' || isspace(start[8]) || start[8] == '\n')) {
        *pos = start + 8;
        while (**pos && **pos != '\n') {
            (*pos)++;
        }
        if (**pos == '\n') {
            (*pos)++;
        }
        source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
        return ast_create_continue_statement(loc);
    }
    
    // Check for SET statements (Variable assignment)
    if (strncmp(start, "set ", 4) == 0) {
        return ast_parse_assignment(pos);
    }
    
    // Check for FUNCTION definitions
    if (strncmp(start, "function ", 9) == 0) {
        return ast_parse_function(pos);
    }
    
    // Check for CLASS definitions
    if (strncmp(start, "class ", 6) == 0) {
        return ast_parse_class(pos);
    }
    
    // Check for PRINT statements
    if (strncmp(start, "print ", 6) == 0) {
        return ast_parse_print(pos);
    }
    
    // Check for File operations
    if (strncmp(start, "File.", 5) == 0) {
        const char* temp_pos = start;
        ast_node* func_call = ast_parse_potential_function_call(&temp_pos);
        if (func_call) {
            *pos = temp_pos;
            return func_call;
        }
    }
    
    // Check for parenthesized function calls EARLY: func(arg1, arg2)
    const char* paren_check = start;
    while (*paren_check && (isalnum(*paren_check) || *paren_check == '_')) {
        paren_check++;
    }
    if (*paren_check == '(' && paren_check > start) {
        // Parse function name
        size_t func_name_len = paren_check - start;
        char* func_name = xmd_malloc(func_name_len + 1);
        if (func_name) {
            strncpy(func_name, start, func_name_len);
            func_name[func_name_len] = '\0';
            
            // Skip opening paren
            const char* arg_start = paren_check + 1;
            
            // Find closing paren
            const char* arg_end = arg_start;
            int paren_depth = 1;
            while (*arg_end && paren_depth > 0) {
                if (*arg_end == '(') paren_depth++;
                else if (*arg_end == ')') paren_depth--;
                if (paren_depth > 0) arg_end++;
            }
            
            if (*arg_end == ')') {
                // Parse arguments
                source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
                ast_node* func_call = ast_create_function_call(func_name, loc);
                
                // Parse argument if present
                if (arg_end > arg_start) {
                    // For now, parse single argument
                    const char* arg_pos = arg_start;
                    ast_node* arg = ast_parse_expression(&arg_pos);
                    if (arg && func_call) {
                        ast_add_argument(func_call, arg);
                    }
                }
                
                *pos = arg_end + 1; // Move past closing paren
                XMD_FREE_SAFE(func_name);
                
                return func_call;
            }
            XMD_FREE_SAFE(func_name);
        }
    }
    
    // Check for variable substitution ${varname}
    if (strncmp(start, "${", 2) == 0) {
        // Parse variable name
        const char* var_pos = start + 2;
        while (*var_pos && *var_pos != '}') {
            var_pos++;
        }
        if (*var_pos == '}') {
            // Extract variable name
            size_t var_len = var_pos - (start + 2);
            char* var_name = xmd_malloc(var_len + 1);
            if (var_name) {
                strncpy(var_name, start + 2, var_len);
                var_name[var_len] = '\0';
                
                // Move position past the variable substitution
                *pos = var_pos + 1;
                
                // Create variable reference node
                source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
                ast_node* var_ref = ast_create_identifier(var_name, loc);
                XMD_FREE_SAFE(var_name);
                return var_ref;
            }
        }
    }
    
    // Parse potential function calls EARLY (before plain text)
    const char* temp_pos = start;
    ast_node* func_call = ast_parse_potential_function_call(&temp_pos);
    if (func_call) {
        *pos = temp_pos;
        return func_call;
    }
    
    // Check for plain text (not starting with commands or ${)
    const char* text_start = start;
    const char* text_pos = start;
    
    // Read until we find a command keyword or variable substitution
    while (*text_pos && *text_pos != '\n' && 
           strncmp(text_pos, "${", 2) != 0 &&
           strncmp(text_pos, "set ", 4) != 0 &&
           strncmp(text_pos, "if ", 3) != 0 &&
           strncmp(text_pos, "for ", 4) != 0 &&
           strncmp(text_pos, "while ", 6) != 0 &&
           strncmp(text_pos, "function ", 9) != 0 &&
           strncmp(text_pos, "class ", 6) != 0 &&
           strncmp(text_pos, "print ", 6) != 0) {
        text_pos++;
    }
    
    if (text_pos > text_start) {
        // Extract plain text content
        size_t text_len = text_pos - text_start;
        char* text_content = xmd_malloc(text_len + 1);
        if (text_content) {
            strncpy(text_content, text_start, text_len);
            text_content[text_len] = '\0';
            
            // Trim trailing whitespace
            char* end = text_content + text_len - 1;
            while (end > text_content && isspace(*end)) {
                *end = '\0';
                end--;
            }
            
            *pos = text_pos;
            
            // Create string literal for plain text
            source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
            ast_node* text_node = ast_create_string_literal(text_content, loc);
            XMD_FREE_SAFE(text_content);
            return text_node;
        }
    }
    
    // Function call parsing moved earlier to prevent conflicts with plain text parsing
    
    // Unknown statement - skip to next line
    while (**pos && **pos != '\n') {
        (*pos)++;
    }
    if (**pos == '\n') {
        (*pos)++;
    }
    
    return NULL;
}
