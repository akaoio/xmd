/**
 * @file security_audit_init.c
 * @brief Initialize security audit system
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security audit subsystem
 */

#include <stdio.h>
#include <pthread.h>
#include "../../../../include/auditor_internal.h"
#include "../../../../include/utils.h"
/**
 * @brief Initialize security audit system
 * @param log_file Path to audit log file
 * @return 0 on success, -1 on error
 */
int security_audit_init(const char* log_file) {
    if (audit_state.initialized) {
        return 0; // Already initialized
    }
    
    if (!log_file) {
        return -1;
    }
    
    if (pthread_mutex_init(&audit_state.mutex, NULL) != 0) {
        return -1;
    }
    
    audit_state.log_file = fopen(log_file, "a");
    if (!audit_state.log_file) {
        pthread_mutex_destroy(&audit_state.mutex);
        return -1;
    }
    
    audit_state.log_path = xmd_strdup(log_file);
    if (!audit_state.log_path) {
        fclose(audit_state.log_file);
        pthread_mutex_destroy(&audit_state.mutex);
        return -1;
    }
    
    audit_state.entries = NULL;
    audit_state.entry_count = 0;
    audit_state.entry_capacity = 0;
    audit_state.initialized = true;
    
    return 0;
}
