/**
 * @file security_audit_log.c
 * @brief Log security audit entry
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security audit subsystem
 */

#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "../../../../include/auditor_internal.h"
#include "../../../../include/security.h"
/**
 * @brief Log security audit entry
 * @param type Audit event type
 * @param message Audit message
 * @param source_file Source file name
 * @param source_function Source function name
 * @param source_line Source line number
 * @param result Security result
 * @return 0 on success, -1 on error
 */
int security_audit_log(audit_event_type type, const char* message,
                      const char* source_file, const char* source_function,
                      int source_line, security_result result) {
    (void)type;    // Will be used for filtering in future
    (void)result;  // Will be used for result tracking
    if (!audit_state.initialized || !message) {
        return -1;
    }
    
    pthread_mutex_lock(&audit_state.mutex);
    
    // Write to log file
    time_t now = time(NULL);
    fprintf(audit_state.log_file, "[%ld] %s:%d %s() - %s\n", 
            now, source_file ? source_file : "unknown", 
            source_line, source_function ? source_function : "unknown", message);
    fflush(audit_state.log_file);
    
    pthread_mutex_unlock(&audit_state.mutex);
    return 0;
}
