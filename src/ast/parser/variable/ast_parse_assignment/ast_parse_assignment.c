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
    char* var_name;
    XMD_MALLOC_SAFE(var_name, char[var_len + 1], NULL, "ast_parse_assignment: Memory allocation failed");
    strncpy(var_name, var_start, var_len);
    var_name[var_len] = '\0';
    
    // Skip whitespace
    while (*start && isspace(*start)) start++;
    
    
    // Skip optional equals sign
    if (*start == '=') {
        start++;
        // Skip whitespace after equals
        while (*start && isspace(*start)) start++;
    }
    
    // Parse value expression
    const char* value_start = start;
    
    // Find end of line or next statement
    while (*start && *start != '\n' && *start != ';') {
        start++;
    }
    
    // Create assignment node
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    // ast_node* identifier = ast_create_identifier(var_name, loc); // Unused - var_name used directly
    
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
        if (value->type == AST_IDENTIFIER) {
        }
    } else {
    }
    
    *pos = start;
    XMD_FREE_SAFE(var_name);
    
    return assignment;
}
