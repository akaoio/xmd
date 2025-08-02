/**
 * @file debugger_log.c
 * @brief Log debug messages with line info
 * 
 * This file contains ONLY the debugger_log function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/devtools_consolidated.c
 */

#include <stdio.h>
#include "../../../../include/devtools.h"
/**
 * @brief Log debug message with line info
 * @param file Source file name
 * @param line Line number
 * @param message Debug message
  * /
 */
void debugger_log(const char* file, int line, const char* message) {
    printf("[DEBUG] %s:%d - %s\n", file ? file : "unknown", line, message ? message : "");
}
