/**
 * @file json_parse_array.c
 * @brief Parse JSON array to XMD variable
 * 
 * Genesis principle: One function per file
 * This file contains only the json_parse_array function
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "store.h"
#include "variable.h"
#include "utils.h"
#include "../../../../utils/common/common_macros.h"

// Forward declaration for json_parse_value
extern variable* json_parse_value(const char* json, size_t* pos);

/**
 * @brief Parse JSON array to XMD variable
 * @param json JSON string to parse
 * @param pos Current position in string
 * @return Parsed variable or NULL
 */
variable* json_parse_array(const char* json, size_t* pos) {
    XMD_VALIDATE_PTRS(NULL, json, pos);
    variable* arr = variable_create_array();
    (*pos)++; // Skip '['
    
    // Skip whitespace
    while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                         json[*pos] == '\n' || json[*pos] == '\r')) {
        (*pos)++;
    }
    
    if (json[*pos] == ']') {
        (*pos)++; // Empty array
        return arr;
    }
    
    while (json[*pos]) {
        // Parse value
        variable* val = json_parse_value(json, pos);
        if (!val) {
            variable_unref(arr);
            return NULL;
        }
        
        variable_array_add(arr, val);
        variable_unref(val);
        
        // Skip whitespace
        while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                             json[*pos] == '\n' || json[*pos] == '\r')) {
            (*pos)++;
        }
        
        if (json[*pos] == ']') {
            (*pos)++;
            break;
        }
        
        if (json[*pos] == ',') {
            (*pos)++;
        } else {
            // Error: expected comma or closing bracket
            variable_unref(arr);
            return NULL;
        }
    }
    
    return arr;
}
