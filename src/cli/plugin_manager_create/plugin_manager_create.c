/**
 * @file plugin_manager_create.c
 * @brief Create plugin manager for CLI
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/cli.h"

/**
 * @brief Create a new plugin manager
 * @return New plugin manager or NULL on error
 */
plugin_manager* plugin_manager_create(void) {
    plugin_manager* manager = malloc(sizeof(plugin_manager));
    if (!manager) {
        return NULL;
    }
    
    // Initialize plugin manager
    manager->plugins = NULL;
    manager->plugin_count = 0;
    manager->plugin_capacity = 0;
    manager->initialized = false;
    
    return manager;
}