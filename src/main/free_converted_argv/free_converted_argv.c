/**
 * @file free_converted_argv.c
 * @brief Converted argv cleanup function
 * @author XMD Team
 *
 * Implementation of converted argument vector cleanup for the XMD main module.
 */

#include "../../../include/main_internal.h"

/**
 * @brief Free converted argument vector
 * @param argc Argument count
 * @param argv Argument vector to free
 */
void free_converted_argv(int argc, char** argv) {
    for (int i = 1; i < argc; i++) { // Skip argv[0] as it's not duplicated
        free(argv[i]);
    }
    free(argv);
}