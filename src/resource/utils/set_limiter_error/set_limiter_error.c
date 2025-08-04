/**
 * @file set_limiter_error.c
 * @brief Set limiter error message
 */

#include <stdlib.h>
#include "../../../../include/resource.h"
#include "../../../../include/utils.h"
#include "../../../../utils/common/common_macros.h"
void set_limiter_error(ResourceLimiter* limiter, const char* error) {
    XMD_ENTRY_VALIDATE_VOID(limiter, error);
    XMD_FREE_SAFE(limiter->last_error);
    limiter->last_error = xmd_strdup(error);
}
