/**
 * @file token_to_string.c
 * @brief Token string conversion function
 * @author XMD Team
 *
 * Implementation of token to string conversion for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Convert token to string representation
 * @param t Token to convert
 * @return String representation (must be freed)
 */
char* token_to_string(const token* t) {
    if (t == NULL) {
        return NULL;
    }
    
    const char* type_str = token_type_to_string(t->type);
    const char* value_str = t->value ? t->value : "(null)";
    
    // Allocate buffer for formatted string
    size_t len = strlen(type_str) + strlen(value_str) + 50; // Extra space for formatting
    char* result = malloc(len);
    if (result == NULL) {
        return NULL;
    }
    
    snprintf(result, len, "%s: \"%s\" at %zu:%zu", 
             type_str, value_str, t->line, t->column);
    
    return result;
}
