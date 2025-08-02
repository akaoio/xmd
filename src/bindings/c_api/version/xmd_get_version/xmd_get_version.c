/**
 * @file xmd_get_version.c
 * @brief Get XMD version information
 * 
 * This file contains ONLY the xmd_get_version function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include "../../../../../include/xmd.h"
/**
 * @brief Get XMD version information
 * @return Version string
  * /
 */
const char* xmd_get_version(void) { 
    return "2.0.0-consolidation"; 
}
