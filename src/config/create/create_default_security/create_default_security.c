/**
 * @file create_default_security.c
 * @brief Create default security settings
 * 
 * This file contains ONLY the create_default_security function.
 * One function per file - Genesis principle compliance.
 * Extracted from: backup/backup_20250801_184028/src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"

/**
 * @brief Create default security settings
 * @return Default security configuration
 */
xmd_security_config create_default_security(void) {
    xmd_security_config security;
    
    security.exec_whitelist = NULL;
    security.exec_whitelist_count = 0;
    security.enable_sandbox = false;
    security.allow_file_access = true;
    security.allow_network_access = false;
    
    return security;
}
