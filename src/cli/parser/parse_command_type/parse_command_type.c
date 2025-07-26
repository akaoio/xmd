/**
 * @file parse_command_type.c
 * @brief Parse command type from string
 * @author XMD Team
 */

#include "../../../../include/parser_internal.h"

/**
 * @brief Parse command type from string
 * @param cmd_str Command string
 * @return Command type or -1 if invalid
 */
int parse_command_type(const char* cmd_str) {
    if (!cmd_str) {
        return -1;
    }
    
    if (strcmp(cmd_str, "process") == 0) {
        return CLI_CMD_PROCESS;
    } else if (strcmp(cmd_str, "watch") == 0) {
        return CLI_CMD_WATCH;
    } else if (strcmp(cmd_str, "validate") == 0) {
        return CLI_CMD_VALIDATE;
    } else if (strcmp(cmd_str, "config") == 0) {
        return CLI_CMD_CONFIG;
    } else if (strcmp(cmd_str, "help") == 0) {
        return CLI_CMD_HELP;
    } else if (strcmp(cmd_str, "version") == 0) {
        return CLI_CMD_VERSION;
    }
    
    return -1;
}