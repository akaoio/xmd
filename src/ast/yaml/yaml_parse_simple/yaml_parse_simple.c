/**
 * @file yaml_parse_simple.c
 * @brief Parse YAML string to XMD variable (Genesis principle: 1 function per file)
 * 
 * This file contains a single function that parses YAML strings into XMD variables.
 * Part of the YAML processing module for XMD.
 * 
 * Note: This is a simplified parser for basic YAML
 * Full YAML support would require libyaml
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../../../include/ast.h"
#include "../../../../include/store.h"
#include "../../../../include/variable.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Parse YAML string to XMD variable
 * @param yaml YAML string to parse
 * @return Parsed variable or NULL
 * 
 * Note: This is a simplified parser for basic YAML
 * Full YAML support would require libyaml
 */
variable* yaml_parse_simple(const char* yaml) {
    XMD_VALIDATE_PTRS(variable_create_null(), yaml);
    
    // Skip whitespace
    while (*yaml && (*yaml == ' ' || *yaml == '\t' || *yaml == '\n')) {
        yaml++;
    }
    
    // Check for special values
    if (strncmp(yaml, "null", 4) == 0) {
        return variable_create_null();
    }
    if (strncmp(yaml, "true", 4) == 0) {
        return variable_create_boolean(true);
    }
    if (strncmp(yaml, "false", 5) == 0) {
        return variable_create_boolean(false);
    }
    
    // Check for array
    if (*yaml == '-') {
        variable* arr = variable_create_array();
        
        // Parse array items
        while (*yaml == '-') {
            yaml++; // Skip '-'
            while (*yaml == ' ') yaml++; // Skip spaces
            
            // Find end of line
            const char* line_end = strchr(yaml, '\n');
            if (!line_end) {
                line_end = yaml + strlen(yaml);
            }
            
            // Extract item value
            size_t len = line_end - yaml;
            char* item_str = xmd_malloc(len + 1);
            strncpy(item_str, yaml, len);
            item_str[len] = '\0';
            
            // Parse item (simplified - just strings for now)
            variable* item = variable_create_string(item_str);
            variable_array_add(arr, item);
            XMD_FREE_SAFE(item_str);
            
            // Move to next line
            yaml = line_end;
            if (*yaml == '\n') yaml++;
            while (*yaml && (*yaml == ' ' || *yaml == '\t')) {
                yaml++;
            }
        }
        
        return arr;
    }
    
    // Check for object
    if (strchr(yaml, ':')) {
        variable* obj = variable_create_object();
        
        // Parse key-value pairs
        while (*yaml && *yaml != '\0') {
            // Skip whitespace
            while (*yaml && (*yaml == ' ' || *yaml == '\t' || *yaml == '\n')) {
                yaml++;
            }
            if (!*yaml) break;
            
            // Find colon
            const char* colon = strchr(yaml, ':');
            if (!colon) break;
            
            // Extract key
            size_t key_len = colon - yaml;
            char* key = xmd_malloc(key_len + 1);
            strncpy(key, yaml, key_len);
            key[key_len] = '\0';
            
            // Skip colon and spaces
            yaml = colon + 1;
            while (*yaml == ' ') yaml++;
            
            // Find end of value (newline or end)
            const char* line_end = strchr(yaml, '\n');
            if (!line_end) {
                line_end = yaml + strlen(yaml);
            }
            
            // Extract value
            size_t val_len = line_end - yaml;
            char* val_str = xmd_malloc(val_len + 1);
            strncpy(val_str, yaml, val_len);
            val_str[val_len] = '\0';
            
            // Create value (simplified - just strings for now)
            variable* val = variable_create_string(val_str);
            variable_object_set(obj, key, val);
            
            XMD_FREE_SAFE(key);
            XMD_FREE_SAFE(val_str);
            
            // Move to next line
            yaml = line_end;
        }
        
        return obj;
    }
    
    // Check for number
    char* endptr;
    double num = strtod(yaml, &endptr);
    if (endptr != yaml && (*endptr == '\0' || *endptr == '\n')) {
        return variable_create_number(num);
    }
    
    // Default to string
    const char* end = strchr(yaml, '\n');
    if (!end) {
        end = yaml + strlen(yaml);
    }
    size_t len = end - yaml;
    char* str = xmd_malloc(len + 1);
    strncpy(str, yaml, len);
    str[len] = '\0';
    
    // Remove quotes if present
    if (str[0] == '"' && str[len-1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
    
    variable* result = variable_create_string(str);
    XMD_FREE_SAFE(str);
    return result;
}
