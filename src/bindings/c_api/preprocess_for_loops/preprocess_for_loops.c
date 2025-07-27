#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file preprocess_for_loops.c
 * @brief For loop preprocessing function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/c_api_internal.h"
#include <ctype.h>

/**
 * @brief Preprocess for loops by expanding them
 * @param input Input content
 * @param input_length Input length
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Output buffer size
 * @return 0 on success, -1 on error
 */
int preprocess_for_loops(const char* input, size_t input_length, store* var_store, 
                        char* output, size_t output_size) {
    size_t output_pos = 0;
    const char* ptr = input;
    const char* input_end = input + input_length;
    
    while (ptr < input_end && output_pos < output_size - 1) {
        // Look for for loop start
        const char* for_start = strstr(ptr, "<!-- xmd:for ");
        if (!for_start) {
            // No more for loops, copy rest of input
            size_t remaining = input_end - ptr;
            if (output_pos + remaining < output_size - 1) {
                memcpy(output + output_pos, ptr, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Copy content before for loop
        size_t before_len = for_start - ptr;
        if (output_pos + before_len < output_size - 1) {
            memcpy(output + output_pos, ptr, before_len);
            output_pos += before_len;
        }
        
        // Find the end of the for directive
        const char* for_end = strstr(for_start, "-->");
        if (!for_end) {
            // Malformed directive, copy as-is
            if (output_pos + strlen(for_start) < output_size - 1) {
                strcpy(output + output_pos, for_start);
                output_pos += strlen(for_start);
            }
            break;
        }
        for_end += 3; // Skip -->
        
        // Extract for arguments
        const char* args_start = for_start + 13; // Skip "<!-- xmd:for "
        const char* args_end = strstr(args_start, " -->");
        if (!args_end) {
            args_end = strstr(args_start, "-->");
        }
        
        if (!args_end) {
            // Malformed directive
            ptr = for_end;
            continue;
        }
        
        size_t args_len = args_end - args_start;
        char args[512];
        if (args_len < sizeof(args)) {
            strncpy(args, args_start, args_len);
            args[args_len] = '\0';
            
            // Find matching endfor
            const char* endfor_start = strstr(for_end, "<!-- xmd:endfor");
            if (!endfor_start) {
                // No matching endfor, skip
                ptr = for_end;
                continue;
            }
            
            const char* endfor_end = strstr(endfor_start, "-->");
            if (!endfor_end) {
                ptr = for_end;
                continue;
            }
            endfor_end += 3;
            
            // Extract loop body
            size_t body_len = endfor_start - for_end;
            char* body = malloc(body_len + 1);
            if (!body) {
                ptr = endfor_end;
                continue;
            }
            
            strncpy(body, for_end, body_len);
            body[body_len] = '\0';
            
            // Parse for arguments and expand loop
            char var_name[256], range_or_collection[256];
            if (sscanf(args, "%255s in %255[^\n]", var_name, range_or_collection) == 2) {
                const char* collection_str = NULL;
                char converted_array[512] = "";
                
                // Check if it's a range expression (contains "..")
                if (strstr(range_or_collection, "..")) {
                    // Parse range and convert to array format
                    char start_str[64], end_str[64];
                    const char* dot_pos = strstr(range_or_collection, "..");
                    if (dot_pos) {
                        // Extract start part
                        size_t start_len = dot_pos - range_or_collection;
                        if (start_len < sizeof(start_str)) {
                            strncpy(start_str, range_or_collection, start_len);
                            start_str[start_len] = '\0';
                            
                            // Trim whitespace from start
                            char* start_trimmed = start_str;
                            while (*start_trimmed == ' ') start_trimmed++;
                            char* start_end = start_trimmed + strlen(start_trimmed) - 1;
                            while (start_end > start_trimmed && *start_end == ' ') *start_end-- = '\0';
                            
                            // Extract end part
                            const char* end_ptr = dot_pos + 2; // Skip ".."
                            while (*end_ptr == ' ') end_ptr++; // Skip leading spaces
                            strncpy(end_str, end_ptr, sizeof(end_str) - 1);
                            end_str[sizeof(end_str) - 1] = '\0';
                            
                            // Trim trailing whitespace from end
                            char* end_trimmed = end_str;
                            char* end_end = end_trimmed + strlen(end_trimmed) - 1;
                            while (end_end > end_trimmed && *end_end == ' ') *end_end-- = '\0';
                            
                            // Parse start value (number or variable)
                            int start_val = 0, end_val = 0;
                            if (isdigit(start_trimmed[0]) || (start_trimmed[0] == '-' && isdigit(start_trimmed[1]))) {
                                start_val = atoi(start_trimmed);
                            } else {
                                // It's a variable
                                variable* start_var = store_get(var_store, start_trimmed);
                                if (start_var) {
                                    const char* start_value = variable_to_string(start_var);
                                    if (start_value) start_val = atoi(start_value);
                                }
                            }
                            
                            // Parse end value (number or variable)
                            if (isdigit(end_trimmed[0]) || (end_trimmed[0] == '-' && isdigit(end_trimmed[1]))) {
                                end_val = atoi(end_trimmed);
                            } else {
                                // It's a variable
                                variable* end_var = store_get(var_store, end_trimmed);
                                if (end_var) {
                                    const char* end_value = variable_to_string(end_var);
                                    if (end_value) end_val = atoi(end_value);
                                }
                            }
                            
                            // Validate range
                            if (start_val <= end_val && end_val - start_val <= 1000) {
                                // Convert range to array format
                                strcpy(converted_array, "[");
                                for (int i = start_val; i <= end_val; i++) {
                                    if (i > start_val) strcat(converted_array, ", ");
                                    char num_str[32];
                                    snprintf(num_str, sizeof(num_str), "%d", i);
                                    strcat(converted_array, num_str);
                                }
                                strcat(converted_array, "]");
                                collection_str = converted_array;
                            }
                        }
                    }
                } 
                // Check if range_or_collection is an inline array [1, 2, 3]
                else if (range_or_collection[0] == '[') {
                    collection_str = range_or_collection;
                } else {
                    // Get collection variable from store
                    variable* collection = store_get(var_store, range_or_collection);
                    if (collection) {
                        collection_str = variable_to_string(collection);
                    }
                }
                
                if (collection_str) {
                    
                    // Simple array parsing: [1, 2, 3] or ["a", "b", "c"]
                    if (collection_str && collection_str[0] == '[') {
                        char* collection_copy = strdup(collection_str);
                        if (collection_copy) {
                            // Remove brackets
                            collection_copy[strlen(collection_copy) - 1] = '\0';
                            char* items = collection_copy + 1;
                            
                            // Split by comma and process each item
                            char* item = strtok(items, ",");
                            while (item && output_pos < output_size - 1000) {
                                // Trim whitespace
                                while (*item == ' ') item++;
                                char* item_end = item + strlen(item) - 1;
                                while (item_end > item && *item_end == ' ') *item_end-- = '\0';
                                
                                // Remove quotes if present
                                if ((item[0] == '"' && item[strlen(item)-1] == '"') ||
                                    (item[0] == '\'' && item[strlen(item)-1] == '\'')) {
                                    item[strlen(item)-1] = '\0';
                                    item++;
                                }
                                
                                // Process loop body with current item
                                char processed_body[4096];
                                size_t processed_len = 0;
                                const char* body_ptr = body;
                                
                                while (*body_ptr && processed_len < sizeof(processed_body) - 1) {
                                    if (body_ptr[0] == '{' && body_ptr[1] == '{') {
                                        // Check if this is our loop variable
                                        const char* var_end = strstr(body_ptr + 2, "}}");
                                        if (var_end) {
                                            size_t var_len = var_end - body_ptr - 2;
                                            if (var_len == strlen(var_name) && 
                                                strncmp(body_ptr + 2, var_name, var_len) == 0) {
                                                // Replace with current item
                                                if (processed_len + strlen(item) < sizeof(processed_body) - 1) {
                                                    strcpy(processed_body + processed_len, item);
                                                    processed_len += strlen(item);
                                                }
                                                body_ptr = var_end + 2;
                                                continue;
                                            }
                                        }
                                    }
                                    processed_body[processed_len++] = *body_ptr++;
                                }
                                processed_body[processed_len] = '\0';
                                
                                // Process the body for other variables after loop variable substitution
                                char final_body[4096];
                                size_t final_pos = 0;
                                const char* body_scan = processed_body;
                                
                                // Manual variable substitution for remaining {{variable}} patterns
                                while (*body_scan && final_pos < sizeof(final_body) - 1) {
                                    if (body_scan[0] == '{' && body_scan[1] == '{') {
                                        const char* var_end = strstr(body_scan + 2, "}}");
                                        if (var_end) {
                                            // Extract variable name
                                            size_t var_name_len = var_end - body_scan - 2;
                                            if (var_name_len < 256) {
                                                char var_name[256];
                                                strncpy(var_name, body_scan + 2, var_name_len);
                                                var_name[var_name_len] = '\0';
                                                
                                                // Look up variable value
                                                variable* var = store_get(var_store, var_name);
                                                const char* var_value = var ? variable_to_string(var) : "";
                                                
                                                // Add variable value to output
                                                size_t value_len = strlen(var_value);
                                                if (final_pos + value_len < sizeof(final_body) - 1) {
                                                    strcpy(final_body + final_pos, var_value);
                                                    final_pos += value_len;
                                                }
                                                
                                                body_scan = var_end + 2; // Skip past }}
                                                continue;
                                            }
                                        }
                                    }
                                    final_body[final_pos++] = *body_scan++;
                                }
                                final_body[final_pos] = '\0';
                                
                                // Use the fully processed body
                                if (output_pos + final_pos < output_size - 1) {
                                    strcpy(output + output_pos, final_body);
                                    output_pos += final_pos;
                                }
                                
                                item = strtok(NULL, ",");
                            }
                            
                            free(collection_copy);
                        }
                    }
                }
            }
            
            free(body);
            ptr = endfor_end;
        } else {
            ptr = for_end;
        }
    }
    
    output[output_pos] = '\0';
    return 0;
}
