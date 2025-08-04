/**
 * @file config_load_env.c
 * @brief Implementation of config_load_env function
 * 
 * This file contains ONLY the config_load_env function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/config_consolidated.c
 */

#include "../../../../include/config.h"
#include "../../../../utils/common/common_macros.h"
#include <stdlib.h>
/**
 * @brief Load configuration from environment variables
 * @param config Configuration to update
 * @return 0 on success, -1 on error
  * /
 */
int config_load_env(xmd_config* config) {
    XMD_VALIDATE_PTRS(-1, config);
    
    xmd_internal_config* internal = (xmd_internal_config*)config;
    
    // Load environment variables for limits
    const char* memory_limit = getenv("XMD_MEMORY_LIMIT_MB");
    if (memory_limit) {
        int limit = atoi(memory_limit);  
        if (limit > 0) internal->limits.memory_limit_mb = limit;
    }
    
    const char* cpu_time = getenv("XMD_CPU_TIME_LIMIT_MS");
    if (cpu_time) {
        int limit = atoi(cpu_time);
        if (limit > 0) internal->limits.cpu_time_limit_ms = limit;
    }
    
    return 0;
}
