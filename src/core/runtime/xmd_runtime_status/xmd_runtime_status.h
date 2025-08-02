#ifndef XMD_RUNTIME_STATUS_H
#define XMD_RUNTIME_STATUS_H

#include <stdbool.h>

typedef enum {
    XMD_STATUS_UNINITIALIZED = 0,
    XMD_STATUS_INITIALIZED = 1,
    XMD_STATUS_RUNNING = 2,
    XMD_STATUS_PAUSED = 3,
    XMD_STATUS_ERROR = 4,
    XMD_STATUS_TERMINATED = 5
} xmd_runtime_status_t;

xmd_runtime_status_t xmd_runtime_status(void);

#endif