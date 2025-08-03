#include "xmd_runtime_init.h"
#include "../../../../include/core_macros.h"
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
    XMD_RUNTIME_VALIDATE_CONFIG(config, "xmd_runtime_init");
    
    g_runtime_config.debug_mode = config->debug_mode;
    g_runtime_config.strict_mode = config->strict_mode;
    g_runtime_config.safe_mode = config->safe_mode;
    g_runtime_config.max_stack_depth = config->max_stack_depth;
    g_runtime_config.max_recursion_depth = config->max_recursion_depth;
    
    if (config->version && strlen(config->version) > 0) {
        g_runtime_config.version = config->version;
    }
    
    // XMD_RUNTIME_DEBUG_PRINT(&g_runtime_config);  // Macro needs fixing for non-pointer types
    
    return true;
}
