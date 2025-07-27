#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file security_audit_get_entries.c
 * @brief Get audit entries within time range
 * @author XMD Team
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/auditor_internal.h"

/**
 * @brief Get audit entries within time range
 * @param start_time Start timestamp
 * @param end_time End timestamp
 * @param entries Output array of entries (must be freed)
 * @param count Output count of entries
 * @return 0 on success, -1 on error
 */
int security_audit_get_entries(uint64_t start_time, uint64_t end_time,
                               security_audit_entry** entries, size_t* count) {
    if (!audit_state.initialized || !entries || !count) {
        return -1;
    }
    
    pthread_mutex_lock(&audit_state.mutex);
    
    // Count matching entries
    size_t matching_count = 0;
    for (size_t i = 0; i < audit_state.entry_count; i++) {
        if (audit_state.entries[i].timestamp >= start_time &&
            audit_state.entries[i].timestamp <= end_time) {
            matching_count++;
        }
    }
    
    if (matching_count == 0) {
        *entries = NULL;
        *count = 0;
        pthread_mutex_unlock(&audit_state.mutex);
        return 0;
    }
    
    // Allocate result array
    security_audit_entry* result = malloc(matching_count * sizeof(security_audit_entry));
    if (!result) {
        pthread_mutex_unlock(&audit_state.mutex);
        return -1;
    }
    
    // Copy matching entries
    size_t result_index = 0;
    for (size_t i = 0; i < audit_state.entry_count; i++) {
        if (audit_state.entries[i].timestamp >= start_time &&
            audit_state.entries[i].timestamp <= end_time) {
            
            result[result_index] = audit_state.entries[i];
            
            // Duplicate strings
            if (audit_state.entries[i].message) {
                result[result_index].message = strdup(audit_state.entries[i].message);
            }
            if (audit_state.entries[i].source_file) {
                result[result_index].source_file = strdup(audit_state.entries[i].source_file);
            }
            if (audit_state.entries[i].source_function) {
                result[result_index].source_function = strdup(audit_state.entries[i].source_function);
            }
            
            result_index++;
        }
    }
    
    *entries = result;
    *count = matching_count;
    
    pthread_mutex_unlock(&audit_state.mutex);
    return 0;
}