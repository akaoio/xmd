/**
 * @file parser_advance_token.h
 * @brief Header for parser_advance_token function
 */

#ifndef XMD_PARSER_ADVANCE_TOKEN_H
#define XMD_PARSER_ADVANCE_TOKEN_H

#include "ast_parser.h"
#include "token.h"

/**
 * @brief Advance to next token in parser state
 * @param state Parser state
 * @return Current token after advance or NULL
 */
token* parser_advance_token(parser_state* state);

#endif /* XMD_PARSER_ADVANCE_TOKEN_H */