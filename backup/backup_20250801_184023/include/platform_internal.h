/**
 * @file platform_internal.h
 * @brief Internal header for platform implementation
 * @author XMD Team
 */

#ifndef PLATFORM_INTERNAL_H
#define PLATFORM_INTERNAL_H

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/resource.h>
#include <signal.h>

#ifdef XMD_PLATFORM_WINDOWS
    #include <windows.h>
    #include <psapi.h>
    #pragma comment(lib, "psapi.lib")
    #pragma comment(lib, "kernel32.lib")
#endif

#ifdef XMD_PLATFORM_LINUX
    #include <sys/sysinfo.h>
#endif

#ifdef XMD_PLATFORM_MACOS
    #include <mach/mach.h>
    #include <sys/sysctl.h>
#endif

#include "platform.h"

#endif /* PLATFORM_INTERNAL_H */
