/**
 * @file parser_utils.c
 * @brief Consolidated parser utility functions for XMD
 * @author XMD Development Team
 *
 * All parser utility functionality consolidated from 7 directories.
 * Provides token manipulation, error handling, and parser state management.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/ast_parser.h"
#include "../include/memory.h"
#include "../include/utils.h"

// Global parser state for error tracking
static parser_state* global_parser_state = NULL;

// ============================================================================
// PARSER STATE MANAGEMENT
// ============================================================================

/**
 * @brief Create new parser state
 * @param tokens Token list to parse
 * @return New parser state or NULL on error
 */
parser_state* parser_state_create(token* tokens, const char* filename) {
    parser_state* state = xmd_malloc(sizeof(parser_state));
    if (!state) {
        return NULL;
    }
    
    state->tokens = tokens;
    state->current_token = tokens;
    state->position = 0;
    state->error_message = NULL;
    state->has_error = false;
    state->filename = filename ? xmd_strdup(filename) : NULL;
    
    // Set as global state for error reporting
    global_parser_state = state;
    
    return state;
}

/**
 * @brief Free parser state
 * @param state Parser state to free
 */
void parser_state_free(parser_state* state) {
    if (!state) {
        return;
    }
    
    free(state->error_message);
    free(state);
}

// ============================================================================
// TOKEN MANIPULATION
// ============================================================================

/**
 * @brief Advance to next token
 * @param state Parser state
 * @return Current token after advance
 */
token* parser_advance_token(parser_state* state) {
    if (!state || !state->current_token) {
        return NULL;
    }
    
    if (state->current_token->next) {
        state->current_token = state->current_token->next;
        state->position++;
    }
    
    return state->current_token;
}

/**
 * @brief Peek at next token without advancing
 * @param state Parser state
 * @return Next token or NULL if none
 */
token* parser_peek_token(parser_state* state) {
    if (!state || !state->current_token) {
        return NULL;
    }
    
    return state->current_token->next;
}

// ============================================================================
// ERROR HANDLING
// ============================================================================

/**
 * @brief Set parser error
 * @param state Parser state
 * @param message Error message
 */
void parser_set_error(parser_state* state, const char* message) {
    if (!state) {
        return;
    }
    
    state->has_error = true;
    free(state->error_message);
    state->error_message = message ? xmd_strdup(message) : NULL;
}

/**
 * @brief Check if parser has error
 * @return true if has error
 */
bool parser_has_error(void) {
    if (!global_parser_state) {
        return false;
    }
    
    return global_parser_state->has_error;
}

/**
 * @brief Get parser error message
 * @return Error message or NULL if no error
 */
const char* parser_get_error(void) {
    if (!global_parser_state) {
        return NULL;
    }
    
    return global_parser_state->error_message;
}

// ============================================================================
// PARSER UTILITY FUNCTIONS
// ============================================================================

/**
 * @brief Check if current token matches expected type
 * @param state Parser state
 * @param type Expected token type
 * @return true if matches
 */
bool parser_expect_token(parser_state* state, int type) {
    if (!state || !state->current_token) {
        return false;
    }
    
    return state->current_token->type == type;
}

/**
 * @brief Consume token if it matches expected type
 * @param state Parser state
 * @param type Expected token type
 * @return true if consumed
 */
bool parser_consume_token(parser_state* state, int type) {
    if (!parser_expect_token(state, type)) {
        return false;
    }
    
    parser_advance_token(state);
    return true;
}

/**
 * @brief Skip whitespace and comment tokens
 * @param state Parser state
 */
void parser_skip_whitespace(parser_state* state) {
    if (!state) {
        return;
    }
    
    while (state->current_token && 
           (state->current_token->type == TOKEN_WHITESPACE ||
            state->current_token->type == TOKEN_COMMENT)) {
        parser_advance_token(state);
    }
}

/**
 * @brief Check if at end of token stream
 * @param state Parser state
 * @return true if at end
 */
bool parser_at_end(parser_state* state) {
    if (!state) {
        return true;
    }
    
    return state->current_token == NULL || 
           state->current_token->type == TOKEN_EOF;
}

/**
 * @brief Save current parser position
 * @param state Parser state
 * @return Saved position
 */
size_t parser_save_position(parser_state* state) {
    if (!state) {
        return 0;
    }
    
    return state->position;
}

/**
 * @brief Restore parser to saved position
 * @param state Parser state
 * @param position Saved position
 */
void parser_restore_position(parser_state* state, size_t position) {
    if (!state || position > state->position) {
        return;
    }
    
    // Reset to beginning and advance to position
    state->current_token = state->tokens;
    state->position = 0;
    
    for (size_t i = 0; i < position && state->current_token; i++) {
        parser_advance_token(state);
    }
}
