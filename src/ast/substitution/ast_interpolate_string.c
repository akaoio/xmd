/**
 * @file ast_interpolate_string.c
 * @brief Interpolate variables in string (${var} syntax)
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../../include/ast_evaluator.h"
#include "../../../include/store.h"
#include "../../../include/variable.h"
#include "../../../include/utils.h"
#include "../../utils/common/common_macros.h"

// Debug: This file was compiled and loaded
// TEMP: Disabled constructor for debugging
// __attribute__((constructor))
// void debug_interpolate_loaded() {
// }

/**
 * @brief Interpolate variables in a string containing ${var} patterns
 * @param str String with potential variable interpolations
 * @param evaluator Evaluator context with variables store
 * @return New string with variables substituted (must be freed)
 */
char* ast_interpolate_string(const char* str, ast_evaluator* evaluator) {
    fflush(stdout);
    fflush(stdout);
    
    // Early return test
    if (!str) {
        fflush(stdout);
        return xmd_strdup("");
    }
    if (!evaluator) {
        fflush(stdout);
        return xmd_strdup(str);
    }
    if (!evaluator->variables) {
        fflush(stdout);
        return xmd_strdup(str);
    }
    
    fflush(stdout);
    
    // First pass: calculate total size needed
    size_t total_size = 0;
    const char* pos = str;
    
    while (*pos) {
        if (pos[0] == '$' && pos[1] == '{') {
            // Find closing }
            const char* var_start = pos + 2;
            const char* var_end = strchr(var_start, '}');
            
            if (var_end) {
                // Extract variable name
                size_t var_len = var_end - var_start;
                char* var_name = xmd_malloc(var_len + 1);
                if (!var_name) {
                    return xmd_strdup(str);
                }
                strncpy(var_name, var_start, var_len);
                var_name[var_len] = '\0';
                
                // Look up variable
                variable* var = store_get(evaluator->variables, var_name);
                if (var) {
                    char* var_value = variable_to_string(var);
                    if (var_value) {
                        total_size += strlen(var_value);
                        XMD_FREE_SAFE(var_value);
                    }
                } else {
                    // Keep original ${var} if not found
                    total_size += var_len + 3; // ${}
                }
                
                XMD_FREE_SAFE(var_name);
                pos = var_end + 1;
            } else {
                // No closing }, treat as regular text
                total_size++;
                pos++;
            }
        } else {
            total_size++;
            pos++;
        }
    }
    
    // Allocate result buffer
    char* result = xmd_malloc(total_size + 1);
    if (!result) {
        return xmd_strdup(str);
    }
    
    // Second pass: perform substitution
    pos = str;
    char* out = result;
    
    while (*pos) {
        if (pos[0] == '$' && pos[1] == '{') {
            // Find closing }
            const char* var_start = pos + 2;
            const char* var_end = strchr(var_start, '}');
            
            if (var_end) {
                // Extract variable name
                size_t var_len = var_end - var_start;
                char* var_name = xmd_malloc(var_len + 1);
                if (!var_name) {
                    XMD_FREE_SAFE(result);
                    return xmd_strdup(str);
                }
                strncpy(var_name, var_start, var_len);
                var_name[var_len] = '\0';
                
                // Look up variable
                variable* var = store_get(evaluator->variables, var_name);
                if (var) {
                    char* var_value = variable_to_string(var);
                    if (var_value) {
                        strcpy(out, var_value);
                        out += strlen(var_value);
                        XMD_FREE_SAFE(var_value);
                    }
                } else {
                    // Keep original ${var} if not found
                    sprintf(out, "${%s}", var_name);
                    out += var_len + 3;
                }
                
                XMD_FREE_SAFE(var_name);
                pos = var_end + 1;
            } else {
                // No closing }, treat as regular text
                *out++ = *pos++;
            }
        } else {
            *out++ = *pos++;
        }
    }
    
    *out = '\0';
    return result;
}
