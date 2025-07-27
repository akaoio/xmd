/**
 * @file create_default_security.c
 * @brief Default security configuration creation function
 * @author XMD Team
 *
 * Implementation of default security configuration creation for the XMD config system.
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/config_internal.h"

/**
 * @brief Create default security configuration
 * @return Default security configuration
 */
xmd_security_config create_default_security(void) {
    xmd_security_config security = {
        .exec_whitelist = NULL,
        .exec_whitelist_count = 0,
        .enable_sandbox = true,
        .allow_file_access = true,
        .allow_network_access = false
    };
    
    // Add default whitelist
    security.exec_whitelist = malloc(3 * sizeof(char*));
    if (security.exec_whitelist) {
        security.exec_whitelist[0] = strdup("echo");
        security.exec_whitelist[1] = strdup("date");
        security.exec_whitelist[2] = strdup("cat");
        security.exec_whitelist_count = 3;
    }
    
    return security;
}
