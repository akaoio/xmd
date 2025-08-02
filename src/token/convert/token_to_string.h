/**
 * @file token_to_string.h
 * @brief Declaration for token_to_string function
 * 
 * This file contains ONLY the token_to_string declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_TO_STRING_H
#define TOKEN_TO_STRING_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
char* token_to_string(const token* t);

#endif /* TOKEN_TO_STRING_H */
