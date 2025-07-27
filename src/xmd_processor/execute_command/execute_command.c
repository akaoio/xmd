/**
 * @file execute_command.c
 * @brief Execute command and capture output implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include <sys/wait.h>
#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Execute command and capture output
 * @param command Command string to execute
 * @param output Buffer to store command output
 * @param output_size Size of output buffer
 * @return Command exit status, -1 on error
 */
int execute_command(const char* command, char* output, size_t output_size) {
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        snprintf(output, output_size, "[Error: Failed to execute command]");
        return -1;
    }
    
    size_t total_read = 0;
    while (total_read < output_size - 1) {
        size_t bytes_read = fread(output + total_read, 1, output_size - total_read - 1, pipe);
        if (bytes_read > 0) {
            total_read += bytes_read;
        } else {
            break;
        }
    }
    
    output[total_read] = '\0';
    
    int status = pclose(pipe);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}
