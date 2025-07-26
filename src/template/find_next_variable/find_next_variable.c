/**
 * @file find_next_variable.c
 * @brief Find next variable reference in template
 * @author XMD Team
 */

#include "../../../include/template_internal.h"

/**
 * @brief Find next variable reference in template
 * @param template Template string
 * @param start Start position to search from
 * @param var_start Output parameter for variable start position
 * @param var_end Output parameter for variable end position
 * @return true if variable found, false otherwise
 */
bool find_next_variable(const char* template, size_t start, 
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