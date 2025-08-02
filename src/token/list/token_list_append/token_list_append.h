/**
 * @file token_list_append.h
 * @brief Declaration for token_list_append function
 * 
 * This file contains ONLY the token_list_append declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_LIST_APPEND_H
#define TOKEN_LIST_APPEND_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
token* token_list_append(token* head, token* t);

#endif /* TOKEN_LIST_APPEND_H */
