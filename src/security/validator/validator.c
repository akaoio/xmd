/**
 * @file validator.c
 * @brief Input validation for security threats
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/security.h"

/**
 * @brief Validate input string for security threats
 * @param input Input string to validate
 * @param max_length Maximum allowed length
 * @return Security validation result
 */
security_result security_validate_input(const char* input, size_t max_length) {
    if (!input) {
        return SECURITY_INVALID_INPUT;
    }
    
    size_t length = strlen(input);
    if (length > max_length) {
        return SECURITY_RESOURCE_LIMIT;
    }
    
    // Check for SQL injection patterns
    const char* sql_patterns[] = {
        "' drop",
        "'; drop",
        "' delete",
        "'; delete",
        "' insert",
        "'; insert",
        "' update",
        "'; update",
        "' create",
        "'; create",
        "' alter",
        "'; alter",
        "union select",
        "union all select",
        "' or '1'='1",
        "' or 1=1",
        "admin'--",
        "admin'/*",
        NULL
    };
    
    // Check for XSS patterns
    const char* xss_patterns[] = {
        "<script",
        "</script>",
        "javascript:",
        "vbscript:",
        "onload=",
        "onerror=",
        "onclick=",
        "onmouseover=",
        "eval(",
        "expression(",
        NULL
    };
    
    // Check for command injection patterns
    const char* cmd_patterns[] = {
        "$(rm",
        "$(cat",
        "$(wget",
        "$(curl",
        "${IFS}",
        "`rm",
        "`cat",
        "`wget",
        "`curl",
        NULL
    };
    
    // Convert to lowercase for case-insensitive matching
    char* lower_input = malloc(length + 1);
    if (!lower_input) {
        return SECURITY_INVALID_INPUT;
    }
    
    for (size_t i = 0; i <= length; i++) {
        lower_input[i] = tolower(input[i]);
    }
    
    // Check SQL injection patterns
    for (int i = 0; sql_patterns[i]; i++) {
        if (strstr(lower_input, sql_patterns[i])) {
            free(lower_input);
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    // Check XSS patterns
    for (int i = 0; xss_patterns[i]; i++) {
        if (strstr(lower_input, xss_patterns[i])) {
            free(lower_input);
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    // Check command injection patterns (both original and lowercase)
    for (int i = 0; cmd_patterns[i]; i++) {
        if (strstr(lower_input, cmd_patterns[i]) || strstr(input, cmd_patterns[i])) {
            free(lower_input);
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    free(lower_input);
    return SECURITY_VALID;
}

/**
 * @brief Validate command for injection attacks
 * @param command Command string to validate
 * @return Security validation result
 */
security_result security_validate_command(const char* command) {
    if (!command) {
        return SECURITY_INVALID_INPUT;
    }
    
    if (strlen(command) == 0) {
        return SECURITY_INVALID_INPUT;
    }
    
    // Check for dangerous/destructive commands (injection category)
    const char* destructive_commands[] = {
        "rm -rf",
        "dd if=",
        "mkfs",
        "fdisk",
        NULL
    };
    
    // Check for privilege escalation commands (permission category)
    const char* privilege_commands[] = {
        "sudo",
        "su ",
        "chmod 777",
        "chmod +x",
        "chown",
        "passwd",
        "/etc/passwd",
        "/etc/shadow",
        NULL
    };
    
    // Check for network commands (injection category)
    const char* network_commands[] = {
        "wget",
        "curl",
        "nc ",
        "netcat",
        "telnet",
        "ssh",
        "scp",
        "rsync",
        "mount",
        "umount",
        NULL
    };
    
    // Check for command injection operators
    const char* injection_operators[] = {
        ";",
        "&&",
        "||",
        "|",
        "`",
        "$(",
        "${",
        ">",
        ">>",
        "<",
        "<<",
        NULL
    };
    
    // Convert to lowercase for matching
    size_t length = strlen(command);
    char* lower_command = malloc(length + 1);
    if (!lower_command) {
        return SECURITY_INVALID_INPUT;
    }
    
    for (size_t i = 0; i <= length; i++) {
        lower_command[i] = tolower(command[i]);
    }
    
    // Check for destructive commands first (injection)
    for (int i = 0; destructive_commands[i]; i++) {
        if (strstr(lower_command, destructive_commands[i])) {
            free(lower_command);
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    // Check for network commands (injection)
    for (int i = 0; network_commands[i]; i++) {
        if (strstr(lower_command, network_commands[i])) {
            free(lower_command);
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    // Check for privilege escalation commands (permission)
    for (int i = 0; privilege_commands[i]; i++) {
        if (strstr(lower_command, privilege_commands[i])) {
            free(lower_command);
            return SECURITY_PERMISSION_DENIED;
        }
    }
    
    // Check for injection operators
    for (int i = 0; injection_operators[i]; i++) {
        if (strstr(command, injection_operators[i])) {
            free(lower_command);
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    free(lower_command);
    return SECURITY_VALID;
}

/**
 * @brief Validate file path for traversal attacks
 * @param path File path to validate
 * @param allowed_base Base directory that must contain the path
 * @return Security validation result
 */
security_result security_validate_path(const char* path, const char* allowed_base) {
    if (!path || !allowed_base) {
        return SECURITY_INVALID_INPUT;
    }
    
    if (strlen(path) == 0 || strlen(allowed_base) == 0) {
        return SECURITY_INVALID_INPUT;
    }
    
    // Check for path traversal patterns
    if (strstr(path, "../") || strstr(path, "..\\") || 
        strstr(path, "/..") || strstr(path, "\\..") ||
        strcmp(path, "..") == 0) {
        return SECURITY_PATH_TRAVERSAL;
    }
    
    // Resolve absolute paths
    char resolved_path[4096];
    char resolved_base[4096];
    
    if (realpath(allowed_base, resolved_base) == NULL) {
        // If base doesn't exist, use as-is for relative comparison
        strncpy(resolved_base, allowed_base, sizeof(resolved_base) - 1);
        resolved_base[sizeof(resolved_base) - 1] = '\0';
    }
    
    // Handle relative paths by prepending base
    if (path[0] != '/') {
        snprintf(resolved_path, sizeof(resolved_path), "%s/%s", resolved_base, path);
    } else {
        strncpy(resolved_path, path, sizeof(resolved_path) - 1);
        resolved_path[sizeof(resolved_path) - 1] = '\0';
    }
    
    // Check if resolved path starts with the base path
    size_t base_len = strlen(resolved_base);
    if (strncmp(resolved_path, resolved_base, base_len) != 0) {
        return SECURITY_PATH_TRAVERSAL;
    }
    
    // Ensure there's no path traversal in the resolved path
    if (strstr(resolved_path, "/../") || strstr(resolved_path, "/./")) {
        return SECURITY_PATH_TRAVERSAL;
    }
    
    return SECURITY_VALID;
}
