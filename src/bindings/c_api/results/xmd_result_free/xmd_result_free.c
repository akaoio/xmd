/**
 * @file xmd_result_free.c
 * @brief Free XMD result structure
 * 
 * This file contains ONLY the xmd_result_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include <stdlib.h>
#include "../../../../../include/xmd.h"
/**
 * @brief Free XMD result structure
 * @param result Result to free
  * /
 */
void xmd_result_free(xmd_result* result) {
    if (!result) return;
    free(result->output);
    free(result->error_message);
    free(result);
}
