/**
 * @file preprocess_if_statements.c
 * @brief If statement preprocessing function
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Preprocess if statements by evaluating conditions and selecting branches
 * @param input Input content
 * @param input_length Input length
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Output buffer size
 * @return 0 on success, -1 on error
 */
int preprocess_if_statements(const char* input, size_t input_length, store* var_store, 
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
            bool condition_result = c_api_evaluate_condition(condition, var_store);
            
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
