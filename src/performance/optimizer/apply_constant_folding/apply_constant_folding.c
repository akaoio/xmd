#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file apply_constant_folding.c
 * @brief Apply constant folding optimization
 * @author XMD Team
 */

#include "../../../../include/optimizer_internal.h"

/**
 * @brief Apply constant folding optimization
 * @param tokens Array of tokens
 * @param token_count Number of tokens
 * @return Number of optimizations applied
 */
uint32_t apply_constant_folding(token** tokens, size_t* token_count) {
    if (!tokens || !*tokens || !token_count || *token_count == 0) {
        return 0;
    }
    
    uint32_t optimizations = 0;
    token* token_array = *tokens;
    
    // Look for consecutive text tokens that can be folded
    if (*token_count < 3) {
        return 0; // Need at least 3 tokens for folding
    }
    
    for (size_t i = 0; i < *token_count - 2; i++) {
        if (token_array[i].type == TOKEN_TEXT && 
            token_array[i + 1].type == TOKEN_TEXT &&
            token_array[i + 2].type == TOKEN_TEXT) {
            
            // Simple arithmetic operations
            if (token_array[i].value && token_array[i + 1].value && token_array[i + 2].value &&
                (strcmp(token_array[i + 1].value, "+") == 0 ||
                 strcmp(token_array[i + 1].value, "-") == 0 ||
                 strcmp(token_array[i + 1].value, "*") == 0)) {
                
                // Try to parse as numbers
                char* endptr1, *endptr2;
                double val1 = strtod(token_array[i].value, &endptr1);
                double val2 = strtod(token_array[i + 2].value, &endptr2);
                
                if (*endptr1 == '\0' && *endptr2 == '\0') {
                    double result = 0;
                    const char* op = token_array[i + 1].value;
                    
                    if (strcmp(op, "+") == 0) {
                        result = val1 + val2;
                    } else if (strcmp(op, "-") == 0) {
                        result = val1 - val2;
                    } else if (strcmp(op, "*") == 0) {
                        result = val1 * val2;
                    }
                    
                    // Replace first token with result
                    free(token_array[i].value);
                    char result_str[64];
                    snprintf(result_str, sizeof(result_str), "%.10g", result);
                    token_array[i].value = strdup(result_str);
                    
                    // Remove the operator and second operand
                    free(token_array[i + 1].value);
                    free(token_array[i + 2].value);
                    
                    // Shift remaining tokens
                    memmove(&token_array[i + 1], &token_array[i + 3], 
                           (*token_count - i - 3) * sizeof(token));
                    *token_count -= 2;
                    
                    optimizations++;
                }
            }
        }
    }
    
    return optimizations;
}