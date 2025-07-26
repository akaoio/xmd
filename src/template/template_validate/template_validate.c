/**
 * @file template_validate.c
 * @brief Validate template syntax
 * @author XMD Team
 */

#include "../../../include/template_internal.h"

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