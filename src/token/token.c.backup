/**
 * @file token.c
 * @brief Token system implementation
 * @author XMD Team
 *
 * Implementation of token creation, destruction, and manipulation
 * functions for XMD markdown parsing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"

/**
 * @brief Create a new token
 * @param type Token type
 * @param value Token value (will be copied)
 * @param line Line number
 * @param column Column number
 * @return New token or NULL on failure
 */
token* token_create(token_type type, const char* value, size_t line, size_t column) {
    token* t = malloc(sizeof(token));
    if (t == NULL) {
        return NULL;
    }
    
    t->type = type;
    t->line = line;
    t->column = column;
    t->next = NULL;
    
    // Copy value if provided
    if (value != NULL) {
        size_t len = strlen(value);
        t->value = malloc(len + 1);
        if (t->value == NULL) {
            free(t);
            return NULL;
        }
        strcpy(t->value, value);
    } else {
        t->value = NULL;
    }
    
    return t;
}

/**
 * @brief Free a token and its resources
 * @param tok Token to free (can be NULL)
 */
void token_free(token* tok) {
    if (tok == NULL) {
        return;
    }
    
    free(tok->value);
    free(tok);
}


/**
 * @brief Duplicate a token
 * @param tok Token to duplicate
 * @return New token copy or NULL on error
 */
token* token_duplicate(const token* tok) {
    if (tok == NULL) {
        return NULL;
    }
    
    return token_create(tok->type, tok->value, tok->line, tok->column);
}

/**
 * @brief Create a copy of a token (alias for token_duplicate)
 * @param t Token to copy
 * @return Copy of token or NULL if input is NULL
 */
token* token_copy(const token* t) {
    return token_duplicate(t);
}

/**
 * @brief Convert token type to string
 * @param type Token type
 * @return String representation of token type
 */
const char* token_type_to_string(token_type type) {
    switch (type) {
        case TOKEN_TEXT:         return "TEXT";
        case TOKEN_HEADING:      return "HEADING";
        case TOKEN_LIST_ITEM:    return "LIST_ITEM";
        case TOKEN_CODE_BLOCK:   return "CODE_BLOCK";
        case TOKEN_HTML_COMMENT: return "HTML_COMMENT";
        case TOKEN_XMD_DIRECTIVE: return "XMD_DIRECTIVE";
        case TOKEN_VARIABLE_REF: return "VARIABLE_REF";
        case TOKEN_EOF:          return "EOF";
        default:                 return "UNKNOWN";
    }
}

/**
 * @brief Check if token type is valid
 * @param type Token type to validate
 * @return true if valid, false otherwise
 */
bool token_type_is_valid(token_type type) {
    return type >= TOKEN_TEXT && type <= TOKEN_EOF;
}

/**
 * @brief Compare two tokens for equality
 * @param tok1 First token
 * @param tok2 Second token
 * @return true if equal, false otherwise
 */
bool token_equals(const token* tok1, const token* tok2) {
    // Handle NULL cases
    if (tok1 == NULL && tok2 == NULL) {
        return true;
    }
    if (tok1 == NULL || tok2 == NULL) {
        return false;
    }
    
    // Compare type, line, and column
    if (tok1->type != tok2->type || tok1->line != tok2->line || tok1->column != tok2->column) {
        return false;
    }
    
    // Compare values
    if (tok1->value == NULL && tok2->value == NULL) {
        return true;
    }
    if (tok1->value == NULL || tok2->value == NULL) {
        return false;
    }
    
    return strcmp(tok1->value, tok2->value) == 0;
}

/**
 * @brief Set token value
 * @param tok Token to modify
 * @param value New value (will be copied, can be NULL)
 * @return 0 on success, non-zero on error
 */
int token_set_value(token* tok, const char* value) {
    if (tok == NULL) {
        return -1;
    }
    
    // Free existing value
    free(tok->value);
    tok->value = NULL;
    
    // Copy new value if provided
    if (value != NULL) {
        size_t len = strlen(value);
        tok->value = malloc(len + 1);
        if (tok->value == NULL) {
            return -1;
        }
        strcpy(tok->value, value);
    }
    
    return 0;
}

/**
 * @brief Append token to end of token list
 * @param head Head of token list (can be NULL)
 * @param t Token to append
 * @return New head of list
 */
token* token_list_append(token* head, token* t) {
    if (t == NULL) {
        return head;
    }
    
    if (head == NULL) {
        return t;
    }
    
    // Find end of list
    token* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = t;
    t->next = NULL;
    
    return head;
}

/**
 * @brief Get length of token list
 * @param head Head of token list
 * @return Number of tokens in list
 */
size_t token_list_length(const token* head) {
    size_t count = 0;
    const token* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

/**
 * @brief Get token at index in list
 * @param head Head of token list
 * @param index Index (0-based)
 * @return Token at index or NULL if not found
 */
token* token_list_get(token* head, size_t index) {
    token* current = head;
    size_t i = 0;
    
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    
    return current;
}

/**
 * @brief Reverse token list
 * @param head Head of token list
 * @return New head of reversed list
 */
token* token_list_reverse(token* head) {
    token* prev = NULL;
    token* current = head;
    token* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

/**
 * @brief Free entire token list
 * @param head Head of token list
 */
void token_list_free(token* head) {
    token* current = head;
    
    while (current != NULL) {
        token* next = current->next;
        token_free(current);
        current = next;
    }
}

/**
 * @brief Destroy entire token list (alias for token_list_free)
 * @param head Head of token list
 */
void token_list_destroy(token* head) {
    token_list_free(head);
}

/**
 * @brief Convert token to string representation
 * @param t Token to convert
 * @return String representation (must be freed)
 */
char* token_to_string(const token* t) {
    if (t == NULL) {
        return NULL;
    }
    
    const char* type_str = token_type_to_string(t->type);
    const char* value_str = t->value ? t->value : "(null)";
    
    // Allocate buffer for formatted string
    size_t len = strlen(type_str) + strlen(value_str) + 50; // Extra space for formatting
    char* result = malloc(len);
    if (result == NULL) {
        return NULL;
    }
    
    snprintf(result, len, "%s: \"%s\" at %zu:%zu", 
             type_str, value_str, t->line, t->column);
    
    return result;
}
