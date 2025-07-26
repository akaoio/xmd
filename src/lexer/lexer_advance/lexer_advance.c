/**
 * @file lexer_advance.c
 * @brief Lexer position advancement function
 * @author XMD Team
 *
 * Implementation of position advancement for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Advance position and update line/column tracking
 * @param lex Lexer instance
 * @return Next character or '\0' if at end
 */
char lexer_advance(lexer* lex) {
    if (lex->position >= lex->length) {
        return '\0';
    }
    
    char ch = lex->input[lex->position];
    lex->position++;
    
    if (ch == '\n') {
        lex->line++;
        lex->column = 1;
    } else {
        lex->column++;
    }
    
    return ch;
}