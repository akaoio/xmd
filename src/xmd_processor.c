/**
 * @file xmd_processor.c
 * @brief XMD directive processor implementation
 * @author XMD Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/token.h"
#include "../include/store.h"
#include "../include/variable.h"
#include "../include/lexer.h"
#include "../include/xmd.h"

#define MAX_OUTPUT_SIZE 65536
#define MAX_LOOP_ITERATIONS 10000

// Forward declarations
static size_t process_variable_substitution(const char* text, store* var_store, char* output, size_t output_size);

/**
 * @brief Parse XMD directive command and arguments
 * @param directive Full directive string (e.g., "xmd:exec(ls -la)")
 * @param command Output buffer for command name
 * @param args Output buffer for arguments
 * @return 0 on success, -1 on error
 */
static int parse_xmd_directive(const char* directive, char* command, char* args) {
    if (!directive || !command || !args) {
        return -1;
    }
    
    // Skip "xmd:" prefix
    const char* ptr = directive;
    if (strncmp(ptr, "xmd:", 4) == 0) {
        ptr += 4;
    }
    
    // Extract command name
    int cmd_len = 0;
    while (*ptr && *ptr != '(' && *ptr != '\n' && cmd_len < 255) {
        command[cmd_len++] = *ptr++;
    }
    command[cmd_len] = '\0';
    
    // Extract arguments if present
    args[0] = '\0';
    if (*ptr == '(') {
        ptr++; // Skip '('
        int arg_len = 0;
        int paren_count = 1;
        
        while (*ptr && paren_count > 0 && arg_len < 4095) {
            if (*ptr == '(') {
                paren_count++;
            } else if (*ptr == ')') {
                paren_count--;
                if (paren_count == 0) break;
            }
            args[arg_len++] = *ptr++;
        }
        args[arg_len] = '\0';
    }
    
    return 0;
}

/**
 * @brief Execute shell command and capture output
 * @param command Command to execute
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int execute_command(const char* command, char* output, size_t output_size) {
    if (!command || !output) {
        return -1;
    }
    
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        snprintf(output, output_size, "Error: Failed to execute command");
        return -1;
    }
    
    size_t total_read = 0;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t len = strlen(buffer);
        if (total_read + len < output_size - 1) {
            strcpy(output + total_read, buffer);
            total_read += len;
        } else {
            break;
        }
    }
    
    output[total_read] = '\0';
    
    int status = pclose(pipe);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

/**
 * @brief Process xmd:exec directive
 * @param args Command arguments
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int process_exec(const char* args, store* var_store, char* output, size_t output_size) {
    // First substitute variables in the command
    char expanded_command[4096];
    process_variable_substitution(args, var_store, expanded_command, sizeof(expanded_command));
    
    return execute_command(expanded_command, output, output_size);
}

/**
 * @brief Process xmd:for directive  
 * @param args Loop arguments (e.g., "i in 1..5")
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int process_for(const char* args, store* var_store, char* output, size_t output_size) {
    // Parse loop variable and range
    char var_name[256];
    int start = 0, end = 0;
    
    // Simple parsing for "var in start..end" format
    if (sscanf(args, "%255s in %d..%d", var_name, &start, &end) != 3) {
        snprintf(output, output_size, "Error: Invalid for loop syntax");
        return -1;
    }
    
    // Validate range
    if (start > end || end - start > MAX_LOOP_ITERATIONS) {
        snprintf(output, output_size, "Error: Invalid or too large loop range");
        return -1;
    }
    
    // For now, return a structured output that can be post-processed
    // This is a limitation of the current single-token processing architecture
    snprintf(output, output_size, "XMD_FOR_LOOP:%s:%d:%d", var_name, start, end);
    return 0;
}

/**
 * @brief Process xmd:if directive
 * @param args Condition arguments
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int process_if(const char* args, store* var_store, char* output, size_t output_size) {
    // First substitute variables in the condition
    char expanded_args[1024];
    process_variable_substitution(args, var_store, expanded_args, sizeof(expanded_args));
    
    // Handle literal boolean values
    if (strcmp(expanded_args, "true") == 0) {
        snprintf(output, output_size, "XMD_IF_TRUE");
        return 1; // Return 1 to indicate condition is true
    } else if (strcmp(expanded_args, "false") == 0) {
        snprintf(output, output_size, "XMD_IF_FALSE");
        return 0; // Return 0 to indicate condition is false
    }
    
    // Execute as shell command and check exit status
    FILE* pipe = popen(expanded_args, "r");
    if (!pipe) {
        snprintf(output, output_size, "XMD_IF_FALSE");
        return 0; // Command failed to execute, treat as false
    }
    
    // Read and discard output (we only care about exit status)
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        // Discard output
    }
    
    int exit_status = pclose(pipe);
    int success = (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) == 0);
    
    if (success) {
        snprintf(output, output_size, "XMD_IF_TRUE");
        return 1;
    } else {
        snprintf(output, output_size, "XMD_IF_FALSE");
        return 0;
    }
}

/**
 * @brief Process xmd:import directive
 * @param args File path to import
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int process_import(const char* args, store* var_store, char* output, size_t output_size) {
    // First substitute variables in the file path
    char expanded_path[1024];
    process_variable_substitution(args, var_store, expanded_path, sizeof(expanded_path));
    
    FILE* file = fopen(expanded_path, "r");
    if (!file) {
        snprintf(output, output_size, "Error: Cannot import file '%s'", expanded_path);
        return -1;
    }
    
    size_t total_read = 0;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t len = strlen(buffer);
        if (total_read + len < output_size - 1) {
            strcpy(output + total_read, buffer);
            total_read += len;
        } else {
            break;
        }
    }
    
    output[total_read] = '\0';
    fclose(file);
    return 0;
}

/**
 * @brief Process xmd:set directive
 * @param args Variable assignment (e.g., "name, value")
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int process_set(const char* args, store* var_store, char* output, size_t output_size) {
    char var_name[256];
    char var_value[4096];
    
    // Parse "name, value" format
    const char* comma = strchr(args, ',');
    if (!comma) {
        snprintf(output, output_size, "Error: Invalid set syntax");
        return -1;
    }
    
    // Extract variable name
    size_t name_len = comma - args;
    if (name_len >= sizeof(var_name)) {
        name_len = sizeof(var_name) - 1;
    }
    strncpy(var_name, args, name_len);
    var_name[name_len] = '\0';
    
    // Extract value (skip comma and spaces)
    const char* value_ptr = comma + 1;
    while (*value_ptr == ' ') value_ptr++;
    
    strncpy(var_value, value_ptr, sizeof(var_value) - 1);
    var_value[sizeof(var_value) - 1] = '\0';
    
    // Store variable as string
    variable* var = variable_create_string(var_value);
    if (var && store_set(var_store, var_name, var)) {
        output[0] = '\0'; // No output for set
        return 0;
    }
    if (var) variable_unref(var);
    
    snprintf(output, output_size, "Error: Failed to set variable");
    return -1;
}

/**
 * @brief Process xmd:get directive
 * @param args Variable name
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int process_get(const char* args, store* var_store, char* output, size_t output_size) {
    variable* var = store_get(var_store, args);
    if (var) {
        const char* value = variable_to_string(var);
        if (value) {
            strncpy(output, value, output_size - 1);
            output[output_size - 1] = '\0';
            return 0;
        }
    }
    
    snprintf(output, output_size, "[undefined: %s]", args);
    return -1;
}


/**
 * @brief Process a single XMD directive
 * @param directive Directive string
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return Number of bytes written to output, or -1 on error
 */
int process_xmd_directive(const char* directive, store* var_store, char* output, size_t output_size) {
    char command[256];
    char args[4096];
    
    if (parse_xmd_directive(directive, command, args) != 0) {
        snprintf(output, output_size, "[Invalid directive: %s]", directive);
        return strlen(output);
    }
    
    int result = 0;
    
    // Process based on command type
    if (strcmp(command, "exec") == 0) {
        result = process_exec(args, var_store, output, output_size);
    } else if (strcmp(command, "for") == 0) {
        result = process_for(args, var_store, output, output_size);
    } else if (strcmp(command, "if") == 0) {
        result = process_if(args, var_store, output, output_size);
    } else if (strcmp(command, "import") == 0) {
        result = process_import(args, var_store, output, output_size);
    } else if (strcmp(command, "set") == 0) {
        result = process_set(args, var_store, output, output_size);
    } else if (strcmp(command, "get") == 0) {
        result = process_get(args, var_store, output, output_size);
    } else if (strcmp(command, "endfor") == 0 || 
               strcmp(command, "endif") == 0 || 
               strcmp(command, "else") == 0) {
        // Control flow markers - no output
        output[0] = '\0';
        result = 0;
    } else {
        snprintf(output, output_size, "[Unknown command: %s]", command);
        result = -1;
    }
    
    return (result >= 0) ? strlen(output) : -1;
}

/**
 * @brief Process text that may contain XMD directives
 * @param text Input text
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return Number of bytes written to output
 */
int process_text_with_directives(const char* text, store* var_store, char* output, size_t output_size) {
    if (!text || !output) {
        return 0;
    }
    
    size_t output_pos = 0;
    const char* ptr = text;
    
    while (*ptr && output_pos < output_size - 1) {
        // Look for xmd: directive
        if (strncmp(ptr, "xmd:", 4) == 0) {
            // Find end of directive
            const char* start = ptr;
            ptr += 4; // Skip "xmd:"
            
            // Skip command name
            while (*ptr && *ptr != '(' && *ptr != ' ' && *ptr != '\n') {
                ptr++;
            }
            
            // Skip arguments if present
            if (*ptr == '(') {
                int paren_count = 1;
                ptr++;
                while (*ptr && paren_count > 0) {
                    if (*ptr == '(') paren_count++;
                    else if (*ptr == ')') paren_count--;
                    ptr++;
                }
            }
            
            // Extract and process directive
            size_t dir_len = ptr - start;
            char* directive = malloc(dir_len + 1);
            if (directive) {
                strncpy(directive, start, dir_len);
                directive[dir_len] = '\0';
                
                char dir_output[4096];
                int bytes = process_xmd_directive(directive, var_store, dir_output, sizeof(dir_output));
                if (bytes > 0 && output_pos + bytes < output_size - 1) {
                    strcpy(output + output_pos, dir_output);
                    output_pos += bytes;
                }
                
                free(directive);
            }
        } else {
            // Copy regular character
            output[output_pos++] = *ptr++;
        }
    }
    
    output[output_pos] = '\0';
    return output_pos;
}

/**
 * @brief Find matching endfor for a for loop
 * @param content Document content
 * @param for_start Position after xmd:for(...) 
 * @param endfor_pos Output: position of matching xmd:endfor
 * @return 0 on success, -1 on error
 */
static int find_matching_endfor(const char* content, size_t for_start, size_t* endfor_pos) {
    const char* ptr = content + for_start;
    int nesting_level = 1;
    
    while (*ptr) {
        if (strncmp(ptr, "xmd:for(", 8) == 0) {
            nesting_level++;
            ptr += 8;
        } else if (strncmp(ptr, "xmd:endfor", 10) == 0) {
            nesting_level--;
            if (nesting_level == 0) {
                *endfor_pos = ptr - content;
                return 0;
            }
            ptr += 10;
        } else {
            ptr++;
        }
    }
    
    return -1; // No matching endfor found
}

/**
 * @brief Process variable references in text (like $variable_name)
 * @param text Input text
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return Number of bytes written
 */
static size_t process_variable_substitution(const char* text, store* var_store, char* output, size_t output_size) {
    size_t output_pos = 0;
    const char* ptr = text;
    
    while (*ptr && output_pos < output_size - 1) {
        if (*ptr == '$' && *(ptr + 1) && (isalpha(*(ptr + 1)) || *(ptr + 1) == '_')) {
            // Found variable reference
            ptr++; // Skip $
            
            // Extract variable name
            char var_name[256];
            size_t name_len = 0;
            while (*ptr && (isalnum(*ptr) || *ptr == '_') && name_len < sizeof(var_name) - 1) {
                var_name[name_len++] = *ptr++;
            }
            var_name[name_len] = '\0';
            
            if (name_len > 0) {
                // Get variable value
                variable* var = store_get(var_store, var_name);
                if (var) {
                    const char* value = variable_to_string(var);
                    if (value) {
                        size_t value_len = strlen(value);
                        if (output_pos + value_len < output_size - 1) {
                            strcpy(output + output_pos, value);
                            output_pos += value_len;
                        }
                    }
                } else {
                    // Variable not found, keep original $var_name
                    if (output_pos + name_len + 1 < output_size - 1) {
                        output[output_pos++] = '$';
                        strcpy(output + output_pos, var_name);
                        output_pos += name_len;
                    }
                }
            }
        } else {
            // Regular character
            output[output_pos++] = *ptr++;
        }
    }
    
    output[output_pos] = '\0';
    return output_pos;
}

/**
 * @brief Find matching endif for an if statement
 * @param content Document content
 * @param if_start Position after xmd:if(...) 
 * @param endif_pos Output: position of matching xmd:endif
 * @param else_pos Output: position of xmd:else (if found, -1 if not)
 * @return 0 on success, -1 on error
 */
static int find_matching_endif(const char* content, size_t if_start, size_t* endif_pos, size_t* else_pos) {
    const char* ptr = content + if_start;
    int nesting_level = 1;
    *else_pos = (size_t)-1; // Initialize to "not found"
    
    while (*ptr) {
        if (strncmp(ptr, "xmd:if(", 7) == 0) {
            nesting_level++;
            ptr += 7;
        } else if (strncmp(ptr, "xmd:endif", 9) == 0) {
            nesting_level--;
            if (nesting_level == 0) {
                *endif_pos = ptr - content;
                return 0;
            }
            ptr += 9;
        } else if (strncmp(ptr, "xmd:else", 8) == 0 && nesting_level == 1) {
            // Only capture else at our nesting level
            *else_pos = ptr - content;
            ptr += 8;
        } else {
            ptr++;
        }
    }
    
    return -1; // No matching endif found
}

/**
 * @brief Process a complete if statement with conditional content
 * @param content Full document content
 * @param if_start Start position of if directive
 * @param args_start Position after opening parenthesis
 * @param args_end Position of closing parenthesis
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return Number of characters processed from input, or -1 on error
 */
int process_complete_if_statement(const char* content, size_t if_start, size_t args_start, 
                                 size_t args_end, store* var_store, char* output, size_t output_size) {
    // Extract condition arguments
    size_t args_len = args_end - args_start;
    if (args_len >= 512) return -1;
    
    char args[512];
    strncpy(args, content + args_start, args_len);
    args[args_len] = '\0';
    
    // Find matching endif and optional else
    size_t endif_pos, else_pos;
    if (find_matching_endif(content, args_end + 1, &endif_pos, &else_pos) != 0) {
        snprintf(output, output_size, "Error: No matching xmd:endif found");
        return -1;
    }
    
    // Evaluate condition - first substitute variables in the condition
    char expanded_args[1024];
    process_variable_substitution(args, var_store, expanded_args, sizeof(expanded_args));
    
    bool condition_result;
    if (strcmp(expanded_args, "true") == 0) {
        condition_result = true;
    } else if (strcmp(expanded_args, "false") == 0) {
        condition_result = false;
    } else {
        // Execute as shell command with variable substitution
        FILE* pipe = popen(expanded_args, "r");
        if (!pipe) {
            condition_result = false;
        } else {
            // Consume output
            char buffer[256];
            while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
                // Discard output
            }
            int exit_status = pclose(pipe);
            condition_result = (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) == 0);
        }
    }
    
    // Determine which content to process
    size_t content_start, content_end;
    
    if (condition_result) {
        // Process IF content
        content_start = args_end + 1;
        content_end = (else_pos != (size_t)-1) ? else_pos : endif_pos;
    } else if (else_pos != (size_t)-1) {
        // Process ELSE content
        content_start = else_pos + 8; // Skip "xmd:else"
        content_end = endif_pos;
    } else {
        // No content to process (condition false, no else)
        output[0] = '\0';
        return endif_pos + 9 - if_start; // 9 = strlen("xmd:endif")
    }
    
    // Extract and process the selected content
    size_t content_len = content_end - content_start;
    char* selected_content = malloc(content_len + 1);
    if (!selected_content) {
        snprintf(output, output_size, "Error: Out of memory");
        return -1;
    }
    
    strncpy(selected_content, content + content_start, content_len);
    selected_content[content_len] = '\0';
    
    // Process content with variable substitution
    char processed_content[4096];
    process_variable_substitution(selected_content, var_store, processed_content, sizeof(processed_content));
    
    // For now, treat as final content since recursive processing is complex
    // In a full implementation, this would recursively process document-level structures
    char final_content[4096];
    size_t final_len = strlen(processed_content);
    if (final_len < 4096 - 1) {
        strcpy(final_content, processed_content);
    } else {
        strncpy(final_content, processed_content, 4095);
        final_content[4095] = '\0';
    }
    
    // Copy to output
    size_t result_len = strlen(final_content);
    if (result_len < output_size - 1) {
        strcpy(output, final_content);
    } else {
        strncpy(output, final_content, output_size - 1);
        output[output_size - 1] = '\0';
    }
    
    free(selected_content);
    
    // Return total characters processed (including endif)
    return endif_pos + 9 - if_start; // 9 = strlen("xmd:endif")
}

/**
 * @brief Process a complete for loop with body content
 * @param content Full document content
 * @param for_start Start position of for directive
 * @param args_start Position after opening parenthesis
 * @param args_end Position of closing parenthesis
 * @param var_store Variable store
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return Number of characters processed from input, or -1 on error
 */
int process_complete_for_loop(const char* content, size_t for_start, size_t args_start, 
                             size_t args_end, store* var_store, char* output, size_t output_size) {
    // Extract arguments
    size_t args_len = args_end - args_start;
    if (args_len >= 512) return -1;
    
    char args[512];
    strncpy(args, content + args_start, args_len);
    args[args_len] = '\0';
    
    // Parse loop parameters
    char var_name[256];
    int start = 0, end = 0;
    if (sscanf(args, "%255s in %d..%d", var_name, &start, &end) != 3) {
        snprintf(output, output_size, "Error: Invalid for loop syntax");
        return -1;
    }
    
    // Validate range
    if (start > end || end - start > MAX_LOOP_ITERATIONS) {
        snprintf(output, output_size, "Error: Invalid or too large loop range");
        return -1;
    }
    
    // Find matching endfor
    size_t endfor_pos;
    if (find_matching_endfor(content, args_end + 1, &endfor_pos) != 0) {
        snprintf(output, output_size, "Error: No matching xmd:endfor found");
        return -1;
    }
    
    // Extract loop body
    size_t body_start = args_end + 1;
    size_t body_len = endfor_pos - body_start;
    
    char* body = malloc(body_len + 1);
    if (!body) {
        snprintf(output, output_size, "Error: Out of memory");
        return -1;
    }
    
    strncpy(body, content + body_start, body_len);
    body[body_len] = '\0';
    
    // Execute loop iterations
    size_t output_pos = 0;
    for (int i = start; i <= end && output_pos < output_size - 1000; i++) {
        // Set loop variable
        variable* loop_var = variable_create_number((double)i);
        if (loop_var) {
            store_set(var_store, var_name, loop_var);
            variable_unref(loop_var);
        }
        
        // Process body content with variable substitution
        char processed_body[4096];
        process_variable_substitution(body, var_store, processed_body, sizeof(processed_body));
        
        // Process any XMD directives in the body
        char final_body[4096];
        process_text_with_directives(processed_body, var_store, final_body, sizeof(final_body));
        
        // Add to output
        size_t body_result_len = strlen(final_body);
        if (output_pos + body_result_len < output_size - 1) {
            strcpy(output + output_pos, final_body);
            output_pos += body_result_len;
        }
    }
    
    free(body);
    
    // Return total characters processed (including endfor)
    return endfor_pos + 10 - for_start; // 10 = strlen("xmd:endfor")
}

/**
 * @brief Validate XMD syntax
 * @param input Input markdown string
 * @param input_length Length of input string
 * @return XMD_SUCCESS if valid, error code otherwise
 */
xmd_error_code xmd_validate_syntax(const char* input, size_t input_length) {
    if (!input) {
        return XMD_ERROR_INVALID_ARGUMENT;
    }
    
    // Create lexer to tokenize and check syntax
    lexer* lex = lexer_create(input);
    if (!lex) {
        return XMD_ERROR_OUT_OF_MEMORY;
    }
    
    token* tok;
    int for_depth = 0;
    int if_depth = 0;
    
    // Check all tokens for syntax errors
    while ((tok = lexer_next_token(lex)) != NULL && tok->type != TOKEN_EOF) {
        if (tok->type == TOKEN_XMD_DIRECTIVE && tok->value) {
            // Parse directive
            char command[256];
            char args[4096];
            
            if (parse_xmd_directive(tok->value, command, args) != 0) {
                token_free(tok);
                lexer_free(lex);
                return XMD_ERROR_SYNTAX;
            }
            
            // Check command validity
            if (strcmp(command, "exec") == 0) {
                if (strlen(args) == 0) {
                    token_free(tok);
                    lexer_free(lex);
                    return XMD_ERROR_SYNTAX;
                }
            } else if (strcmp(command, "set") == 0) {
                if (!strchr(args, ',')) {
                    token_free(tok);
                    lexer_free(lex);
                    return XMD_ERROR_SYNTAX;
                }
            } else if (strcmp(command, "get") == 0) {
                if (strlen(args) == 0) {
                    token_free(tok);
                    lexer_free(lex);
                    return XMD_ERROR_SYNTAX;
                }
            } else if (strcmp(command, "for") == 0) {
                // Check for loop syntax: "var in start..end"
                if (!strstr(args, " in ") || !strstr(args, "..")) {
                    token_free(tok);
                    lexer_free(lex);
                    return XMD_ERROR_SYNTAX;
                }
                for_depth++;
            } else if (strcmp(command, "endfor") == 0) {
                if (for_depth <= 0) {
                    token_free(tok);
                    lexer_free(lex);
                    return XMD_ERROR_SYNTAX;
                }
                for_depth--;
            } else if (strcmp(command, "if") == 0) {
                if (strlen(args) == 0) {
                    token_free(tok);
                    lexer_free(lex);
                    return XMD_ERROR_SYNTAX;
                }
                if_depth++;
            } else if (strcmp(command, "else") == 0) {
                if (if_depth <= 0) {
                    token_free(tok);
                    lexer_free(lex);
                    return XMD_ERROR_SYNTAX;
                }
            } else if (strcmp(command, "endif") == 0) {
                if (if_depth <= 0) {
                    token_free(tok);
                    lexer_free(lex);
                    return XMD_ERROR_SYNTAX;
                }
                if_depth--;
            } else if (strcmp(command, "import") == 0) {
                if (strlen(args) == 0) {
                    token_free(tok);
                    lexer_free(lex);
                    return XMD_ERROR_SYNTAX;
                }
            } else {
                // Unknown command
                token_free(tok);
                lexer_free(lex);
                return XMD_ERROR_SYNTAX;
            }
        }
        
        token_free(tok);
    }
    
    if (tok) {
        token_free(tok);
    }
    
    // Check for unclosed blocks
    if (for_depth > 0 || if_depth > 0) {
        lexer_free(lex);
        return XMD_ERROR_SYNTAX;
    }
    
    lexer_free(lex);
    return XMD_SUCCESS;
}

/**
 * @brief Get error message for error code
 * @param error_code Error code
 * @return Human-readable error message
 */
const char* xmd_error_string(xmd_error_code error_code) {
    switch (error_code) {
        case XMD_SUCCESS: return "Success";
        case XMD_ERROR_PARSE: return "Parse error";
        case XMD_ERROR_SYNTAX: return "Syntax error in XMD directive";
        case XMD_ERROR_PERMISSION: return "Permission denied";
        case XMD_ERROR_MODULE_NOT_FOUND: return "Module not found";
        case XMD_ERROR_CIRCULAR_DEPENDENCY: return "Circular dependency";
        case XMD_ERROR_COMMAND_FAILED: return "Command execution failed";
        case XMD_ERROR_OUT_OF_MEMORY: return "Out of memory";
        case XMD_ERROR_TIMEOUT: return "Operation timeout";
        case XMD_ERROR_INVALID_ARGUMENT: return "Invalid argument";
        case XMD_ERROR_FILE_NOT_FOUND: return "File not found";
        default: return "Unknown error";
    }
}