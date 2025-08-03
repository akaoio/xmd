/**
 * @file parser_peek_token.c
 * @brief Peek at next token without advancing
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include "../../../../include/ast_parser.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Peek at next token without advancing parser
 * @param state Parser state
 * @return Next token or NULL if at end
 */
token* parser_peek_token(parser_state* state) {
    XMD_VALIDATE_PTRS(NULL, state);
    if (!state->current) {
        XMD_ERROR_RETURN(NULL, "parser_peek_token: Parser at end of token stream");
    }
    return state->current->next;
}