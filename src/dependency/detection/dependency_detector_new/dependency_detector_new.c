/**
 * @file dependency_detector_new.c
 * @brief Create a new dependency detector
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency detection subsystem
 */

#include <stdlib.h>
#include "../../../../include/dependency.h"
#include "../../../../include/utils.h"
#include "../../../../src/utils/common/common_macros.h"
/**
 * @brief Create a new dependency detector
 * @param graph Dependency graph to attach
 * @return New dependency detector or NULL on error
 */
DependencyDetector* dependency_detector_new(DependencyGraph* graph) {
    XMD_CREATE_VALIDATED(detector, DependencyDetector, sizeof(DependencyDetector), NULL);
    
    detector->graph = graph;
    detector->cycle_path = NULL;
    detector->cycle_path_count = 0;
    
    if (!detector->graph) {
        XMD_FREE_SAFE(detector);
        return NULL;
    }
    
    return detector;
}
