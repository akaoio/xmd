/**
 * @file formatter.c
 * @brief XMD code formatter for consistent style
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * @brief Format XMD content for consistent style
 * @param content XMD content to format
 * @param output_file Path to write formatted content
 * @return 0 on success, -1 on error
 */
int formatter_format(const char* content, const char* output_file) {
    if (!content || !output_file) {
        return -1;
    }
    
    FILE* output = fopen(output_file, "w");
    if (!output) {
        return -1;
    }
    
    const char* pos = content;
    const char* line_start = pos;
    int line_number = 1;
    bool in_code_block = false;
    
    printf("Formatting XMD content...\n");
    
    while (*pos) {
        if (*pos == '\n') {
            // Process current line
            size_t line_len = pos - line_start;
            char line[1024];
            strncpy(line, line_start, line_len);
            line[line_len] = '\0';
            
            // Skip formatting inside code blocks
            if (strstr(line, "```")) {
                in_code_block = !in_code_block;
                fputs(line, output);
                fputc('\n', output);
            } else if (in_code_block) {
                // Preserve code block content as-is
                fputs(line, output);
                fputc('\n', output);
            } else {
                // Apply formatting rules
                char formatted_line[1024] = {0};
                size_t formatted_pos = 0;
                
                // 1. Normalize whitespace at start of line
                size_t indent_level = 0;
                size_t i = 0;
                
                // Count current indentation
                while (i < line_len && isspace(line[i])) {
                    if (line[i] == '\t') {
                        indent_level += 4; // Convert tabs to 4 spaces
                    } else {
                        indent_level++;
                    }
                    i++;
                }
                
                // Apply consistent indentation (2 spaces per level)
                if (i < line_len) { // Non-empty line
                    size_t normalized_indent = (indent_level / 2) * 2; // Round to even
                    for (size_t j = 0; j < normalized_indent; j++) {
                        formatted_line[formatted_pos++] = ' ';
                    }
                }
                
                // 2. Copy rest of line, normalizing internal whitespace
                bool prev_was_space = false;
                while (i < line_len) {
                    char c = line[i];
                    
                    if (isspace(c)) {
                        if (!prev_was_space) {
                            formatted_line[formatted_pos++] = ' ';
                            prev_was_space = true;
                        }
                    } else {
                        formatted_line[formatted_pos++] = c;
                        prev_was_space = false;
                    }
                    i++;
                }
                
                // 3. Remove trailing whitespace
                while (formatted_pos > 0 && isspace(formatted_line[formatted_pos-1])) {
                    formatted_pos--;
                }
                formatted_line[formatted_pos] = '\0';
                
                // 4. Special formatting for XMD directives
                if (strstr(formatted_line, "<!-- xmd:")) {
                    // Ensure space after directive name
                    char* directive_start = strstr(formatted_line, "xmd:");
                    if (directive_start) {
                        char* space_pos = directive_start + 4; // After "xmd:"
                        while (*space_pos && !isspace(*space_pos) && *space_pos != '-') {
                            space_pos++;
                        }
                        
                        // Add space if needed
                        if (*space_pos != ' ' && *space_pos != '-') {
                            // This would require more complex string manipulation
                            // For now, just output as-is
                        }
                    }
                }
                
                // Write formatted line
                if (strlen(formatted_line) > 0 || line_len == 0) {
                    fputs(formatted_line, output);
                }
                fputc('\n', output);
            }
            
            line_start = pos + 1;
            line_number++;
        }
        pos++;
    }
    
    fclose(output);
    
    printf("Formatted %d lines\n", line_number - 1);
    printf("Output written to: %s\n", output_file);
    
    return 0;
}
