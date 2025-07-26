/**
 * @file apply_dead_code_elimination.c
 * @brief Apply dead code elimination
 * @author XMD Team
 */

#include "../../../../include/optimizer_internal.h"

/**
 * @brief Apply dead code elimination
 * @param tokens Array of tokens
 * @param token_count Number of tokens
 * @return Number of optimizations applied
 */
uint32_t apply_dead_code_elimination(token** tokens, size_t* token_count) {
    if (!tokens || !*tokens || !token_count || *token_count == 0) {
        return 0;
    }
    
    uint32_t optimizations = 0;
    token* token_array = *tokens;
    size_t write_pos = 0;
    
    // Remove tokens that represent dead code patterns
    for (size_t i = 0; i < *token_count; i++) {
        bool is_dead_code = false;
        
        // Check for empty text tokens or HTML comments (dead code in markdown context)
        if (token_array[i].type == TOKEN_HTML_COMMENT) {
            // HTML comments could be considered dead code in some contexts
            is_dead_code = false; // Keep comments for now
        }
        
        // Check for empty text tokens
        if (token_array[i].type == TOKEN_TEXT && token_array[i].value) {
            if (strlen(token_array[i].value) == 0 ||
                (strlen(token_array[i].value) == 1 && token_array[i].value[0] == ' ')) {
                // Empty or single-space text tokens might be dead code
                is_dead_code = false; // Keep for now to preserve formatting
            }
        }
        
        if (!is_dead_code) {
            if (write_pos != i) {
                token_array[write_pos] = token_array[i];
            }
            write_pos++;
        } else {
            free(token_array[i].value);
            optimizations++;
        }
    }
    
    *token_count = write_pos;
    return optimizations;
}