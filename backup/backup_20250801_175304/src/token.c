/**
 * @file token.c
 * @brief Consolidated token operations for XMD
 * @author XMD Development Team
 *
 * All token creation, manipulation, list operations, and utility functions
 * consolidated from 20 separate directories for better maintainability.
 */

#include "../include/token_internal.h"
#include "../include/memory.h"
#include "../include/utils.h"

// ============================================================================
// TOKEN CREATION AND MANAGEMENT
// ============================================================================

/**
 * @brief Create a new token
 * @param type Token type
 * @param value Token value (will be copied)
 * @param line Line number
 * @param column Column number
 * @return New token or NULL on failure
 */
token* token_create(token_type type, const char* value, size_t line, size_t column) {
    token* t = xmd_malloc(sizeof(token));
    if (t == NULL) {
        return NULL;
    }
    
    t->type = type;
    t->line = line;
    t->column = column;
    t->next = NULL;
    
    // Copy value if provided
    if (value != NULL) {
        t->value = xmd_strdup(value);
        if (t->value == NULL) {
            free(t);
            return NULL;
        }
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
 * @brief Copy token data (shallow copy - reuses value pointer)
 * @param dest Destination token
 * @param src Source token
 * @return 0 on success, -1 on error
 */
token* token_copy(const token* t) {
    if (t == NULL) {
        return NULL;
    }
    
    token* copy = xmd_malloc(sizeof(token));
    if (copy == NULL) {
        return NULL;
    }
    
    copy->type = t->type;
    copy->line = t->line;
    copy->column = t->column;
    copy->next = NULL; // Don't copy the next pointer
    
    // Copy value if present
    if (t->value != NULL) {
        copy->value = xmd_strdup(t->value);
        if (copy->value == NULL) {
            free(copy);
            return NULL;
        }
    } else {
        copy->value = NULL;
    }
    
    return copy;
}

/**
 * @brief Set token value
 * @param tok Token to modify
 * @param value New value (will be copied)
 * @return 0 on success, -1 on error
 */
int token_set_value(token* tok, const char* value) {
    if (tok == NULL) {
        return -1;
    }
    
    // Free existing value
    if (tok->value != NULL) {
        free(tok->value);
        tok->value = NULL;
    }
    
    // Copy new value if provided
    if (value != NULL) {
        tok->value = xmd_strdup(value);
        if (tok->value == NULL) {
            return -1;
        }
    }
    
    return 0;
}

/**
 * @brief Check if two tokens are equal
 * @param tok1 First token
 * @param tok2 Second token
 * @return 1 if equal, 0 if not equal
 */
bool token_equals(const token* tok1, const token* tok2) {
    if (tok1 == tok2) {
        return true; // Same pointer or both NULL
    }
    
    if (tok1 == NULL || tok2 == NULL) {
        return false; // One is NULL, the other isn't
    }
    
    // Compare type, line, column
    if (tok1->type != tok2->type || 
        tok1->line != tok2->line || 
        tok1->column != tok2->column) {
        return false;
    }
    
    // Compare values
    if (tok1->value == tok2->value) {
        return true; // Same pointer or both NULL
    }
    
    if (tok1->value == NULL || tok2->value == NULL) {
        return false; // One is NULL, the other isn't
    }
    
    return strcmp(tok1->value, tok2->value) == 0;
}

// ============================================================================
// TOKEN TYPE UTILITIES  
// ============================================================================

/**
 * @brief Convert token type to string representation
 * @param type Token type
 * @return String representation of token type
 */
const char* token_type_to_string(token_type type) {
    switch (type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_STRING: return "STRING";
        case TOKEN_BOOLEAN: return "BOOLEAN";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_DOT: return "DOT";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_COLON: return "COLON";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_MULTIPLY: return "MULTIPLY";
        case TOKEN_DIVIDE: return "DIVIDE";
        case TOKEN_MODULO: return "MODULO";
        case TOKEN_EQUAL: return "EQUAL";
        case TOKEN_NOT_EQUAL: return "NOT_EQUAL";
        case TOKEN_LESS_THAN: return "LESS_THAN";
        case TOKEN_LESS_EQUAL: return "LESS_EQUAL";
        case TOKEN_GREATER_THAN: return "GREATER_THAN";
        case TOKEN_GREATER_EQUAL: return "GREATER_EQUAL";
        case TOKEN_LOGICAL_AND: return "LOGICAL_AND";
        case TOKEN_LOGICAL_OR: return "LOGICAL_OR";
        case TOKEN_LOGICAL_NOT: return "LOGICAL_NOT";
        case TOKEN_IF: return "IF";
        case TOKEN_ELSE: return "ELSE";
        case TOKEN_WHILE: return "WHILE";
        case TOKEN_FOR: return "FOR";
        case TOKEN_FUNCTION: return "FUNCTION";
        case TOKEN_RETURN: return "RETURN";
        case TOKEN_VAR: return "VAR";
        case TOKEN_CONST: return "CONST";
        case TOKEN_NEWLINE: return "NEWLINE";
        case TOKEN_WHITESPACE: return "WHITESPACE";
        case TOKEN_COMMENT: return "COMMENT";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Check if token type is valid
 * @param type Token type to validate
 * @return 1 if valid, 0 if invalid
 */
bool token_type_is_valid(token_type type) {
    return type >= TOKEN_EOF && type <= TOKEN_COMMENT;
}

/**
 * @brief Convert token to string representation
 * @param tok Token to convert
 * @return String representation or NULL on error
 */
char* token_to_string(const token* tok) {
    if (tok == NULL) {
        return xmd_strdup("NULL");
    }
    
    const char* type_str = token_type_to_string(tok->type);
    const char* value_str = tok->value ? tok->value : "";
    
    // Estimate size: type + value + formatting + null terminator
    size_t size = strlen(type_str) + strlen(value_str) + 50;
    char* result = xmd_malloc(size);
    if (result == NULL) {
        return NULL;
    }
    
    snprintf(result, size, "Token{type=%s, value=\"%s\", line=%zu, column=%zu}", 
             type_str, value_str, tok->line, tok->column);
    
    return result;
}

// ============================================================================
// TOKEN LIST OPERATIONS
// ============================================================================

/**
 * @brief Append token to token list
 * @param list Pointer to list head pointer
 * @param tok Token to append
 * @return 0 on success, -1 on error
 */
token* token_list_append(token* head, token* t) {
    if (t == NULL) {
        return head;
    }
    
    t->next = NULL;
    
    if (head == NULL) {
        return t;
    }
    
    token* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = t;
    return head;
}

/**
 * @brief Get token at specific index in list
 * @param list Token list head
 * @param index Index to retrieve (0-based)
 * @return Token at index or NULL if not found
 */
token* token_list_get(token* list, size_t index) {
    if (list == NULL) {
        return NULL;
    }
    
    token* current = list;
    size_t i = 0;
    
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    
    return current;
}

/**
 * @brief Get length of token list
 * @param list Token list head
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
 * @brief Free all tokens in list
 * @param list Token list head
 */
void token_list_free(token* list) {
    token* current = list;
    
    while (current != NULL) {
        token* next = current->next;
        token_free(current);
        current = next;
    }
}

/**
 * @brief Destroy token list (alias for token_list_free)
 * @param list Token list head
 */
void token_list_destroy(token* list) {
    token_list_free(list);
}

/**
 * @brief Reverse token list in place
 * @param list Pointer to list head pointer
 * @return 0 on success, -1 on error
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
