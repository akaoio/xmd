/**
 * @file xmd_process_close.c
 * @brief Close process handle
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Close process handle
 * @param process Process handle
 */
void xmd_process_close(xmd_process_t process) {
#ifdef XMD_PLATFORM_WINDOWS
    CloseHandle(process);
#else
    // Nothing to do on POSIX
    (void)process;
#endif
}
