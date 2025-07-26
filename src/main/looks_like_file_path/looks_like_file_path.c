/**
 * @file looks_like_file_path.c
 * @brief File path detection function
 * @author XMD Team
 *
 * Implementation of file path heuristics for the XMD main module.
 */

#include "../../../include/main_internal.h"

/**
 * @brief Check if argument looks like a file path
 * @param arg Argument to check
 * @return true if looks like file path, false otherwise
 */
bool looks_like_file_path(const char* arg) {
    if (!arg) return false;
    
    // Check for common file extensions
    const char* dot = strrchr(arg, '.');
    if (dot) {
        const char* ext = dot + 1;
        if (strcmp(ext, "md") == 0 || strcmp(ext, "markdown") == 0 || 
            strcmp(ext, "txt") == 0 || strcmp(ext, "html") == 0 ||
            strcmp(ext, "json") == 0) {
            return true;
        }
    }
    
    // Check if contains path separators
    if (strchr(arg, '/') || strchr(arg, '\\')) {
        return true;
    }
    
    // Check if it's a simple filename without extension
    if (strlen(arg) > 0 && arg[0] != '-' && !strchr(arg, ' ') && 
        !strchr(arg, '\n') && !strchr(arg, '\t')) {
        return true;
    }
    
    return false;
}