#include "xmd_runtime_status.h"
#include "../../../../include/core_macros.h"
#include <stdio.h>
#include <stdlib.h>

static xmd_runtime_status_t g_runtime_status = XMD_STATUS_UNINITIALIZED;

xmd_runtime_status_t xmd_runtime_status(void) {
    XMD_RUNTIME_STATUS_DEBUG(g_runtime_status);
    return g_runtime_status;
}
