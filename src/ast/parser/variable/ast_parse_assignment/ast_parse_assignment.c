/**
 * @file ast_parse_assignment.c
 * @brief Parse variable assignment (set var value)
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../../../../../include/ast.h"
#include "../../../../../include/utils.h"
#include "../../../../../src/utils/common/common_macros.h"

/**
 * @brief Parse assignment statement: set var value
 * @param pos Pointer to current position (updated)
 * @return Assignment AST node or NULL
 */
ast_node* ast_parse_assignment(const char** pos) {
    XMD_ENTRY_VALIDATE(pos, *pos);
    
    const char* start = *pos;
    
    // Skip "set "
    if (strncmp(start, "set ", 4) != 0) {
        XMD_ERROR_RETURN(NULL, "Expected 'set' keyword in assignment");
    }
    start += 4;
    
    // Skip whitespace
    while (*start && isspace(*start)) start++;
    
    // Parse variable name
    const char* var_start = start;
    while (*start && (isalnum(*start) || *start == '_')) {
        start++;
    }
    
    if (start == var_start) {
        XMD_ERROR_RETURN(NULL, "Missing variable name after 'set'");
    }
    
    size_t var_len = start - var_start;
    char* var_name = xmd_malloc(var_len + 1);
    if (!var_name) {
        XMD_ERROR_RETURN(NULL, "Memory allocation failed for variable name");
    }
    strncpy(var_name, var_start, var_len);
    var_name[var_len] = '\0';
    
    // Skip whitespace
    while (*start && isspace(*start)) start++;
    
    printf("DEBUG: Assignment parsing - after var name: '%s'\n", start);
    
    // Skip optional equals sign
    if (*start == '=') {
        printf("DEBUG: Found equals sign, skipping\n");
        start++;
        // Skip whitespace after equals
        while (*start && isspace(*start)) start++;
        printf("DEBUG: After skipping equals and whitespace: '%s'\n", start);
    }
    
    // Parse value expression
    const char* value_start = start;
    printf("DEBUG: Value starts at: '%s'\n", value_start);
    
    // Find end of line or next statement
    while (*start && *start != '\n' && *start != ';') {
        start++;
    }
    
    // Create assignment node
    source_location loc = {1, 1, "input"};
    ast_node* identifier = ast_create_identifier(var_name, loc);
    
    // Parse the value expression
    ast_node* value = ast_parse_expression(&value_start);
    if (!value) {
        // If parsing fails, create a string literal with the remaining text
        size_t value_len = start - value_start;
        char* value_str = xmd_malloc(value_len + 1);
        if (value_str) {
            strncpy(value_str, value_start, value_len);
            value_str[value_len] = '\0';
            value = ast_create_string_literal(value_str, loc);
            XMD_FREE_SAFE(value_str);
        }
    }
    
    ast_node* assignment = ast_create_assignment(var_name, BINOP_ASSIGN, value, loc);
    
    // Debug: Check what kind of value node was created
    if (value) {
        printf("DEBUG: Assignment created - variable: '%s', value node type: %d\n", var_name, value->type);
        if (value->type == AST_IDENTIFIER) {
            printf("DEBUG: Value is identifier with name: '%s'\n", value->data.identifier.name);
        }
    } else {
        printf("DEBUG: Assignment created - variable: '%s', value node: NULL\n", var_name);
    }
    
    *pos = start;
    XMD_FREE_SAFE(var_name);
    
    return assignment;
}