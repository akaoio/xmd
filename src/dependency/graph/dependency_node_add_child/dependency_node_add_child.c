/**
 * @file dependency_node_add_child.c
 * @brief Add dependency to node
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Add dependency to node
 * @param node Parent node
 * @param dependency_node Child dependency node
 * @return ModuleResult indicating success/failure
 */
int dependency_node_add_child(DependencyNode* node, DependencyNode* dependency_node) {
    if (!node || !dependency_node) {
        return MODULE_ERROR;
    }
    
    // Check if we need to expand capacity
    if (node->child_count >= node->child_capacity) {
        size_t new_capacity = node->child_capacity == 0 ? 4 : node->child_capacity * 2;
        DependencyNode** new_children = realloc(node->children, 
                                               new_capacity * sizeof(DependencyNode*));
        if (!new_children) {
            return MODULE_ERROR;
        }
        
        node->children = new_children;
        node->child_capacity = new_capacity;
    }
    
    node->children[node->child_count] = dependency_node;
    node->child_count++;
    
    return MODULE_SUCCESS;
}