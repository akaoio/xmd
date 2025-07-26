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
void* xmd_processor_create(const void* config) {
    (void)config; // Suppress unused parameter warning
    
    // Create using the existing xmd_init function
    return xmd_init(NULL);
}
