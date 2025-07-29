/**
 * @file detect_file_type.c
 * @brief File type detection for import functionality
 * @author XMD Implementation Team
 * @date 2025-01-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * @brief File type enumeration
 */
typedef enum {
    FILE_TYPE_UNKNOWN = 0,
    FILE_TYPE_JSON = 1,
    FILE_TYPE_YAML = 2,
    FILE_TYPE_MARKDOWN = 3
} import_file_type_t;

/**
 * @brief Get file extension
 * @param file_path File path
 * @return File extension (without dot) or NULL if no extension
 */
static const char* get_file_extension(const char* file_path) {
    if (file_path == NULL) {
        return NULL;
    }
    
    const char* dot = strrchr(file_path, '.');
    if (dot == NULL || dot == file_path) {
        return NULL;
    }
    
    return dot + 1;
}

/**
 * @brief Convert string to lowercase
 * @param str Input string
 * @param buffer Output buffer (must be large enough)
 */
static void to_lowercase(const char* str, char* buffer) {
    if (str == NULL || buffer == NULL) {
        return;
    }
    
    while (*str) {
        *buffer = tolower(*str);
        str++;
        buffer++;
    }
    *buffer = '\0';
}

/**
 * @brief Detect file type by content
 * @param file_path File path
 * @return File type
 */
static import_file_type_t detect_by_content(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        return FILE_TYPE_UNKNOWN;
    }
    
    char buffer[512];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file);
    fclose(file);
    
    if (bytes_read == 0) {
        return FILE_TYPE_UNKNOWN;
    }
    
    buffer[bytes_read] = '\0';
    
    // Skip whitespace at the beginning
    char* content = buffer;
    while (*content && isspace(*content)) {
        content++;
    }
    
    // Check for JSON
    if (*content == '{' || *content == '[') {
        return FILE_TYPE_JSON;
    }
    
    // Check for YAML patterns
    // Look for key: value patterns or YAML list indicators
    char* line = strtok(content, "\n");
    while (line != NULL) {
        // Skip whitespace
        while (*line && isspace(*line)) {
            line++;
        }
        
        // Skip comments and empty lines
        if (*line == '#' || *line == '\0') {
            line = strtok(NULL, "\n");
            continue;
        }
        
        // Look for YAML key: value pattern
        char* colon = strchr(line, ':');
        if (colon != NULL) {
            // Check if it's not inside quotes (simple check)
            char* quote = strchr(line, '"');
            if (quote == NULL || quote > colon) {
                return FILE_TYPE_YAML;
            }
        }
        
        // Look for YAML list indicator
        if (*line == '-' && (*(line + 1) == ' ' || *(line + 1) == '\t')) {
            return FILE_TYPE_YAML;
        }
        
        line = strtok(NULL, "\n");
    }
    
    return FILE_TYPE_UNKNOWN;
}

/**
 * @brief Detect file type based on extension and content
 * @param file_path File path
 * @return File type
 */
import_file_type_t detect_file_type(const char* file_path) {
    if (file_path == NULL) {
        return FILE_TYPE_UNKNOWN;
    }
    
    // First, try to detect by extension
    const char* extension = get_file_extension(file_path);
    if (extension != NULL) {
        char ext_lower[16];
        to_lowercase(extension, ext_lower);
        
        if (strcmp(ext_lower, "json") == 0) {
            return FILE_TYPE_JSON;
        } else if (strcmp(ext_lower, "yaml") == 0 || strcmp(ext_lower, "yml") == 0) {
            return FILE_TYPE_YAML;
        } else if (strcmp(ext_lower, "md") == 0 || strcmp(ext_lower, "markdown") == 0) {
            return FILE_TYPE_MARKDOWN;
        }
    }
    
    // If extension is not recognized, try content detection
    return detect_by_content(file_path);
}

/**
 * @brief Check if file type is structured data (JSON or YAML)
 * @param type File type
 * @return true if structured data, false otherwise
 */
bool is_structured_data_type(import_file_type_t type) {
    return type == FILE_TYPE_JSON || type == FILE_TYPE_YAML;
}

/**
 * @brief Get file type name as string
 * @param type File type
 * @return Type name string
 */
const char* file_type_to_string(import_file_type_t type) {
    switch (type) {
        case FILE_TYPE_JSON:
            return "JSON";
        case FILE_TYPE_YAML:
            return "YAML";
        case FILE_TYPE_MARKDOWN:
            return "Markdown";
        default:
            return "Unknown";
    }
}