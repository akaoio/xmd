/**
 * @file cleanup_cmd_variables.c
 * @brief Command variables cleanup function
 * @author XMD Team
 *
 * Implementation of command variables cleanup for the XMD main module.
 */

#include "../../../include/main_internal.h"

/**
 * @brief Cleanup command variables array
 * @param cmd_variables Array of command variables
 * @param var_count Number of variables
 */
void cleanup_cmd_variables(cmd_variable_t cmd_variables[], int var_count) {
    for (int i = 0; i < var_count; i++) {
        free(cmd_variables[i].key);
        free(cmd_variables[i].value);
    }
}