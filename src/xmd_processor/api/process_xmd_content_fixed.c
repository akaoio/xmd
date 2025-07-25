/**
 * @file process_xmd_content_fixed.c
 * @brief Fixed XMD content processing with full loop iteration support
 * @author XMD Team
 * @date 2025-07-26
 */

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

#define MAX_LOOP_DEPTH 32
#define MAX_LOOP_ITERATIONS 10000

typedef struct {
    char** items;
    int item_count;
    int current_index;
    char* loop_var_name;
    store* saved_variables;  // For variable scoping
} loop_context;

typedef struct {
    loop_context loops[MAX_LOOP_DEPTH];
    int loop_depth;
} loop_stack;

/**
 * @brief Find matching endfor for a for directive
 */
static const char* find_matching_endfor(const char* start, const char* input_end) {
    const char* ptr = start;
    int for_count = 1;
    
    while (ptr < input_end && for_count > 0) {
        const char* comment_start = strstr(ptr, "<!--");
        if (!comment_start) break;
        
        const char* comment_end = strstr(comment_start + 4, "-->");
        if (!comment_end) break;
        
        // Extract comment content
        size_t comment_len = comment_end - comment_start - 4;
        char* comment_content = malloc(comment_len + 1);
        strncpy(comment_content, comment_start + 4, comment_len);
        comment_content[comment_len] = '\0';
        
        char* trimmed = trim_whitespace(comment_content);
        
        if (strncmp(trimmed, "xmd:", 4) == 0) {
            char* directive = trim_whitespace(trimmed + 4);
            if (strncmp(directive, "for ", 4) == 0) {
                for_count++;
            } else if (strcmp(directive, "endfor") == 0) {
                for_count--;
                if (for_count == 0) {
                    free(comment_content);
                    return comment_end + 3;
                }
            }
        }
        
        free(comment_content);
        ptr = comment_end + 3;
    }
    
    return NULL;
}

/**
 * @brief Create variable scope backup for loop isolation
 */
static store* backup_variable_scope(store* variables, const char* loop_var_name) {
    store* backup = store_create();
    if (!backup) return NULL;
    
    // Get all keys from original store
    size_t count;
    char** keys = store_keys(variables, &count);
    if (!keys) return backup;
    
    // Copy all variables except the loop variable
    for (size_t i = 0; i < count; i++) {
        if (strcmp(keys[i], loop_var_name) != 0) {
            variable* var = store_get(variables, keys[i]);
            if (var) {
                variable* copy = variable_copy(var);
                if (copy) {
                    store_set(backup, keys[i], copy);
                    variable_unref(copy);
                }
            }
        }
        free(keys[i]);
    }
    free(keys);
    
    return backup;
}

/**
 * @brief Restore variable scope after loop
 */
static void restore_variable_scope(store* variables, store* backup, const char* loop_var_name) {
    // Clear current variables
    store_clear(variables);
    
    // Restore from backup
    size_t count;
    char** keys = store_keys(backup, &count);
    if (!keys) return;
    
    for (size_t i = 0; i < count; i++) {
        variable* var = store_get(backup, keys[i]);
        if (var) {
            variable* copy = variable_copy(var);
            if (copy) {
                store_set(variables, keys[i], copy);
                variable_unref(copy);
            }
        }
        free(keys[i]);
    }
    free(keys);
}

/**
 * @brief Process loop body content with current loop variable
 */
static char* process_loop_body(const char* body_start, const char* body_end, 
                              processor_context* ctx, loop_context* loop_ctx) {
    // Set current loop variable
    if (loop_ctx->current_index < loop_ctx->item_count) {
        variable* item_var = variable_create_string(loop_ctx->items[loop_ctx->current_index]);
        if (item_var) {
            store_set(ctx->variables, loop_ctx->loop_var_name, item_var);
            variable_unref(item_var);
        }
    }
    
    // Create temporary input for the loop body
    size_t body_len = body_end - body_start;
    char* temp_input = malloc(body_len + 1);
    strncpy(temp_input, body_start, body_len);
    temp_input[body_len] = '\0';
    
    // Process the body content with a fresh context but same variables
    processor_context* loop_ctx_proc = create_context(ctx->variables);
    size_t input_len = strlen(temp_input);
    size_t output_capacity = input_len * 2;
    char* output = malloc(output_capacity);
    size_t output_pos = 0;
    
    const char* ptr = temp_input;
    const char* input_end = temp_input + input_len;
    
    while (ptr < input_end) {
        // Look for HTML comment start
        const char* comment_start = strstr(ptr, "<!--");
        
        if (!comment_start) {
            // No more comments, copy rest if executing
            if (should_execute_block(loop_ctx_proc)) {
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
        if (should_execute_block(loop_ctx_proc)) {
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
            if (should_execute_block(loop_ctx_proc)) {
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
        
        if (strncmp(trimmed, "xmd:", 4) == 0) {
            char* directive = trim_whitespace(trimmed + 4);
            
            // Process directive with loop context
            char directive_output[4096];
            process_directive(trimmed, loop_ctx_proc, directive_output, sizeof(directive_output));
            
            // Add directive output if any
            if (strlen(directive_output) > 0 && should_execute_block(loop_ctx_proc)) {
                size_t dir_len = strlen(directive_output);
                if (output_pos + dir_len >= output_capacity) {
                    output_capacity = (output_pos + dir_len + 1000) * 2;
                    output = realloc(output, output_capacity);
                }
                memcpy(output + output_pos, directive_output, dir_len);
                output_pos += dir_len;
            }
        } else {
            // Regular HTML comment, copy if executing
            if (should_execute_block(loop_ctx_proc)) {
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
    }
    
    output[output_pos] = '\0';
    
    // Substitute variables in final output
    char* final_output = substitute_variables(output, ctx->variables);
    
    free(output);
    free(temp_input);
    free(loop_ctx_proc);
    
    return final_output;
}

/**
 * @brief Enhanced XMD processing function with full loop support
 * @param input Input markdown content with XMD directives
 * @param variables Variable store for XMD processing
 * @return Processed markdown content (caller must free) or NULL on error
 */
char* process_xmd_content_fixed(const char* input, store* variables) {
    if (!input || !variables) return NULL;
    
    processor_context* ctx = create_context(variables);
    loop_stack loops = { .loop_depth = 0 };
    
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
        
        if (strncmp(trimmed, "xmd:", 4) == 0) {
            char* directive = trim_whitespace(trimmed + 4);
            
            // Handle for loops with full iteration
            if (strncmp(directive, "for ", 4) == 0) {
                if (should_execute_block(ctx) && loops.loop_depth < MAX_LOOP_DEPTH) {
                    // Parse for loop arguments
                    char* args = trim_whitespace(directive + 4);
                    char* args_copy = strdup(args);
                    char* in_pos = strstr(args_copy, " in ");
                    
                    if (in_pos) {
                        *in_pos = '\0';
                        char* item_name = trim_whitespace(args_copy);
                        char* collection_expr = trim_whitespace(in_pos + 4);
                        
                        // Validate for loop syntax
                        if (strlen(item_name) == 0) {
                            const char* error_msg = "Error: For loop missing variable name";
                            if (should_execute_block(ctx)) {
                                size_t error_len = strlen(error_msg);
                                if (output_pos + error_len >= output_capacity) {
                                    output_capacity = (output_pos + error_len + 1000) * 2;
                                    output = realloc(output, output_capacity);
                                }
                                memcpy(output + output_pos, error_msg, error_len);
                                output_pos += error_len;
                            }
                            free(args_copy);
                            free(comment_content);
                            ptr = comment_end + 3;
                            continue;
                        }
                        
                        if (strlen(collection_expr) == 0) {
                            const char* error_msg = "Error: For loop missing collection";
                            if (should_execute_block(ctx)) {
                                size_t error_len = strlen(error_msg);
                                if (output_pos + error_len >= output_capacity) {
                                    output_capacity = (output_pos + error_len + 1000) * 2;
                                    output = realloc(output, output_capacity);
                                }
                                memcpy(output + output_pos, error_msg, error_len);
                                output_pos += error_len;
                            }
                            free(args_copy);
                            free(comment_content);
                            ptr = comment_end + 3;
                            continue;
                        }
                        
                        // Parse collection or range
                        char** items = NULL;
                        int item_count = 0;
                        
                        if (strstr(collection_expr, "..")) {
                            parse_range(collection_expr, variables, &items, &item_count);
                        } else {
                            parse_collection(collection_expr, variables, &items, &item_count);
                        }
                        
                        // Find matching endfor first
                        const char* endfor_pos = find_matching_endfor(comment_end + 3, input_end);
                        
                        if (endfor_pos) {
                            if (items && item_count > 0 && item_count <= MAX_LOOP_ITERATIONS) {
                                // Set up loop context with variable scoping
                                loop_context* current_loop = &loops.loops[loops.loop_depth];
                                current_loop->items = items;
                                current_loop->item_count = item_count;
                                current_loop->loop_var_name = strdup(item_name);
                                current_loop->saved_variables = backup_variable_scope(variables, item_name);
                                
                                loops.loop_depth++;
                                
                                // Find loop body boundaries
                                const char* body_start = comment_end + 3;
                                const char* body_end = endfor_pos - strlen("<!-- xmd:endfor -->");
                                
                                // Iterate through all items
                                for (int i = 0; i < item_count; i++) {
                                    current_loop->current_index = i;
                                    
                                    char* loop_result = process_loop_body(body_start, body_end, ctx, current_loop);
                                    
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
                                
                                // Restore variable scope
                                restore_variable_scope(variables, current_loop->saved_variables, item_name);
                                store_destroy(current_loop->saved_variables);
                                
                                // Clean up loop context
                                for (int i = 0; i < current_loop->item_count; i++) {
                                    free(current_loop->items[i]);
                                }
                                free(current_loop->items);
                                free(current_loop->loop_var_name);
                                loops.loop_depth--;
                                
                                // Skip to after endfor
                                ptr = endfor_pos;
                                free(args_copy);
                                free(comment_content);
                                continue;
                            } else {
                                // Empty collection - skip to endfor without processing loop body
                                ptr = endfor_pos;
                                free(args_copy);
                                free(comment_content);
                                continue;
                            }
                        }
                        
                        // Clean up on error
                        if (items) {
                            for (int i = 0; i < item_count; i++) {
                                free(items[i]);
                            }
                            free(items);
                        }
                    } else {
                        // Missing " in " keyword
                        const char* error_msg = "Error: For loop missing 'in' keyword";
                        if (should_execute_block(ctx)) {
                            size_t error_len = strlen(error_msg);
                            if (output_pos + error_len >= output_capacity) {
                                output_capacity = (output_pos + error_len + 1000) * 2;
                                output = realloc(output, output_capacity);
                            }
                            memcpy(output + output_pos, error_msg, error_len);
                            output_pos += error_len;
                        }
                    }
                    free(args_copy);
                }
            } else if (strcmp(directive, "endfor") == 0) {
                // endfor is handled by for loop processing, just skip
            } else {
                // Handle other directives normally
                if (is_multiline_directive(comment_content)) {
                    process_multiline_directive_enhanced(comment_content, variables);
                } else {
                    char directive_output[4096];
                    process_directive(trimmed, ctx, directive_output, sizeof(directive_output));
                    
                    // Add directive output if any
                    if (strlen(directive_output) > 0 && should_execute_block(ctx)) {
                        size_t dir_len = strlen(directive_output);
                        if (output_pos + dir_len >= output_capacity) {
                            output_capacity = (output_pos + dir_len + 1000) * 2;
                            output = realloc(output, output_capacity);
                        }
                        memcpy(output + output_pos, directive_output, dir_len);
                        output_pos += dir_len;
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
    }
    
    output[output_pos] = '\0';
    
    // Substitute variables in final output
    char* final_output = substitute_variables(output, variables);
    
    free(output);
    free(ctx);
    
    return final_output;
}
