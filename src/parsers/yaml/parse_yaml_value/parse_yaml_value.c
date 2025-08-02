/**
 * @file parse_yaml_value.c
 * @brief Parse YAML string value
 * 
 * This file contains ONLY the parse_yaml_value function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/parsers_consolidated.c (with syntax fixes)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../../../include/variable.h"
/**
 * @brief Parse YAML string value
 * @param yaml YAML content
 * @return Variable containing parsed value or NULL
 */
static variable* parse_yaml_value(const char* yaml) {
    if (!yaml) return NULL;
    
    while (isspace(*yaml)) yaml++;
    
    // Simple YAML parsing (basic implementation)
    if (*yaml == '"' || *yaml == '\'') {
        // Quoted string
        char quote = *yaml;
        yaml++; // Skip opening quote
        const char* end = strchr(yaml, quote);
        if (!end) return NULL;
        
        size_t len = end - yaml;
        char* str_value = malloc(len + 1);
        if (!str_value) return NULL;
        
        strncpy(str_value, yaml, len);
        str_value[len] = '\0';
        
        variable* result = variable_create_string(str_value);
        free(str_value);
        return result;
    } else if (isdigit(*yaml) || *yaml == '-') {
        // Number value
        double num_value = strtod(yaml, NULL);
        return variable_create_number(num_value);
    } else if (strncmp(yaml, "true", 4) == 0 || strncmp(yaml, "yes", 3) == 0) {
        return variable_create_boolean(true);
    } else if (strncmp(yaml, "false", 5) == 0 || strncmp(yaml, "no", 2) == 0) {
        return variable_create_boolean(false);
    } else if (strncmp(yaml, "null", 4) == 0 || strncmp(yaml, "~", 1) == 0) {
        return variable_create_null();
    } else {
        // Unquoted string - find end of value
        const char* end = yaml;
        while (*end && *end != '\n' && *end != '\r') end++;
        
        size_t len = end - yaml;
        char* str_value = malloc(len + 1);
        if (!str_value) return NULL;
        
        strncpy(str_value, yaml, len);
        str_value[len] = '\0';
        
        // Trim trailing whitespace
        char* trim_end = str_value + len - 1;
        while (trim_end > str_value && isspace(*trim_end)) {
            *trim_end = '\0';
            trim_end--;
        }
        
        variable* result = variable_create_string(str_value);
        free(str_value);
        return result;
    }
}
