/**
 * @file token.h
 * @brief Token system for XMD lexical analysis
 * @author XMD Team
 * 
 * Defines token types and functions for the XMD markdown parser.
 * Tokens represent the basic units of the markdown document after lexical analysis.
 */

#ifndef XMD_TOKEN_H
#define XMD_TOKEN_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Token types for markdown and XMD elements
 * @enum token_type
 */
typedef enum {
    TOKEN_TEXT,           /**< Plain text content */
    TOKEN_HEADING,        /**< Markdown heading (# ## ###) */
    TOKEN_LIST_ITEM,      /**< List item (- * +) */
    TOKEN_CODE_BLOCK,     /**< Code block (``` or indented) */
    TOKEN_HTML_COMMENT,   /**< HTML comment (<!-- -->) */
    TOKEN_XMD_DIRECTIVE,  /**< XMD directive (<!-- xmd: -->) */
    TOKEN_VARIABLE_REF,   /**< Variable reference ({{var}}) */
    TOKEN_EOF             /**< End of file marker */
} token_type;

/**
 * @brief Token structure
 * @struct token
 * 
 * Represents a single token in the lexical analysis stream.
 * Contains the token type, value, position information, and linking.
 */
typedef struct token {
    token_type type;      /**< Type of the token */
    char* value;          /**< Token value/content (NULL terminated) */
    size_t line;          /**< Line number (1-based) */
    size_t column;        /**< Column number (1-based) */
    struct token* next;   /**< Next token in the list */
} token;

/* Token creation and destruction */

/**
 * @brief Create a new token
 * @param type Token type
 * @param value Token value (will be copied)
 * @param line Line number
 * @param column Column number
 * @return New token or NULL on error
 */
token* token_create(token_type type, const char* value, size_t line, size_t column);

/**
 * @brief Free a token and its resources  
 * @param tok Token to free (can be NULL)
 */
void token_free(token* tok);


/**
 * @brief Duplicate a token
 * @param tok Token to duplicate
 * @return New token copy or NULL on error
 */
token* token_duplicate(const token* tok);

/**
 * @brief Create a copy of a token (alias for token_duplicate)
 * @param t Token to copy
 * @return Copy of token or NULL if input is NULL
 */
token* token_copy(const token* t);

/* Token type utilities */

/**
 * @brief Check if token type is valid
 * @param type Token type to validate
 * @return true if valid, false otherwise
 */
bool token_type_is_valid(token_type type);

/**
 * @brief Convert token type to string
 * @param type Token type
 * @return String representation of token type
 */
const char* token_type_to_string(token_type type);

/* Token comparison */

/**
 * @brief Compare two tokens for equality
 * @param tok1 First token
 * @param tok2 Second token
 * @return true if equal, false otherwise
 */
bool token_equals(const token* tok1, const token* tok2);

/* Token modification */

/**
 * @brief Set token value
 * @param tok Token to modify
 * @param value New value (will be copied, can be NULL)
 * @return 0 on success, non-zero on error
 */
int token_set_value(token* tok, const char* value);

/* Token list operations */

/**
 * @brief Get length of token list
 * @param head Head of token list
 * @return Number of tokens in list
 */
size_t token_list_length(const token* head);

/**
 * @brief Get token at index in list
 * @param head Head of token list
 * @param index Index (0-based)
 * @return Token at index or NULL if not found
 */
token* token_list_get(token* head, size_t index);

/**
 * @brief Reverse token list
 * @param head Head of token list
 * @return New head of reversed list
 */
token* token_list_reverse(token* head);

/**
 * @brief Free entire token list
 * @param head Head of token list
 */
void token_list_free(token* head);

#endif /* XMD_TOKEN_H */