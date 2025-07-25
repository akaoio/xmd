/**
 * @file plugin.c
 * @brief Plugin loading and management system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/platform.h"
#include "../../../include/cli.h"

/**
 * @brief Create plugin manager
 * @return Plugin manager or NULL on error
 */
plugin_manager* plugin_manager_create(void) {
    plugin_manager* manager = calloc(1, sizeof(plugin_manager));
    if (!manager) {
        return NULL;
    }
    
    manager->plugin_capacity = 16; // Initial capacity
    manager->plugins = calloc(manager->plugin_capacity, sizeof(xmd_plugin*));
    if (!manager->plugins) {
        free(manager);
        return NULL;
    }
    
    manager->plugin_count = 0;
    manager->search_paths = NULL;
    manager->search_path_count = 0;
    
    return manager;
}

/**
 * @brief Resize plugin array if needed
 * @param manager Plugin manager
 * @return 0 on success, -1 on error
 */
static int resize_plugins_if_needed(plugin_manager* manager) {
    if (!manager) {
        return -1;
    }
    
    if (manager->plugin_count >= manager->plugin_capacity) {
        size_t new_capacity = manager->plugin_capacity * 2;
        xmd_plugin** new_plugins = realloc(manager->plugins, 
                                          new_capacity * sizeof(xmd_plugin*));
        if (!new_plugins) {
            return -1;
        }
        
        manager->plugins = new_plugins;
        manager->plugin_capacity = new_capacity;
        
        // Initialize new entries
        for (size_t i = manager->plugin_count; i < new_capacity; i++) {
            manager->plugins[i] = NULL;
        }
    }
    
    return 0;
}

/**
 * @brief Load plugin from path
 * @param manager Plugin manager
 * @param path Plugin path
 * @return 0 on success, -1 on error
 */
int plugin_load(plugin_manager* manager, const char* path) {
    if (!manager || !path) {
        return -1;
    }
    
    // Check if plugin is already loaded
    for (size_t i = 0; i < manager->plugin_count; i++) {
        if (manager->plugins[i] && manager->plugins[i]->path &&
            strcmp(manager->plugins[i]->path, path) == 0) {
            return 0; // Already loaded
        }
    }
    
    // Try to load the dynamic library
    xmd_library_t handle = xmd_library_load(path);
    if (!handle) {
        return -1; // Failed to load
    }
    
    // Look for required symbols
    plugin_init_func init_func = (plugin_init_func)xmd_library_symbol(handle, "plugin_init");
    plugin_cleanup_func cleanup_func = (plugin_cleanup_func)xmd_library_symbol(handle, "plugin_cleanup");
    plugin_process_func process_func = (plugin_process_func)xmd_library_symbol(handle, "plugin_process");
    
    if (!init_func || !cleanup_func || !process_func) {
        xmd_library_unload(handle);
        return -1; // Missing required functions
    }
    
    // Create plugin structure
    if (resize_plugins_if_needed(manager) != 0) {
        xmd_library_unload(handle);
        return -1;
    }
    
    xmd_plugin* plugin = calloc(1, sizeof(xmd_plugin));
    if (!plugin) {
        xmd_library_unload(handle);
        return -1;
    }
    
    plugin->path = strdup(path);
    plugin->handle = handle;
    plugin->init = init_func;
    plugin->cleanup = cleanup_func;
    plugin->process = process_func;
    plugin->loaded = false;
    
    // Extract plugin name from path
    const char* filename = strrchr(path, '/');
    if (filename) {
        filename++; // Skip the '/'
    } else {
        filename = path;
    }
    plugin->name = strdup(filename);
    
    // Initialize the plugin
    if (plugin->init() == 0) {
        plugin->loaded = true;
        manager->plugins[manager->plugin_count] = plugin;
        manager->plugin_count++;
        return 0;
    } else {
        // Initialization failed
        free(plugin->name);
        free(plugin->path);
        xmd_library_unload(handle);
        free(plugin);
        return -1;
    }
}

/**
 * @brief Find plugin by name
 * @param manager Plugin manager
 * @param name Plugin name
 * @return Plugin or NULL if not found
 */
static xmd_plugin* find_plugin(plugin_manager* manager, const char* name) {
    if (!manager || !name) {
        return NULL;
    }
    
    for (size_t i = 0; i < manager->plugin_count; i++) {
        if (manager->plugins[i] && manager->plugins[i]->name &&
            strcmp(manager->plugins[i]->name, name) == 0) {
            return manager->plugins[i];
        }
    }
    
    return NULL;
}

/**
 * @brief Unload plugin
 * @param manager Plugin manager
 * @param name Plugin name
 * @return 0 on success, -1 on error
 */
int plugin_unload(plugin_manager* manager, const char* name) {
    if (!manager || !name) {
        return -1;
    }
    
    for (size_t i = 0; i < manager->plugin_count; i++) {
        if (manager->plugins[i] && manager->plugins[i]->name &&
            strcmp(manager->plugins[i]->name, name) == 0) {
            
            xmd_plugin* plugin = manager->plugins[i];
            
            // Cleanup plugin
            if (plugin->loaded && plugin->cleanup) {
                plugin->cleanup();
            }
            
            // Close dynamic library
            if (plugin->handle) {
                xmd_library_unload(plugin->handle);
            }
            
            // Free plugin resources
            free(plugin->name);
            free(plugin->version);
            free(plugin->description);
            free(plugin->path);
            free(plugin);
            
            // Remove from array
            for (size_t j = i; j < manager->plugin_count - 1; j++) {
                manager->plugins[j] = manager->plugins[j + 1];
            }
            manager->plugin_count--;
            manager->plugins[manager->plugin_count] = NULL;
            
            return 0;
        }
    }
    
    return -1; // Plugin not found
}

/**
 * @brief List all loaded plugins
 * @param manager Plugin manager
 * @param plugins Output array of plugin names
 * @param count Output count of plugins
 * @return 0 on success, -1 on error
 */
int plugin_list(plugin_manager* manager, char*** plugins, size_t* count) {
    if (!manager || !plugins || !count) {
        return -1;
    }
    
    *count = manager->plugin_count;
    
    if (manager->plugin_count == 0) {
        *plugins = NULL;
        return 0;
    }
    
    *plugins = malloc(manager->plugin_count * sizeof(char*));
    if (!*plugins) {
        return -1;
    }
    
    for (size_t i = 0; i < manager->plugin_count; i++) {
        if (manager->plugins[i] && manager->plugins[i]->name) {
            (*plugins)[i] = strdup(manager->plugins[i]->name);
        } else {
            (*plugins)[i] = strdup("unknown");
        }
    }
    
    return 0;
}

/**
 * @brief Process input with plugin
 * @param manager Plugin manager
 * @param plugin_name Plugin name
 * @param input Input string
 * @param output Output string (must be freed)
 * @return 0 on success, -1 on error
 */
int plugin_process(plugin_manager* manager, const char* plugin_name, 
                   const char* input, char** output) {
    if (!manager || !plugin_name || !input || !output) {
        return -1;
    }
    
    xmd_plugin* plugin = find_plugin(manager, plugin_name);
    if (!plugin || !plugin->loaded || !plugin->process) {
        return -1;
    }
    
    return plugin->process(input, output);
}

/**
 * @brief Destroy plugin manager
 * @param manager Plugin manager
 */
void plugin_manager_destroy(plugin_manager* manager) {
    if (!manager) {
        return;
    }
    
    // Unload all plugins
    while (manager->plugin_count > 0) {
        xmd_plugin* plugin = manager->plugins[0];
        if (plugin && plugin->name) {
            plugin_unload(manager, plugin->name);
        } else {
            // Handle orphaned plugin
            manager->plugin_count--;
        }
    }
    
    // Free search paths
    for (size_t i = 0; i < manager->search_path_count; i++) {
        free(manager->search_paths[i]);
    }
    free(manager->search_paths);
    
    free(manager->plugins);
    free(manager);
}