/**
 * @file process_script_block.c
 * @brief Process script-like multiline directive blocks
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/ast_evaluator.h"
#include "../../../include/variable.h"



/**
 * @brief Process for loop with array iteration and body execution
 * @param line The for loop line
 * @param lines Array of remaining lines
 * @param line_count Number of remaining lines
 * @param current_line Current line index (will be updated)
 * @param ctx Processor context
 * @return 0 on success, -1 on error
 */
static int process_for_loop_script(const char* line, char** lines, int line_count, int* current_line, processor_context* ctx) {
    // Parse "for varname in arrayname"
    char* line_copy = strdup(line);
    char* in_pos = strstr(line_copy, " in ");
    
    if (!in_pos) {
        free(line_copy);
        return -1;
    }
    
    *in_pos = '\0';
    char* var_name = trim_whitespace(line_copy + 4); // Skip "for "
    char* array_name = trim_whitespace(in_pos + 4);
    
    // Get the array variable
    variable* array_var = store_get(ctx->variables, array_name);
    if (!array_var || array_var->type != VAR_ARRAY) {
        free(line_copy);
        return -1;
    }
    
    // Find the loop body (lines until we hit something that's not indented)
    int body_start = *current_line + 1;
    int body_end = body_start;
    
    while (body_end < line_count && (lines[body_end][0] == ' ' || lines[body_end][0] == '\t')) {
        body_end++;
    }
    
    // Execute the loop body for each array element
    size_t array_size = variable_array_size(array_var);
    
    // DEBUG: For now, force loop through all elements
    for (size_t i = 0; i < array_size; i++) {
        variable* item = variable_array_get(array_var, i);
        if (item && item->type == VAR_STRING) {
            // Set loop variable
            variable* loop_var = variable_create_string(item->value.string_value);
            store_set(ctx->variables, var_name, loop_var);
            variable_unref(loop_var);
            
            // Execute body lines for this iteration
            for (int line_idx = body_start; line_idx < body_end; line_idx++) {
                char* body_line = trim_whitespace(lines[line_idx]);
                
                // Check for nested for loop
                if (strncmp(body_line, "for ", 4) == 0) {
                    // Process nested for loop recursively
                    process_for_loop_script(body_line, lines, line_count, &line_idx, ctx);
                } else if (strstr(body_line, "+=")) {
                    // Process assignment with concatenation
                    char* line_copy = strdup(body_line);
                    char* eq_pos = strstr(line_copy, "+=");
                    *eq_pos = '\0';
                    char* target_var = trim_whitespace(line_copy);
                    char* expr = trim_whitespace(eq_pos + 2);
                    
                    // Evaluate the expression
                    char* new_value = ast_evaluate_concatenation_expression(expr, ctx);
                    
                    // Get existing value and concatenate
                    variable* existing = store_get(ctx->variables, target_var);
                    if (existing && existing->type == VAR_STRING) {
                        size_t total_len = strlen(existing->value.string_value) + strlen(new_value) + 1;
                        char* combined = malloc(total_len);
                        snprintf(combined, total_len, "%s%s", existing->value.string_value, new_value);
                        
                        variable* combined_var = variable_create_string(combined);
                        store_set(ctx->variables, target_var, combined_var);
                        variable_unref(combined_var);
                        free(combined);
                    } else {
                        // If variable doesn't exist or isn't a string, create it
                        variable* new_var = variable_create_string(new_value);
                        store_set(ctx->variables, target_var, new_var);
                        variable_unref(new_var);
                    }
                    
                    free(new_value);
                    free(line_copy);
                }
            }
        }
    }
    
    // Update current line to skip the body
    *current_line = body_end - 1;
    
    free(line_copy);
    return 0;
}

/**
 * @brief Process script-like multiline directive blocks
 * @param directive_content Content of the script block
 * @param variables Variable store for processing
 */
void process_script_block(const char* directive_content, store* variables) {
    char* content_copy = strdup(directive_content);
    
    // Split into lines
    char* lines[100];
    int line_count = 0;
    char* line = strtok(content_copy, "\n\r");
    
    while (line && line_count < 100) {
        lines[line_count++] = strdup(line);
        line = strtok(NULL, "\n\r");
    }
    
    processor_context* ctx = create_context(variables);
    
    // Process each line
    for (int i = 0; i < line_count; i++) {
        char* trimmed = trim_whitespace(lines[i]);
        
        if (strncmp(trimmed, "set ", 4) == 0) {
            // Handle set directive - check if it contains concatenation
            char* set_args = trimmed + 4;
            if (strstr(set_args, " + ")) {
                // Handle concatenation expression
                char* args_copy = strdup(set_args);
                char* equals_pos = strstr(args_copy, " = ");
                if (equals_pos) {
                    *equals_pos = '\0';
                    char* var_name = trim_whitespace(args_copy);
                    char* expr = trim_whitespace(equals_pos + 3);
                    
                    // Evaluate the concatenation expression
                    char* result = ast_evaluate_concatenation_expression(expr, ctx);
                    if (result) {
                        variable* var = variable_create_string(result);
                        if (var) {
                            store_set(ctx->variables, var_name, var);
                            variable_unref(var);
                        }
                        free(result);
                    }
                }
                free(args_copy);
            } else {
                // Handle regular set directive
                char output[1024];
                process_set(set_args, ctx, output, sizeof(output));
            }
        } else if (strncmp(trimmed, "for ", 4) == 0) {
            // Handle for loop
            process_for_loop_script(trimmed, lines, line_count, &i, ctx);
        } else if (strstr(trimmed, "+=")) {
            // Handle standalone += assignment with expression evaluation
            char* line_copy = strdup(trimmed);
            char* eq_pos = strstr(line_copy, "+=");
            if (eq_pos) {
                *eq_pos = '\0';
                char* target_var = trim_whitespace(line_copy);
                char* expr = trim_whitespace(eq_pos + 2);
                
                // Check if expression contains concatenation
                if (strstr(expr, " + ")) {
                    // Evaluate the concatenation expression
                    char* new_value = ast_evaluate_concatenation_expression(expr, ctx);
                    
                    // Get existing value and concatenate
                    variable* existing = store_get(ctx->variables, target_var);
                    if (existing && existing->type == VAR_STRING) {
                        size_t total_len = strlen(existing->value.string_value) + strlen(new_value) + 1;
                        char* combined = malloc(total_len);
                        snprintf(combined, total_len, "%s%s", existing->value.string_value, new_value);
                        
                        variable* combined_var = variable_create_string(combined);
                        store_set(ctx->variables, target_var, combined_var);
                        variable_unref(combined_var);
                        free(combined);
                    } else {
                        // If variable doesn't exist or isn't a string, create it
                        variable* new_var = variable_create_string(new_value);
                        store_set(ctx->variables, target_var, new_var);
                        variable_unref(new_var);
                    }
                    
                    free(new_value);
                } else {
                    // Simple += without concatenation expression, use process_set
                    char output[1024];
                    process_set(trimmed, ctx, output, sizeof(output));
                }
            }
            free(line_copy);
        } else if (strncmp(trimmed, "print(", 6) == 0) {
            // Handle print function
            char output[4096];
            process_print_function(trimmed, ctx, output, sizeof(output));
            
            // Accumulate print output
            variable* output_var = store_get(ctx->variables, "_multiline_output");
            if (output_var && output_var->type == VAR_STRING) {
                size_t new_len = strlen(output_var->value.string_value) + strlen(output) + 2;
                char* new_output = malloc(new_len);
                if (strlen(output_var->value.string_value) > 0) {
                    snprintf(new_output, new_len, "%s\n%s", output_var->value.string_value, output);
                } else {
                    snprintf(new_output, new_len, "%s", output);
                }
                variable* new_var = variable_create_string(new_output);
                store_set(ctx->variables, "_multiline_output", new_var);
                variable_unref(new_var);
                free(new_output);
            } else {
                variable* new_var = variable_create_string(output);
                store_set(ctx->variables, "_multiline_output", new_var);
                variable_unref(new_var);
            }
        }
    }
    
    // Cleanup
    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    destroy_context(ctx);
    free(content_copy);
}