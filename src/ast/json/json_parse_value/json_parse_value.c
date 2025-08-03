/**
 * @file json_parse_value.c
 * @brief Parse JSON value to XMD variable
 * 
 * Genesis principle: One function per file
 * This file contains only the json_parse_value function
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

// Forward declarations for other JSON parse functions
extern variable* json_parse_object(const char* json, size_t* pos);
extern variable* json_parse_array(const char* json, size_t* pos);

/**
 * @brief Parse JSON value to XMD variable (simplified)
 * @param json JSON string to parse
 * @param pos Current position in string
 * @return Parsed variable or NULL
 */
variable* json_parse_value(const char* json, size_t* pos) {
    // Skip whitespace
    while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                         json[*pos] == '\n' || json[*pos] == '\r')) {
        (*pos)++;
    }
    
    XMD_NULL_CHECK(json[*pos]);
    
    // Object
    if (json[*pos] == '{') {
        return json_parse_object(json, pos);
    }
    
    // Array
    if (json[*pos] == '[') {
        return json_parse_array(json, pos);
    }
    
    // String
    if (json[*pos] == '"') {
        (*pos)++; // Skip opening quote
        size_t str_start = *pos;
        while (json[*pos] && json[*pos] != '"') {
            if (json[*pos] == '\\') (*pos)++; // Skip escaped char
            (*pos)++;
        }
        
        XMD_NULL_CHECK(json[*pos]);
        
        size_t str_len = *pos - str_start;
        char* str = xmd_malloc(str_len + 1);
        strncpy(str, json + str_start, str_len);
        str[str_len] = '\0';
        
        (*pos)++; // Skip closing quote
        
        variable* result = variable_create_string(str);
        XMD_FREE_SAFE(str);
        return result;
    }
    
    // null
    if (strncmp(json + *pos, "null", 4) == 0) {
        *pos += 4;
        return variable_create_null();
    }
    
    // true
    if (strncmp(json + *pos, "true", 4) == 0) {
        *pos += 4;
        return variable_create_boolean(true);
    }
    
    // false
    if (strncmp(json + *pos, "false", 5) == 0) {
        *pos += 5;
        return variable_create_boolean(false);
    }
    
    // Number
    if (json[*pos] == '-' || (json[*pos] >= '0' && json[*pos] <= '9')) {
        size_t num_start = *pos;
        if (json[*pos] == '-') (*pos)++;
        
        while (json[*pos] >= '0' && json[*pos] <= '9') (*pos)++;
        
        if (json[*pos] == '.') {
            (*pos)++;
            while (json[*pos] >= '0' && json[*pos] <= '9') (*pos)++;
        }
        
        if (json[*pos] == 'e' || json[*pos] == 'E') {
            (*pos)++;
            if (json[*pos] == '+' || json[*pos] == '-') (*pos)++;
            while (json[*pos] >= '0' && json[*pos] <= '9') (*pos)++;
        }
        
        size_t num_len = *pos - num_start;
        char* num_str = xmd_malloc(num_len + 1);
        strncpy(num_str, json + num_start, num_len);
        num_str[num_len] = '\0';
        
        double num = atof(num_str);
        XMD_FREE_SAFE(num_str);
        
        return variable_create_number(num);
    }
    
    return NULL;
}
