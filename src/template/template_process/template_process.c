/**
 * @file template_process.c
 * @brief Process template string with variable interpolation
 * @author XMD Team
 */

#include "../../../include/template_internal.h"

/**
 * @brief Process template string with variable interpolation
 * @param ctx Template context
 * @param template Template string with {{variable}} syntax
 * @return Processed string (must be freed) or NULL on error
 */
char* template_process(template_context* ctx, const char* template) {
    if (ctx == NULL || template == NULL) {
        return NULL;
    }
    
    size_t template_len = strlen(template);
    size_t result_capacity = template_len * 2;
    char* result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }
    
    size_t result_len = 0;
    size_t pos = 0;
    size_t var_start, var_end;
    
    while (find_next_variable(template, pos, &var_start, &var_end)) {
        // Copy text before variable
        size_t text_len = var_start - pos;
        if (result_len + text_len >= result_capacity) {
            result_capacity = (result_len + text_len + 1) * 2;
            char* new_result = realloc(result, result_capacity);
            if (new_result == NULL) {
                free(result);
                return NULL;
            }
            result = new_result;
        }
        
        memcpy(result + result_len, template + pos, text_len);
        result_len += text_len;
        
        // Extract variable name
        char* var_name = extract_variable_name(template, var_start, var_end);
        if (var_name == NULL) {
            free(result);
            return NULL;
        }
        
        // Look up variable value
        variable* var = store_get(ctx->variable_store, var_name);
        char* var_value = NULL;
        
        if (var != NULL) {
            var_value = variable_to_string(var);
        } else {
            // Variable not found - keep original reference
            size_t ref_len = var_end - var_start;
            var_value = malloc(ref_len + 1);
            if (var_value != NULL) {
                memcpy(var_value, template + var_start, ref_len);
                var_value[ref_len] = '\0';
            }
        }
        
        // Add variable value to result
        if (var_value != NULL) {
            size_t value_len = strlen(var_value);
            if (result_len + value_len >= result_capacity) {
                result_capacity = (result_len + value_len + 1) * 2;
                char* new_result = realloc(result, result_capacity);
                if (new_result == NULL) {
                    free(result);
                    free(var_name);
                    free(var_value);
                    return NULL;
                }
                result = new_result;
            }
            
            memcpy(result + result_len, var_value, value_len);
            result_len += value_len;
            free(var_value);
        }
        
        free(var_name);
        pos = var_end;
    }
    
    // Copy remaining text
    size_t remaining_len = template_len - pos;
    if (result_len + remaining_len >= result_capacity) {
        result_capacity = result_len + remaining_len + 1;
        char* new_result = realloc(result, result_capacity);
        if (new_result == NULL) {
            free(result);
            return NULL;
        }
        result = new_result;
    }
    
    memcpy(result + result_len, template + pos, remaining_len);
    result_len += remaining_len;
    result[result_len] = '\0';
    
    return result;
}