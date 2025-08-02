/**
 * @file bindings_get_version.c
 * @brief Get bindings version information
 * 
 * This file contains ONLY the bindings_get_version function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include "../../../../../include/xmd.h"
/**
 * @brief Get bindings version information
 * @return Version string
  * /
 */
const char* bindings_get_version(void) {
    return "XMD Language Bindings v2.0 (consolidated)";
}
