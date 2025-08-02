/**
 * @file token_list_destroy.h
 * @brief Declaration for token_list_destroy function
 * 
 * This file contains ONLY the token_list_destroy declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_LIST_DESTROY_H
#define TOKEN_LIST_DESTROY_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
void token_list_destroy(token* head);

#endif /* TOKEN_LIST_DESTROY_H */
