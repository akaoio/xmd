/**
 * @file xmd_processor_create.c
 * @brief Create XMD processor with configuration
 * 
 * This file contains ONLY the xmd_processor_create function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../../include/xmd.h"
#include "../../../../../include/store.h"
#include "../../../../../include/utils.h"
#include "utils/common/common_macros.h"
/**
 * @brief Create XMD processor with configuration
 * @param config Configuration to use (NULL for defaults)
 * @return New processor or NULL on error
  * /
 */
xmd_processor* xmd_processor_create(const xmd_config* config) {
    XMD_CREATE_VALIDATED(processor, xmd_processor, sizeof(xmd_processor), NULL);
    
    // Initialize variable store
    processor->variables = store_create();
    if (!processor->variables) {
        XMD_FREE_SAFE(processor);
        return NULL;
    }
    
    // Copy config (don't just reference)
    if (config) {
        processor->config = xmd_malloc(sizeof(xmd_config));
        if (processor->config) {
            memcpy(processor->config, config, sizeof(xmd_config));
        }
    }
    
    // Initialize other stores with NULL checks
    processor->modules = store_create();
    if (!processor->modules) {
        store_destroy(processor->variables);
        XMD_FREE_SAFE(processor->config);
        XMD_FREE_SAFE(processor);
        return NULL;
    }
    
    processor->functions = store_create();
    if (!processor->functions) {
        store_destroy(processor->modules);
        store_destroy(processor->variables);
        XMD_FREE_SAFE(processor->config);
        XMD_FREE_SAFE(processor);
        return NULL;
    }
    
    processor->exports = store_create();
    if (!processor->exports) {
        store_destroy(processor->functions);
        store_destroy(processor->modules);
        store_destroy(processor->variables);
        XMD_FREE_SAFE(processor->config);
        XMD_FREE_SAFE(processor);
        return NULL;
    }
    
    processor->initialized = true;
    processor->current_file = NULL; // Initialize to NULL for safe XMD_FREE_SAFE()
    return processor;
}
