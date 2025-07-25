/**
 * @file auditor.c
 * @brief Security audit logging and monitoring
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "../../../include/security.h"

/**
 * @brief Internal audit state
 */
static struct {
    FILE* log_file;
    char* log_path;
    security_audit_entry* entries;
    size_t entry_count;
    size_t entry_capacity;
    pthread_mutex_t mutex;
    bool initialized;
} audit_state = {0};

/**
 * @brief Get current timestamp in milliseconds
 * @return Current timestamp
 */
static uint64_t get_timestamp_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (uint64_t)ts.tv_sec * 1000 + (uint64_t)ts.tv_nsec / 1000000;
}

/**
 * @brief Expand audit entries array
 * @return 0 on success, -1 on error
 */
static int expand_entries_array(void) {
    size_t new_capacity = audit_state.entry_capacity == 0 ? 16 : audit_state.entry_capacity * 2;
    security_audit_entry* new_entries = realloc(audit_state.entries, 
                                               new_capacity * sizeof(security_audit_entry));
    if (!new_entries) {
        return -1;
    }
    
    audit_state.entries = new_entries;
    audit_state.entry_capacity = new_capacity;
    return 0;
}

/**
 * @brief Write audit entry to log file
 * @param entry Audit entry to write
 * @return 0 on success, -1 on error
 */
static int write_audit_entry_to_file(const security_audit_entry* entry) {
    if (!audit_state.log_file || !entry) {
        return -1;
    }
    
    const char* event_type_str = "UNKNOWN";
    switch (entry->type) {
        case AUDIT_INPUT_VALIDATION: event_type_str = "INPUT_VALIDATION"; break;
        case AUDIT_COMMAND_EXECUTION: event_type_str = "COMMAND_EXECUTION"; break;
        case AUDIT_FILE_ACCESS: event_type_str = "FILE_ACCESS"; break;
        case AUDIT_NETWORK_ACCESS: event_type_str = "NETWORK_ACCESS"; break;
        case AUDIT_PRIVILEGE_ESCALATION: event_type_str = "PRIVILEGE_ESCALATION"; break;
    }
    
    const char* result_str = "UNKNOWN";
    switch (entry->result) {
        case SECURITY_VALID: result_str = "VALID"; break;
        case SECURITY_INVALID_INPUT: result_str = "INVALID_INPUT"; break;
        case SECURITY_INJECTION_DETECTED: result_str = "INJECTION_DETECTED"; break;
        case SECURITY_PATH_TRAVERSAL: result_str = "PATH_TRAVERSAL"; break;
        case SECURITY_RESOURCE_LIMIT: result_str = "RESOURCE_LIMIT"; break;
        case SECURITY_PERMISSION_DENIED: result_str = "PERMISSION_DENIED"; break;
    }
    
    fprintf(audit_state.log_file,
            "%lu|%s|%s|%s|%s|%d|%s\n",
            entry->timestamp,
            event_type_str,
            result_str,
            entry->message ? entry->message : "",
            entry->source_file ? entry->source_file : "",
            entry->source_line,
            entry->source_function ? entry->source_function : "");
    
    fflush(audit_state.log_file);
    return 0;
}

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
    
    audit_state.log_path = strdup(log_file);
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