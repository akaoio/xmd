/**
 * @file parse_range.c
 * @brief Parse range syntax implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

#define MAX_RANGE_SIZE 1000

/**
 * @brief Parse range syntax (start..end) and expand to array
 * @param range_str Range string like "1..5" or "var1..var2"
 * @param variables Variable store for variable resolution
 * @param items Output array of string values (caller must free)
 * @param count Output count of items
 * @return 0 on success, -1 on error
 */
int parse_range(const char* range_str, store* variables, char*** items, int* count) {
    char* range_copy = strdup(range_str);
    char* dots_pos = strstr(range_copy, "..");
    
    if (!dots_pos) {
        free(range_copy);
        return -1;
    }
    
    *dots_pos = '\0';
    char* start_str = trim_whitespace(range_copy);
    char* end_str = trim_whitespace(dots_pos + 2);
    
    // Resolve start value (variable or literal)
    int start_val;
    variable* start_var = store_get(variables, start_str);
    if (start_var) {
        char* start_value = variable_to_string(start_var);
        start_val = atoi(start_value);
        free(start_value);
    } else {
        start_val = atoi(start_str);
    }
    
    // Resolve end value (variable or literal)
    int end_val;
    variable* end_var = store_get(variables, end_str);
    if (end_var) {
        char* end_value = variable_to_string(end_var);
        end_val = atoi(end_value);
        free(end_value);
    } else {
        end_val = atoi(end_str);
    }
    
    // Calculate range size and direction
    int range_size = abs(end_val - start_val) + 1;
    if (range_size > MAX_RANGE_SIZE) {
        free(range_copy);
        return -1;
    }
    
    // Allocate array
    *items = malloc(range_size * sizeof(char*));
    *count = range_size;
    
    // Generate values
    int step = (end_val >= start_val) ? 1 : -1;
    int current = start_val;
    
    for (int i = 0; i < range_size; i++) {
        (*items)[i] = malloc(32);
        snprintf((*items)[i], 32, "%d", current);
        current += step;
    }
    
    free(range_copy);
    return 0;
}
