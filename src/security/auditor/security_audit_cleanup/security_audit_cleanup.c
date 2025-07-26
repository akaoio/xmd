/**
 * @file security_audit_cleanup.c
 * @brief Cleanup security audit system
 * @author XMD Team
 */

#include "../../../../include/auditor_internal.h"

/**
 * @brief Cleanup security audit system
 */
void security_audit_cleanup(void) {
    if (!audit_state.initialized) {
        return;
    }
    
    pthread_mutex_lock(&audit_state.mutex);
    
    // Free all entries
    for (size_t i = 0; i < audit_state.entry_count; i++) {
        free(audit_state.entries[i].message);
        free(audit_state.entries[i].source_file);
        free(audit_state.entries[i].source_function);
    }
    free(audit_state.entries);
    
    // Close log file
    if (audit_state.log_file) {
        fclose(audit_state.log_file);
    }
    
    free(audit_state.log_path);
    
    // Reset state
    memset(&audit_state, 0, sizeof(audit_state));
    
    pthread_mutex_unlock(&audit_state.mutex);
    pthread_mutex_destroy(&audit_state.mutex);
}