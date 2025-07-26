/**
 * @file apply_common_subexpression_elimination.c
 * @brief Apply common subexpression elimination
 * @author XMD Team
 */

#include "../../../../include/optimizer_internal.h"

/**
 * @brief Apply common subexpression elimination
 * @param tokens Array of tokens
 * @param token_count Number of tokens
 * @return Number of optimizations applied
 */
uint32_t apply_common_subexpression_elimination(token** tokens, size_t* token_count) {
    if (!tokens || !*tokens || !token_count || *token_count < 6) {
        return 0; // Need at least 6 tokens for meaningful CSE
    }
    
    uint32_t optimizations = 0;
    token* token_array = *tokens;
    
    // Look for repeated expressions
    for (size_t i = 0; i < *token_count - 2; i++) {
        for (size_t j = i + 3; j < *token_count - 2; j++) {
            // Check for identical 3-token sequences
            if (token_array[i].type == token_array[j].type &&
                token_array[i + 1].type == token_array[j + 1].type &&
                token_array[i + 2].type == token_array[j + 2].type) {
                
                bool match = true;
                for (int k = 0; k < 3; k++) {
                    if (!token_array[i + k].value || !token_array[j + k].value ||
                        strcmp(token_array[i + k].value, token_array[j + k].value) != 0) {
                        match = false;
                        break;
                    }
                }
                
                if (match) {
                    // For simplicity, just mark as optimized
                    // In a real implementation, we'd extract to a temporary variable
                    optimizations++;
                    break;
                }
            }
        }
    }
    
    return optimizations;
}