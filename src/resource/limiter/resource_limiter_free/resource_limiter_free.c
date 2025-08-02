/**
 * @file resource_limiter_free.c
 * @brief Free resource limiter
 */

#include <stdlib.h>
#include "../../../../include/resource.h"
void resource_limiter_XMD_FREE_SAFE(ResourceLimiter* limiter) {
    if (!limiter) {
        return;
    }
    XMD_FREE_SAFE(limiter->last_error);
    XMD_FREE_SAFE(limiter);
}
