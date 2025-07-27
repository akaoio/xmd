/**
 * @file execute_command.c
 * @brief Execute command and capture output implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE  // For popen/pclose
#include <stdio.h>
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
    // Rule 13: Error handling - validate inputs
    if (!command || !output || output_size == 0) {
        if (output && output_size > 0) {
            output[0] = '\0';
        }
        return -1;
    }
    
    // Rule 13: Ensure minimum buffer size
    if (output_size < 64) {
        output[0] = '\0';
        return -1;
    }
    
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        snprintf(output, output_size, "[Error: Failed to execute command]");
        return -1;
    }
    
    // Use dynamic buffer allocation for reading all output
    size_t buffer_capacity = 4096;  // Start with initial capacity
    char* temp_buffer = malloc(buffer_capacity);
    if (!temp_buffer) {
        pclose(pipe);
        snprintf(output, output_size, "[Error: Memory allocation failed]");
        return -1;
    }
    
    size_t total_read = 0;
    size_t chunk_size = 1024;
    
    while (1) {
        // Ensure we have space for the next chunk plus null terminator
        if (total_read + chunk_size + 1 > buffer_capacity) {
            buffer_capacity *= 2;
            char* new_buffer = realloc(temp_buffer, buffer_capacity);
            if (!new_buffer) {
                free(temp_buffer);
                pclose(pipe);
                snprintf(output, output_size, "[Error: Memory reallocation failed]");
                return -1;
            }
            temp_buffer = new_buffer;
        }
        
        size_t bytes_read = fread(temp_buffer + total_read, 1, chunk_size, pipe);
        if (bytes_read > 0) {
            total_read += bytes_read;
        } else {
            break;  // End of stream or error
        }
    }
    
    // Null terminate the complete output
    temp_buffer[total_read] = '\0';
    
    // Copy as much as fits into the provided output buffer
    size_t copy_size = (total_read < output_size - 1) ? total_read : output_size - 1;
    
    // If we're truncating, try to end at a line boundary to avoid cutting mid-line
    if (copy_size < total_read && copy_size > 0) {
        // Look backwards from the cut point to find the last newline
        for (size_t i = copy_size - 1; i > 0 && i > copy_size - 100; i--) {
            if (temp_buffer[i] == '\n') {
                copy_size = i + 1;  // Include the newline
                break;
            }
        }
    }
    
    memcpy(output, temp_buffer, copy_size);
    output[copy_size] = '\0';
    
    // Clean up
    free(temp_buffer);
    int status = pclose(pipe);
    
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}
