/**
 * @file template_extract_variables.c
 * @brief Extract variable references from template
 * @author XMD Team
 */

#include "../../../include/template_internal.h"

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