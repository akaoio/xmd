/**
 * @file parse_array_literal.c
 * @brief Parse array literal syntax implementation
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Parse array literal from string
 * @param input Input string containing array literal like ["item1", "item2"]
 * @return Array variable or NULL on error
 */
variable* parse_array_literal(const char* input) {
    if (!input) return NULL;
    
    // Skip whitespace and check for opening bracket
    const char* p = input;
    while (isspace(*p)) p++;
    
    if (*p != '[') return NULL;
    p++; // Skip '['
    
    variable* array = variable_create_array();
    if (!array) return NULL;
    
    while (*p && *p != ']') {
        // Skip whitespace
        while (isspace(*p)) p++;
        
        if (*p == ']') break; // Empty array or end
        
        // Parse string literal
        if (*p == '"' || *p == '\'') {
            char quote = *p++;
            const char* start = p;
            
            // Find closing quote
            while (*p && *p != quote) {
                if (*p == '\\' && *(p+1)) p++; // Skip escaped characters
                p++;
            }
            
            if (*p != quote) {
                // Missing closing quote
                variable_unref(array);
                return NULL;
            }
            
            // Create string variable
            size_t len = p - start;
            char* str = malloc(len + 1);
            if (!str) {
                variable_unref(array);
                return NULL;
            }
            
            strncpy(str, start, len);
            str[len] = '\0';
            
            variable* item = variable_create_string(str);
            free(str);
            
            if (!item || !variable_array_add(array, item)) {
                if (item) variable_unref(item);
                variable_unref(array);
                return NULL;
            }
            
            variable_unref(item); // Array took reference
            p++; // Skip closing quote
        } else {
            // Invalid array element
            variable_unref(array);
            return NULL;
        }
        
        // Skip whitespace
        while (isspace(*p)) p++;
        
        // Check for comma or end
        if (*p == ',') {
            p++;
        } else if (*p != ']') {
            // Invalid syntax
            variable_unref(array);
            return NULL;
        }
    }
    
    if (*p != ']') {
        // Missing closing bracket
        variable_unref(array);
        return NULL;
    }
    
    return array;
}