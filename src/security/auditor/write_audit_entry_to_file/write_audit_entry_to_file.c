/**
 * @file write_audit_entry_to_file.c
 * @brief Write audit entry to log file
 * @author XMD Team
 */

#include "../../../../include/auditor_internal.h"

/**
 * @brief Write audit entry to log file
 * @param entry Audit entry to write
 * @return 0 on success, -1 on error
 */
int write_audit_entry_to_file(const security_audit_entry* entry) {
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