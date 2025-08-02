/**
 * @file yaml_functions.c
 * @brief YAML stringify and parse functions for XMD
 * 
 * Genesis principle: This file contains multiple YAML functions
 * as they work together as a unit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/ast.h"
#include "../../../include/store.h"
#include "../../../include/variable.h"
#include "../../../include/utils.h"

/**
 * @brief Convert XMD variable to YAML string
 * @param var Variable to stringify
 * @param indent Current indentation level
 * @return YAML string (must be freed)
 */
static char* yaml_stringify_variable(variable* var, int indent) {
    if (!var) {
        return xmd_strdup("null");
    }
    
    variable_type type = variable_get_type(var);
    char* result = NULL;
    char indent_str[64] = {0};
    
    // Create indentation string
    for (int i = 0; i < indent * 2; i++) {
        indent_str[i] = ' ';
    }
    
    switch (type) {
        case VAR_STRING: {
            const char* str = variable_get_string(var);
            // Quote strings that contain special characters
            if (str && (strchr(str, ':') || strchr(str, '\n') || 
                       strchr(str, '"') || strchr(str, '\''))) {
                size_t len = strlen(str) + 3;
                result = xmd_malloc(len);
                snprintf(result, len, "\"%s\"", str);
            } else {
                result = xmd_strdup(str ? str : "");
            }
            break;
        }
        
        case VAR_NUMBER: {
            result = xmd_malloc(32);
            snprintf(result, 32, "%g", variable_get_number(var));
            break;
        }
        
        case VAR_BOOLEAN: {
            result = xmd_strdup(variable_get_boolean(var) ? "true" : "false");
            break;
        }
        
        case VAR_ARRAY: {
            size_t count = variable_array_size(var);
            if (count == 0) {
                result = xmd_strdup("[]");
            } else {
                size_t total_size = 256;
                result = xmd_malloc(total_size);
                size_t pos = 0;
                
                for (size_t i = 0; i < count; i++) {
                    variable* elem = variable_array_get(var, i);
                    if (elem) {
                        // Add newline and indent
                        pos += snprintf(result + pos, total_size - pos, 
                                      "\n%s- ", indent_str);
                        
                        // Add element value
                        char* elem_str = yaml_stringify_variable(elem, indent + 1);
                        if (elem_str) {
                            // Expand buffer if needed
                            size_t elem_len = strlen(elem_str);
                            if (pos + elem_len >= total_size - 1) {
                                total_size *= 2;
                                result = xmd_realloc(result, total_size);
                            }
                            strcpy(result + pos, elem_str);
                            pos += elem_len;
                            XMD_FREE_SAFE(elem_str);
                        }
                    }
                }
            }
            break;
        }
        
        case VAR_OBJECT: {
            size_t count = variable_object_size(var);
            if (count == 0) {
                result = xmd_strdup("{}");
            } else {
                size_t total_size = 256;
                result = xmd_malloc(total_size);
                size_t pos = 0;
                
                size_t key_count = 0;
                char** keys = variable_object_keys(var, &key_count);
                if (keys) {
                    for (size_t i = 0; i < count; i++) {
                        if (keys[i]) {
                            variable* val = variable_object_get(var, keys[i]);
                            if (val) {
                                // Add newline, indent and key
                                pos += snprintf(result + pos, total_size - pos,
                                              "\n%s%s: ", indent_str, keys[i]);
                                
                                // Add value
                                char* val_str = yaml_stringify_variable(val, indent + 1);
                                if (val_str) {
                                    size_t val_len = strlen(val_str);
                                    if (pos + val_len >= total_size - 1) {
                                        total_size *= 2;
                                        result = xmd_realloc(result, total_size);
                                    }
                                    strcpy(result + pos, val_str);
                                    pos += val_len;
                                    XMD_FREE_SAFE(val_str);
                                }
                            }
                            XMD_FREE_SAFE(keys[i]);
                        }
                    }
                    XMD_FREE_SAFE(keys);
                }
            }
            break;
        }
        
        default:
            result = xmd_strdup("null");
            break;
    }
    
    return result;
}

/**
 * @brief Parse YAML string to XMD variable
 * @param yaml YAML string to parse
 * @return Parsed variable or NULL
 * 
 * Note: This is a simplified parser for basic YAML
 * Full YAML support would require libyaml
 */
static variable* yaml_parse_simple(const char* yaml) {
    if (!yaml) {
        return variable_create_null();
    }
    
    // Skip whitespace
    while (*yaml && (*yaml == ' ' || *yaml == '\t' || *yaml == '\n')) {
        yaml++;
    }
    
    // Check for special values
    if (strncmp(yaml, "null", 4) == 0) {
        return variable_create_null();
    }
    if (strncmp(yaml, "true", 4) == 0) {
        return variable_create_boolean(true);
    }
    if (strncmp(yaml, "false", 5) == 0) {
        return variable_create_boolean(false);
    }
    
    // Check for array
    if (*yaml == '-') {
        variable* arr = variable_create_array();
        
        // Parse array items
        while (*yaml == '-') {
            yaml++; // Skip '-'
            while (*yaml == ' ') yaml++; // Skip spaces
            
            // Find end of line
            const char* line_end = strchr(yaml, '\n');
            if (!line_end) {
                line_end = yaml + strlen(yaml);
            }
            
            // Extract item value
            size_t len = line_end - yaml;
            char* item_str = xmd_malloc(len + 1);
            strncpy(item_str, yaml, len);
            item_str[len] = '\0';
            
            // Parse item (simplified - just strings for now)
            variable* item = variable_create_string(item_str);
            variable_array_add(arr, item);
            XMD_FREE_SAFE(item_str);
            
            // Move to next line
            yaml = line_end;
            if (*yaml == '\n') yaml++;
            while (*yaml && (*yaml == ' ' || *yaml == '\t')) {
                yaml++;
            }
        }
        
        return arr;
    }
    
    // Check for object
    if (strchr(yaml, ':')) {
        variable* obj = variable_create_object();
        
        // Parse key-value pairs
        while (*yaml && *yaml != '\0') {
            // Skip whitespace
            while (*yaml && (*yaml == ' ' || *yaml == '\t' || *yaml == '\n')) {
                yaml++;
            }
            if (!*yaml) break;
            
            // Find colon
            const char* colon = strchr(yaml, ':');
            if (!colon) break;
            
            // Extract key
            size_t key_len = colon - yaml;
            char* key = xmd_malloc(key_len + 1);
            strncpy(key, yaml, key_len);
            key[key_len] = '\0';
            
            // Skip colon and spaces
            yaml = colon + 1;
            while (*yaml == ' ') yaml++;
            
            // Find end of value (newline or end)
            const char* line_end = strchr(yaml, '\n');
            if (!line_end) {
                line_end = yaml + strlen(yaml);
            }
            
            // Extract value
            size_t val_len = line_end - yaml;
            char* val_str = xmd_malloc(val_len + 1);
            strncpy(val_str, yaml, val_len);
            val_str[val_len] = '\0';
            
            // Create value (simplified - just strings for now)
            variable* val = variable_create_string(val_str);
            variable_object_set(obj, key, val);
            
            XMD_FREE_SAFE(key);
            XMD_FREE_SAFE(val_str);
            
            // Move to next line
            yaml = line_end;
        }
        
        return obj;
    }
    
    // Check for number
    char* endptr;
    double num = strtod(yaml, &endptr);
    if (endptr != yaml && (*endptr == '\0' || *endptr == '\n')) {
        return variable_create_number(num);
    }
    
    // Default to string
    const char* end = strchr(yaml, '\n');
    if (!end) {
        end = yaml + strlen(yaml);
    }
    size_t len = end - yaml;
    char* str = xmd_malloc(len + 1);
    strncpy(str, yaml, len);
    str[len] = '\0';
    
    // Remove quotes if present
    if (str[0] == '"' && str[len-1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
    
    variable* result = variable_create_string(str);
    XMD_FREE_SAFE(str);
    return result;
}

/**
 * @brief AST function: yaml.stringify(object)
 * @param args Function arguments (1 expected)
 * @param arg_count Number of arguments
 * @param evaluator Evaluator context
 * @return YAML string as ast_value
 */
ast_value* ast_yaml_stringify(ast_node** args, size_t arg_count, ast_evaluator* evaluator) {
    if (arg_count != 1) {
        return ast_value_create_string("");
    }
    
    // Evaluate the argument
    ast_value* arg_val = ast_evaluate(args[0], evaluator);
    if (!arg_val) {
        return ast_value_create_string("");
    }
    
    // Convert to variable
    variable* var = ast_value_to_variable(arg_val);
    XMD_FREE_SAFE(arg_val);
    
    if (!var) {
        return ast_value_create_string("");
    }
    
    // Stringify to YAML
    char* yaml = yaml_stringify_variable(var, 0);
    variable_unref(var);
    
    if (!yaml) {
        return ast_value_create_string("");
    }
    
    // Create result
    ast_value* result = ast_value_create_string(yaml);
    XMD_FREE_SAFE(yaml);
    return result;
}

/**
 * @brief AST function: yaml.parse(string)
 * @param args Function arguments (1 expected)
 * @param arg_count Number of arguments
 * @param evaluator Evaluator context
 * @return Parsed object as ast_value
 */
ast_value* ast_yaml_parse(ast_node** args, size_t arg_count, ast_evaluator* evaluator) {
    if (arg_count != 1) {
        return ast_value_create_string("");
    }
    
    // Evaluate the argument
    ast_value* arg_val = ast_evaluate(args[0], evaluator);
    if (!arg_val || arg_val->type != AST_VAL_STRING) {
        if (arg_val) XMD_FREE_SAFE(arg_val);
        return ast_value_create_string("");
    }
    
    // Parse YAML
    variable* var = yaml_parse_simple(arg_val->value.string_value);
    XMD_FREE_SAFE(arg_val);
    
    if (!var) {
        return ast_value_create_string("");
    }
    
    // Convert to ast_value
    ast_value* result = ast_value_from_variable(var);
    variable_unref(var);
    
    return result ? result : ast_value_create_string("");
}