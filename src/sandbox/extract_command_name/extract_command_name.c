/**
 * @file extract_command_name.c
 * @brief Extract command name from full command string
 * @author XMD Team
 */

#include "../../../include/sandbox_internal.h"

/**
 * @brief Extract command name from full command string
 * @param command Full command string
 * @param cmd_name Buffer to store command name
 * @param cmd_name_size Size of command name buffer
 * @return 0 on success, -1 on error
 */
int extract_command_name(const char* command, char* cmd_name, size_t cmd_name_size) {
    if (!command || !cmd_name || cmd_name_size == 0) return -1;
    
    // Skip leading whitespace
    while (*command && (*command == ' ' || *command == '\t')) {
        command++;
    }
    
    // Copy command name until first space or end of string
    size_t i = 0;
    while (*command && *command != ' ' && *command != '\t' && i < cmd_name_size - 1) {
        cmd_name[i++] = *command++;
    }
    cmd_name[i] = '\0';
    
    return i > 0 ? 0 : -1;
}