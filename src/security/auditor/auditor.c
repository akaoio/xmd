/**
 * @file auditor.c
 * @brief Security audit logging and monitoring - Functions have been refactored into separate files
 * @author XMD Implementation Team
 * @date 2025-07-25
 * 
 * All functions from this file have been extracted to individual files following
 * INSTRUCTIONS.md Rule 2 (one function per file):
 * - audit_state/audit_state.c (global state)
 * - get_timestamp_ms/get_timestamp_ms.c
 * - expand_entries_array/expand_entries_array.c
 * - write_audit_entry_to_file/write_audit_entry_to_file.c
 * - security_audit_init/security_audit_init.c
 * - security_audit_log/security_audit_log.c
 * - security_audit_get_entries/security_audit_get_entries.c
 * - security_audit_cleanup/security_audit_cleanup.c
 * 
 * The audit_state structure definition remains in the auditor_internal.h header file.
 */
