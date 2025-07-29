/**
 * @file import_tracker.c
 * @brief Implementation of import dependency tracking
 * @author XMD Team
 * @date 2025-07-29
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <libgen.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../../include/import_tracker.h"

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

/**
 * @brief Create a new import tracker
 */
import_tracker_t* import_tracker_create(void) {
    import_tracker_t* tracker = calloc(1, sizeof(import_tracker_t));
    if (!tracker) {
        return NULL;
    }
    tracker->dependencies = NULL;
    tracker->dep_count = 0;
    return tracker;
}

/**
 * @brief Free an import tracker
 */
void import_tracker_free(import_tracker_t* tracker) {
    if (!tracker) {
        return;
    }
    
    import_tracker_clear(tracker);
    free(tracker);
}

/**
 * @brief Clear all dependencies
 */
void import_tracker_clear(import_tracker_t* tracker) {
    if (!tracker) {
        return;
    }
    
    import_dep_t* current = tracker->dependencies;
    while (current) {
        import_dep_t* next = current->next;
        free(current->importer_file);
        free(current->imported_file);
        free(current);
        current = next;
    }
    
    tracker->dependencies = NULL;
    tracker->dep_count = 0;
}

/**
 * @brief Normalize file path
 */
static char* normalize_path(const char* path) {
    char resolved[PATH_MAX];
    if (realpath(path, resolved)) {
        return strdup(resolved);
    }
    return strdup(path);
}

/**
 * @brief Add an import dependency
 */
bool import_tracker_add_dependency(import_tracker_t* tracker, 
                                  const char* importer_file, 
                                  const char* imported_file) {
    if (!tracker || !importer_file || !imported_file) {
        return false;
    }
    
    // Normalize paths
    char* norm_importer = normalize_path(importer_file);
    char* norm_imported = normalize_path(imported_file);
    
    if (!norm_importer || !norm_imported) {
        free(norm_importer);
        free(norm_imported);
        return false;
    }
    
    // Check if dependency already exists
    import_dep_t* current = tracker->dependencies;
    while (current) {
        if (strcmp(current->importer_file, norm_importer) == 0 &&
            strcmp(current->imported_file, norm_imported) == 0) {
            free(norm_importer);
            free(norm_imported);
            return true; // Already exists
        }
        current = current->next;
    }
    
    // Add new dependency
    import_dep_t* new_dep = calloc(1, sizeof(import_dep_t));
    if (!new_dep) {
        free(norm_importer);
        free(norm_imported);
        return false;
    }
    
    new_dep->importer_file = norm_importer;
    new_dep->imported_file = norm_imported;
    new_dep->next = tracker->dependencies;
    tracker->dependencies = new_dep;
    tracker->dep_count++;
    
    return true;
}

/**
 * @brief Get all files that import a given file
 */
bool import_tracker_get_importers(import_tracker_t* tracker,
                                 const char* imported_file,
                                 char*** importers,
                                 int* count) {
    if (!tracker || !imported_file || !importers || !count) {
        return false;
    }
    
    // Normalize the imported file path
    char* norm_imported = normalize_path(imported_file);
    if (!norm_imported) {
        return false;
    }
    
    // Count importers
    int importer_count = 0;
    import_dep_t* current = tracker->dependencies;
    while (current) {
        if (strcmp(current->imported_file, norm_imported) == 0) {
            importer_count++;
        }
        current = current->next;
    }
    
    if (importer_count == 0) {
        *importers = NULL;
        *count = 0;
        free(norm_imported);
        return true;
    }
    
    // Allocate array
    char** result = calloc(importer_count, sizeof(char*));
    if (!result) {
        free(norm_imported);
        return false;
    }
    
    // Fill array
    int idx = 0;
    current = tracker->dependencies;
    while (current && idx < importer_count) {
        if (strcmp(current->imported_file, norm_imported) == 0) {
            result[idx] = strdup(current->importer_file);
            if (!result[idx]) {
                // Cleanup on error
                for (int i = 0; i < idx; i++) {
                    free(result[i]);
                }
                free(result);
                free(norm_imported);
                return false;
            }
            idx++;
        }
        current = current->next;
    }
    
    *importers = result;
    *count = importer_count;
    free(norm_imported);
    return true;
}

/**
 * @brief Extract import path from directive
 */
static char* extract_import_path(const char* directive) {
    // Look for patterns in XMD directives like:
    // <!-- xmd: import path/to/file.md -->
    // <!-- xmd:import path/to/file.md -->
    // {{import("path")}}
    
    const char* start = strstr(directive, "import");
    if (!start) {
        return NULL;
    }
    
    start += 6; // Skip "import"
    
    // Skip whitespace
    while (*start == ' ' || *start == '\t') {
        start++;
    }
    
    // For function syntax: import("path") or import('path')
    if (*start == '(') {
        start++;
        while (*start == ' ' || *start == '\t') {
            start++;
        }
        
        char quote = '\0';
        if (*start == '"' || *start == '\'') {
            quote = *start;
            start++;
        } else {
            return NULL;
        }
        
        // Find closing quote
        const char* end = strchr(start, quote);
        if (!end) {
            return NULL;
        }
        
        // Extract path
        size_t len = end - start;
        char* path = malloc(len + 1);
        if (!path) {
            return NULL;
        }
        
        strncpy(path, start, len);
        path[len] = '\0';
        
        return path;
    }
    
    // For directive syntax: import path/to/file.md
    // Find the end of the path (space, tab, newline, or -->)
    const char* end = start;
    while (*end && *end != ' ' && *end != '\t' && *end != '\n' && 
           !(end[0] == '-' && end[1] == '-' && end[2] == '>')) {
        end++;
    }
    
    // Extract path
    size_t len = end - start;
    if (len == 0) {
        return NULL;
    }
    
    char* path = malloc(len + 1);
    if (!path) {
        return NULL;
    }
    
    strncpy(path, start, len);
    path[len] = '\0';
    
    return path;
}

/**
 * @brief Extract imports from XMD content
 */
bool import_tracker_extract_imports(const char* content,
                                   const char* base_path,
                                   char*** imports,
                                   int* count) {
    if (!content || !imports || !count) {
        return false;
    }
    
    // Dynamic array for imports
    char** import_list = NULL;
    int import_count = 0;
    int import_capacity = 0;
    
    // Get directory of base file
    char* base_copy = strdup(base_path);
    char* base_dir = dirname(base_copy);
    
    // Scan for import directives
    const char* pos = content;
    while ((pos = strstr(pos, "import")) != NULL) {
        // Check if this is within an XMD directive
        const char* line_start = pos;
        while (line_start > content && *(line_start - 1) != '\n') {
            line_start--;
        }
        
        // Check for XMD comment patterns
        bool is_xmd_directive = false;
        // Look for <!-- xmd: import ... --> or <!-- xmd:import ... -->
        if ((strstr(line_start, "<!-- xmd:") || strstr(line_start, "<!--xmd:")) && strstr(line_start, "import")) {
            is_xmd_directive = true;
        } else if (strstr(line_start, "{{") && strstr(line_start, "import")) {
            is_xmd_directive = true;
        }
        
        if (is_xmd_directive) {
            char* import_path = extract_import_path(pos);
            if (import_path) {
                // Resolve relative paths
                char full_path[PATH_MAX];
                if (import_path[0] != '/') {
                    snprintf(full_path, sizeof(full_path), "%s/%s", base_dir, import_path);
                } else {
                    strncpy(full_path, import_path, sizeof(full_path) - 1);
                    full_path[sizeof(full_path) - 1] = '\0';
                }
                
                // Add to list
                if (import_count >= import_capacity) {
                    import_capacity = import_capacity == 0 ? 8 : import_capacity * 2;
                    char** new_list = realloc(import_list, import_capacity * sizeof(char*));
                    if (!new_list) {
                        free(import_path);
                        free(base_copy);
                        // Cleanup
                        for (int i = 0; i < import_count; i++) {
                            free(import_list[i]);
                        }
                        free(import_list);
                        return false;
                    }
                    import_list = new_list;
                }
                
                import_list[import_count] = strdup(full_path);
                if (!import_list[import_count]) {
                    free(import_path);
                    free(base_copy);
                    // Cleanup
                    for (int i = 0; i < import_count; i++) {
                        free(import_list[i]);
                    }
                    free(import_list);
                    return false;
                }
                import_count++;
                
                free(import_path);
            }
        }
        
        pos++;
    }
    
    free(base_copy);
    *imports = import_list;
    *count = import_count;
    return true;
}
