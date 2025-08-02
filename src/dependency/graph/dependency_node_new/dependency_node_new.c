/**
 * @file dependency_node_new.c
 * @brief Create a new dependency node
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of dependency graph subsystem
 */

#include "../../../../include/dependency.h"
#include "../../../../include/utils.h"
/**
 * @brief Create a new dependency node
 * @param module Module to wrap in node
 * @return New dependency node or NULL on error
 */
DependencyNode* dependency_node_new(Module* module) {
    if (!module) {
        return NULL;
    }
    
    DependencyNode* node = xmd_malloc(sizeof(DependencyNode));
    if (!node) {
        return NULL;
    }
    
    node->module = module;
    node->children = NULL;
    node->child_count = 0;
    node->child_capacity = 0;
    node->visit_state = 0; // White (unvisited)
    return node;
}
