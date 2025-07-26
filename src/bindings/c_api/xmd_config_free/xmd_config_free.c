/**
 * @file xmd_config_free.c
 * @brief XMD configuration destroyer
 * @author XMD Team
 *
 * Implementation of XMD configuration destruction for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Free XMD configuration
 * @param config Configuration to free
 */
void xmd_config_free(void* config) {
    if (config) {
        config_destroy((xmd_config*)config);
    }
}
