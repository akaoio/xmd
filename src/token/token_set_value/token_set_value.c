/**
 * @file token_set_value.c
 * @brief Token value setter function
 * @author XMD Team
 *
 * Implementation of token value modification for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Set token value
 * @param tok Token to modify
 * @param value New value (will be copied, can be NULL)
 * @return 0 on success, non-zero on error
 */
int token_set_value(token* tok, const char* value) {
    if (tok == NULL) {
        return -1;
    }
    
    // Free existing value
    free(tok->value);
    tok->value = NULL;
    
    // Copy new value if provided
    if (value != NULL) {
        size_t len = strlen(value);
        tok->value = malloc(len + 1);
        if (tok->value == NULL) {
            return -1;
        }
        strcpy(tok->value, value);
    }
    
    return 0;
}
