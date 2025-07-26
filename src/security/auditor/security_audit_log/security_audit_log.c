/**
 * @file security_audit_log.c
 * @brief Log security audit event
 * @author XMD Team
 */

#include "../../../../include/auditor_internal.h"

/**
 * @brief Log security audit event
 * @param type Event type
 * @param message Event message
 * @param source_file Source file name
 * @param source_function Source function name
 * @param source_line Source line number
 * @param result Security result
 * @return 0 on success, -1 on error
 */
int security_audit_log(audit_event_type type, const char* message,
                      const char* source_file, const char* source_function,
                      int source_line, security_result result) {
    if (!audit_state.initialized) {
        return -1;
    }
    
    pthread_mutex_lock(&audit_state.mutex);
    
    // Expand array if needed
    if (audit_state.entry_count >= audit_state.entry_capacity) {
        if (expand_entries_array() != 0) {
            pthread_mutex_unlock(&audit_state.mutex);
            return -1;
        }
    }
    
    // Create new entry
    security_audit_entry* entry = &audit_state.entries[audit_state.entry_count];
    memset(entry, 0, sizeof(security_audit_entry));
    
    entry->type = type;
    entry->result = result;
    entry->source_line = source_line;
    entry->timestamp = get_timestamp_ms();
    
    // Copy strings
    if (message) {
        entry->message = strdup(message);
    }
    if (source_file) {
        entry->source_file = strdup(source_file);
    }
    if (source_function) {
        entry->source_function = strdup(source_function);
    }
    
    // Write to file
    write_audit_entry_to_file(entry);
    
    audit_state.entry_count++;
    
    pthread_mutex_unlock(&audit_state.mutex);
    return 0;
}