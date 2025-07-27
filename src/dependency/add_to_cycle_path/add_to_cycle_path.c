/**
 * @file add_to_cycle_path.c
 * @brief Add module to dependency cycle path function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/dependency.h"

/**
 * @brief Add module to cycle path
 * @param detector Dependency detector
 * @param module_name Module name to add
 * @return ModuleResult indicating success/failure
 */
int add_to_cycle_path(DependencyDetector* detector, const char* module_name) {
    if (!detector || !module_name) {
        return MODULE_ERROR;
    }
    
    char** new_path = realloc(detector->cycle_path, 
                             (detector->cycle_path_count + 1) * sizeof(char*));
    if (!new_path) {
        return MODULE_ERROR;
    }
    
    detector->cycle_path = new_path;
    detector->cycle_path[detector->cycle_path_count] = strdup(module_name);
    
    if (!detector->cycle_path[detector->cycle_path_count]) {
        return MODULE_ERROR;
    }
    
    detector->cycle_path_count++;
    return MODULE_SUCCESS;
}
