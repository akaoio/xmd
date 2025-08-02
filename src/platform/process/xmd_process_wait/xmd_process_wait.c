/**
 * @file xmd_process_wait.c
 * @brief Wait for process to complete
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include <signal.h>
#include <sys/wait.h>
/**
 * @brief Wait for process to complete
 * @param process Process handle
 * @param exit_code Output exit code
 * @param timeout_ms Timeout in milliseconds
 * @return 0 on success, -1 on error, 1 on timeout
 */
int xmd_process_wait(xmd_process_t process, int* exit_code, uint32_t timeout_ms) {
#ifdef XMD_PLATFORM_WINDOWS
    DWORD wait_result = WaitForSingleObject(process, timeout_ms);
    if (wait_result == WAIT_TIMEOUT) {
        return 1;
    } else if (wait_result == WAIT_OBJECT_0) {
        if (exit_code) {
            DWORD code;
            if (GetExitCodeProcess(process, &code)) {
                *exit_code = (int)code;
            } else {
                *exit_code = -1;
            }
        }
        return 0;
    }
    return -1;
#else
    int status;
    pid_t result;
    if (timeout_ms == 0) {
        // No timeout
        result = waitpid(process, &status, 0);
    } else {
        // Implement timeout using alarm signal
        struct sigaction old_action, new_action;
        new_action.sa_handler = SIG_DFL;
        sigemptyset(&new_action.sa_mask);
        new_action.sa_flags = 0;
        
        sigaction(SIGALRM, &new_action, &old_action);
        alarm(timeout_ms / 1000 + 1); // Convert to seconds, round up
        result = waitpid(process, &status, 0);
        alarm(0); // Cancel alarm
        sigaction(SIGALRM, &old_action, NULL); // Restore old handler
    }
    if (result == -1) {
        return -1;
    }
    if (exit_code) {
        if (WIFEXITED(status)) {
            *exit_code = WEXITSTATUS(status);
        } else {
            *exit_code = -1;
        }
    }
    return 0;
#endif
}
