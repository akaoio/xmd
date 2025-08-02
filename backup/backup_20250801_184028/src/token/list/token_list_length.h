/**
 * @file token_list_length.h
 * @brief Declaration for token_list_length function
 * 
 * This file contains ONLY the token_list_length declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef TOKEN_LIST_LENGTH_H
#define TOKEN_LIST_LENGTH_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct token token;

/* Function declaration */
size_t token_list_length(const token* head);

#endif /* TOKEN_LIST_LENGTH_H */
