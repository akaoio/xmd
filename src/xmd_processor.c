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
#include <unistd.h>
#include <sys/wait.h>
#include "../include/token.h"
#include "../include/store.h"
#include "../include/variable.h"
#include "../include/lexer.h"
#include "../include/xmd.h"

#define MAX_OUTPUT_SIZE 65536
#define MAX_LOOP_ITERATIONS 10000

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
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int process_exec(const char* args, char* output, size_t output_size) {
    return execute_command(args, output, output_size);
}

/**
 * @brief Process xmd:for directive
 * @param args Loop arguments (e.g., "i in 1..5")
 * @param store Variable store
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
    
    // For now, just output a placeholder
    snprintf(output, output_size, "[for loop: %s from %d to %d]", var_name, start, end);
    return 0;
}

/**
 * @brief Process xmd:if directive
 * @param args Condition arguments
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int process_if(const char* args, char* output, size_t output_size) {
    // For now, evaluate simple conditions
    if (strcmp(args, "true") == 0) {
        output[0] = '\0'; // Empty output, content should follow
        return 1; // Return 1 to indicate condition is true
    } else if (strcmp(args, "false") == 0) {
        output[0] = '\0';
        return 0; // Return 0 to indicate condition is false
    }
    
    // Try to execute as shell command and check exit status
    char cmd_output[1024];
    int status = execute_command(args, cmd_output, sizeof(cmd_output));
    output[0] = '\0';
    return (status == 0) ? 1 : 0;
}

/**
 * @brief Process xmd:import directive
 * @param args File path to import
 * @param output Output buffer
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
static int process_import(const char* args, char* output, size_t output_size) {
    FILE* file = fopen(args, "r");
    if (!file) {
        snprintf(output, output_size, "Error: Cannot import file '%s'", args);
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
        result = process_exec(args, output, output_size);
    } else if (strcmp(command, "for") == 0) {
        result = process_for(args, var_store, output, output_size);
    } else if (strcmp(command, "if") == 0) {
        result = process_if(args, output, output_size);
    } else if (strcmp(command, "import") == 0) {
        result = process_import(args, output, output_size);
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