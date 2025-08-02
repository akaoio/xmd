/**
 * @file json_functions.c
 * @brief JSON stringify and parse functions for XMD
 * 
 * Genesis principle: This file contains multiple JSON functions
 * as they work together as a unit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../../include/ast.h"
#include "../../../include/store.h"
#include "../../../include/variable.h"
#include "../../../include/utils.h"

/**
 * @brief Escape string for JSON
 * @param str String to escape
 * @return Escaped string (must be freed)
 */
static char* json_escape_string(const char* str) {
    if (!str) return xmd_strdup("null");
    
    size_t len = strlen(str);
    size_t max_len = len * 2 + 3; // Worst case: all chars need escaping + quotes
    char* result = xmd_malloc(max_len);
    size_t pos = 0;
    
    result[pos++] = '"';
    
    for (size_t i = 0; i < len; i++) {
        switch (str[i]) {
            case '"':  
                result[pos++] = '\\';
                result[pos++] = '"';
                break;
            case '\\': 
                result[pos++] = '\\';
                result[pos++] = '\\';
                break;
            case '\b': 
                result[pos++] = '\\';
                result[pos++] = 'b';
                break;
            case '\f': 
                result[pos++] = '\\';
                result[pos++] = 'f';
                break;
            case '\n': 
                result[pos++] = '\\';
                result[pos++] = 'n';
                break;
            case '\r': 
                result[pos++] = '\\';
                result[pos++] = 'r';
                break;
            case '\t': 
                result[pos++] = '\\';
                result[pos++] = 't';
                break;
            default:
                if ((unsigned char)str[i] < 0x20) {
                    // Control character - escape as \uXXXX
                    pos += snprintf(result + pos, max_len - pos, "\\u%04x", (unsigned char)str[i]);
                } else {
                    result[pos++] = str[i];
                }
                break;
        }
    }
    
    result[pos++] = '"';
    result[pos] = '\0';
    
    return result;
}

/**
 * @brief Convert XMD variable to JSON string
 * @param var Variable to stringify
 * @param pretty Whether to pretty-print
 * @param indent Current indentation level
 * @return JSON string (must be freed)
 */
static char* json_stringify_variable(variable* var, bool pretty, int indent) {
    if (!var) {
        return xmd_strdup("null");
    }
    
    variable_type type = variable_get_type(var);
    char* result = NULL;
    
    switch (type) {
        case VAR_STRING: {
            const char* str = variable_get_string(var);
            result = json_escape_string(str);
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
                strcpy(result, "[");
                size_t pos = 1;
                
                for (size_t i = 0; i < count; i++) {
                    if (i > 0) {
                        // Add comma
                        if (pos + 1 >= total_size) {
                            total_size *= 2;
                            result = xmd_realloc(result, total_size);
                        }
                        result[pos++] = ',';
                    }
                    
                    if (pretty) {
                        // Add newline and indent
                        if (pos + indent * 2 + 3 >= total_size) {
                            total_size *= 2;
                            result = xmd_realloc(result, total_size);
                        }
                        result[pos++] = '\n';
                        for (int j = 0; j <= indent; j++) {
                            result[pos++] = ' ';
                            result[pos++] = ' ';
                        }
                    }
                    
                    variable* elem = variable_array_get(var, i);
                    if (elem) {
                        char* elem_str = json_stringify_variable(elem, pretty, indent + 1);
                        if (elem_str) {
                            size_t elem_len = strlen(elem_str);
                            if (pos + elem_len >= total_size) {
                                total_size = pos + elem_len + 100;
                                result = xmd_realloc(result, total_size);
                            }
                            strcpy(result + pos, elem_str);
                            pos += elem_len;
                            free(elem_str);
                        }
                    }
                }
                
                if (pretty && count > 0) {
                    // Add newline and closing indent
                    if (pos + indent * 2 + 3 >= total_size) {
                        total_size *= 2;
                        result = xmd_realloc(result, total_size);
                    }
                    result[pos++] = '\n';
                    for (int j = 0; j < indent; j++) {
                        result[pos++] = ' ';
                        result[pos++] = ' ';
                    }
                }
                
                result[pos++] = ']';
                result[pos] = '\0';
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
                strcpy(result, "{");
                size_t pos = 1;
                
                size_t key_count = 0;
                char** keys = variable_object_keys(var, &key_count);
                if (keys) {
                    for (size_t i = 0; i < count; i++) {
                        if (keys[i]) {
                            if (i > 0) {
                                // Add comma
                                if (pos + 1 >= total_size) {
                                    total_size *= 2;
                                    result = xmd_realloc(result, total_size);
                                }
                                result[pos++] = ',';
                            }
                            
                            if (pretty) {
                                // Add newline and indent
                                if (pos + indent * 2 + 3 >= total_size) {
                                    total_size *= 2;
                                    result = xmd_realloc(result, total_size);
                                }
                                result[pos++] = '\n';
                                for (int j = 0; j <= indent; j++) {
                                    result[pos++] = ' ';
                                    result[pos++] = ' ';
                                }
                            }
                            
                            // Add key
                            char* key_str = json_escape_string(keys[i]);
                            size_t key_len = strlen(key_str);
                            if (pos + key_len + 2 >= total_size) {
                                total_size = pos + key_len + 100;
                                result = xmd_realloc(result, total_size);
                            }
                            strcpy(result + pos, key_str);
                            pos += key_len;
                            free(key_str);
                            
                            result[pos++] = ':';
                            if (pretty) {
                                result[pos++] = ' ';
                            }
                            
                            // Add value
                            variable* val = variable_object_get(var, keys[i]);
                            if (val) {
                                char* val_str = json_stringify_variable(val, pretty, indent + 1);
                                if (val_str) {
                                    size_t val_len = strlen(val_str);
                                    if (pos + val_len >= total_size) {
                                        total_size = pos + val_len + 100;
                                        result = xmd_realloc(result, total_size);
                                    }
                                    strcpy(result + pos, val_str);
                                    pos += val_len;
                                    free(val_str);
                                }
                            }
                            
                            free(keys[i]);
                        }
                    }
                    free(keys);
                }
                
                if (pretty && count > 0) {
                    // Add newline and closing indent
                    if (pos + indent * 2 + 3 >= total_size) {
                        total_size *= 2;
                        result = xmd_realloc(result, total_size);
                    }
                    result[pos++] = '\n';
                    for (int j = 0; j < indent; j++) {
                        result[pos++] = ' ';
                        result[pos++] = ' ';
                    }
                }
                
                result[pos++] = '}';
                result[pos] = '\0';
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
 * @brief Parse JSON string to XMD variable (simplified)
 * @param json JSON string to parse
 * @param pos Current position in string
 * @return Parsed variable or NULL
 */
static variable* json_parse_value(const char* json, size_t* pos);

static variable* json_parse_object(const char* json, size_t* pos) {
    variable* obj = variable_create_object();
    (*pos)++; // Skip '{'
    
    // Skip whitespace
    while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                         json[*pos] == '\n' || json[*pos] == '\r')) {
        (*pos)++;
    }
    
    if (json[*pos] == '}') {
        (*pos)++; // Empty object
        return obj;
    }
    
    while (json[*pos]) {
        // Skip whitespace
        while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                             json[*pos] == '\n' || json[*pos] == '\r')) {
            (*pos)++;
        }
        
        // Parse key (must be string)
        if (json[*pos] != '"') {
            variable_unref(obj);
            return NULL;
        }
        
        (*pos)++; // Skip opening quote
        size_t key_start = *pos;
        while (json[*pos] && json[*pos] != '"') {
            if (json[*pos] == '\\') (*pos)++; // Skip escaped char
            (*pos)++;
        }
        
        if (!json[*pos]) {
            variable_unref(obj);
            return NULL;
        }
        
        size_t key_len = *pos - key_start;
        char* key = xmd_malloc(key_len + 1);
        strncpy(key, json + key_start, key_len);
        key[key_len] = '\0';
        
        (*pos)++; // Skip closing quote
        
        // Skip whitespace and colon
        while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                             json[*pos] == '\n' || json[*pos] == '\r')) {
            (*pos)++;
        }
        
        if (json[*pos] != ':') {
            free(key);
            variable_unref(obj);
            return NULL;
        }
        (*pos)++; // Skip colon
        
        // Parse value
        variable* val = json_parse_value(json, pos);
        if (!val) {
            free(key);
            variable_unref(obj);
            return NULL;
        }
        
        variable_object_set(obj, key, val);
        variable_unref(val);
        free(key);
        
        // Skip whitespace
        while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                             json[*pos] == '\n' || json[*pos] == '\r')) {
            (*pos)++;
        }
        
        if (json[*pos] == '}') {
            (*pos)++;
            break;
        }
        
        if (json[*pos] == ',') {
            (*pos)++;
        } else {
            // Error: expected comma or closing brace
            variable_unref(obj);
            return NULL;
        }
    }
    
    return obj;
}

static variable* json_parse_array(const char* json, size_t* pos) {
    variable* arr = variable_create_array();
    (*pos)++; // Skip '['
    
    // Skip whitespace
    while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                         json[*pos] == '\n' || json[*pos] == '\r')) {
        (*pos)++;
    }
    
    if (json[*pos] == ']') {
        (*pos)++; // Empty array
        return arr;
    }
    
    while (json[*pos]) {
        // Parse value
        variable* val = json_parse_value(json, pos);
        if (!val) {
            variable_unref(arr);
            return NULL;
        }
        
        variable_array_add(arr, val);
        variable_unref(val);
        
        // Skip whitespace
        while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                             json[*pos] == '\n' || json[*pos] == '\r')) {
            (*pos)++;
        }
        
        if (json[*pos] == ']') {
            (*pos)++;
            break;
        }
        
        if (json[*pos] == ',') {
            (*pos)++;
        } else {
            // Error: expected comma or closing bracket
            variable_unref(arr);
            return NULL;
        }
    }
    
    return arr;
}

static variable* json_parse_value(const char* json, size_t* pos) {
    // Skip whitespace
    while (json[*pos] && (json[*pos] == ' ' || json[*pos] == '\t' || 
                         json[*pos] == '\n' || json[*pos] == '\r')) {
        (*pos)++;
    }
    
    if (!json[*pos]) return NULL;
    
    // Object
    if (json[*pos] == '{') {
        return json_parse_object(json, pos);
    }
    
    // Array
    if (json[*pos] == '[') {
        return json_parse_array(json, pos);
    }
    
    // String
    if (json[*pos] == '"') {
        (*pos)++; // Skip opening quote
        size_t str_start = *pos;
        while (json[*pos] && json[*pos] != '"') {
            if (json[*pos] == '\\') (*pos)++; // Skip escaped char
            (*pos)++;
        }
        
        if (!json[*pos]) return NULL;
        
        size_t str_len = *pos - str_start;
        char* str = xmd_malloc(str_len + 1);
        strncpy(str, json + str_start, str_len);
        str[str_len] = '\0';
        
        (*pos)++; // Skip closing quote
        
        variable* result = variable_create_string(str);
        free(str);
        return result;
    }
    
    // null
    if (strncmp(json + *pos, "null", 4) == 0) {
        *pos += 4;
        return variable_create_null();
    }
    
    // true
    if (strncmp(json + *pos, "true", 4) == 0) {
        *pos += 4;
        return variable_create_boolean(true);
    }
    
    // false
    if (strncmp(json + *pos, "false", 5) == 0) {
        *pos += 5;
        return variable_create_boolean(false);
    }
    
    // Number
    if (json[*pos] == '-' || (json[*pos] >= '0' && json[*pos] <= '9')) {
        size_t num_start = *pos;
        if (json[*pos] == '-') (*pos)++;
        
        while (json[*pos] >= '0' && json[*pos] <= '9') (*pos)++;
        
        if (json[*pos] == '.') {
            (*pos)++;
            while (json[*pos] >= '0' && json[*pos] <= '9') (*pos)++;
        }
        
        if (json[*pos] == 'e' || json[*pos] == 'E') {
            (*pos)++;
            if (json[*pos] == '+' || json[*pos] == '-') (*pos)++;
            while (json[*pos] >= '0' && json[*pos] <= '9') (*pos)++;
        }
        
        size_t num_len = *pos - num_start;
        char* num_str = xmd_malloc(num_len + 1);
        strncpy(num_str, json + num_start, num_len);
        num_str[num_len] = '\0';
        
        double num = atof(num_str);
        free(num_str);
        
        return variable_create_number(num);
    }
    
    return NULL;
}

/**
 * @brief AST function: json.stringify(object)
 * @param args Function arguments (1 expected)
 * @param arg_count Number of arguments
 * @param evaluator Evaluator context
 * @return JSON string as ast_value
 */
ast_value* ast_json_stringify(ast_node** args, size_t arg_count, ast_evaluator* evaluator) {
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
    ast_value_free(arg_val);
    
    if (!var) {
        return ast_value_create_string("");
    }
    
    // Stringify to JSON
    char* json = json_stringify_variable(var, false, 0);
    variable_unref(var);
    
    if (!json) {
        return ast_value_create_string("");
    }
    
    // Create result
    ast_value* result = ast_value_create_string(json);
    free(json);
    return result;
}

/**
 * @brief AST function: json.parse(string)
 * @param args Function arguments (1 expected)
 * @param arg_count Number of arguments
 * @param evaluator Evaluator context
 * @return Parsed object as ast_value
 */
ast_value* ast_json_parse(ast_node** args, size_t arg_count, ast_evaluator* evaluator) {
    if (arg_count != 1) {
        return ast_value_create_string("");
    }
    
    // Evaluate the argument
    ast_value* arg_val = ast_evaluate(args[0], evaluator);
    if (!arg_val || arg_val->type != AST_VAL_STRING) {
        if (arg_val) ast_value_free(arg_val);
        return ast_value_create_string("");
    }
    
    // Parse JSON
    size_t pos = 0;
    variable* var = json_parse_value(arg_val->value.string_value, &pos);
    ast_value_free(arg_val);
    
    if (!var) {
        return ast_value_create_string("");
    }
    
    // Convert to ast_value
    ast_value* result = ast_value_from_variable(var);
    variable_unref(var);
    
    return result ? result : ast_value_create_string("");
}