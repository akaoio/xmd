/**
 * @file ast_evaluator_append_output.c
 * @brief Append output to evaluator's output buffer
 * @author XMD Team
 * @date 2025-07-29
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_evaluator.h"

/**
 * @brief Append string to evaluator's output buffer
 * @param evaluator Evaluator context
 * @param text Text to append
 * @return 0 on success, -1 on error
 */
int ast_evaluator_append_output(ast_evaluator* evaluator, const char* text) {
    if (!evaluator || !text) {
        return -1;
    }
    
    size_t text_len = strlen(text);
    if (text_len == 0) {
        return 0;
    }
    
    // Allocate or expand buffer
    if (!evaluator->output_buffer) {
        evaluator->output_buffer = malloc(text_len + 1);
        if (!evaluator->output_buffer) {
            return -1;
        }
        memcpy(evaluator->output_buffer, text, text_len);
        evaluator->output_buffer[text_len] = '\0';
        evaluator->output_size = text_len;
    } else {
        // Expand existing buffer
        size_t new_size = evaluator->output_size + text_len;
        char* new_buffer = realloc(evaluator->output_buffer, new_size + 1);
        if (!new_buffer) {
            return -1;
        }
        memcpy(new_buffer + evaluator->output_size, text, text_len);
        new_buffer[new_size] = '\0';
        evaluator->output_buffer = new_buffer;
        evaluator->output_size = new_size;
    }
    
    return 0;
}