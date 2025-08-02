/**
 * @file token_set_value.c
 * @brief Implementation of token_set_value function
 * 
 * This file contains ONLY the token_set_value function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/token.c
 */

#include <stdlib.h>

#include "performance.h"
#include "token.h"
#include "utils.h"

/**
 * @brief Set token value
 * @param tok Token to modify
 * @param value New value (will be copied)
 * @return 0 on success, -1 on error
 */

/**
 * @brief Set token value
 * @param tok Token to modify
 * @param value New value (will be copied)
 * @return 0 on success, -1 on error
 */
int token_set_value(token* tok, const char* value) {
    if (tok == NULL) {
        return -1;
    }
    
    // Free existing value
    if (tok->value != NULL) {
        free(tok->value);
        tok->value = NULL;
    }
    
    // Copy new value if provided
    if (value != NULL) {
        tok->value = xmd_strdup(value);
        if (tok->value == NULL) {
            return -1;
        }
    }
    
    return 0;
}