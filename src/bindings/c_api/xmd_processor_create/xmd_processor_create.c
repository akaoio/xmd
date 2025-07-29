/**
 * @file xmd_processor_create.c
 * @brief XMD processor creator
 * @author XMD Team
 *
 * Implementation of XMD processor creation for the C API.
 */

#include "../../../../include/c_api_internal.h"
#include "../../../../include/store_internal.h"

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
    
    // Create a proper store as processor (matches expectation in xmd_process_string)
    store* variable_store = store_create();
    if (!variable_store) {
        return NULL;
    }
    return (xmd_processor*)variable_store;
}

/**
 * @brief Create XMD processor (public API)
 * @param config Configuration
 * @return Processor instance or NULL on error
 */
xmd_processor* xmd_processor_create(const xmd_config* config) {
    return c_api_xmd_processor_create(config);
}
