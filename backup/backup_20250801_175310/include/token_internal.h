/**
 * @file token_internal.h
 * @brief Internal header for token system functions
 * @author XMD Team
 */

#ifndef TOKEN_INTERNAL_H
#define TOKEN_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"

// Function declarations
token* token_create(token_type type, const char* value, size_t line, size_t column);
void token_free(token* tok);
token* token_duplicate(const token* tok);
token* token_copy(const token* t);
const char* token_type_to_string(token_type type);
bool token_type_is_valid(token_type type);
bool token_equals(const token* tok1, const token* tok2);
int token_set_value(token* tok, const char* value);
token* token_list_append(token* head, token* t);
size_t token_list_length(const token* head);
token* token_list_get(token* head, size_t index);
token* token_list_reverse(token* head);
void token_list_free(token* head);
void token_list_destroy(token* head);
char* token_to_string(const token* t);

#endif /* TOKEN_INTERNAL_H */
