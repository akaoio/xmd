/**
 * @file token_create.h
 * @brief Declaration for token_create function
 * 
 * This file contains ONLY the token_create declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_CREATE_H
#define TOKEN_CREATE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
token* token_create(token_type type, const char* value, size_t line, size_t column);

#endif /* TOKEN_CREATE_H */
