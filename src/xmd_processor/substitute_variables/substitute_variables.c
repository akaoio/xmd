/**
 * @file substitute_variables.c
 * @brief Substitute variables in text implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Substitute {{variable}} patterns in text
 * @param text Input text containing {{variable}} patterns
 * @param variables Variable store for variable lookups
 * @return New string with variables substituted (caller must free) or NULL on error
 */
char* substitute_variables(const char* text, store* variables) {
    if (!text) return NULL;
    
    size_t text_len = strlen(text);
    size_t output_capacity = text_len * 2;
    char* output = malloc(output_capacity);
    size_t output_pos = 0;
    
    const char* ptr = text;
    while (*ptr) {
        if (ptr[0] == '{' && ptr[1] == '{') {
            const char* close = strstr(ptr + 2, "}}");
            if (close) {
                size_t var_len = close - ptr - 2;
                char* var_name = malloc(var_len + 1);
                strncpy(var_name, ptr + 2, var_len);
                var_name[var_len] = '\0';
                
                variable* var = store_get(variables, trim_whitespace(var_name));
                char* var_value = var ? variable_to_string(var) : strdup("");
                size_t value_len = strlen(var_value);
                
                if (output_pos + value_len >= output_capacity) {
                    output_capacity = (output_pos + value_len + 1000) * 2;
                    output = realloc(output, output_capacity);
                }
                
                memcpy(output + output_pos, var_value, value_len);
                output_pos += value_len;
                free(var_value);
                
                free(var_name);
                ptr = close + 2;
                continue;
            }
        }
        
        if (output_pos >= output_capacity - 1) {
            output_capacity *= 2;
            output = realloc(output, output_capacity);
        }
        
        output[output_pos++] = *ptr++;
    }
    
    output[output_pos] = '\0';
    return output;
}
