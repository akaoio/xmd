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
#include "utils/common/common_macros.h"
/**
 * @brief Free a dependency node
 * @param node Node to free
 */
void dependency_node_free(DependencyNode* node) {
    XMD_ENTRY_VALIDATE_VOID(node);
    
    XMD_FREE_SAFE(node->children);
    XMD_FREE_SAFE(node);
}
