/**
 * @file template.c
 * @brief Template processing implementation
 * @author XMD Team
 *
 * Implementation of template processing system for variable interpolation
 * and expression evaluation in XMD documents.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "template.h"
#include "variable.h"
#include "store.h"

/**
 * @brief Template processing context structure
 */
struct template_context {
    store* variable_store;  /**< Variable store for lookups */
};

/**
 * @brief Create a new template context
 * @param store Variable store for lookups
 * @return New template context or NULL on failure
 */
template_context* template_context_create(store* store) {
    if (store == NULL) {
        return NULL;
    }
    
    template_context* ctx = malloc(sizeof(template_context));
    if (ctx == NULL) {
        return NULL;
    }
    
    ctx->variable_store = store;
    
    return ctx;
}

/**
 * @brief Destroy template context and free memory
 * @param ctx Template context to destroy (can be NULL)
 */
void template_context_destroy(template_context* ctx) {
    free(ctx);
}

/**
 * @brief Find next variable reference in template
 * @param template Template string
 * @param start Start position to search from
 * @param var_start Output parameter for variable start position
 * @param var_end Output parameter for variable end position
 * @return true if variable found, false otherwise
 */
static bool find_next_variable(const char* template, size_t start, 
                               size_t* var_start, size_t* var_end) {
    if (template == NULL || var_start == NULL || var_end == NULL) {
        return false;
    }
    
    size_t len = strlen(template);
    
    // Need at least 4 characters for {{}}
    if (len < 4) {
        return false;
    }
    
    // Look for opening {{
    for (size_t i = start; i < len - 1; i++) {
        if (template[i] == '{' && template[i + 1] == '{') {
            *var_start = i;
            
            // Look for closing }}
            for (size_t j = i + 2; j < len - 1; j++) {
                if (template[j] == '}' && template[j + 1] == '}') {
                    *var_end = j + 2;
                    return true;
                }
            }
            
            // Found opening but no closing - invalid
            return false;
        }
    }
    
    return false;
}

/**
 * @brief Extract variable name from reference
 * @param template Template string
 * @param start Start of variable reference (at first {)
 * @param end End of variable reference (after last })
 * @return Variable name (must be freed) or NULL on error
 */
static char* extract_variable_name(const char* template, size_t start, size_t end) {
    if (template == NULL || end <= start + 4) { // Minimum: {{x}}
        return NULL;
    }
    
    // Skip {{ and }}
    size_t name_start = start + 2;
    size_t name_end = end - 2;
    size_t name_len = name_end - name_start;
    
    char* name = malloc(name_len + 1);
    if (name == NULL) {
        return NULL;
    }
    
    // Copy name and trim whitespace
    size_t write_pos = 0;
    bool leading_space = true;
    
    for (size_t i = name_start; i < name_end; i++) {
        char c = template[i];
        if (isspace(c)) {
            if (!leading_space) {
                name[write_pos++] = ' ';
                leading_space = true;
            }
        } else {
            name[write_pos++] = c;
            leading_space = false;
        }
    }
    
    // Remove trailing space
    if (write_pos > 0 && leading_space) {
        write_pos--;
    }
    
    name[write_pos] = '\0';
    return name;
}

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

/**
 * @brief Extract variable references from template
 * @param template Template string
 * @param count Output parameter for number of references
 * @return Array of variable names (must be freed) or NULL on error
 */
char** template_extract_variables(const char* template, size_t* count) {
    if (template == NULL || count == NULL) {
        if (count) *count = 0;
        return NULL;
    }
    
    // First pass: count variables
    size_t var_count = 0;
    size_t pos = 0;
    size_t var_start, var_end;
    
    while (find_next_variable(template, pos, &var_start, &var_end)) {
        var_count++;
        pos = var_end;
    }
    
    if (var_count == 0) {
        *count = 0;
        return NULL;
    }
    
    // Allocate array
    char** variables = malloc(var_count * sizeof(char*));
    if (variables == NULL) {
        *count = 0;
        return NULL;
    }
    
    // Second pass: extract variable names
    pos = 0;
    size_t index = 0;
    
    while (find_next_variable(template, pos, &var_start, &var_end) && index < var_count) {
        char* var_name = extract_variable_name(template, var_start, var_end);
        if (var_name == NULL) {
            // Clean up on failure
            for (size_t i = 0; i < index; i++) {
                free(variables[i]);
            }
            free(variables);
            *count = 0;
            return NULL;
        }
        
        variables[index] = var_name;
        index++;
        pos = var_end;
    }
    
    *count = var_count;
    return variables;
}

/**
 * @brief Check if template string contains variable references
 * @param template Template string to check
 * @return true if contains {{variable}} syntax, false otherwise
 */
bool template_has_variables(const char* template) {
    if (template == NULL) {
        return false;
    }
    
    size_t var_start, var_end;
    return find_next_variable(template, 0, &var_start, &var_end);
}

/**
 * @brief Validate template syntax
 * @param template Template string to validate
 * @return true if syntax is valid, false otherwise
 */
bool template_validate(const char* template) {
    if (template == NULL) {
        return false;
    }
    
    size_t len = strlen(template);
    int brace_depth = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (template[i] == '{') {
            if (i + 1 < len && template[i + 1] == '{') {
                brace_depth++;
                i++; // Skip next brace
            } else {
                // Single brace - invalid
                return false;
            }
        } else if (template[i] == '}') {
            if (i + 1 < len && template[i + 1] == '}') {
                if (brace_depth == 0) {
                    // Closing without opening
                    return false;
                }
                brace_depth--;
                i++; // Skip next brace
            } else {
                // Single brace - invalid
                return false;
            }
        }
    }
    
    // All braces should be matched
    return brace_depth == 0;
}
