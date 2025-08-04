/**
 * @file ast_parse_potential_function_call.c
 * @brief Implementation of ast_parse_potential_function_call function
 * 
 * This file contains ONLY the ast_parse_potential_function_call function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "dependency.h"
#include "module.h"
#include "store.h"
#include "utils.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Parse potential function call: name arg1 arg2 ...
 * @param pos Pointer to current position  
 * @return Function call AST node or NULL if not a function call
 */
ast_node* ast_parse_potential_function_call(const char** pos) {
    XMD_VALIDATE_PTRS(NULL, pos, *pos);
    const char* start = *pos;
    
    // Parse function name (identifier with dots for method calls like File.read)
    const char* name_start = start;
    while (*start && (isalnum(*start) || *start == '_' || *start == '.')) {
        start++;
    }
    size_t name_len = start - name_start;
    if (name_len == 0) {
        return NULL;
    }
    // Must be followed by whitespace, newline, or end of string for function call
    if (!*start || (!isspace(*start) && *start != '\n')) {
        return NULL;
    }
    // Check for reserved keywords before allocating memory
    if ((name_len == 6 && strncmp(name_start, "return", 6) == 0) ||
        (name_len == 2 && strncmp(name_start, "if", 2) == 0) ||
        (name_len == 4 && strncmp(name_start, "elif", 4) == 0) ||
        (name_len == 4 && strncmp(name_start, "else", 4) == 0) ||
        (name_len == 5 && strncmp(name_start, "while", 5) == 0) ||
        (name_len == 3 && strncmp(name_start, "for", 3) == 0) ||
        (name_len == 5 && strncmp(name_start, "break", 5) == 0) ||
        (name_len == 8 && strncmp(name_start, "continue", 8) == 0) ||
        (name_len == 3 && strncmp(name_start, "set", 3) == 0) ||
        (name_len == 8 && strncmp(name_start, "function", 8) == 0) ||
        (name_len == 5 && strncmp(name_start, "class", 5) == 0) ||
        (name_len == 5 && strncmp(name_start, "print", 5) == 0)) {
        return NULL;
    }
    
    // Extract function name
    char* func_name = malloc(name_len + 1);
    if (!func_name) return NULL;
    strncpy(func_name, name_start, name_len);
    func_name[name_len] = '\0';
    source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
    ast_node* func_call = NULL;
    // Check for File I/O method calls and create appropriate AST nodes
    if (strcmp(func_name, "File.read") == 0) {
        XMD_CALLOC_STANDARD(func_call, 1, ast_node, NULL);
        func_call->type = AST_FILE_READ;
        func_call->location = loc;
    } else if (strcmp(func_name, "File.write") == 0) {
        XMD_CALLOC_STANDARD(func_call, 1, ast_node, NULL);
        func_call->type = AST_FILE_WRITE;
        func_call->location = loc;
    } else if (strcmp(func_name, "File.exists") == 0) {
        XMD_CALLOC_STANDARD(func_call, 1, ast_node, NULL);
        func_call->type = AST_FILE_EXISTS;
        func_call->location = loc;
    } else if (strcmp(func_name, "File.delete") == 0) {
        XMD_CALLOC_STANDARD(func_call, 1, ast_node, NULL);
        func_call->type = AST_FILE_DELETE;
        func_call->location = loc;
    } else if (strcmp(func_name, "File.list") == 0) {
        XMD_CALLOC_STANDARD(func_call, 1, ast_node, NULL);
        func_call->type = AST_FILE_LIST;
        func_call->location = loc;
    } else {
        // Regular function call
        func_call = ast_create_function_call(func_name, loc);
    }
    XMD_FREE_NULL(func_name);
    if (!func_call) {
        return NULL;
    }
    // Skip whitespace after function name
    while (*start && isspace(*start) && *start != '\n') start++;
    // Handle File I/O operations specially
    if (func_call->type >= AST_FILE_READ && func_call->type <= AST_FILE_LIST) {
        // Parse File I/O arguments - extract first argument as file path
        if (*start && *start != '\n') {
            // Parse first argument (file path)
            const char* arg_start = start;
            
            if (*start == '"') {
                // Handle quoted string argument
                start++; // Skip opening quote
                while (*start && *start != '"') start++;
                if (*start == '"') start++; // Skip closing quote
            } else {
                // Handle unquoted argument (until space or end)
                while (*start && !isspace(*start) && *start != '\n') start++;
            }
            if (start > arg_start) {
                size_t arg_len = start - arg_start;
                char* arg_str = malloc(arg_len + 1);
                if (!arg_str) return NULL;
                strncpy(arg_str, arg_start, arg_len);
                arg_str[arg_len] = '\0';
                    
                    // Remove quotes if present and store as file path
                    if (arg_str[0] == '"' && arg_str[arg_len-1] == '"') {
                        func_call->data.file_io.file_path = malloc(arg_len - 1);
                        if (!func_call->data.file_io.file_path) return NULL;
                        strncpy(func_call->data.file_io.file_path, arg_str + 1, arg_len - 2);
                        func_call->data.file_io.file_path[arg_len - 2] = '\0';
                    } else {
                        func_call->data.file_io.file_path = xmd_strdup(arg_str);
                    }
                    XMD_FREE_NULL(arg_str);
                }
            }
            // For File.write, parse second argument as content
            if (func_call->type == AST_FILE_WRITE) {
                // Skip whitespace
                while (*start && isspace(*start) && *start != '\n') start++;
                
                if (*start && *start != '\n') {
                    const char* content_start = start;
                    if (*start == '"') {
                        // Handle quoted string content
                        start++; // Skip opening quote
                        while (*start && *start != '"') start++;
                        if (*start == '"') start++; // Skip closing quote
                    } else {
                        // Handle unquoted content (rest of line)
                        while (*start && *start != '\n') start++;
                    }
                    if (start > content_start) {
                        size_t content_len = start - content_start;
                        char* content_str = malloc(content_len + 1);
                        if (!content_str) return NULL;
                        strncpy(content_str, content_start, content_len);
                        content_str[content_len] = '\0';
                            
                            // Create content node and store it
                            if (content_str[0] == '"' && content_str[content_len-1] == '"') {
                                // String literal - remove quotes
                                char* str_val = malloc(content_len - 1);
                                if (!str_val) return NULL;
                                strncpy(str_val, content_str + 1, content_len - 2);
                                str_val[content_len - 2] = '\0';
                                source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
                                func_call->data.file_io.content = ast_create_string_literal(str_val, loc);
                                XMD_FREE_NULL(str_val);
                            } else {
                                // Variable reference or other content
                                source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
                                func_call->data.file_io.content = ast_create_identifier(content_str, loc);
                            }
                        XMD_FREE_NULL(content_str);
                } else {
                    func_call->data.file_io.content = NULL;
                }
            }
        }
    } else {
        // Regular function call - parse individual arguments
        while (*start && *start != '\n') {
            // Skip whitespace
            while (*start && isspace(*start) && *start != '\n') start++;
            if (!*start || *start == '\n') break;
            
            // Parse individual argument (not full expression)
            ast_node* arg = NULL;
            const char* arg_start = start;
            
            if (*start == '"') {
                // Parse string literal argument
                start++; // Skip opening quote
                while (*start && *start != '"') start++;
                if (*start == '"') start++; // Skip closing quote
                
                size_t str_len = start - arg_start;
                char* str_val = malloc(str_len + 1);
                if (!str_val) return NULL;
                strncpy(str_val, arg_start, str_len);
                str_val[str_len] = '\0';
                    
                    // Remove quotes and create string literal
                    if (str_val[0] == '"' && str_val[str_len-1] == '"') {
                        char* clean_str = malloc(str_len - 1);
                        if (!clean_str) return NULL;
                        strncpy(clean_str, str_val + 1, str_len - 2);
                        clean_str[str_len - 2] = '\0';
                        source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
                        arg = ast_create_string_literal(clean_str, loc);
                        XMD_FREE_NULL(clean_str);
                    }
                XMD_FREE_NULL(str_val);
            } else if (isdigit(*start) || (*start == '-' && isdigit(*(start+1)))) {
                // Parse number literal argument
                while (*start && (isdigit(*start) || *start == '.' || *start == '-')) start++;
                
                size_t num_len = start - arg_start;
                char* num_str = malloc(num_len + 1);
                if (!num_str) return NULL;
                strncpy(num_str, arg_start, num_len);
                num_str[num_len] = '\0';
                double val = atof(num_str);
                source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
                arg = ast_create_number_literal(val, loc);
                XMD_FREE_NULL(num_str);
            } else {
                // Parse identifier/variable argument
                while (*start && !isspace(*start) && *start != '\n') start++;
                
                size_t id_len = start - arg_start;
                char* id_str = malloc(id_len + 1);
                if (!id_str) return NULL;
                strncpy(id_str, arg_start, id_len);
                id_str[id_len] = '\0';
                source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
                arg = ast_create_identifier(id_str, loc);
                XMD_FREE_NULL(id_str);
            }
            
            if (arg) {
                ast_add_argument(func_call, arg);
            }
        }
    }
    *pos = start;
    return func_call;
}
