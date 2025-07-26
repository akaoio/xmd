/**
 * @file template_extract.c
 * @brief Template variable extraction
 * @author XMD Team
 *
 * Implementation of variable extraction functions for templates.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "template.h"

/**
 * @brief Extract variable references from template
 * @param template Template string
 * @param count Output parameter for number of references
 * @return Array of variable names (must be freed) or NULL on error
 */
char** template_extract_variables(const char* template, size_t* count) {
    if (template == NULL || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }
    
    *count = 0;
    
    // First pass: count variables
    const char* pos = template;
    size_t var_count = 0;
    
    while (*pos) {
        const char* var_start = strstr(pos, "{{");
        if (var_start == NULL) {
            break;
        }
        
        const char* var_end = strstr(var_start + 2, "}}");
        if (var_end == NULL) {
            break;
        }
        
        var_count++;
        pos = var_end + 2;
    }
    
    if (var_count == 0) {
        return NULL;
    }
    
    // Allocate array for variable names
    char** variables = malloc(var_count * sizeof(char*));
    if (variables == NULL) {
        return NULL;
    }
    
    // Second pass: extract variable names
    pos = template;
    size_t var_index = 0;
    
    while (*pos && var_index < var_count) {
        const char* var_start = strstr(pos, "{{");
        if (var_start == NULL) {
            break;
        }
        
        const char* name_start = var_start + 2;
        const char* var_end = strstr(name_start, "}}");
        if (var_end == NULL) {
            break;
        }
        
        // Extract variable name
        size_t name_len = var_end - name_start;
        char* name = malloc(name_len + 1);
        if (name == NULL) {
            // Free already allocated names
            for (size_t i = 0; i < var_index; i++) {
                free(variables[i]);
            }
            free(variables);
            *count = 0;
            return NULL;
        }
        
        strncpy(name, name_start, name_len);
        name[name_len] = '\0';
        
        // Trim whitespace
        char* trimmed_start = name;
        while (*trimmed_start == ' ' || *trimmed_start == '\t') {
            trimmed_start++;
        }
        
        char* trimmed_end = name + name_len - 1;
        while (trimmed_end > trimmed_start && (*trimmed_end == ' ' || *trimmed_end == '\t')) {
            trimmed_end--;
        }
        trimmed_end[1] = '\0';
        
        // Move trimmed content to start of buffer
        if (trimmed_start != name) {
            memmove(name, trimmed_start, trimmed_end - trimmed_start + 2);
        }
        
        variables[var_index] = name;
        var_index++;
        
        pos = var_end + 2;
    }
    
    *count = var_count;
    return variables;
}
