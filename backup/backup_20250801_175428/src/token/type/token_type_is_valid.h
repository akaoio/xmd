/**
 * @file token_type_is_valid.h
 * @brief Declaration for token_type_is_valid function
 * 
 * This file contains ONLY the token_type_is_valid declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_TYPE_IS_VALID_H
#define TOKEN_TYPE_IS_VALID_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
bool token_type_is_valid(token_type type);

#endif /* TOKEN_TYPE_IS_VALID_H */
