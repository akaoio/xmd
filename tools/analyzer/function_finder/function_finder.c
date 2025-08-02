/**
 * @file function_finder.c
 * @brief Find function declarations and calls in C source
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 * Standard C only - no external dependencies
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// External development tool - standalone, no XMD dependencies

#define MAX_LINE_LENGTH 1024

/**
 * @brief Find function declarations and calls in a single C source file
 * @param file_path Path to C source file to analyze
 * @param output_file Output file to write results
 * @return 1 on success, 0 on failure
 */
int function_finder(const char* file_path, FILE* output_file) {
    if (!file_path || !output_file) {
        return 0;
    }
    
    FILE* file = fopen(file_path, "r");
    if (!file) {
        return 0;
    }
    
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line_number++;
        
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Skip empty lines and comments
        char* trimmed = line;
        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;
        if (*trimmed == '\0' || strncmp(trimmed, "//", 2) == 0 || 
            strncmp(trimmed, "/*", 2) == 0 || *trimmed == '*' || *trimmed == '#') {
            continue;
        }
        
        // Look for function definitions (has '{' and parentheses)
        if (strstr(line, "(") && strstr(line, ")") && strstr(line, "{")) {
            char* paren = strstr(line, "(");
            if (paren) {
                // Extract function name
                char* name_end = paren - 1;
                while (name_end > line && (*name_end == ' ' || *name_end == '\t')) {
                    name_end--;
                }
                
                char* name_start = name_end;
                while (name_start > line && 
                       ((*name_start >= 'a' && *name_start <= 'z') ||
                        (*name_start >= 'A' && *name_start <= 'Z') ||
                        (*name_start >= '0' && *name_start <= '9') ||
                        *name_start == '_')) {
                    name_start--;
                }
                name_start++;
                
                if (name_start <= name_end) {
                    int name_len = name_end - name_start + 1;
                    if (name_len > 0 && name_len < 256) {
                        // Write function definition info
                        fprintf(output_file, "DEF:%.*s:%s:%d\n", 
                               name_len, name_start, file_path, line_number);
                    }
                }
            }
        }
        
        // Look for function declarations (has ';' and parentheses, no '{')
        else if (strstr(line, "(") && strstr(line, ")") && strstr(line, ";") && !strstr(line, "{")) {
            char* paren = strstr(line, "(");
            if (paren) {
                char* name_end = paren - 1;
                while (name_end > line && (*name_end == ' ' || *name_end == '\t')) {
                    name_end--;
                }
                
                char* name_start = name_end;
                while (name_start > line && 
                       ((*name_start >= 'a' && *name_start <= 'z') ||
                        (*name_start >= 'A' && *name_start <= 'Z') ||
                        (*name_start >= '0' && *name_start <= '9') ||
                        *name_start == '_')) {
                    name_start--;
                }
                name_start++;
                
                if (name_start <= name_end) {
                    int name_len = name_end - name_start + 1;
                    if (name_len > 0 && name_len < 256) {
                        fprintf(output_file, "DECL:%.*s:%s:%d\n", 
                               name_len, name_start, file_path, line_number);
                    }
                }
            }
        }
        
        // Look for function calls
        char* pos = line;
        while ((pos = strstr(pos, "(")) != NULL) {
            char* name_end = pos - 1;
            while (name_end > line && (*name_end == ' ' || *name_end == '\t')) {
                name_end--;
            }
            
            char* name_start = name_end;
            while (name_start > line && 
                   ((*name_start >= 'a' && *name_start <= 'z') ||
                    (*name_start >= 'A' && *name_start <= 'Z') ||
                    (*name_start >= '0' && *name_start <= '9') ||
                    *name_start == '_')) {
                name_start--;
            }
            name_start++;
            
            if (name_start <= name_end) {
                int name_len = name_end - name_start + 1;
                if (name_len > 1 && name_len < 256) {
                    // Skip common keywords
                    char func_name[256];
                    snprintf(func_name, sizeof(func_name), "%.*s", name_len, name_start);
                    
                    if (strcmp(func_name, "if") != 0 && strcmp(func_name, "for") != 0 &&
                        strcmp(func_name, "while") != 0 && strcmp(func_name, "switch") != 0 &&
                        strcmp(func_name, "sizeof") != 0 && strcmp(func_name, "return") != 0) {
                        fprintf(output_file, "CALL:%s:%s:%d\n", 
                               func_name, file_path, line_number);
                    }
                }
            }
            
            pos++;
        }
    }
    
    fclose(file);
    return 1;
}