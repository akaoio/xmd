/**
 * @file lexer_create.c
 * @brief Lexer creation function
 * @author XMD Team
 *
 * Implementation of lexer creation for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Create a new lexer
 * @param input Input string to tokenize
 * @return New lexer instance or NULL on failure
 */
lexer* lexer_create(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    
    lexer* lex = malloc(sizeof(lexer));
    if (lex == NULL) {
        return NULL;
    }
    
    lex->input = input;
    lex->position = 0;
    lex->length = strlen(input);
    lex->line = 1;
    lex->column = 1;
    lex->peeked_token = NULL;
    
    return lex;
}