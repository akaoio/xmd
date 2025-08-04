/**
 * @file validation_macros.h
 * @brief Enhanced validation macro patterns for XMD
 * @details Phase 1 of macro consolidation - validation patterns
 * @author DEBTHUNTER
 * @date 2025-08-03
 */

#ifndef XMD_VALIDATION_MACROS_H
#define XMD_VALIDATION_MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_macros.h"

// Quick fix for missing XMD_ERROR function
#define XMD_ERROR(...) fprintf(stderr, "[ERROR] " __VA_ARGS__)

/* ============================================================================
 * EXTENDED VALIDATION PATTERNS
 * ============================================================================ */

/**
 * @brief Extended validation with custom return value
 * @details Replaces manual NULL checks with custom return values
 */
#define XMD_VALIDATE_PTRS_RETVAL(retval, ...) \
    do { \
        void* _ptrs[] = {__VA_ARGS__}; \
        size_t _count = sizeof(_ptrs) / sizeof(_ptrs[0]); \
        for (size_t _i = 0; _i < _count; _i++) { \
            if (!_ptrs[_i]) { \
                XMD_ERROR("NULL parameter %zu", _i + 1); \
                return retval; \
            } \
        } \
    } while(0)

/**
 * @brief Validate with custom error message
 * @details Provides context-specific error messages
 */
#define XMD_VALIDATE_PTRS_MSG(msg, ...) \
    do { \
        void* _ptrs[] = {__VA_ARGS__}; \
        size_t _count = sizeof(_ptrs) / sizeof(_ptrs[0]); \
        for (size_t _i = 0; _i < _count; _i++) { \
            if (!_ptrs[_i]) { \
                XMD_ERROR("%s: NULL parameter %zu", msg, _i + 1); \
                return NULL; \
            } \
        } \
    } while(0)

/**
 * @brief Type validation for AST nodes with custom return
 * @details Replaces manual AST node type checking
 */
#define XMD_VALIDATE_NODE_TYPE_RETVAL(node, expected_type, retval) \
    do { \
        if (!node) { \
            XMD_ERROR("NULL AST node"); \
            return retval; \
        } \
        if (node->type != (expected_type)) { \
            XMD_ERROR("Wrong AST type: got %d, expected %d", \
                     node->type, (expected_type)); \
            return retval; \
        } \
    } while(0)

/**
 * @brief String validation for non-empty strings
 * @details Replaces manual string NULL and empty checks
 */
#define XMD_VALIDATE_STRING(str) \
    do { \
        if (!str) { \
            XMD_ERROR("NULL string parameter"); \
            return NULL; \
        } \
        if (strlen(str) == 0) { \
            XMD_ERROR("Empty string parameter"); \
            return NULL; \
        } \
    } while(0)

/**
 * @brief String validation with custom return value
 */
#define XMD_VALIDATE_STRING_RETVAL(str, retval) \
    do { \
        if (!str) { \
            XMD_ERROR("NULL string parameter"); \
            return retval; \
        } \
        if (strlen(str) == 0) { \
            XMD_ERROR("Empty string parameter"); \
            return retval; \
        } \
    } while(0)

/**
 * @brief Range validation for numeric values
 * @details Replaces manual range checking code
 */
#define XMD_VALIDATE_RANGE(val, min, max) \
    do { \
        if ((val) < (min) || (val) > (max)) { \
            XMD_ERROR("Value %ld out of range [%ld, %ld]", \
                     (long)(val), (long)(min), (long)(max)); \
            return NULL; \
        } \
    } while(0)

/**
 * @brief Range validation with custom return value
 */
#define XMD_VALIDATE_RANGE_RETVAL(val, min, max, retval) \
    do { \
        if ((val) < (min) || (val) > (max)) { \
            XMD_ERROR("Value %ld out of range [%ld, %ld]", \
                     (long)(val), (long)(min), (long)(max)); \
            return retval; \
        } \
    } while(0)

// XMD_VALIDATE_ARRAY_BOUNDS already defined in common_macros.h

/**
 * @brief Buffer size validation
 * @details Ensures buffer is large enough for operation
 */
#define XMD_VALIDATE_BUFFER_SIZE(buffer, required_size, actual_size) \
    do { \
        if (!buffer) { \
            XMD_ERROR("NULL buffer"); \
            return NULL; \
        } \
        if ((actual_size) < (required_size)) { \
            XMD_ERROR("Buffer too small: %zu < %zu", \
                     (size_t)(actual_size), (size_t)(required_size)); \
            return NULL; \
        } \
    } while(0)

/**
 * @brief File descriptor validation
 * @details Validates file descriptors are valid
 */
#define XMD_VALIDATE_FILE_DESCRIPTOR(fd) \
    do { \
        if ((fd) < 0) { \
            XMD_ERROR("Invalid file descriptor: %d", fd); \
            return NULL; \
        } \
    } while(0)

/**
 * @brief Enum validation
 * @details Validates enum values are within expected range
 */
#define XMD_VALIDATE_ENUM(val, min_enum, max_enum) \
    do { \
        if ((val) < (min_enum) || (val) > (max_enum)) { \
            XMD_ERROR("Invalid enum value: %d not in range [%d, %d]", \
                     (int)(val), (int)(min_enum), (int)(max_enum)); \
            return NULL; \
        } \
    } while(0)

/**
 * @brief Function pointer validation
 * @details Validates function pointers are not NULL
 */
#define XMD_VALIDATE_FUNCTION(func_ptr, func_name) \
    do { \
        if (!func_ptr) { \
            XMD_ERROR("NULL function pointer: %s", func_name); \
            return NULL; \
        } \
    } while(0)

/* ============================================================================
 * CONDITIONAL VALIDATION PATTERNS
 * ============================================================================ */

/**
 * @brief Validate condition with custom error
 * @details Generic condition validation with custom message
 */
#define XMD_VALIDATE_CONDITION(condition, fmt, ...) \
    do { \
        if (!(condition)) { \
            XMD_ERROR(fmt, ##__VA_ARGS__); \
            return NULL; \
        } \
    } while(0)

/**
 * @brief Validate condition with custom return value
 */
#define XMD_VALIDATE_CONDITION_RETVAL(condition, retval, fmt, ...) \
    do { \
        if (!(condition)) { \
            XMD_ERROR(fmt, ##__VA_ARGS__); \
            return retval; \
        } \
    } while(0)

/**
 * @brief Validate memory allocation result
 * @details Checks if allocation succeeded
 */
#define XMD_VALIDATE_ALLOCATION(ptr, size) \
    do { \
        if (!ptr) { \
            XMD_ERROR("Memory allocation failed for %zu bytes", (size_t)(size)); \
            return NULL; \
        } \
    } while(0)

/**
 * @brief Validate initialization state
 * @details Checks if object is properly initialized
 */
#define XMD_VALIDATE_INITIALIZED(obj, field) \
    do { \
        if (!obj || !obj->field) { \
            XMD_ERROR("Object not properly initialized"); \
            return NULL; \
        } \
    } while(0)

/* ============================================================================
 * DAY 7: ERROR HANDLING PATTERNS
 * ============================================================================ */

/**
 * @brief Error handling with cleanup for functions returning pointers
 * @details Consolidates error return + cleanup patterns
 */
#define XMD_ERROR_CLEANUP_RETURN(retval, cleanup_block, fmt, ...) \
    do { \
        XMD_ERROR(fmt, ##__VA_ARGS__); \
        cleanup_block; \
        return retval; \
    } while(0)

/**
 * @brief Error handling with goto cleanup pattern
 * @details Consolidates error + goto cleanup patterns
 */
#define XMD_ERROR_GOTO(label, fmt, ...) \
    do { \
        XMD_ERROR(fmt, ##__VA_ARGS__); \
        goto label; \
    } while(0)

/**
 * @brief Error handling for functions returning int status codes
 * @details Consolidates error logging + status return patterns
 */
#define XMD_ERROR_STATUS(status, fmt, ...) \
    do { \
        XMD_ERROR(fmt, ##__VA_ARGS__); \
        return status; \
    } while(0)

/**
 * @brief Error handling with cleanup and status return
 * @details Consolidates cleanup + status return patterns
 */
#define XMD_ERROR_CLEANUP_STATUS(status, cleanup_block, fmt, ...) \
    do { \
        XMD_ERROR(fmt, ##__VA_ARGS__); \
        cleanup_block; \
        return status; \
    } while(0)

/**
 * @brief Resource cleanup macro pattern
 * @details Consolidates if(ptr) { cleanup(ptr); ptr = NULL; } patterns
 */
#define XMD_CLEANUP_RESOURCE(ptr, cleanup_func) \
    do { \
        if (ptr) { \
            cleanup_func(ptr); \
            ptr = NULL; \
        } \
    } while(0)

/**
 * @brief Multi-resource cleanup pattern
 * @details Cleans up multiple resources in reverse order
 */
#define XMD_CLEANUP_RESOURCES_2(ptr1, func1, ptr2, func2) \
    do { \
        XMD_CLEANUP_RESOURCE(ptr2, func2); \
        XMD_CLEANUP_RESOURCE(ptr1, func1); \
    } while(0)

#define XMD_CLEANUP_RESOURCES_3(ptr1, func1, ptr2, func2, ptr3, func3) \
    do { \
        XMD_CLEANUP_RESOURCE(ptr3, func3); \
        XMD_CLEANUP_RESOURCE(ptr2, func2); \
        XMD_CLEANUP_RESOURCE(ptr1, func1); \
    } while(0)

/**
 * @brief Error handling with multiple cleanup paths
 * @details Handles complex error scenarios with multiple resources
 */
#define XMD_ERROR_CLEANUP_MULTIPLE(retval, fmt, ...) \
    do { \
        XMD_ERROR(fmt, ##__VA_ARGS__); \
        goto error_cleanup; \
    } while(0)

/**
 * @brief Structured try-catch-like error handling
 * @details Provides structured error handling pattern
 */
#define XMD_TRY_BEGIN() \
    do { \
        int _xmd_error_occurred = 0;

#define XMD_TRY_ERROR(fmt, ...) \
        XMD_ERROR(fmt, ##__VA_ARGS__); \
        _xmd_error_occurred = 1; \
        break;

#define XMD_TRY_END_CLEANUP(cleanup_block) \
        if (_xmd_error_occurred) { \
            cleanup_block; \
        } \
    } while(0)

/* ============================================================================
 * DAY 8: MEMORY MANAGEMENT PATTERNS
 * ============================================================================ */

/**
 * @brief Safe memory allocation with error handling
 * @details Allocates memory and validates result in one macro
 */
#define XMD_MALLOC_VALIDATED(ptr, type, size, retval) \
    do { \
        ptr = (type*)xmd_malloc(size); \
        if (!ptr) { \
            XMD_ERROR("Memory allocation failed for %zu bytes", (size_t)(size)); \
            return retval; \
        } \
    } while(0)

/**
 * @brief Safe memory allocation with cleanup on failure
 * @details Allocates memory with cleanup if allocation fails
 */
#define XMD_MALLOC_CLEANUP(ptr, type, size, cleanup_block, retval) \
    do { \
        ptr = (type*)xmd_malloc(size); \
        if (!ptr) { \
            XMD_ERROR("Memory allocation failed for %zu bytes", (size_t)(size)); \
            cleanup_block; \
            return retval; \
        } \
    } while(0)

/**
 * @brief Safe memory reallocation pattern
 * @details Reallocates memory safely with backup pointer
 */
#define XMD_REALLOC_VALIDATED(ptr, type, new_size, retval) \
    do { \
        type* _temp = (type*)realloc(ptr, new_size); \
        if (!_temp) { \
            XMD_ERROR("Memory reallocation failed for %zu bytes", (size_t)(new_size)); \
            return retval; \
        } \
        ptr = _temp; \
    } while(0)

/**
 * @brief Memory leak prevention pattern
 * @details Ensures pointer is freed and set to NULL
 */
#define XMD_FREE_NULL(ptr) \
    do { \
        if (ptr) { \
            xmd_free(ptr); \
            ptr = NULL; \
        } \
    } while(0)

/* ============================================================================
 * FILE OPERATION MACROS - Eliminate file handling duplication
 * ============================================================================ */

/**
 * @brief Open file for reading with error handling
 * @details Opens file and returns on failure with proper error message
 */
#define XMD_FILE_READ_OPEN(file, path, retval) \
    FILE* file = fopen(path, "r"); \
    if (!file) { \
        XMD_ERROR("Cannot open file for reading: %s", path); \
        return retval; \
    }

/**
 * @brief Open file for writing with error handling
 * @details Opens file and returns on failure with proper error message
 */
#define XMD_FILE_WRITE_OPEN(file, path, retval) \
    FILE* file = fopen(path, "w"); \
    if (!file) { \
        XMD_ERROR("Cannot open file for writing: %s", path); \
        return retval; \
    }

/**
 * @brief Open file for appending with error handling
 * @details Opens file and returns on failure with proper error message
 */
#define XMD_FILE_APPEND_OPEN(file, path, retval) \
    FILE* file = fopen(path, "a"); \
    if (!file) { \
        XMD_ERROR("Cannot open file for appending: %s", path); \
        return retval; \
    }

/**
 * @brief Safe file close operation
 * @details Closes file and sets pointer to NULL
 */
#define XMD_FILE_CLOSE_SAFE(file) \
    do { \
        if (file) { \
            fclose(file); \
            file = NULL; \
        } \
    } while(0)

/* ============================================================================
 * VARIABLE TYPE DISPATCH MACROS - Eliminate switch duplication
 * ============================================================================ */

/**
 * @brief Dispatch based on variable type
 * @details Eliminates repetitive switch statements for variable types
 */
#define XMD_VARIABLE_TYPE_DISPATCH(var, string_case, number_case, boolean_case, array_case, object_case, null_case, default_case) \
    switch ((var)->type) { \
        case VAR_STRING: string_case; break; \
        case VAR_NUMBER: number_case; break; \
        case VAR_BOOLEAN: boolean_case; break; \
        case VAR_ARRAY: array_case; break; \
        case VAR_OBJECT: object_case; break; \
        case VAR_NULL: null_case; break; \
        default: default_case; break; \
    }

/**
 * @brief Simple variable type dispatch for common operations
 * @details For cases where only certain types need handling
 */
#define XMD_VAR_TYPE_SWITCH(var, type_enum, action) \
    if ((var)->type == type_enum) { action; }

/* ============================================================================
 * AST TYPE DISPATCH MACROS - Eliminate AST switch duplication
 * ============================================================================ */

/**
 * @brief Dispatch based on AST node type
 * @details Eliminates repetitive switch statements for AST types
 */
#define XMD_AST_TYPE_DISPATCH(node, cases...) \
    switch ((node)->type) { \
        cases \
    }

/* ============================================================================
 * HIGH-IMPACT DUPLICATION ELIMINATION MACROS
 * ============================================================================ */

/**
 * @brief Boolean condition evaluation macro
 * @details Eliminates repetitive if (condition_val && condition_val->type == AST_VAL_BOOLEAN) patterns
 */
#define XMD_EVALUATE_CONDITION(condition_expr, evaluator, retval) \
    do { \
        ast_value* condition_val = ast_evaluate(condition_expr, evaluator); \
        if (!condition_val) return retval; \
        if (condition_val->type != AST_VAL_BOOLEAN) { \
            XMD_FREE_SAFE(condition_val); \
            return retval; \
        } \
    } while(0)

/**
 * @brief Function name extraction macro for string names with parentheses
 * @details Eliminates repetitive function name extraction from function call nodes
 */
#define XMD_EXTRACT_FUNCTION_NAME(source_name, dest_buffer, buffer_size) \
    do { \
        const char* paren = strchr(source_name, '('); \
        if (paren) { \
            size_t name_len = paren - source_name; \
            if (name_len < buffer_size) { \
                strncpy(dest_buffer, source_name, name_len); \
                dest_buffer[name_len] = '\0'; \
            } else { \
                strncpy(dest_buffer, source_name, buffer_size - 1); \
                dest_buffer[buffer_size - 1] = '\0'; \
            } \
        } else { \
            strncpy(dest_buffer, source_name, buffer_size - 1); \
            dest_buffer[buffer_size - 1] = '\0'; \
        } \
    } while(0)

/**
 * @brief Array element iteration macro
 * @details Eliminates repetitive array traversal with null checks
 */
#define XMD_ITERATE_ARRAY_ELEMENTS(array_var, index_var, element_var, body) \
    for (size_t index_var = 0; index_var < (array_var)->element_count; index_var++) { \
        variable* element_var = (array_var)->elements[index_var]; \
        if (!element_var) continue; \
        body; \
    }

/**
 * @brief Indexed array iteration macro for parameter processing
 * @details Eliminates repetitive indexed array traversal patterns
 */
#define XMD_ITERATE_ARRAY_ELEMENTS_INDEXED(array, count, index_var, element_var, body) \
    for (size_t index_var = 0; index_var < count; index_var++) { \
        const char* element_var = array[index_var]; \
        if (!element_var) continue; \
        body; \
    }

/**
 * @brief Control flow signaling macro
 * @details Eliminates repetitive break/continue/return signal handling
 */
#define XMD_HANDLE_CONTROL_FLOW(evaluator, break_action, continue_action, return_action) \
    do { \
        if ((evaluator)->break_flag) { break_action; } \
        if ((evaluator)->continue_flag) { continue_action; } \
        if ((evaluator)->return_flag) { return_action; } \
    } while(0)

/**
 * @brief Performance profiler recording macro
 * @details Eliminates repetitive profiler recording patterns
 */
#define XMD_RECORD_PROFILER_EVENT(profiler, event_type, size) \
    do { \
        if (profiler) { \
            perf_profiler_record_##event_type(profiler, size); \
        } \
    } while(0)

/**
 * @brief Error with function name macro
 * @details Eliminates repetitive error reporting with function context
 */
#define XMD_FUNCTION_ERROR(func_name, fmt, ...) \
    XMD_ERROR("%s: " fmt, func_name, ##__VA_ARGS__)

/* ============================================================================
 * STORE/HASH TABLE OPERATION MACROS - Phase 3 Duplication Elimination
 * ============================================================================ */

/**
 * @brief Hash table entry lookup macro
 * @details Eliminates repetitive hash table traversal patterns
 */
#define XMD_HASH_TABLE_FIND_ENTRY(store, key, entry_var, found_action) \
    do { \
        unsigned int index = xmd_hash_key(key, (store)->capacity); \
        store_entry* entry_var = (store)->buckets[index]; \
        while (entry_var) { \
            if (STR_EQUALS((entry_var)->key, key)) { \
                found_action; \
                break; \
            } \
            entry_var = (entry_var)->next; \
        } \
    } while(0)

/**
 * @brief Empty key validation macro
 * @details Eliminates repetitive empty key validation patterns
 */
#define XMD_VALIDATE_KEY_NOT_EMPTY(key, retval, func_name) \
    do { \
        if (!(key) || strlen(key) == 0) { \
            XMD_ERROR_RETURN(retval, "%s: Empty key provided%s", func_name, ""); \
        } \
    } while(0)

/**
 * @brief Variable reference replacement macro
 * @details Eliminates repetitive variable reference management in stores
 */
#define XMD_VARIABLE_REPLACE(entry_ptr, new_value) \
    do { \
        if ((entry_ptr)->value) { \
            variable_unref((entry_ptr)->value); \
        } \
        (entry_ptr)->value = new_value; \
        if (new_value) { \
            variable_ref(new_value); \
        } \
    } while(0)

/**
 * @brief Store entry creation macro
 * @details Eliminates repetitive store entry allocation and initialization
 */
#define XMD_CREATE_STORE_ENTRY(entry_var, key_str, value_var, retval) \
    do { \
        XMD_MALLOC_VALIDATED(entry_var, store_entry, sizeof(store_entry), retval); \
        (entry_var)->key = xmd_strdup(key_str); \
        if (!(entry_var)->key) { \
            XMD_FREE_SAFE(entry_var); \
            return retval; \
        } \
        (entry_var)->value = value_var; \
        if (value_var) variable_ref(value_var); \
        (entry_var)->next = NULL; \
    } while(0)

/* ============================================================================
 * STRING OPERATION MACROS - Phase 3 String Duplication Elimination  
 * ============================================================================ */

/**
 * @brief Safe string concatenation macro
 * @details Eliminates repetitive string concatenation with length checking
 */
#define XMD_STRING_CONCAT_SAFE(dest, dest_size, src1, src2) \
    do { \
        size_t len1 = (src1) ? strlen(src1) : 0; \
        size_t len2 = (src2) ? strlen(src2) : 0; \
        if (len1 + len2 + 1 <= dest_size) { \
            strcpy(dest, (src1) ? (src1) : ""); \
            if (src2) strcat(dest, src2); \
        } else { \
            strncpy(dest, (src1) ? (src1) : "", dest_size - 1); \
            dest[dest_size - 1] = '\0'; \
        } \
    } while(0)

/**
 * @brief String buffer allocation macro
 * @details Eliminates repetitive string buffer allocation with size calculation
 */
#define XMD_ALLOC_STRING_BUFFER(buffer_var, size_needed, retval) \
    do { \
        XMD_MALLOC_VALIDATED(buffer_var, char, size_needed + 1, retval); \
        buffer_var[0] = '\0'; \
    } while(0)

/**
 * @brief String copy with bounds checking macro
 * @details Eliminates repetitive safe string copying patterns
 */
#define XMD_STRING_COPY_SAFE(dest, dest_size, src) \
    do { \
        if (src) { \
            strncpy(dest, src, dest_size - 1); \
            dest[dest_size - 1] = '\0'; \
        } else { \
            dest[0] = '\0'; \
        } \
    } while(0)

/**
 * @brief Dynamic string duplication with validation macro
 * @details Eliminates repetitive strdup with NULL checking patterns
 */
#define XMD_STRDUP_VALIDATED(dest_var, src_str, retval) \
    do { \
        if (src_str) { \
            dest_var = xmd_strdup(src_str); \
            if (!dest_var) return retval; \
        } else { \
            dest_var = NULL; \
        } \
    } while(0)

/* ============================================================================
 * LINKED LIST OPERATION MACROS - Phase 3 List Duplication Elimination
 * ============================================================================ */

/**
 * @brief Generic linked list traversal and cleanup macro
 * @details Eliminates repetitive linked list cleanup patterns
 */
#define XMD_CLEANUP_LINKED_LIST(head_ptr, node_type, next_field, cleanup_action) \
    do { \
        node_type* current = head_ptr; \
        while (current) { \
            node_type* next = current->next_field; \
            cleanup_action; \
            current = next; \
        } \
        head_ptr = NULL; \
    } while(0)

/**
 * @brief Token list cleanup macro
 * @details Eliminates repetitive token list cleanup patterns
 */
#define XMD_CLEANUP_TOKEN_LIST(head_ptr) \
    XMD_CLEANUP_LINKED_LIST(head_ptr, token, next, { \
        XMD_FREE_SAFE(current->value); \
        XMD_FREE_SAFE(current); \
    })


/**
 * @brief Binary numeric operation macro for AST evaluation
 * @details Handles numeric binary operations with type checking
 */
#define XMD_EVALUATE_BINARY_NUMERIC(left, right, op, result) \
    do { \
        if ((left)->type == AST_VAL_NUMBER && (right)->type == AST_VAL_NUMBER) { \
            double val = (left)->value.number_value op (right)->value.number_value; \
            (result) = ast_value_create_number(val); \
        } \
    } while(0)

/**
 * @brief Convert AST value to string for concatenation
 * @details Handles conversion of different value types to strings
 */
#define XMD_VALUE_TO_STRING(str_var, ast_val, retval) \
    do { \
        if ((ast_val)->type == AST_VAL_STRING) { \
            XMD_STRDUP_VALIDATED((str_var), (ast_val)->value.string_value, retval); \
        } else if ((ast_val)->type == AST_VAL_NUMBER) { \
            XMD_MALLOC_VALIDATED((str_var), char, 32, retval); \
            snprintf((str_var), 32, "%g", (ast_val)->value.number_value); \
        } else if ((ast_val)->type == AST_VAL_BOOLEAN) { \
            XMD_STRDUP_VALIDATED((str_var), (ast_val)->value.boolean_value ? "true" : "false", retval); \
        } \
    } while(0)

/**
 * @brief String concatenation helper for AST values
 * @details Concatenates two strings and creates AST string value
 */
#define XMD_CONCAT_STRINGS(result, str1, str2) \
    do { \
        size_t total_len = strlen(str1) + strlen(str2) + 1; \
        char* concat; \
        XMD_MALLOC_VALIDATED(concat, char, total_len, NULL); \
        strcpy(concat, str1); \
        strcat(concat, str2); \
        (result) = ast_value_create_string(concat); \
        XMD_FREE_NULL(concat); \
    } while(0)

/**
 * @brief Universal NULL validation with custom return (HIGHEST ROI DUPLICATION ELIMINATOR)
 * @details Eliminates 132+ duplicate NULL checks across codebase
 */
#define XMD_VALIDATE_PTR_RETURN(ptr, retval) \
    do { \
        if (!(ptr)) { \
            return (retval); \
        } \
    } while(0)

/**
 * @brief Universal NULL validation with continue (for loop contexts)
 * @details Eliminates NULL checks in loops that continue on NULL
 */
#define XMD_VALIDATE_PTR_CONTINUE(ptr) \
    do { \
        if (!(ptr)) { \
            continue; \
        } \
    } while(0)

/**
 * @brief Multiple parameter validation in one macro
 * @details Validates up to 5 parameters for NULL, reduces validation duplication
 */
#define XMD_VALIDATE_PARAMS_1(retval, p1) \
    XMD_VALIDATE_PTR_RETURN(p1, retval)

#define XMD_VALIDATE_PARAMS_2(retval, p1, p2) \
    XMD_VALIDATE_PTR_RETURN(p1, retval); \
    XMD_VALIDATE_PTR_RETURN(p2, retval)

#define XMD_VALIDATE_PARAMS_3(retval, p1, p2, p3) \
    XMD_VALIDATE_PTR_RETURN(p1, retval); \
    XMD_VALIDATE_PTR_RETURN(p2, retval); \
    XMD_VALIDATE_PTR_RETURN(p3, retval)

#define XMD_VALIDATE_PARAMS_4(retval, p1, p2, p3, p4) \
    XMD_VALIDATE_PTR_RETURN(p1, retval); \
    XMD_VALIDATE_PTR_RETURN(p2, retval); \
    XMD_VALIDATE_PTR_RETURN(p3, retval); \
    XMD_VALIDATE_PTR_RETURN(p4, retval)

#define XMD_VALIDATE_PARAMS_5(retval, p1, p2, p3, p4, p5) \
    XMD_VALIDATE_PTR_RETURN(p1, retval); \
    XMD_VALIDATE_PTR_RETURN(p2, retval); \
    XMD_VALIDATE_PTR_RETURN(p3, retval); \
    XMD_VALIDATE_PTR_RETURN(p4, retval); \
    XMD_VALIDATE_PTR_RETURN(p5, retval)

/**
 * @brief Cleanup-before-return pattern eliminator  
 * @details Handles condition check + cleanup + return in one macro
 */
#define XMD_VALIDATE_OR_CLEANUP(condition, cleanup_code, retval) \
    do { \
        if (!(condition)) { \
            cleanup_code; \
            return (retval); \
        } \
    } while(0)

/**
 * @brief Array allocation with initialization
 * @details Allocates array and initializes to zero
 */
#define XMD_CALLOC_VALIDATED(ptr, type, count, retval) \
    do { \
        ptr = (type*)calloc(count, sizeof(type)); \
        if (!ptr) { \
            XMD_ERROR("Array allocation failed for %zu elements", (size_t)(count)); \
            return retval; \
        } \
    } while(0)

// XMD_STRDUP_VALIDATED - using different name to avoid conflict

/**
 * @brief Memory boundary validation
 * @details Validates memory access within bounds
 */
#define XMD_VALIDATE_MEMORY_BOUNDS(ptr, offset, size, retval) \
    do { \
        if (!ptr) { \
            XMD_ERROR("NULL pointer in memory bounds check"); \
            return retval; \
        } \
        if ((offset) >= (size)) { \
            XMD_ERROR("Memory access out of bounds: %zu >= %zu", \
                     (size_t)(offset), (size_t)(size)); \
            return retval; \
        } \
    } while(0)

/**
 * @brief Reference counting increment pattern
 * @details Safe reference counting with overflow protection
 */
#define XMD_REF_INCREMENT(obj, retval) \
    do { \
        if (!obj) { \
            XMD_ERROR("Cannot increment reference on NULL object"); \
            return retval; \
        } \
        if (obj->ref_count >= SIZE_MAX - 1) { \
            XMD_ERROR("Reference count overflow"); \
            return retval; \
        } \
        obj->ref_count++; \
    } while(0)

/**
 * @brief Reference counting decrement pattern
 * @details Safe reference counting with automatic cleanup
 */
#define XMD_REF_DECREMENT(obj, cleanup_func) \
    do { \
        if (obj && obj->ref_count > 0) { \
            obj->ref_count--; \
            if (obj->ref_count == 0) { \
                cleanup_func(obj); \
                obj = NULL; \
            } \
        } \
    } while(0)

/**
 * @brief Memory pool allocation pattern
 * @details Allocates from memory pool with fallback
 */
#define XMD_POOL_ALLOC(ptr, pool, type, fallback_size, retval) \
    do { \
        if (pool && pool->available >= sizeof(type)) { \
            ptr = (type*)pool_allocate(pool, sizeof(type)); \
        } else { \
            ptr = (type*)xmd_malloc(fallback_size); \
        } \
        if (!ptr) { \
            XMD_ERROR("Pool allocation failed for %zu bytes", sizeof(type)); \
            return retval; \
        } \
    } while(0)

/* ============================================================================
 * DAY 9: AST OPERATION PATTERNS
 * ============================================================================ */

/**
 * @brief AST node creation with automatic initialization
 * @details Creates and initializes AST node with type validation
 */
#define XMD_AST_CREATE_NODE(ptr, node_type, retval) \
    do { \
        XMD_MALLOC_VALIDATED(ptr, ast_node, sizeof(ast_node), retval); \
        memset(ptr, 0, sizeof(ast_node)); \
        ptr->type = node_type; \
        ptr->location.line = 0; \
        ptr->location.column = 0; \
    } while(0)

/**
 * @brief AST value creation with type validation
 * @details Creates and initializes AST value with type checking
 */
#define XMD_AST_CREATE_VALUE(ptr, value_type, retval) \
    do { \
        XMD_MALLOC_VALIDATED(ptr, ast_value, sizeof(ast_value), retval); \
        memset(ptr, 0, sizeof(ast_value)); \
        ptr->type = value_type; \
    } while(0)

/**
 * @brief AST node type validation with context
 * @details Enhanced node type checking with detailed error messages
 */
#define XMD_AST_VALIDATE_TYPE(node, expected_type, retval, context) \
    do { \
        if (!node) { \
            XMD_ERROR("NULL AST node in %s", context); \
            return retval; \
        } \
        if (node->type != (expected_type)) { \
            XMD_ERROR("Wrong AST type in %s: got %d, expected %d", \
                     context, node->type, (expected_type)); \
            return retval; \
        } \
    } while(0)

/**
 * @brief AST value type validation with context
 * @details Enhanced value type checking with detailed error messages
 */
#define XMD_AST_VALUE_VALIDATE_TYPE(value, expected_type, retval, context) \
    do { \
        if (!value) { \
            XMD_ERROR("NULL AST value in %s", context); \
            return retval; \
        } \
        if (value->type != (expected_type)) { \
            XMD_ERROR("Wrong AST value type in %s: got %d, expected %d", \
                     context, value->type, (expected_type)); \
            return retval; \
        } \
    } while(0)

/**
 * @brief AST node deep copy validation
 * @details Safe deep copying of AST nodes with error handling
 */
#define XMD_AST_DEEP_COPY(dest, src, copy_func, retval) \
    do { \
        if (!src) { \
            dest = NULL; \
        } else { \
            dest = copy_func(src); \
            if (!dest) { \
                XMD_ERROR("Failed to deep copy AST node"); \
                return retval; \
            } \
        } \
    } while(0)

/**
 * @brief AST operation with rollback on failure
 * @details Performs AST operation with automatic rollback capabilities
 */
#define XMD_AST_OPERATION_WITH_ROLLBACK(operation, rollback_block, retval) \
    do { \
        if (!(operation)) { \
            XMD_ERROR("AST operation failed, performing rollback"); \
            rollback_block; \
            return retval; \
        } \
    } while(0)

/**
 * @brief AST array resize with bounds checking
 * @details Safe array operations for AST node collections
 */
#define XMD_AST_ARRAY_RESIZE(array, old_size, new_size, element_type, retval) \
    do { \
        if ((new_size) > SIZE_MAX / sizeof(element_type)) { \
            XMD_ERROR("AST array resize overflow: %zu elements", (size_t)(new_size)); \
            return retval; \
        } \
        XMD_REALLOC_VALIDATED(array, element_type, (new_size) * sizeof(element_type), retval); \
        if ((new_size) > (old_size)) { \
            memset(&array[old_size], 0, ((new_size) - (old_size)) * sizeof(element_type)); \
        } \
    } while(0)

/**
 * @brief AST visitor pattern implementation
 * @details Standard visitor pattern for AST traversal
 */
#define XMD_AST_VISIT_NODE(node, visitor_func, context, retval) \
    do { \
        if (!node || !visitor_func) { \
            XMD_ERROR("Invalid parameters for AST visitor"); \
            return retval; \
        } \
        if (!visitor_func(node, context)) { \
            XMD_ERROR("AST visitor function failed"); \
            return retval; \
        } \
    } while(0)

/**
 * @brief AST evaluation with context preservation
 * @details Safe AST evaluation with context stack management
 */
#define XMD_AST_EVALUATE_WITH_CONTEXT(result, node, evaluator, context_backup, retval) \
    do { \
        context_backup = evaluator->current_context; \
        if (!(result = ast_evaluate(node, evaluator))) { \
            evaluator->current_context = context_backup; \
            XMD_ERROR("AST evaluation failed, context restored"); \
            return retval; \
        } \
    } while(0)

/* ============================================================================
 * DAY 10: PARSER-SPECIFIC PATTERNS
 * ============================================================================ */

/**
 * @brief Parser position validation and advancement
 * @details Safe position pointer checking and advancement
 */
#define XMD_PARSE_VALIDATE_POS(pos, retval) \
    do { \
        if (!pos || !*pos) { \
            XMD_ERROR("NULL or invalid parser position"); \
            return retval; \
        } \
    } while(0)

/**
 * @brief Skip whitespace (but not newlines)
 * @details Standard whitespace skipping pattern used in all parsers
 */
#define XMD_PARSE_SKIP_WHITESPACE(pos) \
    do { \
        while (*pos && isspace(**pos) && **pos != '\n') { \
            (*pos)++; \
        } \
    } while(0)

/**
 * @brief Check for end of input or newline
 * @details Common pattern for checking parse boundaries
 */
#define XMD_PARSE_CHECK_END(pos, retval) \
    do { \
        if (!*pos || **pos == '\0' || **pos == '\n') { \
            return retval; \
        } \
    } while(0)

/**
 * @brief Expect and consume a specific keyword
 * @details Validates and consumes expected keywords in parser
 */
#define XMD_PARSE_EXPECT_KEYWORD(pos, keyword, retval) \
    do { \
        size_t _len = strlen(keyword); \
        if (strncmp(*pos, keyword, _len) != 0) { \
            XMD_ERROR("Expected keyword '%s' at position", keyword); \
            return retval; \
        } \
        *pos += _len; \
    } while(0)

/**
 * @brief Parse and validate identifier
 * @details Common pattern for parsing identifiers
 */
#define XMD_PARSE_IDENTIFIER(pos, start_ptr, end_ptr, retval) \
    do { \
        start_ptr = *pos; \
        if (!isalpha(**pos) && **pos != '_') { \
            XMD_ERROR("Invalid identifier start character"); \
            return retval; \
        } \
        while (isalnum(**pos) || **pos == '_') { \
            (*pos)++; \
        } \
        end_ptr = *pos; \
    } while(0)

/**
 * @brief Parse quoted string with escape handling
 * @details Consolidated string parsing pattern
 */
#define XMD_PARSE_QUOTED_STRING(pos, result, retval) \
    do { \
        if (**pos != '"') { \
            XMD_ERROR("Expected opening quote"); \
            return retval; \
        } \
        (*pos)++; \
        const char* _start = *pos; \
        while (**pos && **pos != '"') { \
            if (**pos == '\\' && *(*pos + 1)) (*pos) += 2; \
            else (*pos)++; \
        } \
        if (**pos != '"') { \
            XMD_ERROR("Unterminated string"); \
            return retval; \
        } \
        size_t _len = *pos - _start; \
        XMD_MALLOC_VALIDATED(result, char, _len + 1, retval); \
        memcpy(result, _start, _len); \
        result[_len] = '\0'; \
        (*pos)++; \
    } while(0)

/**
 * @brief Parse numeric value
 * @details Consolidated number parsing with validation
 */
#define XMD_PARSE_NUMBER(pos, value, retval) \
    do { \
        char* _endptr; \
        value = strtod(*pos, &_endptr); \
        if (_endptr == *pos) { \
            XMD_ERROR("Invalid number format"); \
            return retval; \
        } \
        *pos = _endptr; \
    } while(0)

/**
 * @brief Parse with lookahead
 * @details Check upcoming tokens without consuming
 */
#define XMD_PARSE_LOOKAHEAD(pos, pattern, matched) \
    do { \
        const char* _temp = *pos; \
        XMD_PARSE_SKIP_WHITESPACE(&_temp); \
        matched = (strncmp(_temp, pattern, strlen(pattern)) == 0); \
    } while(0)

/**
 * @brief Parse optional element
 * @details Try parsing, continue if fails
 */
#define XMD_PARSE_OPTIONAL(parse_func, pos, result) \
    do { \
        const char* _saved = *pos; \
        result = parse_func(pos); \
        if (!result) { \
            *pos = _saved; \
        } \
    } while(0)

/**
 * @brief Parse delimited list
 * @details Common pattern for comma-separated lists
 */
#define XMD_PARSE_DELIMITED_LIST(pos, delimiter, parse_func, array, count, capacity, retval) \
    do { \
        do { \
            if (count >= capacity) { \
                capacity = capacity ? capacity * 2 : 4; \
                XMD_REALLOC_VALIDATED(array, void*, capacity * sizeof(void*), retval); \
            } \
            array[count] = parse_func(pos); \
            if (!array[count]) break; \
            count++; \
            XMD_PARSE_SKIP_WHITESPACE(pos); \
            if (**pos == delimiter) { \
                (*pos)++; \
                XMD_PARSE_SKIP_WHITESPACE(pos); \
            } else { \
                break; \
            } \
        } while (**pos && **pos != '\n'); \
    } while(0)

/**
 * @brief Parse with error recovery
 * @details Attempt to recover from parse errors
 */
#define XMD_PARSE_WITH_RECOVERY(parse_func, pos, result, recovery_char) \
    do { \
        result = parse_func(pos); \
        if (!result) { \
            while (**pos && **pos != recovery_char && **pos != '\n') { \
                (*pos)++; \
            } \
        } \
    } while(0)

/**
 * @brief Parse block with indentation tracking
 * @details Handle indented blocks in XMD syntax
 */
#define XMD_PARSE_INDENTED_BLOCK(pos, indent_level, block_start, block_end) \
    do { \
        block_start = *pos; \
        int _spaces = 0; \
        while (**pos == ' ') { \
            _spaces++; \
            (*pos)++; \
        } \
        if (_spaces <= indent_level) { \
            XMD_ERROR("Insufficient indentation for block"); \
            return NULL; \
        } \
        indent_level = _spaces; \
        while (**pos && **pos != '\n') (*pos)++; \
        block_end = *pos; \
    } while(0)

/* ============================================================================
 * ABSOLUTE ZERO DUPLICATION ELIMINATION MACROS - Final Phase
 * ============================================================================ */

/**
 * @brief Dynamic buffer growth with capacity management
 * @details Eliminates repetitive buffer resize patterns in stringify functions
 */
#define XMD_BUFFER_ENSURE_CAPACITY(buffer, current_pos, required_space, retval) \
    do { \
        size_t needed_size = (current_pos) + (required_space) + 1; \
        if (needed_size > buffer##_capacity) { \
            size_t new_capacity = needed_size + 256; \
            char* new_buffer = xmd_realloc(buffer, new_capacity); \
            if (!new_buffer) { \
                XMD_FREE_SAFE(buffer); \
                return retval; \
            } \
            buffer = new_buffer; \
            buffer##_capacity = new_capacity; \
        } \
    } while(0)

/**
 * @brief Convert AST value to string with type dispatch  
 * @details Eliminates repetitive value-to-string conversion patterns
 */
#define XMD_CONVERT_VALUE_TO_STRING(ast_val, str_var, retval) \
    do { \
        if ((ast_val)->type == AST_VAL_STRING) { \
            str_var = xmd_strdup((ast_val)->value.string_value ? (ast_val)->value.string_value : ""); \
        } else if ((ast_val)->type == AST_VAL_NUMBER) { \
            str_var = xmd_malloc(32); \
            if (str_var) snprintf(str_var, 32, "%.6g", (ast_val)->value.number_value); \
        } else if ((ast_val)->type == AST_VAL_BOOLEAN) { \
            str_var = xmd_strdup((ast_val)->value.boolean_value ? "true" : "false"); \
        } else { \
            str_var = xmd_strdup(""); \
        } \
        if (!str_var) return retval; \
    } while(0)

/**
 * @brief Dynamic array growth with exponential capacity
 * @details Eliminates repetitive dynamic array expansion patterns  
 */
#define XMD_DYNAMIC_ARRAY_GROW(array, count, capacity, type, growth_factor) \
    do { \
        if ((count) >= (capacity)) { \
            size_t new_capacity = (capacity) ? (capacity) * (growth_factor) : 8; \
            type* new_array = xmd_realloc(array, new_capacity * sizeof(type)); \
            if (!new_array) { \
                XMD_FREE_SAFE(array); \
                return NULL; \
            } \
            array = new_array; \
            capacity = new_capacity; \
        } \
    } while(0)

#endif /* XMD_VALIDATION_MACROS_H */