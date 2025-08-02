/**
 * @file token_list_free.h
 * @brief Declaration for token_list_free function
 * 
 * This file contains ONLY the token_list_free declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_LIST_FREE_H
#define TOKEN_LIST_FREE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
void token_list_free(token* head);

#endif /* TOKEN_LIST_FREE_H */
