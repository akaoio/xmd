/**
 * @file json_parse_object.c
 * @brief Parse JSON object to XMD variable
 * 
 * Genesis principle: One function per file
 * This file contains only the json_parse_object function
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

// Forward declaration for json_parse_value
extern variable* json_parse_value(const char* json, size_t* pos);

/**
 * @brief Parse JSON object to XMD variable
 * @param json JSON string to parse
 * @param pos Current position in string
 * @return Parsed variable or NULL
 */
variable* json_parse_object(const char* json, size_t* pos) {
    XMD_VALIDATE_PTRS(NULL, json, pos);
    variable* obj = variable_create_object();
    (*pos)++; // Skip '{'
    
    // Skip whitespace
    while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                         json[*pos] == '\n' || json[*pos] == '\r')) {
        (*pos)++;
    }
    
    if (json[*pos] == '}') {
        (*pos)++; // Empty object
        return obj;
    }
    
    while (json[*pos]) {
        // Skip whitespace
        while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                             json[*pos] == '\n' || json[*pos] == '\r')) {
            (*pos)++;
        }
        
        // Parse key (must be string)
        if (json[*pos] != '"') {
            variable_unref(obj);
            return NULL;
        }
        
        (*pos)++; // Skip opening quote
        size_t key_start = *pos;
        while (json[*pos] && json[*pos] != '"') {
            if (json[*pos] == '\\') (*pos)++; // Skip escaped char
            (*pos)++;
        }
        
        if (!json[*pos]) {
            variable_unref(obj);
            return NULL;
        }
        
        size_t key_len = *pos - key_start;
        char* key = xmd_malloc(key_len + 1);
        strncpy(key, json + key_start, key_len);
        key[key_len] = '\0';
        
        (*pos)++; // Skip closing quote
        
        // Skip whitespace and colon
        while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                             json[*pos] == '\n' || json[*pos] == '\r')) {
            (*pos)++;
        }
        
        if (json[*pos] != ':') {
            XMD_FREE_SAFE(key);
            variable_unref(obj);
            return NULL;
        }
        (*pos)++; // Skip colon
        
        // Parse value
        variable* val = json_parse_value(json, pos);
        if (!val) {
            XMD_FREE_SAFE(key);
            variable_unref(obj);
            return NULL;
        }
        
        variable_object_set(obj, key, val);
        variable_unref(val);
        XMD_FREE_SAFE(key);
        
        // Skip whitespace
        while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                             json[*pos] == '\n' || json[*pos] == '\r')) {
            (*pos)++;
        }
        
        if (json[*pos] == '}') {
            (*pos)++;
            break;
        }
        
        if (json[*pos] == ',') {
            (*pos)++;
        } else {
            // Error: expected comma or closing brace
            variable_unref(obj);
            return NULL;
        }
    }
    
    return obj;
}
