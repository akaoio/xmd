/**
 * @file xmd_get_version.c
 * @brief XMD version getter
 * @author XMD Team
 */

#include "../../../../include/c_api_internal.h"

// Function prototype for dynamic version getter
extern char* get_version(void);

/**
 * @brief Get XMD library version
 * @return Version string
 */
const char* c_api_xmd_get_version(void) {
    return get_version();
}

/**
 * @brief Get XMD library version (public API)
 * @return Version string
 */
const char* xmd_get_version(void) {
    return c_api_xmd_get_version();
}