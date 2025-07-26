/**
 * @file perf_optimizer_init.c
 * @brief Initialize AST optimizer
 * @author XMD Team
 */

#include "../../../../include/optimizer_internal.h"

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