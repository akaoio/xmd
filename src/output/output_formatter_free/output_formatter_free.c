/**
 * @file output_formatter_free.c
 * @brief Output formatter cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/output.h"

/**
 * @brief Free an output formatter
 * @param formatter Formatter to free
 */
void output_formatter_free(OutputFormatter* formatter) {
    if (!formatter) {
        return;
    }
    
    free(formatter->last_error);
    free(formatter);
}