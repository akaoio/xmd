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
void xmd_processor_free(void* processor) {
    if (processor) {
        xmd_cleanup(processor);
    }
}
