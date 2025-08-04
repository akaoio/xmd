/**
 * @file xmd_internal_config_load_env.c
 * @brief Load configuration from environment variables
 * 
 * This file contains ONLY the xmd_internal_config_load_env function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "utils/common/common_macros.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Load configuration from environment variables
 * @param config Configuration to load into
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_load_env(xmd_internal_config* config) {
    XMD_VALIDATE_PTRS(-1, config);
    
    const char* env_value;
    
    // Load memory limit
    env_value = getenv("XMD_MEMORY_LIMIT_MB");
    if (env_value) {
        config->limits.memory_limit_mb = (size_t)atoi(env_value);
    }
    
    // Load CPU time limit
    env_value = getenv("XMD_CPU_TIME_LIMIT_MS");
    if (env_value) {
        config->limits.cpu_time_limit_ms = (size_t)atoi(env_value);
    }
    
    // Load execution time limit
    env_value = getenv("XMD_EXECUTION_TIME_LIMIT_MS");
    if (env_value) {
        config->limits.execution_time_limit_ms = (size_t)atoi(env_value);
    }
    
    // Load max output size
    env_value = getenv("XMD_MAX_OUTPUT_SIZE");
    if (env_value) {
        config->limits.max_output_size = (size_t)atoi(env_value);
    }
    
    // Load temp directory
    env_value = getenv("XMD_TEMP_DIR");
    if (env_value) {
        XMD_FREE_SAFE(config->paths.temp_dir);
        config->paths.temp_dir = strdup(env_value);
    }
    
    // Load security settings
    env_value = getenv("XMD_ENABLE_SANDBOX");
    if (env_value) {
        config->security.enable_sandbox = (strcmp(env_value, "true") == 0 || 
                                          strcmp(env_value, "1") == 0);
    }
    
    env_value = getenv("XMD_ALLOW_FILE_ACCESS");
    if (env_value) {
        config->security.allow_file_access = (strcmp(env_value, "true") == 0 || 
                                             strcmp(env_value, "1") == 0);
    }
    
    env_value = getenv("XMD_ALLOW_NETWORK_ACCESS");
    if (env_value) {
        config->security.allow_network_access = (strcmp(env_value, "true") == 0 || 
                                                strcmp(env_value, "1") == 0);
    }
    
    return 0;
}