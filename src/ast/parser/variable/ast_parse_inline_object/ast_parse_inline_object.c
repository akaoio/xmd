/**
 * @file ast_parse_inline_object.c
 * @brief Implementation of ast_parse_inline_object function
 * 
 * This file contains ONLY the ast_parse_inline_object function.
 * One function per file - Genesis principle compliance.
 * 
 * Implements XMD inline object syntax: set user name "Alice", age 30, active true
 * This creates an object: {name: "Alice", age: 30, active: true}
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "utils.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Parse inline object syntax: key value, key value, ...
 * @param pos Pointer to current position (updated)
 * @param variable_name The object variable name
 * @return Object literal AST node or NULL on error
 * 
 * XMD Syntax: set user name "Alice", age 30, active true
 * Creates: {name: "Alice", age: 30, active: true}
 */
ast_node* ast_parse_inline_object(const char** pos, const char* variable_name) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    XMD_VALIDATE_STRING_RETVAL(variable_name, NULL);
    
    const char* start = *pos;
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    
    // Create program node to hold multiple assignments that create the object
    ast_node* program_node = ast_create_program();
    if (!program_node) {
        return NULL;
    }
    
    // Parse key-value pairs separated by commas
    while (*start && *start != '\n') {
        // Skip whitespace
        while (*start && isspace(*start) && *start != '\n') {
            start++;
        }
        
        if (!*start || *start == '\n') {
            break;
        }
        
        // Parse key (identifier)
        const char* key_start = start;
        while (*start && (isalnum(*start) || *start == '_') && *start != '\n') {
            start++;
        }
        
        if (start == key_start) {
            // No valid key found
            ast_free(program_node);
            return NULL;
        }
        
        // Extract key name
        size_t key_len = start - key_start;
        char* key_name = xmd_malloc(key_len + 1);
        if (!key_name) {
            ast_free(program_node);  
            return NULL;
        }
        strncpy(key_name, key_start, key_len);
        key_name[key_len] = '\0';
        
        // Skip whitespace after key
        while (*start && isspace(*start) && *start != '\n') {
            start++;
        }
        
        // Parse value expression
        ast_node* value_expr = ast_parse_expression(&start);
        if (!value_expr) {
            XMD_FREE_SAFE(key_name);
            ast_free(program_node);
            return NULL;
        }
        
        // Create full property name: variable_name.key_name
        size_t full_name_len = strlen(variable_name) + 1 + key_len + 1;
        char* full_property_name = xmd_malloc(full_name_len);
        if (!full_property_name) {
            XMD_FREE_SAFE(key_name);
            ast_free(value_expr);
            ast_free(program_node);
            return NULL;
        }
        snprintf(full_property_name, full_name_len, "%s.%s", variable_name, key_name);
        
        // Create property assignment: variable_name.key = value
        ast_node* property_assignment = ast_create_assignment(full_property_name, BINOP_ASSIGN, value_expr, loc);
        if (property_assignment) {
            // Add assignment to program
            ast_add_statement(program_node, property_assignment);
        } else {
            XMD_FREE_SAFE(key_name);
            XMD_FREE_SAFE(full_property_name);
            ast_free(value_expr);
            ast_free(program_node);
            return NULL; 
        }
        
        XMD_FREE_SAFE(key_name);
        XMD_FREE_SAFE(full_property_name);
        
        // Skip whitespace
        while (*start && isspace(*start) && *start != '\n') {
            start++;
        }
        
        // Check for comma (continue) or end (break)
        if (*start == ',') {
            start++; // Skip comma
            continue;
        } else {
            // End of object
            break;
        }
    }
    
    *pos = start;
    return program_node;
}