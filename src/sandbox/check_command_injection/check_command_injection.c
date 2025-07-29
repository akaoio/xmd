/**
 * @file check_command_injection.c
 * @brief Check for command injection vulnerabilities
 * @author XMD Team
 */

#include "../../../include/sandbox.h"
#include <string.h>
#include <ctype.h>

/**
 * @brief Check for command injection vulnerabilities
 * @param command Command to check
 * @return SANDBOX_SUCCESS if safe, SANDBOX_ERROR if dangerous
 */
int check_command_injection(const char* command) {
    if (!command) return SANDBOX_ERROR;
    
    // Check for dangerous characters and patterns
    const char* dangerous_chars = ";|&`$(){}[]<>";
    const char* dangerous_patterns[] = {
        "rm -rf",
        "sudo ",
        "chmod ",
        "chown ",
        "> /",
        ">> /",
        "< /",
        "| /",
        "$(", 
        "`",
        NULL
    };
    
    // Check for dangerous characters
    for (size_t i = 0; dangerous_chars[i]; i++) {
        if (strchr(command, dangerous_chars[i])) {
            return SANDBOX_ERROR;
        }
    }
    
    // Check for dangerous patterns
    for (int i = 0; dangerous_patterns[i]; i++) {
        if (strstr(command, dangerous_patterns[i])) {
            return SANDBOX_ERROR;
        }
    }
    
    return SANDBOX_SUCCESS;
}