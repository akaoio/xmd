/**
 * @file xmd_processor_free.c
 * @brief XMD processor destructor
 * @author XMD Team
 *
 * Implementation of XMD processor destruction for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Free XMD processor
 * @param processor Processor to free
 */
void c_api_xmd_processor_free(xmd_processor* processor) {
    if (processor) {
        // Free the processor memory - in a full implementation this would
        // properly clean up the processor context
        // xmd_cleanup() is a global cleanup function
        free(processor);
    }
}

/**
 * @brief Free XMD processor (public API)
 * @param processor Processor to free
 */
void xmd_processor_free(xmd_processor* processor) {
    c_api_xmd_processor_free(processor);
}
