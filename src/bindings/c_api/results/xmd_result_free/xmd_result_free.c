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
#include "../../../../../utils/common/common_macros.h"
/**
 * @brief Free XMD result structure
 * @param result Result to free
  * /
 */
void xmd_result_free(xmd_result* result) {
    XMD_ENTRY_VALIDATE_VOID(result);
    XMD_FREE_SAFE(result->output);
    XMD_FREE_SAFE(result->error_message);
    XMD_FREE_SAFE(result);
}
