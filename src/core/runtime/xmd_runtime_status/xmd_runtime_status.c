#include "xmd_runtime_status.h"
#include <stdio.h>
#include <stdlib.h>

static xmd_runtime_status_t g_runtime_status = XMD_STATUS_UNINITIALIZED;

xmd_runtime_status_t xmd_runtime_status(void) {
    if (getenv("XMD_DEBUG")) {
        const char* status_names[] = {
            "UNINITIALIZED",
            "INITIALIZED",
            "RUNNING",
            "PAUSED",
            "ERROR",
            "TERMINATED"
        };
        
        if (g_runtime_status >= 0 && g_runtime_status <= 5) {
            printf("XMD Runtime status: %s\n", status_names[g_runtime_status]);
        }
    }
    
    return g_runtime_status;
}