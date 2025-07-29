/**
 * @file ast_split_comma_string.c
 * @brief Split comma-separated string into array variable
 * @author XMD Team
 * @date 2025-07-29
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/variable.h"

/**
 * @brief Split comma-separated string into array variable
 * @param str String to split
 * @return Array variable or NULL on error
 */
variable* ast_split_comma_string(const char* str) {
    if (!str) {
        return NULL;
    }
    
    variable* array = variable_create_array();
    if (!array) {
        return NULL;
    }
    
    char* str_copy = strdup(str);
    if (!str_copy) {
        variable_unref(array);
        return NULL;
    }
    
    char* token = strtok(str_copy, ",");
    while (token) {
        // Trim whitespace
        while (*token == ' ' || *token == '\t') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && (*end == ' ' || *end == '\t')) end--;
        *(end + 1) = '\0';
        
        variable* item = variable_create_string(token);
        if (item) {
            if (!variable_array_add(array, item)) {
                variable_unref(item);
                variable_unref(array);
                free(str_copy);
                return NULL;
            }
            variable_unref(item); // Array took reference
        }
        
        token = strtok(NULL, ",");
    }
    
    free(str_copy);
    return array;
}