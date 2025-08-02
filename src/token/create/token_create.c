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
#include "performance.h"
#include "token.h"
#include "utils.h"
#include "variable.h"
/**
 * @brief Create a new token
 * @param type Token type
 * @param value Token value (will be copied)
 * @param line Line number
 * @param column Column number
 * @return New token or NULL on failure
 */
token* token_create(token_type type, const char* value, size_t line, size_t column) {
    token* t = xmd_malloc(sizeof(token));
    if (t == NULL) {
        return NULL;
    }
    
    t->type = type;
    t->line = line;
    t->column = column;
    t->next = NULL;
    // Copy value if provided
    if (value != NULL) {
        t->value = xmd_strdup(value);
        if (t->value == NULL) {
            xmd_free(t);
            return NULL;
        }
    } else {
        t->value = NULL;
    }
    return t;
}
