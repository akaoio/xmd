/**
 * @file json_stringify_variable.c
 * @brief Convert XMD variable to JSON string
 * 
 * Genesis principle: One function per file
 * This file contains only the json_stringify_variable function
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

// Forward declaration for json_escape_string
extern char* json_escape_string(const char* str);

/**
 * @brief Convert XMD variable to JSON string
 * @param var Variable to stringify
 * @param pretty Whether to pretty-print
 * @param indent Current indentation level
 * @return JSON string (must be freed)
 */
char* json_stringify_variable(variable* var, bool pretty, int indent) {
    if (!var) {
        return xmd_strdup("null");
    }
    
    variable_type type = variable_get_type(var);
    char* result = NULL;
    
    switch (type) {
        case VAR_STRING: {
            const char* str = variable_get_string(var);
            result = json_escape_string(str);
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
                strcpy(result, "[");
                size_t pos = 1;
                
                for (size_t i = 0; i < count; i++) {
                    if (i > 0) {
                        // Add comma
                        if (pos + 1 >= total_size) {
                            total_size *= 2;
                            result = xmd_realloc(result, total_size);
                        }
                        result[pos++] = ',';
                    }
                    
                    if (pretty) {
                        // Add newline and indent
                        if (pos + indent * 2 + 3 >= total_size) {
                            total_size *= 2;
                            result = xmd_realloc(result, total_size);
                        }
                        result[pos++] = '\n';
                        for (int j = 0; j <= indent; j++) {
                            result[pos++] = ' ';
                            result[pos++] = ' ';
                        }
                    }
                    
                    variable* elem = variable_array_get(var, i);
                    if (elem) {
                        char* elem_str = json_stringify_variable(elem, pretty, indent + 1);
                        if (elem_str) {
                            size_t elem_len = strlen(elem_str);
                            if (pos + elem_len >= total_size) {
                                total_size = pos + elem_len + 100;
                                result = xmd_realloc(result, total_size);
                            }
                            strcpy(result + pos, elem_str);
                            pos += elem_len;
                            XMD_FREE_SAFE(elem_str);
                        }
                    }
                }
                
                if (pretty && count > 0) {
                    // Add newline and closing indent
                    if (pos + indent * 2 + 3 >= total_size) {
                        total_size *= 2;
                        result = xmd_realloc(result, total_size);
                    }
                    result[pos++] = '\n';
                    for (int j = 0; j < indent; j++) {
                        result[pos++] = ' ';
                        result[pos++] = ' ';
                    }
                }
                
                result[pos++] = ']';
                result[pos] = '\0';
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
                strcpy(result, "{");
                size_t pos = 1;
                
                size_t key_count = 0;
                char** keys = variable_object_keys(var, &key_count);
                if (keys) {
                    for (size_t i = 0; i < count; i++) {
                        if (keys[i]) {
                            if (i > 0) {
                                // Add comma
                                if (pos + 1 >= total_size) {
                                    total_size *= 2;
                                    result = xmd_realloc(result, total_size);
                                }
                                result[pos++] = ',';
                            }
                            
                            if (pretty) {
                                // Add newline and indent
                                if (pos + indent * 2 + 3 >= total_size) {
                                    total_size *= 2;
                                    result = xmd_realloc(result, total_size);
                                }
                                result[pos++] = '\n';
                                for (int j = 0; j <= indent; j++) {
                                    result[pos++] = ' ';
                                    result[pos++] = ' ';
                                }
                            }
                            
                            // Add key
                            char* key_str = json_escape_string(keys[i]);
                            size_t key_len = strlen(key_str);
                            if (pos + key_len + 2 >= total_size) {
                                total_size = pos + key_len + 100;
                                result = xmd_realloc(result, total_size);
                            }
                            strcpy(result + pos, key_str);
                            pos += key_len;
                            XMD_FREE_SAFE(key_str);
                            
                            result[pos++] = ':';
                            if (pretty) {
                                result[pos++] = ' ';
                            }
                            
                            // Add value
                            variable* val = variable_object_get(var, keys[i]);
                            if (val) {
                                char* val_str = json_stringify_variable(val, pretty, indent + 1);
                                if (val_str) {
                                    size_t val_len = strlen(val_str);
                                    if (pos + val_len >= total_size) {
                                        total_size = pos + val_len + 100;
                                        result = xmd_realloc(result, total_size);
                                    }
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
                
                if (pretty && count > 0) {
                    // Add newline and closing indent
                    if (pos + indent * 2 + 3 >= total_size) {
                        total_size *= 2;
                        result = xmd_realloc(result, total_size);
                    }
                    result[pos++] = '\n';
                    for (int j = 0; j < indent; j++) {
                        result[pos++] = ' ';
                        result[pos++] = ' ';
                    }
                }
                
                result[pos++] = '}';
                result[pos] = '\0';
            }
            break;
        }
        
        default:
            result = xmd_strdup("null");
            break;
    }
    
    return result;
}
