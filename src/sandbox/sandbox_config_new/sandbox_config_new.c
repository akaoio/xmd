/**
 * @file sandbox_config_new.c
 * @brief Create a new sandbox configuration
 * @author XMD Team
 */

#include "../../../include/sandbox_internal.h"

/**
 * @brief Create a new sandbox configuration
 * @return New sandbox configuration or NULL on error
 */
SandboxConfig* sandbox_config_new(void) {
    SandboxConfig* config = malloc(sizeof(SandboxConfig));
    if (!config) return NULL;
    
    memset(config, 0, sizeof(SandboxConfig));
    return config;
}