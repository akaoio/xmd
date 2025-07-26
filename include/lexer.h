/**
 * @file lexer.h
 * @brief Lexical analyzer for XMD markdown processing
 * @author XMD Team
 * 
 * Lexer that tokenizes markdown input with XMD extensions.
 * Handles UTF-8 encoding, position tracking, and XMD directive detection.
 */

#ifndef XMD_LEXER_H
#define XMD_LEXER_H

#include <stddef.h>
#include "token.h"

/**
 * @brief Lexer structure (opaque)
 * @struct lexer
 */
typedef struct lexer lexer;

/* Lexer creation and destruction */

/**
 * @brief Create a new lexer
 * @param input Input markdown string (must remain valid during lexer lifetime)
 * @return New lexer instance or NULL on error
 */
lexer* lexer_create(const char* input);

/**
 * @brief Free lexer resources
 * @param lex Lexer to free (can be NULL)
 */
void lexer_free(lexer* lex);


/* Token generation */

/**
 * @brief Get next token from input
 * @param lex Lexer instance
 * @return Next token or NULL on error (caller must free)
 */
token* lexer_next_token(lexer* lex);

/**
 * @brief Peek at next token without consuming it
 * @param lex Lexer instance
 * @return Next token or NULL on error (caller must free)
 */
token* lexer_peek_token(lexer* lex);

/* Position tracking */

/**
 * @brief Get current byte position in input
 * @param lex Lexer instance
 * @return Current position (0-based)
 */
size_t lexer_get_position(const lexer* lex);

/**
 * @brief Get current line number
 * @param lex Lexer instance
 * @return Current line (1-based)
 */
size_t lexer_get_line(const lexer* lex);

/**
 * @brief Get current column number
 * @param lex Lexer instance
 * @return Current column (1-based)
 */
size_t lexer_get_column(const lexer* lex);

/* Utility functions */

/**
 * @brief Check if lexer has reached end of input
 * @param lex Lexer instance
 * @return true if at end, false otherwise
 */
bool lexer_at_end(const lexer* lex);

/**
 * @brief Reset lexer to beginning of input
 * @param lex Lexer instance
 */
void lexer_reset(lexer* lex);

#endif /* XMD_LEXER_H */
