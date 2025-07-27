/**
 * @file append_to_result.c
 * @brief Append content to result string
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/loop.h"

/**
 * @brief Append content to result string
 * @param current_result Current result string
 * @param new_content Content to append
 * @return New result string (caller must free)
 */
char* append_to_result(char* current_result, const char* new_content) {
    if (!current_result || !new_content) {
        return NULL;
    }
    
    size_t current_len = strlen(current_result);
    size_t new_len = strlen(new_content);
    size_t total_len = current_len + new_len + 1;
    
    char* result = malloc(total_len);
    if (!result) {
        return NULL;
    }
    
    strcpy(result, current_result);
    strcat(result, new_content);
    
    return result;
}