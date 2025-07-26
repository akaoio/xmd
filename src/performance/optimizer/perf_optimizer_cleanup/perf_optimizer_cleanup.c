/**
 * @file perf_optimizer_cleanup.c
 * @brief Cleanup optimizer resources
 * @author XMD Team
 */

#include "../../../../include/optimizer_internal.h"

/**
 * @brief Cleanup optimizer resources
 */
void perf_optimizer_cleanup(void) {
    optimizer_state.level = PERF_OPT_NONE;
    optimizer_state.initialized = false;
    optimizer_state.optimizations_applied = 0;
}