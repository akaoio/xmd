/**
 * @file extract_variable_name.c
 * @brief Extract variable name from reference
 * @author XMD Team
 */

#include "../../../include/template_internal.h"

/**
 * @brief Extract variable name from reference
 * @param template Template string
 * @param start Start of variable reference (at first {)
 * @param end End of variable reference (after last })
 * @return Variable name (must be freed) or NULL on error
 */
char* extract_variable_name(const char* template, size_t start, size_t end) {
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