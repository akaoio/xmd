/**
 * @file ast_parse_multiple_variables_handler.c
 * @brief Implementation of ast_parse_multiple_variables_handler function
 * 
 * This file contains ONLY the ast_parse_multiple_variables_handler function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "error.h"
#include "module.h"
#include "performance.h"
#include "store_internal.h"
#include "token.h"
#include "variable.h"
/**
 * @brief Parse multiple variable assignments: set x 10, y 20, z 30
 * @param pos Pointer to current position  
 * @param first_name First variable name already parsed
 * @return Program node containing multiple assignment statements
 */
ast_node* ast_parse_multiple_variables_handler(const char** pos, const char* first_name) {
    if (!pos || !*pos || !first_name) {
        return NULL;
    }
    
    const char* start = *pos;
    source_location loc = {1, 1, "input"};
    
    // Create program node to hold multiple assignments
    ast_node* program = ast_create_program();
    if (!program) {
        return NULL;
    }
    
    // Skip "set " and first variable name (already parsed)
    start += 4; // Skip "set "
    while (*start && isspace(*start)) start++;
    while (*start && !isspace(*start)) start++; // Skip first var name
    while (*start && isspace(*start)) start++;
    
    // Parse first assignment: first_name value
    const char* value_start = start;
    
    // Find end of first value - need to be more precise about parsing
    // Skip to the actual value (e.g., number, string)
    const char* value_end = start;
    if (isdigit(*value_end)) {
        // Parse number
        while (*value_end && (isdigit(*value_end) || *value_end == '.')) {
            value_end++;
        }
    } else if (*value_end == '"') {
        // Parse quoted string
        value_end++; // Skip opening quote
        while (*value_end && *value_end != '"') {
            if (*value_end == '\\') value_end++; // Skip escaped char
            if (*value_end) value_end++;
        }
        if (*value_end == '"') value_end++; // Skip closing quote
    } else if (isalpha(*value_end) || *value_end == '_') {
        // Parse identifier (could be boolean like "true" or variable reference)
        while (*value_end && (isalnum(*value_end) || *value_end == '_')) {
            value_end++;
        }
    } else {
        // Skip until comma or newline as fallback
        while (*value_end && *value_end != ',' && *value_end != '\n') {
            value_end++;
        }
    }
    
    // Create a temporary string with just the first value
    size_t first_value_len = value_end - value_start;
    char* first_value_str = malloc(first_value_len + 1);
    if (!first_value_str) return NULL;
    
    strncpy(first_value_str, value_start, first_value_len);
    first_value_str[first_value_len] = '\0';
    
    // Trim whitespace
    char* trimmed = first_value_str;
    while (*trimmed && isspace(*trimmed)) trimmed++;
    char* end = first_value_str + first_value_len - 1;
    while (end > first_value_str && isspace(*end)) *end-- = '\0';
    
    // Parse the trimmed value
    const char* value_pos = trimmed;
    ast_node* first_value = ast_parse_expression(&value_pos);
    if (!first_value) {
        // Create string literal from raw text
        first_value = ast_create_string_literal(trimmed, loc);
    }
    
    free(first_value_str);
    start = value_end;
    
    if (first_value) {
        ast_node* first_assignment = ast_create_assignment(first_name, BINOP_ASSIGN, first_value, loc);
        if (first_assignment) {
            ast_add_statement(program, first_assignment);
        }
    }
    
    // Parse remaining variable assignments
    while (*start == ',') {
        start++; // Skip comma
        while (*start && isspace(*start)) start++; // Skip whitespace
        
        // Parse variable name
        const char* var_start = start;
        while (*start && (isalnum(*start) || *start == '_')) {
            start++;
        }
        
        if (start == var_start) {
            break; // No more variable names
        }
        
        size_t var_len = start - var_start;
        char* var_name = malloc(var_len + 1);
        if (!var_name) break;
        
        strncpy(var_name, var_start, var_len);
        var_name[var_len] = '\0';
        
        // Skip whitespace
        while (*start && isspace(*start)) start++;
        
        // Parse value with precise delimiting
        value_start = start;
        const char* value_end = start;
        
        // Find exact end of this value
        if (isdigit(*value_end)) {
            // Parse number
            while (*value_end && (isdigit(*value_end) || *value_end == '.')) {
                value_end++;
            }
        } else if (*value_end == '"') {
            // Parse quoted string
            value_end++; // Skip opening quote
            while (*value_end && *value_end != '"') {
                if (*value_end == '\\') value_end++; // Skip escaped char
                if (*value_end) value_end++;
            }
            if (*value_end == '"') value_end++; // Skip closing quote
        } else if (isalpha(*value_end) || *value_end == '_') {
            // Parse identifier
            while (*value_end && (isalnum(*value_end) || *value_end == '_')) {
                value_end++;
            }
        } else {
            // Fallback: skip until comma or newline
            while (*value_end && *value_end != ',' && *value_end != '\n') {
                value_end++;
            }
        }
        
        // Create temporary string with just this value
        size_t this_value_len = value_end - value_start;
        char* this_value_str = malloc(this_value_len + 1);
        if (!this_value_str) break;
        
        strncpy(this_value_str, value_start, this_value_len);
        this_value_str[this_value_len] = '\0';
        
        // Trim whitespace
        char* trimmed = this_value_str;
        while (*trimmed && isspace(*trimmed)) trimmed++;
        char* end = this_value_str + this_value_len - 1;
        while (end > this_value_str && isspace(*end)) *end-- = '\0';
        
        // Parse the trimmed value
        value_pos = trimmed;
        ast_node* value = ast_parse_expression(&value_pos);
        if (!value) {
            // Create string literal from raw text
            value = ast_create_string_literal(trimmed, loc);
        }
        
        free(this_value_str);
        start = value_end;
        
        if (value) {
            ast_node* assignment = ast_create_assignment(var_name, BINOP_ASSIGN, value, loc);
            if (assignment) {
                ast_add_statement(program, assignment);
            }
        }
        
        free(var_name);
    }
    
    *pos = start;
    return program;
}
