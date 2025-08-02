/**
 * @file lexer_internal.h
 * @brief Internal header for lexer system functions
 * @author XMD Team
 */

#ifndef LEXER_INTERNAL_H
#define LEXER_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "lexer.h"
#include "token.h"

/**
 * @struct lexer
 * @brief Lexer state structure
 */
struct lexer {
    const char* input;     /**< Input string */
    size_t position;       /**< Current position in input */
    size_t length;         /**< Length of input */
    size_t line;           /**< Current line number (1-based) */
    size_t column;         /**< Current column number (1-based) */
    token* peeked_token;   /**< Cached token for peek functionality */
};

// Function declarations
lexer* lexer_create(const char* input);
void lexer_free(lexer* lex);
char lexer_current_char(const lexer* lex);
char lexer_advance(lexer* lex);
char lexer_peek_char(const lexer* lex);
void lexer_skip_whitespace(lexer* lex);
bool lexer_starts_with(const lexer* lex, const char* str);
char* lexer_extract_substring(const lexer* lex, size_t start_pos, size_t length);
char* lexer_read_line(lexer* lex);
char* lexer_read_html_comment(lexer* lex);
char* lexer_read_code_block(lexer* lex);
char* lexer_read_variable_ref(lexer* lex);
char* lexer_read_xmd_directive(lexer* lex);
char* lexer_read_text(lexer* lex);
token* lexer_next_token(lexer* lex);
token* lexer_peek_token(lexer* lex);
size_t lexer_get_position(const lexer* lex);
size_t lexer_get_line(const lexer* lex);
size_t lexer_get_column(const lexer* lex);
bool lexer_at_end(const lexer* lex);
void lexer_reset(lexer* lex);

#endif /* LEXER_INTERNAL_H */
