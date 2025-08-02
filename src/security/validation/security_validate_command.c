/**
 * @file security_validate_command.c
 * @brief Validate command security
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security validation subsystem
 */

#include <string.h>
#include "../../../include/security.h"
#include "../../../include/auditor_internal.h"
/**
 * @brief Validate command security
 * @param command Command to validate
 * @return SECURITY_VALID if safe, error code if dangerous
 */
security_result security_validate_command(const char* command) {
    if (!command) {
        return SECURITY_INVALID_INPUT;
    }
    
    // Check for dangerous commands
    const char* dangerous[] = {
        "rm -rf", "format", "del /f", "rm *", "sudo", "chmod 777", NULL
    };
    
    for (int i = 0; dangerous[i]; i++) {
        if (strstr(command, dangerous[i])) {
            security_audit_log(AUDIT_COMMAND_EXECUTION, command, __FILE__, __func__, __LINE__, SECURITY_INJECTION_DETECTED);
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    return SECURITY_VALID;
}
