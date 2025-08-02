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
/**
 * @brief Parse potential function call: name arg1 arg2 ...
 * @param pos Pointer to current position  
 * @return Function call AST node or NULL if not a function call
 */
ast_node* ast_parse_potential_function_call(const char** pos) {
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
    // Must be followed by whitespace for function call
    if (!*start || !isspace(*start)) {
        return NULL;
    }
    // Extract function name
    char* func_name = xmd_malloc(name_len + 1);
    if (!func_name) return NULL;
    strncpy(func_name, name_start, name_len);
    func_name[name_len] = '\0';
    source_location loc = {1, 1, "input"};
    ast_node* func_call = NULL;
    // Check for File I/O method calls and create appropriate AST nodes
    if (strcmp(func_name, "File.read") == 0) {
        func_call = xmd_calloc(1, sizeof(ast_node));
        if (func_call) {
            func_call->type = AST_FILE_READ;
            func_call->location = loc;
        }
    } else if (strcmp(func_name, "File.write") == 0) {
        func_call = xmd_calloc(1, sizeof(ast_node));
        if (func_call) {
            func_call->type = AST_FILE_WRITE;
            func_call->location = loc;
        }
    } else if (strcmp(func_name, "File.exists") == 0) {
        func_call = xmd_calloc(1, sizeof(ast_node));
        if (func_call) {
            func_call->type = AST_FILE_EXISTS;
            func_call->location = loc;
        }
    } else if (strcmp(func_name, "File.delete") == 0) {
        func_call = xmd_calloc(1, sizeof(ast_node));
        if (func_call) {
            func_call->type = AST_FILE_DELETE;
            func_call->location = loc;
        }
    } else if (strcmp(func_name, "File.list") == 0) {
        func_call = xmd_calloc(1, sizeof(ast_node));
        if (func_call) {
            func_call->type = AST_FILE_LIST;
            func_call->location = loc;
        }
    } else {
        // Regular function call
        func_call = ast_create_function_call(func_name, loc);
    }
    XMD_FREE_SAFE(func_name);
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
                char* arg_str = xmd_malloc(arg_len + 1);
                if (arg_str) {
                    strncpy(arg_str, arg_start, arg_len);
                    arg_str[arg_len] = '\0';
                    
                    // Remove quotes if present and store as file path
                    if (arg_str[0] == '"' && arg_str[arg_len-1] == '"') {
                        func_call->data.file_io.file_path = xmd_malloc(arg_len - 1);
                        if (func_call->data.file_io.file_path) {
                            strncpy(func_call->data.file_io.file_path, arg_str + 1, arg_len - 2);
                            func_call->data.file_io.file_path[arg_len - 2] = '\0';
                        }
                    } else {
                        func_call->data.file_io.file_path = xmd_strdup(arg_str);
                    }
                    XMD_FREE_SAFE(arg_str);
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
                        char* content_str = xmd_malloc(content_len + 1);
                        if (content_str) {
                            strncpy(content_str, content_start, content_len);
                            content_str[content_len] = '\0';
                            
                            // Create content node and store it
                            if (content_str[0] == '"' && content_str[content_len-1] == '"') {
                                // String literal - remove quotes
                                char* str_val = xmd_malloc(content_len - 1);
                                if (str_val) {
                                    strncpy(str_val, content_str + 1, content_len - 2);
                                    str_val[content_len - 2] = '\0';
                                    source_location loc = {1, 1, "input"};
                                    func_call->data.file_io.content = ast_create_string_literal(str_val, loc);
                                    XMD_FREE_SAFE(str_val);
                                }
                            } else {
                                // Variable reference or other content
                                source_location loc = {1, 1, "input"};
                                func_call->data.file_io.content = ast_create_identifier(content_str, loc);
                            }
                            XMD_FREE_SAFE(content_str);
                        }
                    }
                } else {
                    func_call->data.file_io.content = NULL;
                }
            }
        }
    } else {
        // Regular function call - parse arguments normally
        while (*start && *start != '\n') {
            // Skip whitespace
            while (*start && isspace(*start) && *start != '\n') start++;
            if (!*start || *start == '\n') break;
            // Parse argument as a full expression (handles strings, math, concatenation, etc.)
            ast_node* arg = ast_parse_expression(&start);
            if (arg) {
                ast_add_argument(func_call, arg);
            }
            // If expression parsing fails, skip to next whitespace
        }
    }
    *pos = start;
    return func_call;
}
