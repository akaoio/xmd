/**
 * @file c_api.c
 * @brief C API interface for language bindings
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include "../../../include/c_api_internal.h"

// Forward declaration for XMD directive processor
int process_xmd_directive(const char* directive, store* var_store, char* output, size_t output_size);
int process_text_with_directives(const char* text, store* var_store, char* output, size_t output_size);
int process_complete_for_loop(const char* content, size_t for_start, size_t args_start, 
                             size_t args_end, store* var_store, char* output, size_t output_size);
int process_complete_if_statement(const char* content, size_t if_start, size_t args_start, 
                                 size_t args_end, store* var_store, char* output, size_t output_size);
bool is_multiline_directive(const char* comment_content);
void process_multiline_directive_enhanced(const char* directive_content, store* variables);
char* trim_whitespace(const char* str);





/**
 * @brief Internal XMD context structure
 */


/**
 * @brief Process markdown string
 * @param handle XMD context handle
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_string_api(void* handle, const char* input, size_t input_length) {
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
            for (size_t i = 0; i < line_diff && output_pos < preprocessed_len * 2 + 999; i++) {
                output[output_pos++] = '\n';
            }
        }
        
        // Process each token based on its type
        switch (tok->type) {
            case TOKEN_TEXT:
                // Copy text content directly
                if (tok->value) {
                    size_t text_len = strlen(tok->value);
                    if (output_pos + text_len < preprocessed_len * 2 + 999) {
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
                    
                    if (output_pos + strlen(var_value) < preprocessed_len * 2 + 999) {
                        strcpy(output + output_pos, var_value);
                        output_pos += strlen(var_value);
                    }
                }
                break;
                
            case TOKEN_XMD_DIRECTIVE:
                // Process XMD directives
                if (tok->value) {
                    char directive_output[32768];  // Increased from 8192 to 32KB for long command outputs
                    
                    // Check if this is a multiline directive
                    bool is_multiline = is_multiline_directive(tok->value);
                    
                    if (is_multiline) {
                        // Use multiline directive processor
                        process_multiline_directive_enhanced(tok->value, var_store);
                        
                        // Get accumulated output from multiline processing
                        variable* output_var = store_get(var_store, "_multiline_output");
                        if (output_var) {
                            const char* multiline_output = variable_to_string(output_var);
                            if (multiline_output && strlen(multiline_output) > 0) {
                                size_t dir_len = strlen(multiline_output);
                                if (output_pos + dir_len < preprocessed_len * 2 + 999) {
                                    strcpy(output + output_pos, multiline_output);
                                    output_pos += dir_len;
                                }
                                // Clear the multiline output variable for next use
                                variable* empty_var = variable_create_string("");
                                if (empty_var) {
                                    store_set(var_store, "_multiline_output", empty_var);
                                    variable_unref(empty_var);
                                }
                            }
                        }
                    } else {
                        // Use single-line directive processor
                        
                        // Extract directive content from HTML comment
                        const char* directive_content = tok->value;
                        if (strstr(directive_content, "<!--") && strstr(directive_content, "-->")) {
                            // Extract content between <!-- and -->
                            const char* start = strstr(directive_content, "<!--") + 4;
                            const char* end = strstr(directive_content, "-->");
                            if (start && end && end > start) {
                                size_t content_len = end - start;
                                char* extracted = malloc(content_len + 1);
                                if (extracted) {
                                    strncpy(extracted, start, content_len);
                                    extracted[content_len] = '\0';
                                    
                                    // Trim whitespace
                                    char* trimmed = trim_whitespace(extracted);
                                    
                                    int bytes_written = process_xmd_directive(trimmed, var_store, 
                                                                            directive_output, sizeof(directive_output));
                                    
                                    free(extracted);
                                    
                                    if (bytes_written >= 0) {
                                        // For exec commands, we want the output even if it's empty
                                        size_t dir_len = strlen(directive_output);
                                        if (output_pos + dir_len < preprocessed_len * 2 + 999) {
                                            strcpy(output + output_pos, directive_output);
                                            output_pos += dir_len;
                                        }
                                    }
                                }
                            }
                        } else {
                            // No HTML comment wrapper, use as-is
                            int bytes_written = process_xmd_directive(directive_content, var_store, 
                                                                    directive_output, sizeof(directive_output));
                            
                            if (bytes_written >= 0) {
                                size_t dir_len = strlen(directive_output);
                                if (output_pos + dir_len < preprocessed_len * 2 + 999) {
                                    strcpy(output + output_pos, directive_output);
                                    output_pos += dir_len;
                                }
                            }
                        }
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















