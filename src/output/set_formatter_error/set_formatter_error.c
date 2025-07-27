#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file set_formatter_error.c
 * @brief Output formatter error setting function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/output.h"

/**
 * @brief Set error message in formatter
 * @param formatter Output formatter
 * @param message Error message
 */
void set_formatter_error(OutputFormatter* formatter, const char* message) {
    if (!formatter || !message) {
        return;
    }
    
    free(formatter->last_error);
    formatter->last_error = strdup(message);
}