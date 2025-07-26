/**
 * @file expand_entries_array.c
 * @brief Expand audit entries array
 * @author XMD Team
 */

#include "../../../../include/auditor_internal.h"

/**
 * @brief Expand audit entries array
 * @return 0 on success, -1 on error
 */
int expand_entries_array(void) {
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