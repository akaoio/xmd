/**
 * @file token_copy.c
 * @brief Implementation of token_copy function
 * 
 * This file contains ONLY the token_copy function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/token.c
 */

#include <stdlib.h>
#include "performance.h"
#include "token.h"
#include "utils.h"
#include "variable.h"
/**
 * @brief Copy token data (shallow copy - reuses value pointer)
 * @param t Source token
 * @return New token copy or NULL on error
 */
token* token_copy(const token* t) {
    if (t == NULL) {
        return NULL;
    }
    
    token* copy = xmd_malloc(sizeof(token));
    if (copy == NULL) {
        return NULL;
    }
    
    copy->type = t->type;
    copy->line = t->line;
    copy->column = t->column;
    copy->next = NULL; // Don't copy the next pointer
    // Copy value if present
    if (t->value != NULL) {
        copy->value = xmd_strdup(t->value);
        if (copy->value == NULL) {
            free(copy);
            return NULL;
        }
    } else {
        copy->value = NULL;
    }
    
    return copy;
}
