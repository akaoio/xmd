/**
 * @file set_limiter_error.c
 * @brief Set limiter error message
 */

#include <stdlib.h>
#include "../../../../include/resource.h"
#include "../../../../include/utils.h"
void set_limiter_error(ResourceLimiter* limiter, const char* error) {
    if (!limiter || !error) {
        return;
    }
    free(limiter->last_error);
    limiter->last_error = xmd_strdup(error);
}
