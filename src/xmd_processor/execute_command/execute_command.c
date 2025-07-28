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
    
    // Redirect stderr to stdout to capture error messages too
    char* full_command = malloc(strlen(command) + 8); // +8 for " 2>&1" + null
    sprintf(full_command, "%s 2>&1", command);
    
    FILE* pipe = popen(full_command, "r");
    free(full_command);
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
        // Look backwards from the cut point to find the last newline (increased search range)
        for (size_t i = copy_size - 1; i > 0 && i > copy_size - 500; i--) {
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

/**
 * @brief Execute command with fully dynamic output allocation
 * @param command Command string to execute
 * @param exit_status Pointer to store command exit status (can be NULL)
 * @return Dynamically allocated output string (caller must free) or NULL on error
 */
char* execute_command_dynamic(const char* command, int* exit_status) {
    // Rule 13: Error handling - validate inputs
    if (!command) {
        if (exit_status) *exit_status = -1;
        return NULL;
    }
    
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        if (exit_status) *exit_status = -1;
        return strdup("[Error: Failed to execute command]");
    }
    
    // Start with a reasonable initial capacity and grow as needed
    size_t buffer_capacity = 8192;  // Start with 8KB
    char* buffer = malloc(buffer_capacity);
    if (!buffer) {
        pclose(pipe);
        if (exit_status) *exit_status = -1;
        return strdup("[Error: Memory allocation failed]");
    }
    
    size_t total_read = 0;
    size_t chunk_size = 4096;  // Read in 4KB chunks
    
    while (1) {
        // Ensure we have space for the next chunk plus null terminator
        while (total_read + chunk_size + 1 > buffer_capacity) {
            buffer_capacity *= 2;
            char* new_buffer = realloc(buffer, buffer_capacity);
            if (!new_buffer) {
                free(buffer);
                pclose(pipe);
                if (exit_status) *exit_status = -1;
                return strdup("[Error: Memory reallocation failed]");
            }
            buffer = new_buffer;
        }
        
        size_t bytes_read = fread(buffer + total_read, 1, chunk_size, pipe);
        if (bytes_read > 0) {
            total_read += bytes_read;
        } else {
            break;  // End of stream or error
        }
    }
    
    // Null terminate the output
    buffer[total_read] = '\0';
    
    // Shrink buffer to actual size needed (optional optimization)
    if (total_read + 1 < buffer_capacity / 2) {
        char* final_buffer = realloc(buffer, total_read + 1);
        if (final_buffer) {
            buffer = final_buffer;
        }
    }
    
    int status = pclose(pipe);
    if (exit_status) {
        *exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
    
    return buffer;
}
