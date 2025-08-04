/**
 * @file token_create.c
 * @brief Implementation of token_create function
 * 
 * This file contains ONLY the token_create function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/token.c
 */

#include <stddef.h>
#include <stdlib.h>
#include "../../../include/performance.h"
#include "../../../include/token.h"
#include "../../../include/utils.h"
#include "../../../include/variable.h"
#include "../../utils/common/common_macros.h"
#include "../../utils/common/validation_macros.h"
/**
 * @brief Create a new token
 * @param type Token type
 * @param value Token value (will be copied)
 * @param line Line number
 * @param column Column number
 * @return New token or NULL on failure
 */
token* token_create(token_type type, const char* value, size_t line, size_t column) {
    XMD_CREATE_VALIDATED(t, token, sizeof(token), NULL);
    
    t->type = type;
    t->line = line;
    t->column = column;
    t->next = NULL;
    
    // Copy value if provided
    if (value != NULL) {
        t->value = xmd_strdup(value);
        XMD_VALIDATE_OR_CLEANUP(t->value, XMD_FREE_SAFE(t), NULL);
    } else {
        t->value = NULL;
    }
    return t;
}
