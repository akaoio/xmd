/**
 * @file normalize_path.c
 * @brief Normalize file paths by resolving . and .. components
 * @author XMD Team
 * @date 2025-07-30
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../../include/sandbox.h"

/**
 * @brief Normalize path (remove .. and . components)
 * @param path Input path
 * @return Normalized path (caller must free) or NULL on error
 */
char* normalize_path(const char* path) {
    if (!path || !*path) return strdup("");
    
    #ifdef DEBUG_NORMALIZE
    fprintf(stderr, "[DEBUG] normalize_path called with: '%s'\n", path);
    #endif
    
    // Allocate enough space for the normalized path (worst case is same as input)
    size_t path_len = strlen(path);
    char* normalized = malloc(path_len + 2);  // +2 for potential '/' and null terminator
    if (!normalized) return NULL;
    
    #ifdef DEBUG_NORMALIZE
    fprintf(stderr, "[DEBUG] allocated normalized buffer: %p\n", normalized);
    #endif
    
    char* components[256];
    int component_count = 0;
    
    // Copy path for tokenization
    char* path_copy = strdup(path);
    if (!path_copy) {
        free(normalized);
        return NULL;
    }
    
    #ifdef DEBUG_NORMALIZE
    fprintf(stderr, "[DEBUG] path_copy allocated: %p, content: '%s'\n", path_copy, path_copy);
    #endif
    
    // Split path into components
    char* token = strtok(path_copy, "/");
    int is_absolute = (path[0] == '/');
    
    while (token && component_count < 256) {
        if (strcmp(token, ".") == 0) {
            // Skip current directory references
            continue;
        } else if (strcmp(token, "..") == 0) {
            // Go up one directory if possible
            if (component_count > 0 && strcmp(components[component_count - 1], "..") != 0) {
                // Free the component we're removing
                free(components[component_count - 1]);
                component_count--;
            } else if (!is_absolute) {
                // Keep .. for relative paths that can't be resolved further
                components[component_count++] = strdup(token);
            }
        } else {
            // Normal component
            components[component_count++] = strdup(token);
        }
        token = strtok(NULL, "/");
    }
    
    // Rebuild path safely
    size_t pos = 0;
    if (is_absolute && pos < path_len + 1) {
        normalized[pos++] = '/';
    }
    
    for (int i = 0; i < component_count; i++) {
        if ((i > 0 || is_absolute) && pos < path_len + 1) {
            normalized[pos++] = '/';
        }
        size_t comp_len = strlen(components[i]);
        if (pos + comp_len < path_len + 2) {
            strcpy(normalized + pos, components[i]);
            pos += comp_len;
        }
        free(components[i]);
    }
    normalized[pos] = '\0';
    
    // Handle empty result for relative paths
    if (normalized[0] == '\0') {
        strcpy(normalized, ".");
    }
    
    free(path_copy);
    return normalized;
}