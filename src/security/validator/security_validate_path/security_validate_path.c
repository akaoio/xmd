/**
 * @file security_validate_path.c
 * @brief Validate file path for traversal attacks
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "../../../../include/security.h"

/**
 * @brief Normalize path by resolving . and .. components
 * @param path Input path
 * @return Normalized path (must be freed) or NULL on error
 */
static char* normalize_path(const char* path) {
    if (!path) return NULL;
    
    char* normalized = malloc(PATH_MAX);
    if (!normalized) return NULL;
    
    // Use realpath to get canonical path
    if (realpath(path, normalized) == NULL) {
        // If realpath fails, manually normalize
        free(normalized);
        
        // Simple normalization for non-existent paths
        normalized = malloc(strlen(path) + 1);
        if (!normalized) return NULL;
        
        strcpy(normalized, path);
        
        // Remove double slashes
        char* src = normalized;
        char* dst = normalized;
        while (*src) {
            if (*src == '/' && *(src + 1) == '/') {
                src++;
            } else {
                *dst++ = *src++;
            }
        }
        *dst = '\0';
    }
    
    return normalized;
}

/**
 * @brief Check if path contains traversal patterns
 * @param path Path to check
 * @return true if traversal detected
 */
static bool contains_path_traversal(const char* path) {
    // Check for obvious traversal patterns
    if (strstr(path, "../") || strstr(path, "..\\") ||
        strstr(path, "/..") || strstr(path, "\\..") ||
        strcmp(path, "..") == 0) {
        return true;
    }
    
    // Check for encoded traversal
    if (strstr(path, "%2e%2e") || strstr(path, "%2E%2E") ||
        strstr(path, "%2e%2e%2f") || strstr(path, "%2E%2E%2F")) {
        return true;
    }
    
    // Check for null byte injection
    size_t len = strlen(path);
    for (size_t i = 0; i < len; i++) {
        if (path[i] == '\0' && i < len - 1) {
            return true;
        }
    }
    
    return false;
}

/**
 * @brief Check if normalized path is within allowed base
 * @param normalized_path Normalized path
 * @param normalized_base Normalized base directory
 * @return true if path is within base
 */
static bool is_within_base(const char* normalized_path, const char* normalized_base) {
    if (!normalized_path || !normalized_base) {
        return false;
    }
    
    size_t base_len = strlen(normalized_base);
    
    // Ensure base doesn't end with slash for consistent comparison
    char* base_copy = strdup(normalized_base);
    if (!base_copy) return false;
    
    if (base_len > 1 && base_copy[base_len - 1] == '/') {
        base_copy[base_len - 1] = '\0';
        base_len--;
    }
    
    // Check if path starts with base
    bool within = (strncmp(normalized_path, base_copy, base_len) == 0) &&
                  (normalized_path[base_len] == '/' || normalized_path[base_len] == '\0');
    
    free(base_copy);
    return within;
}

/**
 * @brief Validate file path for traversal attacks
 * @param path File path to validate
 * @param allowed_base Base directory that must contain the path
 * @return Security validation result
 */
security_result security_validate_path(const char* path, const char* allowed_base) {
    if (!path || !allowed_base) {
        return SECURITY_INVALID_INPUT;
    }
    
    // Empty path is invalid
    if (strlen(path) == 0) {
        return SECURITY_INVALID_INPUT;
    }
    
    // Check for obvious traversal patterns first
    if (contains_path_traversal(path)) {
        return SECURITY_PATH_TRAVERSAL;
    }
    
    // Normalize both paths
    char* normalized_path = normalize_path(path);
    char* normalized_base = normalize_path(allowed_base);
    
    if (!normalized_path || !normalized_base) {
        free(normalized_path);
        free(normalized_base);
        return SECURITY_PATH_TRAVERSAL;
    }
    
    // Check if the normalized path is within the allowed base
    bool within_base = is_within_base(normalized_path, normalized_base);
    
    free(normalized_path);
    free(normalized_base);
    
    return within_base ? SECURITY_VALID : SECURITY_PATH_TRAVERSAL;
}