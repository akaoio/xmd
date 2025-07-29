/**
 * @file import_tracker.h
 * @brief Track import dependencies for the watch command
 * @author XMD Team
 * @date 2025-07-29
 */

#ifndef IMPORT_TRACKER_H
#define IMPORT_TRACKER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Import dependency entry
 */
typedef struct import_dep {
    char* importer_file;    /**< File that imports another file */
    char* imported_file;    /**< File being imported */
    struct import_dep* next; /**< Next in linked list */
} import_dep_t;

/**
 * @brief Import tracker structure
 */
typedef struct import_tracker {
    import_dep_t* dependencies; /**< Linked list of dependencies */
    int dep_count;             /**< Number of dependencies */
} import_tracker_t;

/**
 * @brief Create a new import tracker
 * @return New import tracker or NULL on error
 */
import_tracker_t* import_tracker_create(void);

/**
 * @brief Free an import tracker
 * @param tracker Tracker to free
 */
void import_tracker_free(import_tracker_t* tracker);

/**
 * @brief Add an import dependency
 * @param tracker Import tracker
 * @param importer_file File that imports
 * @param imported_file File being imported
 * @return true on success, false on error
 */
bool import_tracker_add_dependency(import_tracker_t* tracker, 
                                  const char* importer_file, 
                                  const char* imported_file);

/**
 * @brief Clear all dependencies
 * @param tracker Import tracker
 */
void import_tracker_clear(import_tracker_t* tracker);

/**
 * @brief Get all files that import a given file
 * @param tracker Import tracker
 * @param imported_file File being imported
 * @param importers Output array of importer files (caller must free)
 * @param count Output count of importers
 * @return true on success, false on error
 */
bool import_tracker_get_importers(import_tracker_t* tracker,
                                 const char* imported_file,
                                 char*** importers,
                                 int* count);

/**
 * @brief Extract imports from XMD content
 * @param content XMD file content
 * @param base_path Base path for resolving relative imports
 * @param imports Output array of imported files (caller must free)
 * @param count Output count of imports
 * @return true on success, false on error
 */
bool import_tracker_extract_imports(const char* content,
                                   const char* base_path,
                                   char*** imports,
                                   int* count);

#ifdef __cplusplus
}
#endif

#endif /* IMPORT_TRACKER_H */