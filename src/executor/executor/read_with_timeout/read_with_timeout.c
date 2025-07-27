/**
 * @file read_with_timeout.c
 * @brief Read data from file descriptor with timeout
 * @author XMD Team
 */

#include "../../../../include/executor_internal.h"

/**
 * @brief Read data from file descriptor with timeout with dynamic buffer growth
 * @param fd File descriptor to read from
 * @param buffer Pointer to buffer pointer (will be reallocated if needed)
 * @param buffer_size Pointer to current buffer size (will be updated)
 * @param max_size Maximum size to read
 * @param timeout_ms Timeout in milliseconds
 * @return Number of bytes read, or -1 on error
 */
ssize_t read_with_timeout_dynamic(int fd, char** buffer, size_t* buffer_size, size_t max_size, int timeout_ms) {
    fd_set readfds;
    struct timeval timeout;
    size_t total_read = 0;
    size_t current_buffer_size = *buffer_size;
    char* current_buffer = *buffer;
    
    while (total_read < max_size - 1) {
        // Check if we need to grow the buffer
        if (total_read >= current_buffer_size - 1) {
            size_t new_size = current_buffer_size * 2;
            if (new_size > max_size) {
                new_size = max_size;
            }
            
            char* new_buffer = realloc(current_buffer, new_size);
            if (!new_buffer) {
                break; // Out of memory
            }
            
            current_buffer = new_buffer;
            current_buffer_size = new_size;
            *buffer = current_buffer;
            *buffer_size = current_buffer_size;
        }
        
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        
        timeout.tv_sec = timeout_ms / 1000;
        timeout.tv_usec = (timeout_ms % 1000) * 1000;
        
        int ready = select(fd + 1, &readfds, NULL, NULL, &timeout);
        if (ready <= 0) {
            break; // Timeout or error
        }
        
        ssize_t bytes_read = read(fd, current_buffer + total_read, current_buffer_size - total_read - 1);
        if (bytes_read <= 0) {
            break; // EOF or error
        }
        
        total_read += bytes_read;
    }
    
    current_buffer[total_read] = '\0';
    return total_read;
}

/**
 * @brief Read data from file descriptor with timeout (legacy interface)
 * @param fd File descriptor to read from
 * @param buffer Buffer to store data
 * @param max_size Maximum size to read
 * @param timeout_ms Timeout in milliseconds
 * @return Number of bytes read, or -1 on error
 */
ssize_t read_with_timeout(int fd, char* buffer, size_t max_size, int timeout_ms) {
    fd_set readfds;
    struct timeval timeout;
    size_t total_read = 0;
    
    while (total_read < max_size - 1) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        
        timeout.tv_sec = timeout_ms / 1000;
        timeout.tv_usec = (timeout_ms % 1000) * 1000;
        
        int ready = select(fd + 1, &readfds, NULL, NULL, &timeout);
        if (ready <= 0) {
            break; // Timeout or error
        }
        
        ssize_t bytes_read = read(fd, buffer + total_read, max_size - total_read - 1);
        if (bytes_read <= 0) {
            break; // EOF or error
        }
        
        total_read += bytes_read;
    }
    
    buffer[total_read] = '\0';
    return total_read;
}