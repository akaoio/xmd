/**
 * @file dependency_detector_new.c
 * @brief Dependency detector creation function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/dependency.h"

/**
 * @brief Create a new dependency detector
 * @param graph Dependency graph to analyze
 * @return New dependency detector or NULL on error
 */
DependencyDetector* dependency_detector_new(DependencyGraph* graph) {
    if (!graph) {
        return NULL;
    }
    
    DependencyDetector* detector = malloc(sizeof(DependencyDetector));
    if (!detector) {
        return NULL;
    }
    
    detector->graph = graph;
    detector->cycle_path = NULL;
    detector->cycle_path_count = 0;
    detector->last_error = NULL;
    
    return detector;
}