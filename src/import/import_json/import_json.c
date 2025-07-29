/**
 * @file import_json.c
 * @brief JSON file import functionality
 * @author XMD Implementation Team
 * @date 2025-01-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/variable.h"
#include "../../../include/xmd.h"
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/store.h"

// Forward declarations
extern variable* unified_data_converter_import_file(const char* file_path, char** error_message);
extern variable* unified_data_converter_import_string(const char* data_string, const char* format_hint, char** error_message);

/**
 * @brief Import JSON file and make it available as a variable
 * @param processor XMD processor context
 * @param file_path Path to JSON file
 * @param variable_name Name to assign to the imported data
 * @return 0 on success, -1 on error
 */
int import_json_file(xmd_processor* processor, const char* file_path, const char* variable_name) {
    if (processor == NULL || file_path == NULL || variable_name == NULL) {
        return -1;
    }
    
    char* error_message = NULL;
    variable* imported_data = unified_data_converter_import_file(file_path, &error_message);
    
    if (imported_data == NULL) {
        // Log error if available
        if (error_message != NULL) {
            fprintf(stderr, "Error importing JSON: %s\n", error_message);
            free(error_message);
        }
        return -1;
    }
    
    // Set the variable in the processor's variable store
    processor_context* ctx = (processor_context*)processor;
    if (!store_set(ctx->variables, variable_name, imported_data)) {
        variable_unref(imported_data);
        return -1;
    }
    
    variable_unref(imported_data); // store_set increments reference
    return 0;
}

/**
 * @brief Import JSON string and make it available as a variable
 * @param processor XMD processor context
 * @param json_string JSON string to parse
 * @param variable_name Name to assign to the imported data
 * @return 0 on success, -1 on error
 */
int import_json_string(xmd_processor* processor, const char* json_string, const char* variable_name) {
    if (processor == NULL || json_string == NULL || variable_name == NULL) {
        return -1;
    }
    
    char* error_message = NULL;
    variable* imported_data = unified_data_converter_import_string(json_string, "json", &error_message);
    
    if (imported_data == NULL) {
        // Log error if available
        if (error_message != NULL) {
            fprintf(stderr, "Error importing JSON: %s\n", error_message);
            free(error_message);
        }
        return -1;
    }
    
    // Set the variable in the processor's variable store
    processor_context* ctx = (processor_context*)processor;
    if (!store_set(ctx->variables, variable_name, imported_data)) {
        variable_unref(imported_data);
        return -1;
    }
    
    variable_unref(imported_data); // store_set increments reference
    return 0;
}

/**
 * @brief Check if file is a JSON file based on extension
 * @param file_path File path to check
 * @return true if JSON file, false otherwise
 */
bool is_json_file(const char* file_path) {
    if (file_path == NULL) {
        return false;
    }
    
    const char* extension = strrchr(file_path, '.');
    if (extension == NULL) {
        return false;
    }
    
    return strcmp(extension, ".json") == 0;
}

/**
 * @brief Validate JSON string syntax
 * @param json_string JSON string to validate
 * @return true if valid, false otherwise
 */
bool validate_json_string(const char* json_string) {
    if (json_string == NULL) {
        return false;
    }
    
    char* error_message = NULL;
    variable* test_parse = unified_data_converter_import_string(json_string, "json", &error_message);
    
    if (test_parse != NULL) {
        variable_unref(test_parse);
        return true;
    } else {
        if (error_message != NULL) {
            free(error_message);
        }
        return false;
    }
}