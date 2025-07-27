#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file parse_command_args.c
 * @brief Parse command into arguments
 * @author XMD Team
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/executor_internal.h"

/**
 * @brief Parse command into arguments
 * @param command Command string
 * @param args Array to store arguments (must be freed)
 * @return Number of arguments
 */
int parse_command_args(const char* command, char*** args) {
    if (!command || !args) {
        return -1;
    }
    
    // Simple parsing - split on spaces (doesn't handle quotes properly)
    // This is a security limitation but keeps the implementation simple
    char* command_copy = strdup(command);
    if (!command_copy) {
        return -1;
    }
    
    int argc = 0;
    char* token = strtok(command_copy, " \t\n");
    char** argv = NULL;
    
    while (token) {
        argv = realloc(argv, (argc + 1) * sizeof(char*));
        if (!argv) {
            free(command_copy);
            return -1;
        }
        
        argv[argc] = strdup(token);
        argc++;
        token = strtok(NULL, " \t\n");
    }
    
    // NULL-terminate the array
    argv = realloc(argv, (argc + 1) * sizeof(char*));
    if (argv) {
        argv[argc] = NULL;
    }
    
    free(command_copy);
    *args = argv;
    return argc;
}