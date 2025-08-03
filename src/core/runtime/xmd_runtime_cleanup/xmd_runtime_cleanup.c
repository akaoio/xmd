#include "xmd_runtime_cleanup.h"
#include "../../../../include/core_macros.h"
#include <stdio.h>
#include <stdlib.h>

static int g_cleanup_count = 0;

bool xmd_runtime_cleanup(void) {
    g_cleanup_count++;
    XMD_RUNTIME_CLEANUP_DEBUG(g_cleanup_count);
    return true;
}
