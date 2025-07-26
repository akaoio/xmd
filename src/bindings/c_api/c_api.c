/**
 * @file c_api.c
 * @brief C API interface for language bindings
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../../../include/cli.h"
#include "../../../include/lexer.h"
#include "../../../include/token.h"
#include "../../../include/store.h"

// Forward declaration for XMD directive processor
int process_xmd_directive(const char* directive, store* var_store, char* output, size_t output_size);
int process_text_with_directives(const char* text, store* var_store, char* output, size_t output_size);
int process_complete_for_loop(const char* content, size_t for_start, size_t args_start, 
                             size_t args_end, store* var_store, char* output, size_t output_size);
int process_complete_if_statement(const char* content, size_t if_start, size_t args_start, 
                                 size_t args_end, store* var_store, char* output, size_t output_size);

/**
 * @brief Preprocess variables by extracting and storing them, and removing set directives
 * @param input Input content
 * @param input_length Input length
 * @param var_store Variable store
 * @param output Output buffer with set directives removed
 * @param output_size Output buffer size
 * @return 0 on success, -1 on error
 */
static int preprocess_variables(const char* input, size_t input_length, store* var_store, 
                               char* output, size_t output_size) {
    const char* ptr = input;
    const char* input_end = input + input_length;
    size_t output_pos = 0;
    
    while (ptr < input_end && output_pos < output_size - 1) {
        // Look for set directive
        const char* set_start = strstr(ptr, "<!-- xmd:set ");
        if (!set_start) {
            // No more set directives, copy rest of input
            size_t remaining = input_end - ptr;
            if (output_pos + remaining < output_size - 1) {
                memcpy(output + output_pos, ptr, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Copy content before set directive
        size_t before_len = set_start - ptr;
        if (output_pos + before_len < output_size - 1) {
            memcpy(output + output_pos, ptr, before_len);
            output_pos += before_len;
        }
        
        // Find the end of the set directive
        const char* set_end = strstr(set_start, "-->");
        if (!set_end) {
            // Malformed directive, copy as-is
            if (output_pos + strlen(set_start) < output_size - 1) {
                strcpy(output + output_pos, set_start);
                output_pos += strlen(set_start);
            }
            break;
        }
        set_end += 3; // Skip -->
        
        // Extract set arguments
        const char* args_start = set_start + 13; // Skip "<!-- xmd:set "
        size_t args_len = set_end - 3 - args_start; // Don't include -->
        
        if (args_len > 0 && args_len < 512) {
            char args[512];
            strncpy(args, args_start, args_len);
            args[args_len] = '\0';
            
            // Create a proper directive string for processing
            char directive[600];
            snprintf(directive, sizeof(directive), "xmd:set %s", args);
            
            // Process the set directive
            char dummy_output[64];
            process_xmd_directive(directive, var_store, dummy_output, sizeof(dummy_output));
        }
        
        // Skip the set directive entirely (don't copy to output)
        ptr = set_end;
    }
    
    output[output_pos] = '\0';
    return 0;
}

/**
 * @brief Preprocess for loops by expanding them
 * @param input Input content
 * @param input_length Input length
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Output buffer size
 * @return 0 on success, -1 on error
 */
static int preprocess_for_loops(const char* input, size_t input_length, store* var_store, 
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

/**
 * @brief Simple condition evaluator for if statements
 * @param condition Condition string (e.g., "status == \"active\"")
 * @param var_store Variable store
 * @return true if condition is true, false otherwise
 */
static bool evaluate_condition(const char* condition, store* var_store) {
    if (!condition || !var_store) {
        return false;
    }
    
    // Simple condition parsing: var == "value" or var != "value"
    char var_name[256], operator[8], value[256];
    
    // Try to parse pattern: var == "value" or var != "value"
    if (sscanf(condition, "%255s %7s \"%255[^\"]\"", var_name, operator, value) == 3) {
        variable* var = store_get(var_store, var_name);
        const char* var_value = var ? variable_to_string(var) : "";
        
        if (strcmp(operator, "==") == 0) {
            return strcmp(var_value, value) == 0;
        } else if (strcmp(operator, "!=") == 0) {
            return strcmp(var_value, value) != 0;
        }
    }
    
    // Try without quotes: var == value or var != value
    if (sscanf(condition, "%255s %7s %255s", var_name, operator, value) == 3) {
        variable* var = store_get(var_store, var_name);
        const char* var_value = var ? variable_to_string(var) : "";
        
        if (strcmp(operator, "==") == 0) {
            return strcmp(var_value, value) == 0;
        } else if (strcmp(operator, "!=") == 0) {
            return strcmp(var_value, value) != 0;
        }
    }
    
    // Default: treat as variable existence check
    variable* var = store_get(var_store, condition);
    return var != NULL;
}

/**
 * @brief Preprocess if statements by evaluating conditions and selecting branches
 * @param input Input content
 * @param input_length Input length
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Output buffer size
 * @return 0 on success, -1 on error
 */
static int preprocess_if_statements(const char* input, size_t input_length, store* var_store, 
                                   char* output, size_t output_size) {
    size_t output_pos = 0;
    const char* ptr = input;
    const char* input_end = input + input_length;
    
    while (ptr < input_end && output_pos < output_size - 1) {
        // Look for if statement start
        const char* if_start = strstr(ptr, "<!-- xmd:if ");
        if (!if_start) {
            // No more if statements, copy rest of input
            size_t remaining = input_end - ptr;
            if (output_pos + remaining < output_size - 1) {
                memcpy(output + output_pos, ptr, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Copy content before if statement
        size_t before_len = if_start - ptr;
        if (output_pos + before_len < output_size - 1) {
            memcpy(output + output_pos, ptr, before_len);
            output_pos += before_len;
        }
        
        // Find the end of the if directive
        const char* if_end = strstr(if_start, "-->");
        if (!if_end) {
            // Malformed directive, copy as-is
            if (output_pos + strlen(if_start) < output_size - 1) {
                strcpy(output + output_pos, if_start);
                output_pos += strlen(if_start);
            }
            break;
        }
        if_end += 3; // Skip -->
        
        // Extract if condition
        const char* condition_start = if_start + 12; // Skip "<!-- xmd:if "
        const char* condition_end = strstr(condition_start, " -->");
        if (!condition_end) {
            condition_end = strstr(condition_start, "-->");
        }
        
        if (!condition_end) {
            ptr = if_end;
            continue;
        }
        
        size_t condition_len = condition_end - condition_start;
        char condition[512];
        if (condition_len < sizeof(condition)) {
            strncpy(condition, condition_start, condition_len);
            condition[condition_len] = '\0';
            
            // Find matching else and endif
            const char* else_start = strstr(if_end, "<!-- xmd:else");
            const char* endif_start = strstr(if_end, "<!-- xmd:endif");
            
            if (!endif_start) {
                ptr = if_end;
                continue;
            }
            
            const char* endif_end = strstr(endif_start, "-->");
            if (!endif_end) {
                ptr = if_end;
                continue;
            }
            endif_end += 3;
            
            // Evaluate condition
            bool condition_result = evaluate_condition(condition, var_store);
            
            if (condition_result) {
                // Take the true branch (from if_end to else_start or endif_start)
                const char* true_branch_end = else_start ? else_start : endif_start;
                size_t true_branch_len = true_branch_end - if_end;
                
                // Copy branch content to temporary buffer for variable substitution
                char branch_content[4096];
                if (true_branch_len < sizeof(branch_content) - 1) {
                    memcpy(branch_content, if_end, true_branch_len);
                    branch_content[true_branch_len] = '\0';
                    
                    // Apply variable substitution to branch content
                    char processed_branch[4096];
                    size_t processed_pos = 0;
                    const char* scan = branch_content;
                    
                    while (*scan && processed_pos < sizeof(processed_branch) - 1) {
                        if (scan[0] == '{' && scan[1] == '{') {
                            const char* var_end = strstr(scan + 2, "}}");
                            if (var_end) {
                                size_t var_name_len = var_end - scan - 2;
                                if (var_name_len < 256) {
                                    char var_name[256];
                                    strncpy(var_name, scan + 2, var_name_len);
                                    var_name[var_name_len] = '\0';
                                    
                                    variable* var = store_get(var_store, var_name);
                                    const char* var_value = var ? variable_to_string(var) : "";
                                    
                                    size_t value_len = strlen(var_value);
                                    if (processed_pos + value_len < sizeof(processed_branch) - 1) {
                                        strcpy(processed_branch + processed_pos, var_value);
                                        processed_pos += value_len;
                                    }
                                    
                                    scan = var_end + 2;
                                    continue;
                                }
                            }
                        }
                        processed_branch[processed_pos++] = *scan++;
                    }
                    processed_branch[processed_pos] = '\0';
                    
                    // Add processed branch to output
                    if (output_pos + processed_pos < output_size - 1) {
                        strcpy(output + output_pos, processed_branch);
                        output_pos += processed_pos;
                    }
                }
            } else if (else_start) {
                // Take the false branch (from else_end to endif_start)
                const char* else_end = strstr(else_start, "-->");
                if (else_end) {
                    else_end += 3;
                    size_t false_branch_len = endif_start - else_end;
                    
                    // Copy branch content to temporary buffer for variable substitution
                    char branch_content[4096];
                    if (false_branch_len < sizeof(branch_content) - 1) {
                        memcpy(branch_content, else_end, false_branch_len);
                        branch_content[false_branch_len] = '\0';
                        
                        // Apply variable substitution to branch content
                        char processed_branch[4096];
                        size_t processed_pos = 0;
                        const char* scan = branch_content;
                        
                        while (*scan && processed_pos < sizeof(processed_branch) - 1) {
                            if (scan[0] == '{' && scan[1] == '{') {
                                const char* var_end = strstr(scan + 2, "}}");
                                if (var_end) {
                                    size_t var_name_len = var_end - scan - 2;
                                    if (var_name_len < 256) {
                                        char var_name[256];
                                        strncpy(var_name, scan + 2, var_name_len);
                                        var_name[var_name_len] = '\0';
                                        
                                        variable* var = store_get(var_store, var_name);
                                        const char* var_value = var ? variable_to_string(var) : "";
                                        
                                        size_t value_len = strlen(var_value);
                                        if (processed_pos + value_len < sizeof(processed_branch) - 1) {
                                            strcpy(processed_branch + processed_pos, var_value);
                                            processed_pos += value_len;
                                        }
                                        
                                        scan = var_end + 2;
                                        continue;
                                    }
                                }
                            }
                            processed_branch[processed_pos++] = *scan++;
                        }
                        processed_branch[processed_pos] = '\0';
                        
                        // Add processed branch to output
                        if (output_pos + processed_pos < output_size - 1) {
                            strcpy(output + output_pos, processed_branch);
                            output_pos += processed_pos;
                        }
                    }
                }
            }
            // If condition is false and no else branch, output nothing
            
            ptr = endif_end;
        } else {
            ptr = if_end;
        }
    }
    
    output[output_pos] = '\0';
    return 0;
}

/**
 * @brief Internal XMD context structure
 */
typedef struct xmd_context_internal {
    xmd_config* config;
    bool initialized;
    store* global_variables;
} xmd_context_internal;

/**
 * @brief Initialize XMD processor
 * @param config_path Path to configuration file (optional)
 * @return XMD context handle or NULL on error
 */
void* xmd_init(const char* config_path) {
    xmd_context_internal* ctx = calloc(1, sizeof(xmd_context_internal));
    if (!ctx) {
        return NULL;
    }
    
    // Initialize configuration
    ctx->config = config_create();
    if (!ctx->config) {
        free(ctx);
        return NULL;
    }
    
    // Load configuration file if provided
    if (config_path) {
        if (config_load_file(ctx->config, config_path) != 0) {
            config_destroy(ctx->config);
            free(ctx);
            return NULL;
        }
    }
    
    // Load environment configuration
    config_load_env(ctx->config);
    
    // Initialize global variable store
    ctx->global_variables = store_create();
    if (!ctx->global_variables) {
        config_destroy(ctx->config);
        free(ctx);
        return NULL;
    }
    
    ctx->initialized = true;
    return ctx;
}

/**
 * @brief Create result structure
 * @param error_code Error code
 * @param output Output string
 * @param error_message Error message
 * @return Result structure
 */
static xmd_result* create_result(int error_code, const char* output, const char* error_message) {
    xmd_result* result = calloc(1, sizeof(xmd_result));
    if (!result) {
        return NULL;
    }
    
    result->error_code = error_code;
    
    if (output) {
        result->output = strdup(output);
        result->output_length = strlen(output);
    } else {
        result->output = NULL;
        result->output_length = 0;
    }
    
    if (error_message) {
        result->error_message = strdup(error_message);
    } else {
        result->error_message = NULL;
    }
    
    result->processing_time_ms = 0.0;
    
    return result;
}

/**
 * @brief Process markdown string
 * @param handle XMD context handle
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_string(void* handle, const char* input, size_t input_length) {
    if (!handle || !input) {
        return NULL; // Return NULL for invalid parameters
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized) {
        return create_result(-1, NULL, "XMD context not initialized");
    }
    
    // Record start time
    clock_t start_time = clock();
    
    // Pre-process FOR loops (document-level processing)
    char* preprocessed_input = malloc(input_length * 4 + 10000); // Extra space for loop expansion
    if (!preprocessed_input) {
        return create_result(-1, NULL, "Memory allocation failed for preprocessing");
    }
    
    // Create variable store for preprocessing
    store* var_store = store_create();
    if (!var_store) {
        free(preprocessed_input);
        return create_result(-1, NULL, "Failed to create variable store");
    }
    
    // Copy global variables from context to processing store
    if (ctx->global_variables) {
        size_t global_var_count;
        char** global_keys = store_keys(ctx->global_variables, &global_var_count);
        if (global_keys) {
            for (size_t i = 0; i < global_var_count; i++) {
                variable* global_var = store_get(ctx->global_variables, global_keys[i]);
                if (global_var) {
                    // Create a copy of the variable for the processing store
                    const char* var_value = variable_to_string(global_var);
                    if (var_value) {
                        variable* var_copy = variable_create_string(var_value);
                        if (var_copy) {
                            store_set(var_store, global_keys[i], var_copy);
                        }
                    }
                }
            }
            free(global_keys);
        }
    }
    
    // First, extract and process variable declarations to populate the store and remove set directives
    char* var_processed_input = malloc(input_length * 2 + 1000);
    if (!var_processed_input) {
        free(preprocessed_input);
        store_destroy(var_store);
        return create_result(-1, NULL, "Memory allocation failed for variable preprocessing");
    }
    
    if (preprocess_variables(input, input_length, var_store, var_processed_input, input_length * 2 + 1000) != 0) {
        free(var_processed_input);
        free(preprocessed_input);
        store_destroy(var_store);
        return create_result(-1, NULL, "Failed to preprocess variables");
    }
    
    // Then pre-process for loops by expanding them
    size_t var_processed_len = strlen(var_processed_input);
    if (preprocess_for_loops(var_processed_input, var_processed_len, var_store, preprocessed_input, 
                            input_length * 4 + 10000) != 0) {
        free(var_processed_input);
        free(preprocessed_input);
        store_destroy(var_store);
        return create_result(-1, NULL, "Failed to preprocess for loops");
    }
    
    // Free var_processed_input as we now have preprocessed_input
    free(var_processed_input);
    
    // Then pre-process if statements by evaluating conditions and selecting branches
    char* if_processed_input = malloc(input_length * 4 + 10000);
    if (!if_processed_input) {
        free(preprocessed_input);
        store_destroy(var_store);
        return create_result(-1, NULL, "Memory allocation failed for if preprocessing");
    }
    
    size_t for_processed_len = strlen(preprocessed_input);
    if (preprocess_if_statements(preprocessed_input, for_processed_len, var_store, if_processed_input, 
                                input_length * 4 + 10000) != 0) {
        free(if_processed_input);
        free(preprocessed_input);
        store_destroy(var_store);
        return create_result(-1, NULL, "Failed to preprocess if statements");
    }
    
    // Replace preprocessed_input with if_processed_input for further processing
    free(preprocessed_input);
    preprocessed_input = if_processed_input;
    
    // Process the input through the XMD pipeline
    // 1. Create lexer to tokenize preprocessed input
    lexer* lex = lexer_create(preprocessed_input);
    if (!lex) {
        free(preprocessed_input);
        store_destroy(var_store);
        return create_result(-1, NULL, "Failed to create lexer");
    }
    
    // 3. Process tokens and build output
    size_t preprocessed_len = strlen(preprocessed_input);
    char* output = malloc(preprocessed_len * 2 + 1000); // Allocate extra space for processing
    if (!output) {
        store_destroy(var_store);
        lexer_free(lex);
        free(preprocessed_input);
        return create_result(-1, NULL, "Memory allocation failed");
    }
    
    // 4. Process the markdown content
    size_t output_pos = 0;
    token* tok;
    size_t last_line = 0;
    
    while ((tok = lexer_next_token(lex)) != NULL && tok->type != TOKEN_EOF) {
        // Add newlines if we've moved to a new line
        if (last_line > 0 && tok->line > last_line) {
            // Add newlines for the line difference
            size_t line_diff = tok->line - last_line;
            for (size_t i = 0; i < line_diff && output_pos < input_length * 2 + 998; i++) {
                output[output_pos++] = '\n';
            }
        }
        
        // Process each token based on its type
        switch (tok->type) {
            case TOKEN_TEXT:
                // Copy text content directly
                if (tok->value) {
                    size_t text_len = strlen(tok->value);
                    if (output_pos + text_len < input_length * 2 + 999) {
                        strcpy(output + output_pos, tok->value);
                        output_pos += text_len;
                    }
                }
                break;
                
            case TOKEN_VARIABLE_REF:
                // Process variable references
                if (tok->value) {
                    // Extract variable name (remove {{ and }})
                    char var_name[256];
                    strncpy(var_name, tok->value, sizeof(var_name) - 1);
                    var_name[sizeof(var_name) - 1] = '\0';
                    
                    // Remove {{ and }} if present
                    char* clean_name = var_name;
                    if (strncmp(clean_name, "{{", 2) == 0) {
                        clean_name += 2;
                    }
                    char* end = strstr(clean_name, "}}");
                    if (end) *end = '\0';
                    
                    // Look up variable in store
                    variable* var = store_get(var_store, clean_name);
                    const char* var_value = var ? variable_to_string(var) : "";
                    
                    if (output_pos + strlen(var_value) < input_length * 2 + 999) {
                        strcpy(output + output_pos, var_value);
                        output_pos += strlen(var_value);
                    }
                }
                break;
                
            case TOKEN_XMD_DIRECTIVE:
                // Process XMD directives
                if (tok->value) {
                    char directive_output[8192];
                    int bytes_written = process_xmd_directive(tok->value, var_store, 
                                                            directive_output, sizeof(directive_output));
                    if (bytes_written > 0 && output_pos + bytes_written < preprocessed_len * 2 + 999) {
                        strcpy(output + output_pos, directive_output);
                        output_pos += bytes_written;
                    }
                }
                break;
                
            default:
                // For other token types (including TOKEN_HEADING), process text with variable substitution
                if (tok->value) {
                    char processed_text[8192];
                    size_t processed_pos = 0;
                    const char* scan = tok->value;
                    
                    // Manual variable substitution for {{variable}} patterns
                    while (*scan && processed_pos < sizeof(processed_text) - 1) {
                        if (scan[0] == '{' && scan[1] == '{') {
                            const char* var_end = strstr(scan + 2, "}}");
                            if (var_end) {
                                // Extract variable name
                                size_t var_name_len = var_end - scan - 2;
                                if (var_name_len < 256) {
                                    char var_name[256];
                                    strncpy(var_name, scan + 2, var_name_len);
                                    var_name[var_name_len] = '\0';
                                    
                                    // Look up variable value
                                    variable* var = store_get(var_store, var_name);
                                    const char* var_value = var ? variable_to_string(var) : "";
                                    
                                    // Add variable value to output
                                    size_t value_len = strlen(var_value);
                                    if (processed_pos + value_len < sizeof(processed_text) - 1) {
                                        strcpy(processed_text + processed_pos, var_value);
                                        processed_pos += value_len;
                                    }
                                    
                                    scan = var_end + 2; // Skip past }}
                                    continue;
                                }
                            }
                        }
                        processed_text[processed_pos++] = *scan++;
                    }
                    processed_text[processed_pos] = '\0';
                    
                    // Add processed text to output
                    if (output_pos + processed_pos < preprocessed_len * 2 + 999) {
                        strcpy(output + output_pos, processed_text);
                        output_pos += processed_pos;
                    }
                }
                break;
        }
        
        // Update last line for newline tracking
        last_line = tok->line;
        token_free(tok);
    }
    
    if (tok) {
        token_free(tok);
    }
    
    output[output_pos] = '\0';
    
    // Cleanup
    store_destroy(var_store);
    lexer_free(lex);
    free(preprocessed_input);
    
    // Calculate processing time
    clock_t end_time = clock();
    double processing_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    xmd_result* result = create_result(0, output, NULL);
    if (result) {
        result->processing_time_ms = processing_time;
    }
    
    free(output);
    return result;
}

/**
 * @brief Process markdown file
 * @param handle XMD context handle
 * @param input_path Input file path
 * @param output_path Output file path (optional)
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_file(void* handle, const char* input_path, const char* output_path) {
    if (!handle || !input_path) {
        return NULL; // Return NULL for invalid parameters
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized) {
        return create_result(-1, NULL, "XMD context not initialized");
    }
    
    // Read input file
    FILE* input_file = fopen(input_path, "r");
    if (!input_file) {
        return create_result(-1, NULL, "Failed to open input file");
    }
    
    // Get file size
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(input_file);
        return create_result(-1, NULL, "Failed to get file size");
    }
    
    // Read file content
    char* content = malloc(file_size + 1);
    if (!content) {
        fclose(input_file);
        return create_result(-1, NULL, "Memory allocation failed");
    }
    
    size_t bytes_read = fread(content, 1, file_size, input_file);
    content[bytes_read] = '\0';
    fclose(input_file);
    
    // Process the content
    xmd_result* result = xmd_process_string(handle, content, bytes_read);
    
    // Write output file if specified
    if (output_path && result && result->error_code == 0) {
        FILE* output_file = fopen(output_path, "w");
        if (output_file) {
            fwrite(result->output, 1, result->output_length, output_file);
            fclose(output_file);
        }
    }
    
    free(content);
    return result;
}

/**
 * @brief Validate markdown syntax
 * @param handle XMD context handle
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Validation result (must be freed with xmd_result_free)
 */
xmd_result* xmd_validate(void* handle, const char* input, size_t input_length) {
    if (!handle || !input) {
        return NULL; // Return NULL for invalid parameters
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized) {
        return create_result(-1, NULL, "XMD context not initialized");
    }
    
    // Record start time
    clock_t start_time = clock();
    
    // Basic validation - check for balanced directives
    // In a full implementation, this would parse and validate the entire syntax
    int directive_balance = 0;
    const char* pos = input;
    const char* end = input + input_length;
    
    while (pos < end) {
        if (strncmp(pos, "<!-- xmd:", 9) == 0) {
            // Found XMD directive start
            if (strstr(pos, "if") || strstr(pos, "for") || strstr(pos, "while") || strstr(pos, "try")) {
                directive_balance++;
            } else if (strstr(pos, "endif") || strstr(pos, "endfor") || strstr(pos, "endwhile") || strstr(pos, "endtry")) {
                directive_balance--;
            }
        }
        pos++;
    }
    
    // Calculate processing time
    clock_t end_time = clock();
    double processing_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    xmd_result* result;
    if (directive_balance == 0) {
        result = create_result(0, "Validation successful", NULL);
    } else {
        result = create_result(1, NULL, "Unbalanced XMD directives");
    }
    
    if (result) {
        result->processing_time_ms = processing_time;
    }
    
    return result;
}

/**
 * @brief Set configuration option
 * @param handle XMD context handle
 * @param key Configuration key
 * @param value Configuration value
 * @return 0 on success, -1 on error
 */
int xmd_set_config(void* handle, const char* key, const char* value) {
    if (!handle || !key || !value) {
        return -1;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized || !ctx->config) {
        return -1;
    }
    
    config_value* config_val = malloc(sizeof(config_value));
    if (!config_val) {
        return -1;
    }
    
    config_val->type = CONFIG_STRING;
    config_val->data.string_val = strdup(value);
    
    return config_set(ctx->config, key, config_val);
}

/**
 * @brief Get configuration option
 * @param handle XMD context handle
 * @param key Configuration key
 * @return Configuration value or NULL if not found (must be freed)
 */
char* xmd_get_config(void* handle, const char* key) {
    if (!handle || !key) {
        return NULL;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized || !ctx->config) {
        return NULL;
    }
    
    config_value* value = config_get(ctx->config, key);
    if (value && value->type == CONFIG_STRING && value->data.string_val) {
        return strdup(value->data.string_val);
    }
    
    return NULL;
}

/**
 * @brief Free result structure
 * @param result Result structure
 */
void xmd_result_free(xmd_result* result) {
    if (!result) {
        return;
    }
    
    free(result->output);
    free(result->error_message);
    free(result);
}

/**
 * @brief Cleanup XMD processor
 * @param handle XMD context handle
 */
void xmd_cleanup(void* handle) {
    if (!handle) {
        return;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    
    if (ctx->config) {
        config_destroy(ctx->config);
    }
    
    if (ctx->global_variables) {
        store_destroy(ctx->global_variables);
    }
    
    free(ctx);
}

/**
 * @brief Get version information
 * @return Version string
 */
const char* xmd_get_version(void) {
    return "1.0.0";
}



/**
 * @brief Set variable in processor context
 * @param processor Processor instance (actually xmd_context_internal*)
 * @param key Variable name
 * @param value Variable value
 * @return 0 on success, -1 on error
 */
int xmd_set_variable(void* processor, const char* key, const char* value) {
    if (!processor || !key || !value) {
        return -1;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)processor;
    if (!ctx->initialized || !ctx->global_variables) {
        return -1;
    }
    
    // Create a string variable and store it
    variable* var = variable_create_string(value);
    if (!var) {
        return -1;
    }
    
    if (!store_set(ctx->global_variables, key, var)) {
        variable_unref(var);
        return -1;
    }
    
    return 0;
}

/**
 * @brief Get variable from processor context
 * @param processor Processor instance (actually xmd_context_internal*)
 * @param key Variable name
 * @return Variable value or NULL if not found
 */
char* xmd_get_variable(void* processor, const char* key) {
    if (!processor || !key) {
        return NULL;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)processor;
    if (!ctx->initialized) {
        return NULL;
    }
    
    // In a full implementation, would lookup from variable context
    // For now, return NULL (not found)
    return NULL;
}

/**
 * @brief Create default XMD configuration
 * @return Default configuration structure
 */
void* xmd_config_create_default(void) {
    return config_create();
}

/**
 * @brief Free XMD configuration
 * @param config Configuration to free
 */
void xmd_config_free(void* config) {
    if (config) {
        config_destroy((xmd_config*)config);
    }
}

/**
 * @brief Create XMD processor
 * @param config Configuration
 * @return Processor instance or NULL on error
 */
void* xmd_processor_create(const void* config) {
    (void)config; // Suppress unused parameter warning
    
    // Create using the existing xmd_init function
    return xmd_init(NULL);
}

/**
 * @brief Free XMD processor
 * @param processor Processor to free
 */
void xmd_processor_free(void* processor) {
    if (processor) {
        xmd_cleanup(processor);
    }
}