/**
 * @file security.h
 * @brief Security hardening components for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef XMD_SECURITY_H
#define XMD_SECURITY_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Security validation result
 */
typedef enum {
    SECURITY_VALID = 0,
    SECURITY_INVALID_INPUT = 1,
    SECURITY_INJECTION_DETECTED = 2,
    SECURITY_PATH_TRAVERSAL = 3,
    SECURITY_RESOURCE_LIMIT = 4,
    SECURITY_PERMISSION_DENIED = 5
} security_result;

/**
 * @brief Security audit event type
 */
typedef enum {
    AUDIT_INPUT_VALIDATION = 0,
    AUDIT_COMMAND_EXECUTION = 1,
    AUDIT_FILE_ACCESS = 2,
    AUDIT_NETWORK_ACCESS = 3,
    AUDIT_PRIVILEGE_ESCALATION = 4
} audit_event_type;

/**
 * @brief Security audit entry
 */
typedef struct security_audit_entry {
    audit_event_type type;
    char* message;
    char* source_file;
    char* source_function;
    int source_line;
    uint64_t timestamp;
    security_result result;
} security_audit_entry;

/* Validator functions */

/**
 * @brief Validate input string for security threats
 * @param input Input string to validate
 * @param max_length Maximum allowed length
 * @return Security validation result
 */
security_result security_validate_input(const char* input, size_t max_length);

/**
 * @brief Validate command for injection attacks
 * @param command Command string to validate
 * @return Security validation result
 */
security_result security_validate_command(const char* command);

/**
 * @brief Validate file path for traversal attacks
 * @param path File path to validate
 * @param allowed_base Base directory that must contain the path
 * @return Security validation result
 */
security_result security_validate_path(const char* path, const char* allowed_base);

/* Sanitizer functions */

/**
 * @brief Sanitize output string for safe rendering
 * @param input Input string to sanitize
 * @return Sanitized string (must be freed) or NULL on error
 */
char* security_sanitize_output(const char* input);

/**
 * @brief Sanitize HTML content
 * @param html HTML content to sanitize
 * @return Sanitized HTML (must be freed) or NULL on error
 */
char* security_sanitize_html(const char* html);

/**
 * @brief Sanitize command output for inclusion in markdown
 * @param output Command output to sanitize
 * @return Sanitized output (must be freed) or NULL on error
 */
char* security_sanitize_command_output(const char* output);

/* Auditor functions */

/**
 * @brief Initialize security audit system
 * @param log_file Path to audit log file
 * @return 0 on success, -1 on error
 */
int security_audit_init(const char* log_file);

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
                      int source_line, security_result result);

/**
 * @brief Get audit entries within time range
 * @param start_time Start timestamp
 * @param end_time End timestamp
 * @param entries Output array of entries (must be freed)
 * @param count Output count of entries
 * @return 0 on success, -1 on error
 */
int security_audit_get_entries(uint64_t start_time, uint64_t end_time,
                               security_audit_entry** entries, size_t* count);

/**
 * @brief Cleanup security audit system
 */
void security_audit_cleanup(void);

/* Convenience macros */
#define SECURITY_AUDIT(type, message, result) \
    security_audit_log((type), (message), __FILE__, __func__, __LINE__, (result))

#define SECURITY_VALIDATE_AND_AUDIT(input, max_len) \
    ({ \
        security_result __result = security_validate_input((input), (max_len)); \
        SECURITY_AUDIT(AUDIT_INPUT_VALIDATION, "Input validation", __result); \
        __result; \
    })

#ifdef __cplusplus
}
#endif

#endif /* XMD_SECURITY_H */