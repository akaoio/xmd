/**
 * @file free_security_config.c
 * @brief Free security configuration function
 * @author XMD Team
 *
 * Implementation of security configuration cleanup for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Free security configuration
 * @param security Security configuration to free
 */
void free_security_config(xmd_security_config* security) {
    for (size_t i = 0; i < security->exec_whitelist_count; i++) {
        free(security->exec_whitelist[i]);
    }
    free(security->exec_whitelist);
}