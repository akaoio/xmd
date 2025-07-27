/**
 * @file clear_cycle_path.c
 * @brief Clear dependency cycle path function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/dependency.h"

/**
 * @brief Clear the current cycle path
 * @param detector Dependency detector
 */
void clear_cycle_path(DependencyDetector* detector) {
    if (!detector) {
        return;
    }
    
    for (size_t i = 0; i < detector->cycle_path_count; i++) {
        free(detector->cycle_path[i]);
    }
    free(detector->cycle_path);
    
    detector->cycle_path = NULL;
    detector->cycle_path_count = 0;
}