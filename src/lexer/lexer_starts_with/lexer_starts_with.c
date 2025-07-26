/**
 * @file lexer_starts_with.c
 * @brief Lexer string matching function
 * @author XMD Team
 *
 * Implementation of string matching at current position for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Check if string starts at current position
 * @param lex Lexer instance
 * @param str String to check
 * @return true if string matches at current position
 */
bool lexer_starts_with(const lexer* lex, const char* str) {
    size_t len = strlen(str);
    if (lex->position + len > lex->length) {
        return false;
    }
    return strncmp(&lex->input[lex->position], str, len) == 0;
}