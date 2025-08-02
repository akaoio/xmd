/**
 * @file dependency_graph_find_node.c
 * @brief Find node by module name
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency graph subsystem
 */

#include <string.h>
#include "../../../../include/dependency.h"
/**
 * @brief Find node by module name
 * @param graph Dependency graph
 * @param module_name Module name to find
 * @return Dependency node or NULL if not found
 */
DependencyNode* dependency_graph_find_node(DependencyGraph* graph, const char* module_name) {
    if (!graph || !module_name) {
        return NULL;
    }
    
    for (size_t i = 0; i < graph->node_count; i++) {
        if (graph->nodes[i] && graph->nodes[i]->module && 
            strcmp(graph->nodes[i]->module->name, module_name) == 0) {
            return graph->nodes[i];
        }
    }
    
    return NULL;
}
