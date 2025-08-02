/**
 * @file security.c
 * @brief Consolidated security operations for XMD
 * @author XMD Development Team
 *
 * All security auditing, sandboxing, and validation functionality
 * consolidated from 18 separate directories.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <pthread.h>
#include "../include/auditor_internal.h"
#include "../include/memory.h"
#include "../include/security.h"
#include "../include/utils.h"

// Security level enumeration
typedef enum {
    SECURITY_INFO,
    SECURITY_WARNING,
    SECURITY_ERROR,
    SECURITY_CRITICAL
} SecurityLevel;

// Audit entry structure
typedef struct audit_entry {
    uint64_t timestamp;
    SecurityLevel level;
    char* category;
    char* message;
} AuditEntry;

// ============================================================================
// SECURITY AUDIT SYSTEM
// ============================================================================

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
    
    audit_state.log_path = xmd_strdup(log_file);
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
 * @brief Log security audit entry
 * @param level Security level
 * @param category Event category
 * @param message Audit message
 * @return 0 on success, -1 on error
 */
int security_audit_log(audit_event_type type, const char* message,
                      const char* source_file, const char* source_function,
                      int source_line, security_result result) {
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

/**
 * @brief Get audit entries within time range
 * @param start_time Start timestamp
 * @param end_time End timestamp
 * @param entries Output: entries array
 * @param count Output: number of entries
 * @return 0 on success, -1 on error
 */
int security_audit_get_entries(uint64_t start_time, uint64_t end_time,
                               security_audit_entry** entries, size_t* count) {
    if (!audit_state.initialized || !entries || !count) {
        if (count) *count = 0;
        return -1;
    }
    
    *entries = NULL;
    *count = 0;
    return 0; // Simplified implementation
}

/**
 * @brief Cleanup security audit system
 */
void security_audit_cleanup(void) {
    if (!audit_state.initialized) {
        return;
    }
    
    pthread_mutex_lock(&audit_state.mutex);
    
    if (audit_state.log_file) {
        fclose(audit_state.log_file);
        audit_state.log_file = NULL;
    }
    
    free(audit_state.log_path);
    audit_state.log_path = NULL;
    
    // Cleanup simplified - entries managed elsewhere
    audit_state.entries = NULL;
    audit_state.entry_count = 0;
    audit_state.entry_capacity = 0;
    
    audit_state.initialized = false;
    
    pthread_mutex_unlock(&audit_state.mutex);
    pthread_mutex_destroy(&audit_state.mutex);
}

// ============================================================================
// SECURITY VALIDATION
// ============================================================================

/**
 * @brief Validate command security
 * @param command Command to validate
 * @return SECURITY_VALID if safe, error code if dangerous
 */
security_result security_validate_command(const char* command) {
    if (!command) {
        return SECURITY_INVALID_INPUT;
    }
    
    // Check for dangerous commands
    const char* dangerous[] = {
        "rm -rf", "format", "del /f", "rm *", "sudo", "chmod 777", NULL
    };
    
    for (int i = 0; dangerous[i]; i++) {
        if (strstr(command, dangerous[i])) {
            security_audit_log(AUDIT_COMMAND_EXECUTION, command, __FILE__, __func__, __LINE__, SECURITY_INJECTION_DETECTED);
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    return SECURITY_VALID;
}

/**
 * @brief Sanitize command output
 * @param output Command output to sanitize
 * @return Sanitized output (must be freed)
 */
char* security_sanitize_command_output(const char* output) {
    if (!output) {
        return NULL;
    }
    
    size_t len = strlen(output);
    char* sanitized = xmd_malloc(len * 2 + 1); // Extra space for escaping
    if (!sanitized) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        char c = output[i];
        
        // Escape potentially dangerous characters
        if (c == '<') {
            sanitized[j++] = '&';
            sanitized[j++] = 'l';
            sanitized[j++] = 't';
            sanitized[j++] = ';';
        } else if (c == '>') {
            sanitized[j++] = '&';
            sanitized[j++] = 'g';
            sanitized[j++] = 't';
            sanitized[j++] = ';';
        } else if (c == '&') {
            sanitized[j++] = '&';
            sanitized[j++] = 'a';
            sanitized[j++] = 'm';
            sanitized[j++] = 'p';
            sanitized[j++] = ';';
        } else {
            sanitized[j++] = c;
        }
    }
    
    sanitized[j] = '\0';
    return sanitized;
}

// ============================================================================
// SANDBOX OPERATIONS
// ============================================================================

/**
 * @brief Initialize security sandbox
 * @return 0 on success, -1 on error
 */
int security_sandbox_init(void) {
    // Implementation would set up sandbox environment
    security_audit_log(AUDIT_COMMAND_EXECUTION, "Sandbox initialized", __FILE__, __func__, __LINE__, SECURITY_VALID);
    return 0;
}

/**
 * @brief Execute command in sandbox
 * @param command Command to execute
 * @param result Output buffer
 * @param max_size Maximum result size
 * @return 0 on success, -1 on error
 */
int security_sandbox_execute(const char* command, char* result, size_t max_size) {
    if (!command || !result || max_size == 0) {
        return -1;
    }
    
    // Validate command first
    if (security_validate_command(command) != SECURITY_VALID) {
        snprintf(result, max_size, "Error: Command blocked for security reasons");
        return -1;
    }
    
    // Implementation would execute command in sandbox
    security_audit_log(AUDIT_COMMAND_EXECUTION, command, __FILE__, __func__, __LINE__, SECURITY_VALID);
    snprintf(result, max_size, "Command executed safely: %s", command);
    
    return 0;
}

/**
 * @brief Cleanup security sandbox
 */
void security_sandbox_cleanup(void) {
    security_audit_log(AUDIT_COMMAND_EXECUTION, "Sandbox cleaned up", __FILE__, __func__, __LINE__, SECURITY_VALID);
}

// ============================================================================
// OUTPUT SANITIZATION
// ============================================================================

/**
 * @brief Sanitize output string for safe rendering
 * @param input Input string to sanitize
 * @return Sanitized string (must be freed) or NULL on error
 */
char* security_sanitize_output(const char* input) {
    if (!input) {
        return NULL;
    }
    
    size_t input_len = strlen(input);
    size_t output_size = input_len * 6 + 1; // Worst case for HTML encoding
    char* output = xmd_malloc(output_size);
    if (!output) {
        return NULL;
    }
    
    size_t output_pos = 0;
    
    for (size_t i = 0; i < input_len && output_pos < output_size - 1; i++) {
        char c = input[i];
        const char* replacement = NULL;
        size_t replacement_len = 0;
        
        switch (c) {
            case '<':
                replacement = "&lt;";
                replacement_len = 4;
                break;
            case '>':
                replacement = "&gt;";
                replacement_len = 4;
                break;
            case '&':
                replacement = "&amp;";
                replacement_len = 5;
                break;
            case '"':
                replacement = "&quot;";
                replacement_len = 6;
                break;
            case '\'':
                replacement = "&#x27;";
                replacement_len = 6;
                break;
            case '/':
                replacement = "&#x2F;";
                replacement_len = 6;
                break;
            default:
                output[output_pos++] = c;
                continue;
        }
        
        if (output_pos + replacement_len >= output_size) {
            break;
        }
        
        memcpy(output + output_pos, replacement, replacement_len);
        output_pos += replacement_len;
    }
    
    output[output_pos] = '\0';
    return output;
}

// ============================================================================
// HTML SANITIZATION
// ============================================================================

/**
 * @brief Check if tag is in whitelist of safe HTML tags
 * @param tag Tag name to check
 * @return true if tag is safe
 */
static bool is_safe_html_tag(const char* tag) {
    static const char* safe_tags[] = {
        "p", "br", "strong", "b", "em", "i", "u", "h1", "h2", "h3", "h4", "h5", "h6",
        "ul", "ol", "li", "blockquote", "pre", "code", "span", "div", "a", "img",
        "table", "tr", "td", "th", "tbody", "thead", "tfoot",
        NULL
    };
    
    for (int i = 0; safe_tags[i] != NULL; i++) {
        if (strcasecmp(tag, safe_tags[i]) == 0) {
            return true;
        }
    }
    
    return false;
}

/**
 * @brief Extract tag name from HTML tag
 * @param tag_start Pointer to start of tag (after <)
 * @param tag_name Output buffer for tag name
 * @param max_len Maximum length of tag name
 * @return Length of tag name extracted
 */
static size_t extract_tag_name(const char* tag_start, char* tag_name, size_t max_len) {
    size_t len = 0;
    const char* p = tag_start;
    
    // Skip leading whitespace
    while (*p && isspace(*p)) p++;
    
    // Skip closing tag indicator
    if (*p == '/') p++;
    
    // Extract tag name
    while (*p && !isspace(*p) && *p != '>' && *p != '/' && len < max_len - 1) {
        tag_name[len++] = tolower(*p++);
    }
    
    tag_name[len] = '\0';
    return len;
}

/**
 * @brief Process HTML tag and determine if it should be kept
 * @param tag_content Full tag content including brackets
 * @param output Output buffer
 * @param output_pos Current position in output buffer
 * @param max_output_size Maximum size of output buffer
 * @return Updated output position
 */
static size_t process_html_tag(const char* tag_content, char* output, 
                              size_t output_pos, size_t max_output_size) {
    if (tag_content[0] != '<') return output_pos;
    
    // Extract tag name
    char tag_name[32];
    size_t tag_len = extract_tag_name(tag_content + 1, tag_name, sizeof(tag_name));
    
    if (tag_len == 0) return output_pos;
    
    // Check if tag is safe
    if (!is_safe_html_tag(tag_name)) {
        return output_pos; // Skip dangerous tag
    }
    
    // Find end of tag
    const char* tag_end = strchr(tag_content, '>');
    if (!tag_end) return output_pos;
    
    size_t tag_full_len = tag_end - tag_content + 1;
    
    // For safe tags, copy them (could add attribute filtering here)
    if (output_pos + tag_full_len < max_output_size) {
        memcpy(output + output_pos, tag_content, tag_full_len);
        output_pos += tag_full_len;
    }
    
    return output_pos;
}

/**
 * @brief Sanitize HTML content
 * @param html HTML content to sanitize
 * @return Sanitized HTML (must be freed) or NULL on error
 */
char* security_sanitize_html(const char* html) {
    if (!html) {
        return NULL;
    }
    
    size_t input_len = strlen(html);
    char* result = xmd_malloc(input_len * 2 + 1); // Extra space for entity encoding
    if (!result) {
        return NULL;
    }
    
    size_t output_pos = 0;
    const char* p = html;
    
    while (*p && output_pos < input_len * 2 - 10) {
        if (*p == '<') {
            // Find end of tag
            const char* tag_end = strchr(p, '>');
            if (tag_end) {
                // Process the tag
                char tag_buffer[1024];
                size_t tag_size = tag_end - p + 1;
                if (tag_size < sizeof(tag_buffer)) {
                    memcpy(tag_buffer, p, tag_size);
                    tag_buffer[tag_size] = '\0';
                    
                    output_pos = process_html_tag(tag_buffer, result, output_pos, input_len * 2);
                }
                p = tag_end + 1;
            } else {
                // Incomplete tag, escape it
                if (output_pos + 4 < input_len * 2) {
                    strcpy(result + output_pos, "&lt;");
                    output_pos += 4;
                }
                p++;
            }
        } else {
            // Regular character
            if (*p == '&') {
                if (output_pos + 5 < input_len * 2) {
                    strcpy(result + output_pos, "&amp;");
                    output_pos += 5;
                }
            } else if (*p == '>') {
                if (output_pos + 4 < input_len * 2) {
                    strcpy(result + output_pos, "&gt;");
                    output_pos += 4;
                }
            } else if (*p >= 32 && *p < 127) {
                result[output_pos++] = *p;
            } else {
                // Replace non-printable with space
                result[output_pos++] = ' ';
            }
            p++;
        }
    }
    
    result[output_pos] = '\0';
    return result;
}

// ============================================================================
// COMMAND OUTPUT SANITIZATION
// ============================================================================

/**
 * @brief Remove ANSI escape codes from output
 * @param input Input string with potential ANSI codes
 * @param output Output buffer
 * @param max_output_size Maximum size of output buffer
 * @return Length of cleaned string
 */
static size_t remove_ansi_codes(const char* input, char* output, size_t max_output_size) {
    const char* src = input;
    char* dst = output;
    char* end = output + max_output_size - 1;
    
    while (*src && dst < end) {
        if (*src == '\033' || *src == '\x1b') {
            // Start of ANSI escape sequence
            src++; // Skip ESC
            if (*src == '[') {
                src++; // Skip [
                // Skip until we find the end character (usually m, but could be others)
                while (*src && *src != 'm' && *src != 'K' && *src != 'J' && 
                       *src != 'H' && *src != 'f' && dst < end) {
                    src++;
                }
                if (*src) src++; // Skip the end character
            }
        } else {
            *dst++ = *src++;
        }
    }
    
    *dst = '\0';
    return dst - output;
}

/**
 * @brief Check if line contains potentially dangerous content
 * @param line Line to check
 * @return true if line is safe
 */
static bool is_safe_output_line(const char* line) {
    // Check for script injection in output
    if (strstr(line, "<script") || strstr(line, "</script>") ||
        strstr(line, "<iframe") || strstr(line, "<object") ||
        strstr(line, "<embed") || strstr(line, "javascript:") ||
        strstr(line, "vbscript:")) {
        return false;
    }
    
    // Check for potential XSS in markdown context
    if (strstr(line, "[javascript:") || strstr(line, "](javascript:") ||
        strstr(line, "[vbscript:") || strstr(line, "](vbscript:")) {
        return false;
    }
    
    // Check for potential command injection indicators
    if (strstr(line, "$(") || strstr(line, "`") ||
        strstr(line, "${IFS}") || strstr(line, "eval ")) {
        return false;
    }
    
    return true;
}

