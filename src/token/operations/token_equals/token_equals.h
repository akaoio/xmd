/**
 * @file token_equals.h
 * @brief Declaration for token_equals function
 * 
 * This file contains ONLY the token_equals declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_EQUALS_H
#define TOKEN_EQUALS_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
bool token_equals(const token* tok1, const token* tok2);

#endif /* TOKEN_EQUALS_H */
