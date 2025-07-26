/**
 * @file dependency_node_free.c
 * @brief Free a dependency node
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Free a dependency node
 * @param node Node to free
 */
void dependency_node_free(DependencyNode* node) {
    if (!node) {
        return;
    }
    
    // Note: We don't free the module itself as it's owned by the registry
    free(node->children);
    free(node);
}