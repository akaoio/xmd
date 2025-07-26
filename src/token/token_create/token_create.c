/**
 * @file token_create.c
 * @brief Token creation function
 * @author XMD Team
 *
 * Implementation of token creation for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Create a new token
 * @param type Token type
 * @param value Token value (will be copied)
 * @param line Line number
 * @param column Column number
 * @return New token or NULL on failure
 */
token* token_create(token_type type, const char* value, size_t line, size_t column) {
    token* t = malloc(sizeof(token));
    if (t == NULL) {
        return NULL;
    }
    
    t->type = type;
    t->line = line;
    t->column = column;
    t->next = NULL;
    
    // Copy value if provided
    if (value != NULL) {
        size_t len = strlen(value);
        t->value = malloc(len + 1);
        if (t->value == NULL) {
            free(t);
            return NULL;
        }
        strcpy(t->value, value);
    } else {
        t->value = NULL;
    }
    
    return t;
}
