/**
 * @file token_list_reverse.h
 * @brief Declaration for token_list_reverse function
 * 
 * This file contains ONLY the token_list_reverse declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_LIST_REVERSE_H
#define TOKEN_LIST_REVERSE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
token* token_list_reverse(token* head);

#endif /* TOKEN_LIST_REVERSE_H */
