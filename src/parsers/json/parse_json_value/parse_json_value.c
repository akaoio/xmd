/**
 * @file parse_json_value.c
 * @brief Parse JSON string value
 * 
 * This file contains ONLY the parse_json_value function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/parsers_consolidated.c (with syntax fixes)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../../include/variable.h"
/**
 * @brief Parse JSON string value
 * @param json JSON content
 * @return Variable containing parsed value or NULL
 */
static variable* parse_json_value(const char* json) {
    if (!json) return NULL;
    
    while (isspace(*json)) json++;
    
    // Simple JSON parsing (basic implementation)
    if (*json == '"') {
        // String value
        json++; // Skip opening quote
        const char* end = strchr(json, '"');
        if (!end) return NULL;
        
        size_t len = end - json;
        char* str_value = xmd_malloc(len + 1);
        if (!str_value) return NULL;
        
        strncpy(str_value, json, len);
        str_value[len] = '\0';
        
        variable* result = variable_create_string(str_value);
        XMD_FREE_SAFE(str_value);
        return result;
    } else if (isdigit(*json) || *json == '-') {
        // Number value
        double num_value = strtod(json, NULL);
        return variable_create_number(num_value);
    } else if (strncmp(json, "true", 4) == 0) {
        return variable_create_boolean(true);
    } else if (strncmp(json, "false", 5) == 0) {
        return variable_create_boolean(false);
    } else if (strncmp(json, "null", 4) == 0) {
        return variable_create_null();
    }
    
    // For complex objects/arrays, return as string for now
    return variable_create_string(json);
}
