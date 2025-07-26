/**
 * @file free_command_args.c
 * @brief Free command arguments
 * @author XMD Team
 */

#include "../../../../include/executor_internal.h"

/**
 * @brief Free command arguments
 * @param args Arguments array
 * @param argc Number of arguments
 */
void free_command_args(char** args, int argc) {
    if (!args) {
        return;
    }
    
    for (int i = 0; i < argc; i++) {
        free(args[i]);
    }
    free(args);
}