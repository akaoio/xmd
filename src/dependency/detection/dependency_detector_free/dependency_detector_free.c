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
#include "../../../../utils/common/common_macros.h"

// Forward declaration
void dependency_graph_free(DependencyGraph* graph);
/**
 * @brief Free a dependency detector
 * @param detector Detector to free
 */
void dependency_detector_free(DependencyDetector* detector) {
    XMD_ENTRY_VALIDATE_VOID(detector);
    
    dependency_graph_free(detector->graph);
    XMD_FREE_SAFE(detector->cycle_path);
    XMD_FREE_SAFE(detector);
}
