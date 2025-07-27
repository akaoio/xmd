/**
 * @file xmd_internal_config_add_exec_whitelist.c
 * @brief Add executable to whitelist function
 * @author XMD Team
 *
 * Implementation of executable whitelist addition for the XMD config system.
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include "../../../include/config_internal.h"

/**
 * @brief Add executable to whitelist
 * @param config Configuration to modify
 * @param executable Executable to add to whitelist
 * @return 0 on success, -1 on error
 */
int xmd_internal_config_add_exec_whitelist(xmd_internal_config* config, const char* executable) {
    if (!config || !executable) {
        return -1;
    }
    
    char** new_whitelist = realloc(config->security.exec_whitelist,
                                  (config->security.exec_whitelist_count + 1) * sizeof(char*));
    if (!new_whitelist) {
        return -1;
    }
    
    config->security.exec_whitelist = new_whitelist;
    config->security.exec_whitelist[config->security.exec_whitelist_count] = strdup(executable);
    config->security.exec_whitelist_count++;
    
    return 0;
}