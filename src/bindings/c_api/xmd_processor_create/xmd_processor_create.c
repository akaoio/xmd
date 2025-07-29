/**
 * @file xmd_processor_create.c
 * @brief XMD processor creator
 * @author XMD Team
 *
 * Implementation of XMD processor creation for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Create XMD processor
 * @param config Configuration
 * @return Processor instance or NULL on error
 */
xmd_processor* c_api_xmd_processor_create(const xmd_config* config) {
    (void)config; // Suppress unused parameter warning
    
    // Initialize XMD system first
    if (xmd_init() != XMD_SUCCESS) {
        return NULL;
    }
    
    // Create a dummy processor pointer with malloc so it can be freed
    // In full implementation, would create actual processor context
    xmd_processor* dummy_processor = malloc(sizeof(void*));
    if (!dummy_processor) {
        return NULL;
    }
    return dummy_processor;
}

/**
 * @brief Create XMD processor (public API)
 * @param config Configuration
 * @return Processor instance or NULL on error
 */
xmd_processor* xmd_processor_create(const xmd_config* config) {
    return c_api_xmd_processor_create(config);
}
