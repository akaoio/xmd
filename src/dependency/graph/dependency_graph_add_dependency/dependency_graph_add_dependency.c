/**
 * @file dependency_graph_add_dependency.c
 * @brief Add dependency relationship
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency graph subsystem
 */

#include "../../../../include/dependency.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Add dependency relationship
 * @param graph Dependency graph
 * @param parent_name Parent module name
 * @param child_name Child dependency name
 * @return 0 on success, -1 on error
 */
int dependency_graph_add_dependency(DependencyGraph* graph, const char* parent_name, const char* child_name) {
    XMD_VALIDATE_PTRS(-1, graph, parent_name, child_name);
    
    DependencyNode* parent = dependency_graph_find_node(graph, parent_name);
    DependencyNode* child = dependency_graph_find_node(graph, child_name);
    
    if (!parent || !child) {
        return -1; // Both nodes must exist
    }
    
    return dependency_node_add_child(parent, child);
}
