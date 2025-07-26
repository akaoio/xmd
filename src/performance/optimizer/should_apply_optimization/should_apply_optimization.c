/**
 * @file should_apply_optimization.c
 * @brief Check if optimization should be applied based on level
 * @author XMD Team
 */

#include "../../../../include/optimizer_internal.h"

/**
 * @brief Check if optimization should be applied based on level
 * @param pass Optimization pass to check
 * @return true if should apply, false otherwise
 */
bool should_apply_optimization(ast_optimization_pass pass) {
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