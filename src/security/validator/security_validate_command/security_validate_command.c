/**
 * @file security_validate_command.c
 * @brief Validate command for injection attacks
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../../include/security.h"

/**
 * @brief Check if command contains dangerous patterns
 * @param command Command string to check
 * @return true if dangerous command detected
 */
static bool is_dangerous_command(const char* command) {
    static const char* dangerous_commands[] = {
        "rm -rf",
        "sudo",
        "su ",
        "chmod 777",
        "chown",
        "passwd",
        "useradd",
        "userdel",
        "usermod",
        "deluser",
        "adduser",
        "mkfs",
        "fdisk",
        "mount",
        "umount",
        "iptables",
        "ifconfig",
        "route",
        "/etc/passwd",
        "/etc/shadow",
        "/etc/sudoers",
        "wget",
        "curl",
        "nc ",
        "netcat",
        "telnet",
        "ssh",
        "scp",
        "rsync",
        NULL
    };
    
    char* lower_command = malloc(strlen(command) + 1);
    if (!lower_command) return false;
    
    for (size_t i = 0; command[i]; i++) {
        lower_command[i] = tolower(command[i]);
    }
    lower_command[strlen(command)] = '\0';
    
    bool found = false;
    for (int i = 0; dangerous_commands[i] != NULL; i++) {
        if (strstr(lower_command, dangerous_commands[i])) {
            found = true;
            break;
        }
    }
    
    free(lower_command);
    return found;
}

/**
 * @brief Check if pipe usage is safe
 * @param command Command string to check
 * @return true if pipe is safe
 */
static bool is_safe_pipe(const char* command) {
    // Safe commands that can be piped to
    static const char* safe_pipe_targets[] = {
        "head",
        "tail",
        "grep",
        "sort",
        "uniq",
        "wc",
        "cut",
        "awk",
        "sed",
        NULL
    };
    
    // Check if the pipe is to a safe command
    const char* pipe_pos = strstr(command, " | ");
    if (pipe_pos) {
        // Skip the " | " part
        const char* cmd_after_pipe = pipe_pos + 3;
        
        // Check each safe command
        for (int i = 0; safe_pipe_targets[i] != NULL; i++) {
            const char* safe_cmd = safe_pipe_targets[i];
            size_t cmd_len = strlen(safe_cmd);
            
            // Check if it starts with the safe command
            if (strncmp(cmd_after_pipe, safe_cmd, cmd_len) == 0) {
                // Make sure it's followed by space, dash, or end of string (including trailing spaces)
                char next_char = cmd_after_pipe[cmd_len];
                if (next_char == '\0' || next_char == ' ' || next_char == '-') {
                    return true;
                }
            }
        }
    }
    
    return false;
}

/**
 * @brief Check if command contains injection patterns
 * @param command Command string to check
 * @return true if injection detected
 */
static bool contains_command_injection(const char* command) {
    // Check for command chaining
    if (strstr(command, "; ") || strstr(command, "&&") || 
        strstr(command, "||")) {
        return true;
    }
    
    // Check for pipes, but allow safe ones
    if (strstr(command, " | ") && !is_safe_pipe(command)) {
        return true;
    }
    
    // Check for command substitution
    if (strstr(command, "`") || strstr(command, "$(")) {
        return true;
    }
    
    // Check for redirection that could be dangerous
    if (strstr(command, "> /") || strstr(command, ">> /")) {
        return true;
    }
    
    return false;
}

/**
 * @brief Check if command is in whitelist of safe commands
 * @param command Command string to check
 * @return true if command is safe
 */
static bool is_safe_command(const char* command) {
    static const char* safe_commands[] = {
        "echo",
        "date",
        "ls",
        "pwd",
        "whoami",
        "id",
        "uptime",
        "uname",
        "hostname",
        "cat /proc/version",
        "ps aux",
        "df -h",
        "free -h",
        "head",
        "tail",
        "grep",
        "wc",
        "sort",
        "uniq",
        "cut",
        "awk",
        "sed",
        "find",
        NULL
    };
    
    // Extract just the command name (first word)
    char* command_copy = strdup(command);
    if (!command_copy) return false;
    
    char* first_word = strtok(command_copy, " \t\n");
    if (!first_word) {
        free(command_copy);
        return false;
    }
    
    bool is_safe = false;
    for (int i = 0; safe_commands[i] != NULL; i++) {
        if (strcmp(first_word, safe_commands[i]) == 0) {
            is_safe = true;
            break;
        }
    }
    
    free(command_copy);
    return is_safe;
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
    
    // Empty command is invalid
    if (strlen(command) == 0) {
        return SECURITY_INVALID_INPUT;
    }
    
    // DEBUG: Log command being validated
    if (getenv("XMD_DEBUG_SECURITY")) {
        fprintf(stderr, "DEBUG security_validate_command: '%s'\n", command);
    }
    
    // Check for command injection patterns
    if (contains_command_injection(command)) {
        return SECURITY_INJECTION_DETECTED;
    }
    
    // Check for dangerous commands first
    if (is_dangerous_command(command)) {
        return SECURITY_PERMISSION_DENIED;
    }
    
    // If it's a safe command, allow it
    if (is_safe_command(command)) {
        return SECURITY_VALID;
    }
    
    // For any other command, be cautious and require explicit approval
    return SECURITY_PERMISSION_DENIED;
}