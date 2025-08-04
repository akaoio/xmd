/**
 * @file yaml_stringify_variable.c
 * @brief Convert XMD variable to YAML string (Genesis principle: 1 function per file)
 * 
 * This file contains a single function that converts XMD variables to YAML format.
 * Part of the YAML processing module for XMD.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "store.h"
#include "variable.h"
#include "utils.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Convert XMD variable to YAML string
 * @param var Variable to stringify
 * @param indent Current indentation level
 * @return YAML string (must be freed)
 */
char* yaml_stringify_variable(variable* var, int indent) {
    XMD_VALIDATE_PTRS(xmd_strdup("null"), var);
    
    variable_type type = variable_get_type(var);
    char* result = NULL;
    char indent_str[64] = {0};
    
    // Create indentation string
    for (int i = 0; i < indent * 2; i++) {
        indent_str[i] = ' ';
    }
    
    switch (type) {
        case VAR_STRING: {
            const char* str = variable_get_string(var);
            // Quote strings that contain special characters
            if (str && (strchr(str, ':') || strchr(str, '\n') || 
                       strchr(str, '"') || strchr(str, '\''))) {
                size_t len = strlen(str) + 3;
                result = xmd_malloc(len);
                snprintf(result, len, "\"%s\"", str);
            } else {
                result = xmd_strdup(str ? str : "");
            }
            break;
        }
        
        case VAR_NUMBER: {
            result = xmd_malloc(32);
            snprintf(result, 32, "%g", variable_get_number(var));
            break;
        }
        
        case VAR_BOOLEAN: {
            result = xmd_strdup(variable_get_boolean(var) ? "true" : "false");
            break;
        }
        
        case VAR_ARRAY: {
            size_t count = variable_array_size(var);
            if (count == 0) {
                result = xmd_strdup("[]");
            } else {
                size_t total_size = 256;
                result = xmd_malloc(total_size);
                size_t result_capacity = total_size;
                size_t pos = 0;
                
                for (size_t i = 0; i < count; i++) {
                    variable* elem = variable_array_get(var, i);
                    if (elem) {
                        // Add newline and indent
                        pos += snprintf(result + pos, total_size - pos, 
                                       "\n%s- ", indent_str);
                        
                        // Add element value
                        char* elem_str = yaml_stringify_variable(elem, indent + 1);
                        if (elem_str) {
                            // Expand buffer if needed
                            size_t elem_len = strlen(elem_str);
                            XMD_BUFFER_ENSURE_CAPACITY(result, pos, elem_len, NULL);
                            strcpy(result + pos, elem_str);
                            pos += elem_len;
                            XMD_FREE_SAFE(elem_str);
                        }
                    }
                }
            }
            break;
        }
        
        case VAR_OBJECT: {
            size_t count = variable_object_size(var);
            if (count == 0) {
                result = xmd_strdup("{}");
            } else {
                size_t total_size = 256;
                result = xmd_malloc(total_size);
                size_t result_capacity = total_size;
                size_t pos = 0;
                
                size_t key_count = 0;
                char** keys = variable_object_keys(var, &key_count);
                if (keys) {
                    for (size_t i = 0; i < count; i++) {
                        if (keys[i]) {
                            variable* val = variable_object_get(var, keys[i]);
                            if (val) {
                                // Add newline, indent and key
                                pos += snprintf(result + pos, total_size - pos,
                                               "\n%s%s: ", indent_str, keys[i]);
                                
                                // Add value
                                char* val_str = yaml_stringify_variable(val, indent + 1);
                                if (val_str) {
                                    size_t val_len = strlen(val_str);
                                    XMD_BUFFER_ENSURE_CAPACITY(result, pos, val_len, NULL);
                                    strcpy(result + pos, val_str);
                                    pos += val_len;
                                    XMD_FREE_SAFE(val_str);
                                }
                            }
                            XMD_FREE_SAFE(keys[i]);
                        }
                    }
                    XMD_FREE_SAFE(keys);
                }
            }
            break;
        }
        
        default:
            result = xmd_strdup("null");
            break;
    }
    
    return result;
}
