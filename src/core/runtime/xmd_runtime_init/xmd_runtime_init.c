#include "xmd_runtime_init.h"
#include "../xmd_runtime_global_config/xmd_runtime_global_config.h"
#include "../../../../include/core_macros.h"
#include "utils/common/common_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool xmd_runtime_init(const xmd_runtime_config* config) {
    XMD_VALIDATE_PTRS(false, config);
    
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
