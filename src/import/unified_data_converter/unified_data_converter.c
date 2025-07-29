/**
 * @file unified_data_converter.c
 * @brief Unified data converter for JSON and YAML import
 * @author XMD Implementation Team
 * @date 2025-01-29
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/variable.h"
#include "../../../include/xmd.h"

// Forward declarations for parser functions
extern variable* json_parser_parse_file(const char* file_path);
extern variable* yaml_parser_parse_file(const char* file_path);
extern variable* json_parser_parse_string(const char* json_string);
extern variable* yaml_parser_parse_string(const char* yaml_string);

// Forward declarations for file type detection
typedef enum {
    FILE_TYPE_UNKNOWN = 0,
    FILE_TYPE_JSON = 1,
    FILE_TYPE_YAML = 2,
    FILE_TYPE_MARKDOWN = 3
} import_file_type_t;

extern import_file_type_t detect_file_type(const char* file_path);
extern bool is_structured_data_type(import_file_type_t type);
extern const char* file_type_to_string(import_file_type_t type);

/**
 * @brief Import structured data file and convert to unified XMD variable
 * @param file_path Path to the file to import
 * @param error_message Pointer to store error message (optional)
 * @return XMD variable containing the data or NULL on error
 */
variable* unified_data_converter_import_file(const char* file_path, char** error_message) {
    if (file_path == NULL) {
        if (error_message) {
            *error_message = strdup("File path is NULL");
        }
        return NULL;
    }
    
    // DEBUG: Print file path
    printf("DEBUG CONVERTER: Importing file [%s]\n", file_path);
    fflush(stdout);
    
    // Detect file type
    import_file_type_t file_type = detect_file_type(file_path);
    
    // DEBUG: Print detected file type
    printf("DEBUG CONVERTER: Detected file type [%d]\n", file_type);
    fflush(stdout);
    
    if (!is_structured_data_type(file_type)) {
        printf("DEBUG CONVERTER: File type not structured data\n");
        fflush(stdout);
        if (error_message) {
            *error_message = strdup("File is not a supported structured data format (JSON or YAML)");
        }
        return NULL;
    }
    
    variable* result = NULL;
    
    switch (file_type) {
        case FILE_TYPE_JSON:
            printf("DEBUG CONVERTER: Calling JSON parser\n");
            fflush(stdout);
            result = json_parser_parse_file(file_path);
            printf("DEBUG CONVERTER: JSON parser returned [%p]\n", (void*)result);
            fflush(stdout);
            if (result == NULL && error_message) {
                *error_message = strdup("Failed to parse JSON file");
            }
            break;
            
        case FILE_TYPE_YAML:
            printf("DEBUG CONVERTER: Calling YAML parser\n");
            fflush(stdout);
            result = yaml_parser_parse_file(file_path);
            printf("DEBUG CONVERTER: YAML parser returned [%p]\n", (void*)result);
            fflush(stdout);
            if (result == NULL && error_message) {
                *error_message = strdup("Failed to parse YAML file");
            }
            break;
            
        default:
            if (error_message) {
                *error_message = strdup("Unsupported file type");
            }
            break;
    }
    
    return result;
}

/**
 * @brief Import structured data string and convert to unified XMD variable
 * @param data_string String containing JSON or YAML data
 * @param format_hint Format hint ("json", "yaml", or NULL for auto-detection)
 * @param error_message Pointer to store error message (optional)
 * @return XMD variable containing the data or NULL on error
 */
variable* unified_data_converter_import_string(const char* data_string, const char* format_hint, char** error_message) {
    if (data_string == NULL) {
        if (error_message) {
            *error_message = strdup("Data string is NULL");
        }
        return NULL;
    }
    
    variable* result = NULL;
    
    if (format_hint != NULL) {
        // Use format hint
        if (strcmp(format_hint, "json") == 0) {
            result = json_parser_parse_string(data_string);
            if (result == NULL && error_message) {
                *error_message = strdup("Failed to parse JSON string");
            }
        } else if (strcmp(format_hint, "yaml") == 0 || strcmp(format_hint, "yml") == 0) {
            result = yaml_parser_parse_string(data_string);
            if (result == NULL && error_message) {
                *error_message = strdup("Failed to parse YAML string");
            }
        } else {
            if (error_message) {
                *error_message = strdup("Unsupported format hint");
            }
        }
    } else {
        // Auto-detect format
        // Try JSON first (stricter format)
        result = json_parser_parse_string(data_string);
        if (result == NULL) {
            // Try YAML
            result = yaml_parser_parse_string(data_string);
            if (result == NULL && error_message) {
                *error_message = strdup("Failed to parse string as JSON or YAML");
            }
        }
    }
    
    return result;
}

/**
 * @brief Validate that variable can be used as structured data
 * @param var Variable to validate
 * @return true if valid, false otherwise
 */
bool unified_data_converter_validate_variable(variable* var) {
    if (var == NULL) {
        return false;
    }
    
    // Any XMD variable type is valid for our unified data model
    // The variable system already handles proper type checking
    return true;
}

/**
 * @brief Deep copy a variable for import isolation
 * @param var Variable to copy
 * @return Copied variable or NULL on error
 */
variable* unified_data_converter_copy_variable(variable* var) {
    if (var == NULL) {
        return NULL;
    }
    
    // Use the existing variable copy function
    return variable_copy(var);
}

/**
 * @brief Get variable type as string for debugging
 * @param var Variable to inspect
 * @return Type name string
 */
const char* unified_data_converter_get_type_string(variable* var) {
    if (var == NULL) {
        return "null";
    }
    
    variable_type type = variable_get_type(var);
    
    switch (type) {
        case VAR_NULL:
            return "null";
        case VAR_BOOLEAN:
            return "boolean";
        case VAR_NUMBER:
            return "number";
        case VAR_STRING:
            return "string";
        case VAR_ARRAY:
            return "array";
        case VAR_OBJECT:
            return "object";
        default:
            return "unknown";
    }
}

/**
 * @brief Check if two variables have compatible types for unified handling
 * @param var1 First variable
 * @param var2 Second variable
 * @return true if compatible, false otherwise
 */
bool unified_data_converter_types_compatible(variable* var1, variable* var2) {
    if (var1 == NULL || var2 == NULL) {
        return false;
    }
    
    variable_type type1 = variable_get_type(var1);
    variable_type type2 = variable_get_type(var2);
    
    // Same types are always compatible
    if (type1 == type2) {
        return true;
    }
    
    // Numbers and strings can often be converted
    if ((type1 == VAR_NUMBER && type2 == VAR_STRING) ||
        (type1 == VAR_STRING && type2 == VAR_NUMBER)) {
        return true;
    }
    
    // Booleans and strings can be converted
    if ((type1 == VAR_BOOLEAN && type2 == VAR_STRING) ||
        (type1 == VAR_STRING && type2 == VAR_BOOLEAN)) {
        return true;
    }
    
    return false;
}