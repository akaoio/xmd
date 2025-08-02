/**
 * @file resource_limiter_free.c
 * @brief Free resource limiter
 */

#include <stdlib.h>
#include "../../../../include/resource.h"
void resource_limiter_free(ResourceLimiter* limiter) {
    if (!limiter) {
        return;
    }
    free(limiter->last_error);
    free(limiter);
}
