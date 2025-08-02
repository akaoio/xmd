/**
 * @file dependency_node_add_child.c
 * @brief Add child dependency to node
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency graph subsystem
 */

#include "../../../../include/dependency.h"
#include "../../../../include/utils.h"
/**
 * @brief Add child dependency to node
 * @param parent Parent node
 * @param child Child node to add
 * @return 0 on success, -1 on error
 */
int dependency_node_add_child(DependencyNode* parent, DependencyNode* child) {
    if (!parent || !child) {
        return -1;
    }
    
    // Check if we need to expand capacity
    if (parent->child_count >= parent->child_capacity) {
        size_t new_capacity = parent->child_capacity == 0 ? 4 : parent->child_capacity * 2;
        DependencyNode** new_children = xmd_realloc(parent->children, 
                                                    new_capacity * sizeof(DependencyNode*));
        if (!new_children) {
            return -1;
        }
        
        parent->children = new_children;
        parent->child_capacity = new_capacity;
    }
    
    parent->children[parent->child_count++] = child;
    return 0;
}
