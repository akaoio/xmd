/**
 * @file auditor_internal.h
 * @brief Internal header for auditor functions
 * @author XMD Team
 */

#ifndef AUDITOR_INTERNAL_H
#define AUDITOR_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "security.h"

/**
 * @brief Internal audit state structure
 */
struct audit_state_struct {
    FILE* log_file;
    char* log_path;
    security_audit_entry* entries;
    size_t entry_count;
    size_t entry_capacity;
    pthread_mutex_t mutex;
    bool initialized;
};

/**
 * @brief Internal audit state
 */
extern struct audit_state_struct audit_state;

// Internal function declarations
uint64_t get_timestamp_ms(void);
int expand_entries_array(void);
int write_audit_entry_to_file(const security_audit_entry* entry);

// Public function declarations
int security_audit_init(const char* log_file);
int security_audit_log(audit_event_type type, const char* message,
                      const char* source_file, const char* source_function,
                      int source_line, security_result result);
int security_audit_get_entries(uint64_t start_time, uint64_t end_time,
                               security_audit_entry** entries, size_t* count);
void security_audit_cleanup(void);

#endif /* AUDITOR_INTERNAL_H */