/**
 * @file dependency_node_free.c
 * @brief Free a dependency node
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency graph subsystem
 */

#include <stdlib.h>
#include "../../../../include/dependency.h"
/**
 * @brief Free a dependency node
 * @param node Node to free
 */
void dependency_node_free(DependencyNode* node) {
    if (!node) {
        return;
    }
    
    free(node->children);
    free(node);
}
