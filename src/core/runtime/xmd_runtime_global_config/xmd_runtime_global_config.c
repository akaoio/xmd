/**
 * @file xmd_runtime_global_config.c
 * @brief Global runtime configuration storage
 * 
 * This file contains ONLY the global runtime configuration variable.
 * One component per file - Genesis principle compliance.
 */

#include "xmd_runtime_global_config.h"

xmd_runtime_config g_runtime_config = {
    .debug_mode = false,
    .strict_mode = false,
    .safe_mode = true,
    .max_stack_depth = 1000,
    .max_recursion_depth = 100,
    .version = "0.0.2"
};
