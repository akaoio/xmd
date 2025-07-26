/**
 * @file perf_optimize_ast.c
 * @brief Optimize AST with specified passes
 * @author XMD Team
 */

#include "../../../../include/optimizer_internal.h"

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