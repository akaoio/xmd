/**
 * @file security_validate_input.c
 * @brief Validate input string for security threats
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../../include/security.h"

/**
 * @brief Check if string contains SQL injection patterns
 * @param input Input string to check
 * @return true if injection detected
 */
static bool contains_sql_injection(const char* input) {
    static const char* sql_patterns[] = {
        "'; DROP",
        "'; DELETE",
        "'; INSERT",
        "'; UPDATE",
        "' OR '1'='1",
        "' OR 1=1",
        "' UNION ",
        "--",
        "/*",
        "*/",
        "xp_",
        "sp_",
        NULL
    };
    
    char* lower_input = malloc(strlen(input) + 1);
    if (!lower_input) return false;
    
    // Convert to lowercase for case-insensitive matching
    for (size_t i = 0; input[i]; i++) {
        lower_input[i] = tolower(input[i]);
    }
    lower_input[strlen(input)] = '\0';
    
    bool found = false;
    for (int i = 0; sql_patterns[i] != NULL; i++) {
        if (strstr(lower_input, sql_patterns[i])) {
            found = true;
            break;
        }
    }
    
    free(lower_input);
    return found;
}

/**
 * @brief Check if string contains XSS patterns
 * @param input Input string to check
 * @return true if XSS detected
 */
static bool contains_xss_injection(const char* input) {
    static const char* xss_patterns[] = {
        "<script",
        "</script>",
        "<iframe",
        "<object",
        "<embed",
        "javascript:",
        "vbscript:",
        "onload=",
        "onerror=",
        "onclick=",
        "onmouseover=",
        NULL
    };
    
    char* lower_input = malloc(strlen(input) + 1);
    if (!lower_input) return false;
    
    for (size_t i = 0; input[i]; i++) {
        lower_input[i] = tolower(input[i]);
    }
    lower_input[strlen(input)] = '\0';
    
    bool found = false;
    for (int i = 0; xss_patterns[i] != NULL; i++) {
        if (strstr(lower_input, xss_patterns[i])) {
            found = true;
            break;
        }
    }
    
    free(lower_input);
    return found;
}

/**
 * @brief Check if string contains shell injection patterns
 * @param input Input string to check
 * @return true if shell injection detected
 */
static bool contains_shell_injection(const char* input) {
    static const char* shell_patterns[] = {
        "$(rm",
        "${IFS}",
        "`rm",
        "rm -rf",
        "wget ",
        "curl ",
        "/etc/passwd",
        "/etc/shadow",
        "chmod ",
        "chown ",
        NULL
    };
    
    for (int i = 0; shell_patterns[i] != NULL; i++) {
        if (strstr(input, shell_patterns[i])) {
            return true;
        }
    }
    
    return false;
}

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
    
    // Check length limit
    if (length > max_length) {
        return SECURITY_RESOURCE_LIMIT;
    }
    
    // Check for null bytes
    for (size_t i = 0; i < length; i++) {
        if (input[i] == '\0' && i < length - 1) {
            return SECURITY_INJECTION_DETECTED;
        }
    }
    
    // Check for SQL injection
    if (contains_sql_injection(input)) {
        return SECURITY_INJECTION_DETECTED;
    }
    
    // Check for XSS injection
    if (contains_xss_injection(input)) {
        return SECURITY_INJECTION_DETECTED;
    }
    
    // Check for shell injection
    if (contains_shell_injection(input)) {
        return SECURITY_INJECTION_DETECTED;
    }
    
    return SECURITY_VALID;
}