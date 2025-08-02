/**
 * @file token_list_get.h
 * @brief Declaration for token_list_get function
 * 
 * This file contains ONLY the token_list_get declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_LIST_GET_H
#define TOKEN_LIST_GET_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
token* token_list_get(token* head, size_t index);

#endif /* TOKEN_LIST_GET_H */
