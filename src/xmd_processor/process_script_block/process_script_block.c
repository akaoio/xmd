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
#include "../../../include/variable.h"

/**
 * @brief Evaluate import expression within a string
 * @param expr Expression like "import varname"
 * @param ctx Processor context
 * @return Imported content as string (caller must free)
 */
static char* evaluate_import_expression(const char* expr, processor_context* ctx) {
    // Check if it's "import varname"
    if (strncmp(expr, "import ", 7) == 0) {
        char* var_name = trim_whitespace((char*)(expr + 7));
        
        // Get the variable that contains the filename
        variable* var = store_get(ctx->variables, var_name);
        if (var && var->type == VAR_STRING) {
            // Now import that file
            char output[4096];
            if (process_import(var->value.string_value, ctx, output, sizeof(output)) == 0) {
                return strdup(output);
            }
        }
    }
    
    return strdup(""); // Return empty string on error
}

/**
 * @brief Evaluate string concatenation expression
 * @param expr Expression like "\"### \" + import principle + \"\\n\\n\""
 * @param ctx Processor context
 * @return Concatenated string (caller must free)
 */
static char* evaluate_concatenation_expression(const char* expr, processor_context* ctx) {
    char* result = malloc(4096);
    result[0] = '\0';
    
    const char* p = expr;
    
    while (*p) {
        // Skip whitespace
        while (isspace(*p)) p++;
        if (!*p) break;
        
        // Find the next '+' that's not inside quotes
        const char* token_start = p;
        const char* token_end = p;
        bool in_quotes = false;
        
        while (*token_end && (in_quotes || *token_end != '+')) {
            if (*token_end == '"' && (token_end == expr || *(token_end-1) != '\\')) {
                in_quotes = !in_quotes;
            }
            token_end++;
        }
        
        // Extract the token
        size_t token_len = token_end - token_start;
        char* token = malloc(token_len + 1);
        strncpy(token, token_start, token_len);
        token[token_len] = '\0';
        
        // Trim whitespace from token
        char* trimmed = trim_whitespace(token);
        
        if (trimmed[0] == '"' && trimmed[strlen(trimmed)-1] == '"') {
            // String literal - remove quotes and add to result
            trimmed[strlen(trimmed)-1] = '\0';
            trimmed++;
            // Handle escape sequences
            char* processed = malloc(strlen(trimmed) + 1);
            char* src = trimmed, *dst = processed;
            while (*src) {
                if (*src == '\\' && *(src+1) == 'n') {
                    *dst++ = '\n';
                    src += 2;
                } else {
                    *dst++ = *src++;
                }
            }
            *dst = '\0';
            strcat(result, processed);
            free(processed);
        } else if (strncmp(trimmed, "import ", 7) == 0) {
            // Import expression
            char* import_result = evaluate_import_expression(trimmed, ctx);
            strcat(result, import_result);
            free(import_result);
        } else {
            // Variable name
            variable* var = store_get(ctx->variables, trimmed);
            if (var && var->type == VAR_STRING) {
                strcat(result, var->value.string_value);
            }
        }
        
        free(token);
        
        // Move past the '+' if there is one
        if (*token_end == '+') {
            p = token_end + 1;
        } else {
            break;
        }
    }
    
    return result;
}

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
                
                // Process assignment with concatenation
                if (strstr(body_line, "+=")) {
                    // Make a copy to avoid modifying the original line
                    char* line_copy = strdup(body_line);
                    char* eq_pos = strstr(line_copy, "+=");
                    *eq_pos = '\0';
                    char* target_var = trim_whitespace(line_copy);
                    char* expr = trim_whitespace(eq_pos + 2);
                    
                    // Evaluate the expression
                    char* new_value = evaluate_concatenation_expression(expr, ctx);
                    
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
            // Handle set directive
            char output[1024];
            process_set(trimmed + 4, ctx, output, sizeof(output));
        } else if (strncmp(trimmed, "for ", 4) == 0) {
            // Handle for loop
            process_for_loop_script(trimmed, lines, line_count, &i, ctx);
        }
    }
    
    // Cleanup
    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    destroy_context(ctx);
    free(content_copy);
}