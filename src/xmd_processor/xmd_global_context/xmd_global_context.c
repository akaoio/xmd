/**
 * @file xmd_global_context.c
 * @brief Global context for XMD processing
 * @author XMD Team
 * @date 2025-07-29
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Thread-local storage for current file path
static __thread char* g_current_file_path = NULL;

/**
 * @brief Set the current file path being processed
 * @param path File path (will be copied)
 */
void xmd_set_current_file_path(const char* path) {
    if (g_current_file_path) {
        free(g_current_file_path);
        g_current_file_path = NULL;
    }
    if (path) {
        g_current_file_path = strdup(path);
    }
}

/**
 * @brief Get the current file path being processed
 * @return Current file path or NULL
 */
const char* xmd_get_current_file_path(void) {
    return g_current_file_path;
}

/**
 * @brief Clear the current file path
 */
void xmd_clear_current_file_path(void) {
    if (g_current_file_path) {
        free(g_current_file_path);
        g_current_file_path = NULL;
    }
}