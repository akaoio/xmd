/**
 * @file xmd_process_create.c
 * @brief Create a new process
 * @author XMD Development Team
 */

#include "../../../../include/platform_internal.h"
#include "../../../utils/common/common_macros.h"
#include <string.h>
/**
 * @brief Create a new process
 * @param command Command to execute
 * @param argv Command arguments
 * @param process Output process handle
 * @return 0 on success, -1 on error
 */
int xmd_process_create(const char* command, char* const argv[], xmd_process_t* process) {
    XMD_VALIDATE_PTRS(-1, command, process);
#ifdef XMD_PLATFORM_WINDOWS
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    // Build command line
    char cmdline[2048] = {0};
    snprintf(cmdline, sizeof(cmdline), "%s", command);
    if (argv) {
        for (int i = 0; argv[i]; i++) {
            strcat(cmdline, " ");
            strcat(cmdline, argv[i]);
        }
    }
    if (!CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        return -1;
    }
    CloseHandle(pi.hThread);
    *process = pi.hProcess;
    return 0;
#else
    pid_t pid = fork();
    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        // Child process
        if (argv) {
            execvp(command, argv);
        } else {
            execl(command, command, (char*)NULL);
        }
        exit(127); // If exec fails
    } else {
        // Parent process
        *process = pid;
        return 0;
    }
#endif
}
