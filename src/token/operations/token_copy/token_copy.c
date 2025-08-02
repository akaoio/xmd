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
#include "utils/common/common_macros.h"
/**
 * @brief Copy token data (shallow copy - reuses value pointer)
 * @param t Source token
 * @return New token copy or NULL on error
 */
token* token_copy(const token* t) {
    XMD_NULL_CHECK(t, NULL);
    
    token* copy = xmd_malloc(sizeof(token));
    XMD_NULL_CHECK(copy, NULL);
    
    copy->type = t->type;
    copy->line = t->line;
    copy->column = t->column;
    copy->next = NULL; // Don't copy the next pointer
    // Copy value if present
    if (t->value != NULL) {
        copy->value = xmd_strdup(t->value);
        if (copy->value == NULL) {
            XMD_FREE_SAFE(copy);
            return NULL;
        }
    } else {
        copy->value = NULL;
    }
    
    return copy;
}
