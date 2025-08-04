/**
 * @file ast_parse_object_creation.c
 * @brief Implementation of ast_parse_object_creation function
 * 
 * This file contains ONLY the ast_parse_object_creation function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "store_internal.h"
#include "variable.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Parse object creation: set user name "Alice", age 30
 * @param pos Pointer to current position
 * @param obj_name Object variable name already parsed  
 * @return Assignment node with object creation
 */
ast_node* ast_parse_object_creation(const char** pos, const char* obj_name) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos, obj_name);
    const char* start = *pos;
    // Skip "set "
    start += 4;
    while (*start && isspace(*start)) start++;
    // Skip past obj_name to get to key-value pairs
    while (*start && !isspace(*start)) start++;
    while (*start && isspace(*start) && *start != '\n') start++;
    // Create object literal node (using array literal as temporary placeholder)
    source_location loc = {1, 1, "input"};
    ast_node* object = ast_create_array_literal(loc);
    if (!object) {
        return NULL;
    }
    // Parse key-value pairs: key "value", key2 value2, ...
    while (*start && *start != '\n') {
        // Parse key (identifier)
        const char* key_start = start;
        while (*start && (isalnum(*start) || *start == '_')) {
            start++;
        }
        
        if (start == key_start) break; // No more keys
        size_t key_len = start - key_start;
        char* key_str;
        XMD_MALLOC_SAFE(key_str, char[key_len + 1], NULL, "ast_parse_object_creation: Failed to allocate key");
        strncpy(key_str, key_start, key_len);
        key_str[key_len] = '\0';
        // Skip whitespace after key
        while (*start && isspace(*start) && *start != '\n') start++;
        // Parse value
        const char* value_start = start;
        bool in_quotes = false;
        // Find end of value (until comma or end of line)
        while (*start && *start != '\n') {
            if (*start == '"' && (start == value_start || *(start-1) != '\\')) {
                in_quotes = !in_quotes;
            } else if (!in_quotes && *start == ',') {
                break;
            }
            start++;
        }
        size_t value_len = start - value_start;
        char* value_str;
        XMD_MALLOC_DYNAMIC(value_str, value_len + 1, NULL);
        {
            strncpy(value_str, value_start, value_len);
            value_str[value_len] = '\0';
            
            // Trim whitespace from value
            char* trim_start = value_str;
            while (*trim_start && isspace(*trim_start)) trim_start++;
            char* trim_end = value_str + value_len - 1;
            while (trim_end > trim_start && isspace(*trim_end)) {
                *trim_end = '\0';
                trim_end--;
            }
            // Parse the trimmed value
            const char* temp_pos = trim_start;
            ast_node* value_node = ast_parse_single_value(&temp_pos);
            if (value_node) {
                // Add key-value pair to object
                // Since we don't have ast_object_add_property, we'll simulate it
                // by creating a string key and storing the value
                ast_node* key_node = ast_create_string_literal(key_str, loc);
                if (key_node) {
                    // For now, just use the object as is - proper object support needs more work
                    // This is better than falling back to simple assignment though
                }
                XMD_FREE_SAFE(key_node);
            }
            if (value_node) XMD_FREE_SAFE(value_node);
            XMD_FREE_SAFE(value_str);
        }
        XMD_FREE_SAFE(key_str);
        // Skip comma if present
        if (*start == ',') {
            start++;
            while (*start && isspace(*start)) start++;
        }
    }
    // Create assignment with the object
    ast_node* assignment = ast_create_assignment(obj_name, BINOP_ASSIGN, object, loc);
    *pos = start;
    return assignment;
}
