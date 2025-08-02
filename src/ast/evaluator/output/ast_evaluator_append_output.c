/**
 * @file ast_evaluator_append_output.c
 * @brief Append output to evaluator's output buffer
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include <string.h>
#include <stdlib.h>
#include "utils/common/common_macros.h"
#include "../../../../include/ast_evaluator.h"
#include "../../../../include/utils.h"

/**
 * @brief Append text to evaluator's output buffer
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
    
    // Ensure capacity
    size_t needed = evaluator->output_size + text_len + 1;
    if (needed > evaluator->output_capacity) {
        size_t new_capacity = evaluator->output_capacity ? evaluator->output_capacity * 2 : 1024;
        while (new_capacity < needed) {
            new_capacity *= 2;
        }
        
        char* new_buffer = xmd_realloc(evaluator->output_buffer, new_capacity);
        if (!new_buffer) {
            return -1;
        }
        
        evaluator->output_buffer = new_buffer;
        evaluator->output_capacity = new_capacity;
    }
    
    // Append text
    memcpy(evaluator->output_buffer + evaluator->output_size, text, text_len);
    evaluator->output_size += text_len;
    evaluator->output_buffer[evaluator->output_size] = '\0';
    
    return 0;
}