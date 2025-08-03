/**
 * @file security_audit_cleanup.c
 * @brief Cleanup security audit system
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security audit subsystem
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../../../../include/auditor_internal.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Cleanup security audit system
 */
void security_audit_cleanup(void) {
    if (!audit_state.initialized) {
        return;
    }
    
    if (audit_state.log_file) {
        fclose(audit_state.log_file);
        audit_state.log_file = NULL;
    }
    
    XMD_FREE_SAFE(audit_state.log_path);
    audit_state.log_path = NULL;
    
    // Cleanup simplified - entries managed elsewhere
    pthread_mutex_destroy(&audit_state.mutex);
    audit_state.initialized = false;
}
