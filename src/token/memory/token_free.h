/**
 * @file token_free.h
 * @brief Declaration for token_free function
 * 
 * This file contains ONLY the token_free declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_FREE_H
#define TOKEN_FREE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
void token_free(token* tok);

#endif /* TOKEN_FREE_H */
