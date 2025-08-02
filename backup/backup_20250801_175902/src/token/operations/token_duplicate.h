/**
 * @file token_duplicate.h
 * @brief Declaration for token_duplicate function
 * 
 * This file contains ONLY the token_duplicate declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_DUPLICATE_H
#define TOKEN_DUPLICATE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
token* token_duplicate(const token* tok);

#endif /* TOKEN_DUPLICATE_H */
