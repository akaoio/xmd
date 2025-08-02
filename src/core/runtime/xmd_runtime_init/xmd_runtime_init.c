#include "xmd_runtime_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static xmd_runtime_config g_runtime_config = {
    .debug_mode = false,
    .strict_mode = false,
    .safe_mode = true,
    .max_stack_depth = 1000,
    .max_recursion_depth = 100,
    .version = "0.0.2"
};

bool xmd_runtime_init(const xmd_runtime_config* config) {
    if (!config) {
        fprintf(stderr, "Error: xmd_runtime_init: config is NULL\n");
        return false;
    }
    
    if (config->max_stack_depth <= 0) {
        fprintf(stderr, "Error: xmd_runtime_init: invalid max_stack_depth: %d\n", 
                config->max_stack_depth);
        return false;
    }
    
    if (config->max_recursion_depth <= 0) {
        fprintf(stderr, "Error: xmd_runtime_init: invalid max_recursion_depth: %d\n",
                config->max_recursion_depth);
        return false;
    }
    
    g_runtime_config.debug_mode = config->debug_mode;
    g_runtime_config.strict_mode = config->strict_mode;
    g_runtime_config.safe_mode = config->safe_mode;
    g_runtime_config.max_stack_depth = config->max_stack_depth;
    g_runtime_config.max_recursion_depth = config->max_recursion_depth;
    
    if (config->version && strlen(config->version) > 0) {
        g_runtime_config.version = config->version;
    }
    
    if (g_runtime_config.debug_mode) {
        printf("XMD Runtime initialized:\n");
        printf("  Version: %s\n", g_runtime_config.version);
        printf("  Debug: %s\n", g_runtime_config.debug_mode ? "true" : "false");
        printf("  Strict: %s\n", g_runtime_config.strict_mode ? "true" : "false");
        printf("  Safe: %s\n", g_runtime_config.safe_mode ? "true" : "false");
        printf("  Max stack depth: %d\n", g_runtime_config.max_stack_depth);
        printf("  Max recursion depth: %d\n", g_runtime_config.max_recursion_depth);
    }
    
    return true;
}