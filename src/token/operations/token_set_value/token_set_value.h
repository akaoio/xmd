/**
 * @file token_set_value.h
 * @brief Declaration for token_set_value function
 * 
 * This file contains ONLY the token_set_value declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_SET_VALUE_H
#define TOKEN_SET_VALUE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
int token_set_value(token* tok, const char* value);

#endif /* TOKEN_SET_VALUE_H */
