/**
 * @file parse_collection.c
 * @brief Parse collection syntax implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Parse collection syntax and expand to array
 * @param collection_name Name of collection variable
 * @param variables Variable store
 * @param items Output array of string values (caller must free)
 * @param count Output count of items
 * @return 0 on success, -1 on error
 */
int parse_collection(const char* collection_name, store* variables, char*** items, int* count) {
    char* collection_str = NULL;
    
    // Check if it's a literal string (starts and ends with quotes)
    if (collection_name[0] == '"' && collection_name[strlen(collection_name)-1] == '"') {
        // Parse literal string directly
        collection_str = malloc(strlen(collection_name) - 1);
        strncpy(collection_str, collection_name + 1, strlen(collection_name) - 2);
        collection_str[strlen(collection_name) - 2] = '\0';
    } else {
        // Try to get variable
        variable* collection = store_get(variables, collection_name);
        if (!collection) {
            return -1;
        }
        
        collection_str = variable_to_string(collection);
        if (!collection_str) {
            return -1;
        }
    }
    
    // Check for empty string first
    char* trimmed_collection = trim_whitespace(collection_str);
    if (strlen(trimmed_collection) == 0) {
        *items = NULL;
        *count = 0;
        free(collection_str);
        return 0;
    }
    
    // Count items by counting commas + 1
    int item_count = 1;
    for (char* p = collection_str; *p; p++) {
        if (*p == ',') item_count++;
    }
    
    // Allocate array
    *items = malloc(item_count * sizeof(char*));
    *count = item_count;
    
    // Parse items
    char* token = strtok(collection_str, ",");
    int i = 0;
    while (token && i < item_count) {
        char* trimmed = trim_whitespace(token);
        (*items)[i] = strdup(trimmed);
        i++;
        token = strtok(NULL, ",");
    }
    *count = i; // Actual count
    
    free(collection_str);
    return 0;
}
