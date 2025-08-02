/**
 * @file security_sandbox_cleanup.c
 * @brief Cleanup security sandbox
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security sandbox subsystem
 */

#include "../../../../include/security.h"
#include "../../../../include/auditor_internal.h"
/**
 * @brief Cleanup security sandbox
 */
void security_sandbox_cleanup(void) {
    security_audit_log(AUDIT_COMMAND_EXECUTION, "Sandbox cleaned up", __FILE__, __func__, __LINE__, SECURITY_VALID);
}
