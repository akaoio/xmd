/**
 * @file c_api_xmd_cleanup.c
 * @brief Clean up XMD C API context
 * 
 * This file contains ONLY the c_api_xmd_cleanup function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include <stdlib.h>
#include "../../../../../include/xmd.h"
#include "../../../../../include/c_api_internal.h"
#include "../../../../../include/config_internal.h"
#include "../../../../../include/store.h"
#include "../../../../../utils/common/common_macros.h"
/**
 * @brief Clean up XMD C API context
 * @param handle Context handle to clean up
  * /
 */
void c_api_xmd_cleanup(void* handle) {
    XMD_ENTRY_VALIDATE_VOID(handle);
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (ctx->config) config_destroy(ctx->config);
    if (ctx->global_variables) store_destroy(ctx->global_variables);
    XMD_FREE_SAFE(ctx);
}
