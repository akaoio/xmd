/**
 * @file xmd_internal_config_set_exec_whitelist.c
 * @brief Set complete executable whitelist function
 * @author XMD Team
 *
 * Implementation of complete executable whitelist replacement for the XMD config system.
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/config_internal.h"

/**
 * @brief Set complete executable whitelist (replaces existing)
 * @param config Configuration to modify
 * @param executables Array of executables
 * @param count Number of executables
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_set_exec_whitelist(xmd_internal_config* config, const char** executables, size_t count) {
    if (!config) {
        return -1;
    }
    
    // Free existing whitelist
    for (size_t i = 0; i < config->security.exec_whitelist_count; i++) {
        free(config->security.exec_whitelist[i]);
    }
    free(config->security.exec_whitelist);
    
    // Set new whitelist
    if (count == 0 || !executables) {
        config->security.exec_whitelist = NULL;
        config->security.exec_whitelist_count = 0;
        return 0;
    }
    
    config->security.exec_whitelist = malloc(count * sizeof(char*));
    if (!config->security.exec_whitelist) {
        config->security.exec_whitelist_count = 0;
        return -1;
    }
    
    for (size_t i = 0; i < count; i++) {
        config->security.exec_whitelist[i] = strdup(executables[i]);
        if (!config->security.exec_whitelist[i]) {
            // Cleanup on error
            for (size_t j = 0; j < i; j++) {
                free(config->security.exec_whitelist[j]);
            }
            free(config->security.exec_whitelist);
            config->security.exec_whitelist = NULL;
            config->security.exec_whitelist_count = 0;
            return -1;
        }
    }
    
    config->security.exec_whitelist_count = count;
    return 0;
}
