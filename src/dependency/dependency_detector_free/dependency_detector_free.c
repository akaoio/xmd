/**
 * @file dependency_detector_free.c
 * @brief Dependency detector cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/dependency.h"

/**
 * @brief Free a dependency detector
 * @param detector Detector to free
 */
void dependency_detector_free(DependencyDetector* detector) {
    if (!detector) {
        return;
    }
    
    // Free cycle path
    for (size_t i = 0; i < detector->cycle_path_count; i++) {
        free(detector->cycle_path[i]);
    }
    free(detector->cycle_path);
    
    free(detector->last_error);
    free(detector);
}