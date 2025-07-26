/**
 * @file dependency_node_new.c
 * @brief Create a new dependency node
 * @author XMD Team
 */

#include "../../../../include/dependency_graph_internal.h"

/**
 * @brief Create a new dependency node
 * @param module Module for this node
 * @return New dependency node or NULL on error
 */
DependencyNode* dependency_node_new(Module* module) {
    if (!module) {
        return NULL;
    }
    
    DependencyNode* node = malloc(sizeof(DependencyNode));
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