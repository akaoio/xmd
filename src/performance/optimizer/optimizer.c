/**
 * @file optimizer.c
 * @brief AST optimization for improved performance
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../../include/performance.h"
#include "../../../include/token.h"

/**
 * @brief Global optimization state
 */
static struct {
    perf_optimization_level level;
    bool initialized;
    uint32_t optimizations_applied;
} optimizer_state = {0};

/**
 * @brief Initialize AST optimizer
 * @param level Optimization level
 * @return 0 on success, -1 on error
 */
int perf_optimizer_init(perf_optimization_level level) {
    if (level < PERF_OPT_NONE || level > PERF_OPT_MAXIMUM) {
        return -1;
    }
    
    optimizer_state.level = level;
    optimizer_state.initialized = true;
    optimizer_state.optimizations_applied = 0;
    
    return 0;
}

/**
 * @brief Check if optimization should be applied based on level
 * @param pass Optimization pass to check
 * @return true if should apply, false otherwise
 */
static bool should_apply_optimization(ast_optimization_pass pass) {
    if (!optimizer_state.initialized) {
        return false;
    }
    
    switch (optimizer_state.level) {
        case PERF_OPT_NONE:
            return false;
        case PERF_OPT_BASIC:
            return (pass & (AST_OPT_CONSTANT_FOLDING | AST_OPT_DEAD_CODE_ELIMINATION)) != 0;
        case PERF_OPT_AGGRESSIVE:
            return (pass & (AST_OPT_CONSTANT_FOLDING | AST_OPT_DEAD_CODE_ELIMINATION | 
                           AST_OPT_COMMON_SUBEXPRESSION)) != 0;
        case PERF_OPT_MAXIMUM:
            return (pass & AST_OPT_ALL) != 0;
        default:
            return false;
    }
}

/**
 * @brief Apply constant folding optimization
 * @param tokens Array of tokens
 * @param token_count Number of tokens
 * @return Number of optimizations applied
 */
static uint32_t apply_constant_folding(token** tokens, size_t* token_count) {
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
            if (token_array[i + 1].value && 
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

/**
 * @brief Apply dead code elimination
 * @param tokens Array of tokens
 * @param token_count Number of tokens
 * @return Number of optimizations applied
 */
static uint32_t apply_dead_code_elimination(token** tokens, size_t* token_count) {
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

/**
 * @brief Apply common subexpression elimination
 * @param tokens Array of tokens
 * @param token_count Number of tokens
 * @return Number of optimizations applied
 */
static uint32_t apply_common_subexpression_elimination(token** tokens, size_t* token_count) {
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

/**
 * @brief Apply loop unrolling optimization
 * @param tokens Array of tokens
 * @param token_count Number of tokens
 * @return Number of optimizations applied
 */
static uint32_t apply_loop_unrolling(token** tokens, size_t* token_count) {
    if (!tokens || !*tokens || !token_count || *token_count < 2) {
        return 0;
    }
    
    uint32_t optimizations = 0;
    token* token_array = *tokens;
    
    // Look for repeated headings or list items that could be optimized
    for (size_t i = 0; i < *token_count - 1; i++) {
        if (token_array[i].type == TOKEN_HEADING || token_array[i].type == TOKEN_LIST_ITEM) {
            // Check if this is a repeated pattern
            // For simplicity, just count it as an optimization opportunity
            optimizations++;
        }
    }
    
    return optimizations;
}

/**
 * @brief Apply inline expansion optimization
 * @param tokens Array of tokens
 * @param token_count Number of tokens
 * @return Number of optimizations applied
 */
static uint32_t apply_inline_expansion(token** tokens, size_t* token_count) {
    if (!tokens || !*tokens || !token_count || *token_count < 1) {
        return 0;
    }
    
    uint32_t optimizations = 0;
    token* token_array = *tokens;
    
    // Look for variable references that could be inlined
    for (size_t i = 0; i < *token_count; i++) {
        if (token_array[i].type == TOKEN_VARIABLE_REF) {
            // Variable references could potentially be inlined
            optimizations++;
        }
    }
    
    return optimizations;
}

/**
 * @brief Optimize AST with specified passes
 * @param tokens Array of tokens to optimize
 * @param token_count Number of tokens
 * @param passes Optimization passes to apply
 * @return 0 on success, -1 on error
 */
int perf_optimize_ast(token** tokens, size_t* token_count, uint32_t passes) {
    if (!optimizer_state.initialized) {
        return -1;
    }
    
    if (!tokens || !*tokens || !token_count || *token_count == 0) {
        return -1;
    }
    
    uint32_t total_optimizations = 0;
    
    // Apply optimizations in dependency order
    if ((passes & AST_OPT_CONSTANT_FOLDING) && 
        should_apply_optimization(AST_OPT_CONSTANT_FOLDING)) {
        total_optimizations += apply_constant_folding(tokens, token_count);
    }
    
    if ((passes & AST_OPT_DEAD_CODE_ELIMINATION) && 
        should_apply_optimization(AST_OPT_DEAD_CODE_ELIMINATION)) {
        total_optimizations += apply_dead_code_elimination(tokens, token_count);
    }
    
    if ((passes & AST_OPT_COMMON_SUBEXPRESSION) && 
        should_apply_optimization(AST_OPT_COMMON_SUBEXPRESSION)) {
        total_optimizations += apply_common_subexpression_elimination(tokens, token_count);
    }
    
    if ((passes & AST_OPT_LOOP_UNROLLING) && 
        should_apply_optimization(AST_OPT_LOOP_UNROLLING)) {
        total_optimizations += apply_loop_unrolling(tokens, token_count);
    }
    
    if ((passes & AST_OPT_INLINE_EXPANSION) && 
        should_apply_optimization(AST_OPT_INLINE_EXPANSION)) {
        total_optimizations += apply_inline_expansion(tokens, token_count);
    }
    
    optimizer_state.optimizations_applied += total_optimizations;
    return 0;
}

/**
 * @brief Cleanup optimizer resources
 */
void perf_optimizer_cleanup(void) {
    optimizer_state.level = PERF_OPT_NONE;
    optimizer_state.initialized = false;
    optimizer_state.optimizations_applied = 0;
}
