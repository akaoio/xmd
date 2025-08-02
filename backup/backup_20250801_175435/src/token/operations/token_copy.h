/**
 * @file token_copy.h
 * @brief Declaration for token_copy function
 * 
 * This file contains ONLY the token_copy declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_COPY_H
#define TOKEN_COPY_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
token* token_copy(const token* t);

#endif /* TOKEN_COPY_H */
