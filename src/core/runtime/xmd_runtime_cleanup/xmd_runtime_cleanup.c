#include "xmd_runtime_cleanup.h"
#include <stdio.h>
#include <stdlib.h>

static int g_cleanup_count = 0;

bool xmd_runtime_cleanup(void) {
    g_cleanup_count++;
    
    if (getenv("XMD_DEBUG")) {
        printf("XMD Runtime cleanup called (count: %d)\n", g_cleanup_count);
    }
    
    return true;
}