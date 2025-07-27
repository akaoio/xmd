/**
 * @file formatter.c
 * @brief Output formatter creation function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/output.h"

/**
 * @brief Create a new output formatter
 * @return New output formatter or NULL on error
 */
OutputFormatter* output_formatter_new(void) {
    OutputFormatter* formatter = malloc(sizeof(OutputFormatter));
    if (!formatter) {
        return NULL;
    }
    
    formatter->last_error = NULL;
    
    return formatter;
}
