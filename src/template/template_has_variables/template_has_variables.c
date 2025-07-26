/**
 * @file template_has_variables.c
 * @brief Check if template string contains variable references
 * @author XMD Team
 */

#include "../../../include/template_internal.h"

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