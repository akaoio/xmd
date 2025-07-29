/**
 * @file xmd_global_import_tracker.c
 * @brief Global import tracker for watch mode
 * @author XMD Team
 * @date 2025-07-29
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include "../../include/import_tracker.h"

// Global import tracker instance (only used in watch mode)
static import_tracker_t* g_watch_import_tracker = NULL;

/**
 * @brief Set the global import tracker for watch mode
 * @param tracker Import tracker instance (can be NULL)
 */
void xmd_set_global_import_tracker(import_tracker_t* tracker) {
    g_watch_import_tracker = tracker;
}

/**
 * @brief Get the global import tracker
 * @return Import tracker instance or NULL
 */
import_tracker_t* xmd_get_global_import_tracker(void) {
    return g_watch_import_tracker;
}

/**
 * @brief Check if we're in watch mode (import tracker is set)
 * @return true if in watch mode, false otherwise
 */
bool xmd_is_watch_mode(void) {
    return g_watch_import_tracker != NULL;
}