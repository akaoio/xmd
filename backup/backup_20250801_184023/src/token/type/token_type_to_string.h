/**
 * @file token_type_to_string.h
 * @brief Declaration for token_type_to_string function
 * 
 * This file contains ONLY the token_type_to_string declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_TYPE_TO_STRING_H
#define TOKEN_TYPE_TO_STRING_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
const char* token_type_to_string(token_type type);

#endif /* TOKEN_TYPE_TO_STRING_H */
