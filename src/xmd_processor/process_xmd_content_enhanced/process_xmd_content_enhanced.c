/**
 * @file process_xmd_content_enhanced.c
 * @brief Enhanced XMD content processing with proper loop iteration support
 * @author XMD Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"
#include "../../../include/ast_evaluator.h"

#define MAX_LOOP_DEPTH 8

typedef struct {
    char** items;
    int item_count;
    int current_index;
    char* loop_var_name;
    const char* loop_start_pos;
    const char* loop_end_pos;
} loop_state;

typedef struct {
    loop_state loops[MAX_LOOP_DEPTH];
    int loop_depth;
    int total_iterations;
    processor_context* ctx;
} enhanced_context;

/**
 * @brief Process content within a loop iteration
 */
static char* process_loop_content(enhanced_context* ectx, const char* content_start, 
                                 const char* content_end, loop_state* current_loop) {
    // Set loop variable to current item
    if (current_loop->current_index < current_loop->item_count) {
        variable* item_var = variable_create_string(current_loop->items[current_loop->current_index]);
        if (item_var) {
            store_set(ectx->ctx->variables, current_loop->loop_var_name, item_var);
            variable_unref(item_var);
        }
    }
    
    // Create a temporary input string for the loop content
    size_t content_len = content_end - content_start;
    char* temp_input = malloc(content_len + 1);
    strncpy(temp_input, content_start, content_len);
    temp_input[content_len] = '\0';
    
    // Process the loop content recursively
    char* result = ast_process_xmd_content(temp_input, ectx->ctx->variables);
    
    free(temp_input);
    return result;
}

/**
 * @brief Enhanced XMD processing function with proper loop support
 * @param input Input markdown content with XMD directives
 * @param variables Variable store for XMD processing
 * @return Processed markdown content (caller must free) or NULL on error
 */
char* process_xmd_content_enhanced(const char* input, store* variables) {
    if (!input || !variables) return NULL;
    
    processor_context* ctx = create_context(variables);
    enhanced_context ectx = { .loop_depth = 0, .total_iterations = 0, .ctx = ctx };
    
    size_t input_len = strlen(input);
    size_t output_capacity = input_len * 3;
    char* output = malloc(output_capacity);
    size_t output_pos = 0;
    
    const char* ptr = input;
    const char* input_end = input + input_len;
    
    while (ptr < input_end) {
        // Look for HTML comment start
        const char* comment_start = strstr(ptr, "<!--");
        
        if (!comment_start) {
            // No more comments, copy rest if executing
            if (should_execute_block(ctx)) {
                size_t remaining = input_end - ptr;
                if (output_pos + remaining >= output_capacity) {
                    output_capacity = (output_pos + remaining + 1) * 2;
                    output = realloc(output, output_capacity);
                }
                memcpy(output + output_pos, ptr, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Copy content before comment if executing
        if (should_execute_block(ctx)) {
            size_t before_len = comment_start - ptr;
            if (output_pos + before_len >= output_capacity) {
                output_capacity = (output_pos + before_len + 1000) * 2;
                output = realloc(output, output_capacity);
            }
            memcpy(output + output_pos, ptr, before_len);
            output_pos += before_len;
        }
        
        // Find comment end
        const char* comment_end = strstr(comment_start + 4, "-->");
        if (!comment_end) {
            // Malformed comment, copy as-is if executing
            if (should_execute_block(ctx)) {
                size_t remaining = input_end - comment_start;
                if (output_pos + remaining >= output_capacity) {
                    output_capacity = (output_pos + remaining + 1) * 2;
                    output = realloc(output, output_capacity);
                }
                memcpy(output + output_pos, comment_start, remaining);
                output_pos += remaining;
            }
            break;
        }
        
        // Extract comment content
        size_t comment_content_len = comment_end - comment_start - 4;
        char* comment_content = malloc(comment_content_len + 1);
        strncpy(comment_content, comment_start + 4, comment_content_len);
        comment_content[comment_content_len] = '\0';
        
        // Check if this is an XMD directive
        char* trimmed = trim_whitespace(comment_content);
        bool is_xmd_directive = (strncmp(trimmed, "xmd:", 4) == 0);
        bool is_multiline = is_xmd_directive && is_multiline_directive(comment_content);
        
        if (is_xmd_directive) {
            char* directive = trim_whitespace(trimmed + 4);
            
            // Handle for loops specially
            if (strncmp(directive, "for ", 4) == 0) {
                if (should_execute_block(ctx) && ectx.loop_depth < MAX_LOOP_DEPTH) {
                    // Parse for loop
                    char* args = trim_whitespace(directive + 4);
                    char** items = NULL;
                    int item_count = 0;
                    
                    // Parse for loop syntax: "item in collection_or_range"
                    char* args_copy = strdup(args);
                    char* in_pos = strstr(args_copy, " in ");
                    
                    if (in_pos) {
                        *in_pos = '\0';
                        char* item_name = trim_whitespace(args_copy);
                        char* collection_expr = trim_whitespace(in_pos + 4);
                        
                        // Get items from collection or range
                        if (strstr(collection_expr, "..")) {
                            parse_range(collection_expr, variables, &items, &item_count);
                        } else {
                            parse_collection(collection_expr, variables, &items, &item_count);
                        }
                        
                        if (items && item_count > 0) {
                            // Find matching endfor
                            const char* endfor_pos = find_matching_endfor(comment_end + 3, input_end);
                            
                            if (endfor_pos) {
                                // Set up loop state
                                loop_state* current_loop = &ectx.loops[ectx.loop_depth];
                                current_loop->items = items;
                                current_loop->item_count = item_count;
                                current_loop->current_index = 0;
                                current_loop->loop_var_name = strdup(item_name);
                                current_loop->loop_start_pos = comment_end + 3;
                                current_loop->loop_end_pos = endfor_pos;
                                
                                ectx.loop_depth++;
                                
                                // Iterate through all items
                                for (int i = 0; i < item_count && i < MAX_LOOP_ITERATIONS && ectx.total_iterations < MAX_LOOP_ITERATIONS; i++) {
                                    current_loop->current_index = i;
                                    ectx.total_iterations++;
                                    
                                    // Process loop content
                                    char* loop_result = process_loop_content(&ectx, 
                                        current_loop->loop_start_pos, 
                                        current_loop->loop_end_pos - strlen("<!-- xmd:endfor -->"),
                                        current_loop);
                                    
                                    if (loop_result) {
                                        size_t result_len = strlen(loop_result);
                                        if (output_pos + result_len >= output_capacity) {
                                            output_capacity = (output_pos + result_len + 1000) * 2;
                                            output = realloc(output, output_capacity);
                                        }
                                        memcpy(output + output_pos, loop_result, result_len);
                                        output_pos += result_len;
                                        free(loop_result);
                                    }
                                }
                                
                                // Clean up loop state
                                for (int i = 0; i < current_loop->item_count; i++) {
                                    free(current_loop->items[i]);
                                }
                                free(current_loop->items);
                                free(current_loop->loop_var_name);
                                ectx.loop_depth--;
                                
                                // Skip to after endfor
                                ptr = current_loop->loop_end_pos;
                                free(args_copy);
                                free(comment_content);
                                continue;
                            }
                        }
                    }
                    free(args_copy);
                }
            } else {
                // Handle other directives normally - always process as multiline in enhanced mode
                if (true) { // All XMD directives treated as multiline in enhanced mode
                    // Process multiline directive and capture output
                    process_multiline_directive_enhanced(comment_content, variables, ctx);
                    
                    // Get accumulated output from multiline processing
                    variable* output_var = store_get(variables, "_multiline_output");
                    if (output_var && should_execute_block(ctx)) {
                        const char* multiline_output = variable_to_string(output_var);
                        if (multiline_output && strlen(multiline_output) > 0) {
                            size_t dir_len = strlen(multiline_output);
                            if (output_pos + dir_len >= output_capacity) {
                                output_capacity = (output_pos + dir_len + 1000) * 2;
                                output = realloc(output, output_capacity);
                            }
                            memcpy(output + output_pos, multiline_output, dir_len);
                            output_pos += dir_len;
                            
                            // Clear the multiline output variable for next use
                            variable* empty_var = variable_create_string("");
                            if (empty_var) {
                                store_set(variables, "_multiline_output", empty_var);
                                variable_unref(empty_var);
                            }
                        }
                    }
                } else {
                    // Check if this is an exec directive - use dynamic allocation for it
                    char* space = strchr(directive, ' ');
                    char command[64];
                    char* args = "";
                    
                    if (space) {
                        size_t cmd_len = space - directive;
                        if (cmd_len >= sizeof(command)) cmd_len = sizeof(command) - 1;
                        strncpy(command, directive, cmd_len);
                        command[cmd_len] = '\0';
                        args = trim_whitespace(space + 1);
                    } else {
                        strncpy(command, directive, sizeof(command) - 1);
                        command[sizeof(command) - 1] = '\0';
                    }
                    
                    char* directive_output = NULL;
                    
                    if (strcmp(command, "exec") == 0) {
                        // Use dynamic allocation for exec commands
                        directive_output = process_exec_dynamic(args, ctx);
                    } else {
                        // Use fixed buffer for other directives
                        char* fixed_buffer = malloc(65536);  // 64KB should be enough for non-exec directives
                        if (fixed_buffer) {
                            process_directive(trimmed, ctx, fixed_buffer, 65536);
                            directive_output = fixed_buffer;
                        }
                    }
                    
                    // Add directive output if any
                    if (directive_output && strlen(directive_output) > 0 && should_execute_block(ctx)) {
                        size_t dir_len = strlen(directive_output);
                        if (output_pos + dir_len >= output_capacity) {
                            output_capacity = (output_pos + dir_len + 1000) * 2;
                            output = realloc(output, output_capacity);
                        }
                        memcpy(output + output_pos, directive_output, dir_len);
                        output_pos += dir_len;
                    }
                    
                    // Rule 14: Memory management - free allocated buffer
                    if (directive_output) {
                        free(directive_output);
                    }
                }
            }
        } else {
            // Regular HTML comment, copy if executing
            if (should_execute_block(ctx)) {
                size_t comment_len = comment_end + 3 - comment_start;
                if (output_pos + comment_len >= output_capacity) {
                    output_capacity = (output_pos + comment_len + 1) * 2;
                    output = realloc(output, output_capacity);
                }
                memcpy(output + output_pos, comment_start, comment_len);
                output_pos += comment_len;
            }
        }
        
        free(comment_content);
        ptr = comment_end + 3;
        
        // If this was a multiline directive that didn't produce output,
        // and it was at the start of a line, skip any trailing newline
        // to avoid creating empty lines
        if (is_multiline) {
            // Check if the directive was at the beginning of a line
            bool at_line_start = (comment_start == input || *(comment_start - 1) == '\n');
            
            // Check if no output was produced
            variable* output_var = store_get(variables, "_multiline_output");
            bool no_output = (!output_var || !output_var->value.string_value || 
                            strlen(output_var->value.string_value) == 0);
            
            // If at line start and no output, skip trailing newline
            if (at_line_start && no_output && *ptr == '\n') {
                ptr++;
            }
        }
    }
    
    output[output_pos] = '\0';
    
    // Substitute variables in final output
    char* final_output = substitute_variables(output, variables);
    
    free(output);
    free(ctx);
    
    return final_output;
}
