/**
 * @file xmd_process_kill.c
 * @brief Kill a process
 * @author XMD Team
 */

#include "../../../include/platform_internal.h"

/**
 * @brief Kill a process
 * @param process Process handle
 * @return 0 on success, -1 on error
 */
int xmd_process_kill(xmd_process_t process) {
#ifdef XMD_PLATFORM_WINDOWS
    return TerminateProcess(process, 1) ? 0 : -1;
#else
    return kill(process, SIGTERM) == 0 ? 0 : -1;
#endif
}
