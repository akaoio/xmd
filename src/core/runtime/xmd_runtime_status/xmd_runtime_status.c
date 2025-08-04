#include "xmd_runtime_status.h"
#include "../../../../include/core_macros.h"
#include "../../../../include/platform.h"
#include <stdio.h>
#include <stdlib.h>

static xmd_runtime_status_t g_runtime_status = XMD_STATUS_UNINITIALIZED;
static xmd_mutex_t status_mutex = {0};
static bool mutex_initialized = false;

xmd_runtime_status_t xmd_runtime_status(void) {
    // Initialize mutex on first use (thread-safe once-only initialization)
    if (!mutex_initialized) {
        static xmd_mutex_t init_mutex = {0};
        xmd_mutex_init(&init_mutex);
        xmd_mutex_lock(&init_mutex);
        if (!mutex_initialized) {
            xmd_mutex_init(&status_mutex);
            mutex_initialized = true;
        }
        xmd_mutex_unlock(&init_mutex);
    }
    
    xmd_mutex_lock(&status_mutex);
    xmd_runtime_status_t result = g_runtime_status;
    XMD_RUNTIME_STATUS_DEBUG(result);
    xmd_mutex_unlock(&status_mutex);
    
    return result;
}
