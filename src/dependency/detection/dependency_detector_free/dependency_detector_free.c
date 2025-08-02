/**
 * @file dependency_detector_free.c
 * @brief Free a dependency detector
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency detection subsystem
 */

#include <stdlib.h>
#include "../../../../include/dependency.h"

// Forward declaration
void dependency_graph_free(DependencyGraph* graph);
/**
 * @brief Free a dependency detector
 * @param detector Detector to free
 */
void dependency_detector_free(DependencyDetector* detector) {
    if (!detector) {
        return;
    }
    
    dependency_graph_free(detector->graph);
    free(detector->cycle_path);
    free(detector);
}
