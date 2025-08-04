#ifndef XMD_COMMON_MACROS_H
#define XMD_COMMON_MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * XMD Common Macros Framework
 * Phase 2 of Refactoring Plan - Reduce 70% code duplication
 * 
 * These macros follow XMD sacred principles:
 * - No external dependencies (pure C)
 * - Memory management: Validate → Use → Free
 * - Error handling: All paths handled explicitly
 */

/* ==================== NULL VALIDATION MACROS ==================== */

/**
 * Check if pointer is NULL and return specified value if true
 * Usage: XMD_NULL_CHECK(ptr, NULL)
 * Note: Checks for existing definition to avoid conflicts with ast.h
 */
#ifndef XMD_NULL_CHECK
#define XMD_NULL_CHECK(ptr, return_val) \
    do { \
        if (!(ptr)) { \
            fprintf(stderr, "[ERROR] NULL pointer at %s:%d in %s()\n", \
                    __FILE__, __LINE__, __func__); \
            return return_val; \
        } \
    } while(0)
#endif

/**
 * Check if pointer is NULL and return void
 * Usage: XMD_NULL_CHECK_VOID(ptr)
 */
#define XMD_NULL_CHECK_VOID(ptr) \
    do { \
        if (!(ptr)) { \
            fprintf(stderr, "[ERROR] NULL pointer at %s:%d in %s()\n", \
                    __FILE__, __LINE__, __func__); \
            return; \
        } \
    } while(0)

/**
 * AST Node Type Validation Macro
 * PHASE 2 MANUAL CONSOLIDATION: Standardize type validation patterns
 * Usage: XMD_VALIDATE_NODE_TYPE(node, AST_PROGRAM, NULL, "error_msg")
 */
#define XMD_VALIDATE_NODE_TYPE(node, expected_type, return_val, error_msg) \
    do { \
        if ((node)->type != (expected_type)) { \
            fprintf(stderr, "[ERROR] %s at %s:%d\n", (error_msg), __FILE__, __LINE__); \
            return (return_val); \
        } \
    } while(0)

/**
 * Memory Allocation with Error Handling Macro
 * PHASE 2 MANUAL CONSOLIDATION: Standardize memory allocation patterns
 * Usage: XMD_MALLOC_SAFE(ptr, type, return_val, error_msg)
 */
#define XMD_MALLOC_SAFE(ptr, type, return_val, error_msg) \
    do { \
        (ptr) = xmd_malloc(sizeof(type)); \
        if (!(ptr)) { \
            fprintf(stderr, "[ERROR] %s at %s:%d\n", (error_msg), __FILE__, __LINE__); \
            return (return_val); \
        } \
    } while(0)

/**
 * Simple NULL check with custom return value
 * Usage: XMD_NULL_CHECK_RETURN(ptr, retval)
 */
#define XMD_NULL_CHECK_RETURN(ptr, retval) \
    do { \
        if (!(ptr)) { \
            fprintf(stderr, "[ERROR] NULL pointer at %s:%d in %s()\n", \
                    __FILE__, __LINE__, __func__); \
            return (retval); \
        } \
    } while(0)

/**
 * NULL check with goto
 * Usage: XMD_NULL_CHECK_GOTO(ptr, label)
 */
#define XMD_NULL_CHECK_GOTO(ptr, label) \
    do { \
        if (!(ptr)) { \
            fprintf(stderr, "[ERROR] NULL pointer at %s:%d in %s()\n", \
                    __FILE__, __LINE__, __func__); \
            goto label; \
        } \
    } while(0)

/**
 * Validate multiple pointers at once
 * Usage: XMD_VALIDATE_PTRS(return_val, ptr1, ptr2, ptr3)
 * Note: Uses const void* to handle both const and non-const pointers
 */
#define XMD_VALIDATE_PTRS(return_val, ...) \
    do { \
        const void* _ptrs[] = {__VA_ARGS__}; \
        size_t _count = sizeof(_ptrs) / sizeof(_ptrs[0]); \
        for (size_t _i = 0; _i < _count; _i++) { \
            if (!_ptrs[_i]) { \
                fprintf(stderr, "[ERROR] NULL pointer (arg %zu) at %s:%d in %s()\n", \
                        _i + 1, __FILE__, __LINE__, __func__); \
                return return_val; \
            } \
        } \
    } while(0)

/* ==================== MEMORY ALLOCATION MACROS ==================== */

/**
 * Safe malloc with automatic NULL check and zero initialization (REMOVED)
 * NOTE: This definition was removed to avoid conflict with line 67
 * Use the macro at line 67 instead: XMD_MALLOC_SAFE(ptr, type, return_val, error_msg)
 */

/**
 * Safe calloc with automatic NULL check
 * Usage: XMD_CALLOC_SAFE(MyStruct, var_name, count)
 */
#define XMD_CALLOC_SAFE(type, var, count) \
    type* var = (type*)calloc(count, sizeof(type)); \
    if (!(var)) { \
        fprintf(stderr, "[ERROR] Memory allocation failed for " #type "[%zu] at %s:%d\n", \
                (size_t)(count), __FILE__, __LINE__); \
        return NULL; \
    }

/**
 * Safe realloc with fallback to original pointer
 * Usage: XMD_REALLOC_SAFE(ptr, new_size, type)
 */
#define XMD_REALLOC_SAFE(ptr, new_size, type) \
    do { \
        void* _new_ptr = realloc(ptr, new_size); \
        if (!_new_ptr && new_size > 0) { \
            fprintf(stderr, "[ERROR] Realloc failed at %s:%d\n", \
                    __FILE__, __LINE__); \
        } else { \
            ptr = (type*)_new_ptr; \
        } \
    } while(0)

/**
 * Dynamic malloc with size calculation and error handling
 * Usage: XMD_MALLOC_DYNAMIC(ptr, size, return_val)
 */
#define XMD_MALLOC_DYNAMIC(ptr, size, return_val) \
    do { \
        (ptr) = xmd_malloc(size); \
        if (!(ptr)) { \
            fprintf(stderr, "[ERROR] Dynamic allocation failed (%zu bytes) at %s:%d\n", \
                    (size_t)(size), __FILE__, __LINE__); \
            return (return_val); \
        } \
    } while(0)

/**
 * Standard calloc with automatic error handling
 * Usage: XMD_CALLOC_STANDARD(ptr, count, type, return_val)
 */
#define XMD_CALLOC_STANDARD(ptr, count, type, return_val) \
    do { \
        (ptr) = (type*)xmd_calloc(count, sizeof(type)); \
        if (!(ptr)) { \
            fprintf(stderr, "[ERROR] Calloc allocation failed (" #type "[%zu]) at %s:%d\n", \
                    (size_t)(count), __FILE__, __LINE__); \
            return (return_val); \
        } \
    } while(0)

/* ==================== STRING OPERATION MACROS ==================== */

/**
 * Safe string duplication with NULL check
 * Usage: XMD_STRDUP_SAFE(source_str, dest_var)
 */
#define XMD_STRDUP_SAFE(source, dest) \
    char* dest = NULL; \
    if (source) { \
        dest = strdup(source); \
        if (!dest) { \
            fprintf(stderr, "[ERROR] String duplication failed at %s:%d\n", \
                    __FILE__, __LINE__); \
            return NULL; \
        } \
    }

/**
 * Safe string copy with bounds checking
 * Usage: XMD_STRCPY_SAFE(dest, source, dest_size)
 */
#define XMD_STRCPY_SAFE(dest, source, size) \
    do { \
        if (dest && source) { \
            strncpy(dest, source, (size) - 1); \
            dest[(size) - 1] = '\0'; \
        } \
    } while(0)

/* ==================== ERROR HANDLING MACROS ==================== */

/**
 * Log error and return
 * Usage: XMD_ERROR_RETURN(return_val, "Error message: %s", error_detail)
 */
/* Use GNU extension for compatibility, suppress warning with pragma */
#ifdef __GNUC__
#pragma GCC diagnostic push
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic ignored "-Wvariadic-macros"
#endif
#endif

#define XMD_ERROR_RETURN(return_val, fmt, ...) \
    do { \
        fprintf(stderr, "[ERROR] %s:%d in %s(): ", \
                __FILE__, __LINE__, __func__); \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
        fprintf(stderr, "\n"); \
        return return_val; \
    } while(0)

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

/**
 * Log warning but continue execution
 * Usage: XMD_WARNING("Warning message: %s", warning_detail)
 */
#define XMD_WARNING(fmt, ...) \
    do { \
        fprintf(stderr, "[WARNING] %s:%d in %s(): ", \
                __FILE__, __LINE__, __func__); \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
        fprintf(stderr, "\n"); \
    } while(0)

/**
 * Debug output (only in debug builds)
 * Usage: XMD_DEBUG("Debug info: %d", value)
 */
#ifdef DEBUG
    #define XMD_DEBUG(fmt, ...) \
        do { \
            fprintf(stderr, "[DEBUG] %s:%d in %s(): ", \
                    __FILE__, __LINE__, __func__); \
            fprintf(stderr, fmt, ##__VA_ARGS__); \
            fprintf(stderr, "\n"); \
        } while(0)
#else
    #define XMD_DEBUG(fmt, ...) ((void)0)
#endif

/* ==================== CLEANUP MACROS ==================== */

/**
 * Safe free with NULL check and pointer reset
 * Usage: XMD_FREE_SAFE(ptr)
 */
#define XMD_FREE_SAFE(ptr) \
    do { \
        if (ptr) { \
            free(ptr); \
            ptr = NULL; \
        } \
    } while(0)

/**
 * Cleanup and return on error
 * Usage: XMD_CLEANUP_RETURN(cleanup_func(data), return_val)
 */
#define XMD_CLEANUP_RETURN(cleanup_code, return_val) \
    do { \
        cleanup_code; \
        return return_val; \
    } while(0)

/* ==================== ASSERTION MACROS ==================== */

/**
 * XMD_ASSERT is defined in platform.h to avoid conflicts
 * The platform.h version is the canonical definition
 * 
 * If you need assertions with custom messages, use XMD_ASSERT_MSG instead
 */
#ifndef XMD_ASSERT
    /* Fallback if platform.h not included */
    #ifdef DEBUG
        #define XMD_ASSERT(x) do { if (!(x)) { fprintf(stderr, "Assertion failed: %s at %s:%d\n", #x, __FILE__, __LINE__); abort(); } } while(0)
    #else
        #define XMD_ASSERT(x) ((void)0)
    #endif
#endif

/**
 * Assert with custom message (alternative to avoid conflict)
 * Usage: XMD_ASSERT_MSG(condition, "Error message")
 */
#ifdef DEBUG
    #define XMD_ASSERT_MSG(condition, msg) \
        do { \
            if (!(condition)) { \
                fprintf(stderr, "[ASSERT FAILED] %s:%d: %s\n", \
                        __FILE__, __LINE__, msg); \
                abort(); \
            } \
        } while(0)
#else
    #define XMD_ASSERT_MSG(condition, msg) ((void)0)
#endif

/* ==================== RANGE VALIDATION MACROS ==================== */

/**
 * Check if value is within range
 * Usage: XMD_CHECK_RANGE(index, 0, array_size, -1)
 */
#define XMD_CHECK_RANGE(value, min, max, return_val) \
    do { \
        if ((value) < (min) || (value) >= (max)) { \
            fprintf(stderr, "[ERROR] Value %ld out of range [%ld, %ld) at %s:%d\n", \
                    (long)(value), (long)(min), (long)(max), \
                    __FILE__, __LINE__); \
            return return_val; \
        } \
    } while(0)

/* ==================== FILE OPERATION MACROS ==================== */

/**
 * Safe file open with error checking
 * Usage: XMD_FOPEN_SAFE(file_ptr, "path.txt", "r")
 */
#define XMD_FOPEN_SAFE(file_var, path, mode) \
    FILE* file_var = fopen(path, mode); \
    if (!file_var) { \
        fprintf(stderr, "[ERROR] Failed to open file '%s' (mode: %s) at %s:%d\n", \
                path, mode, __FILE__, __LINE__); \
        return NULL; \
    }

/**
 * Safe file close
 * Usage: XMD_FCLOSE_SAFE(file_ptr)
 */
#define XMD_FCLOSE_SAFE(file_ptr) \
    do { \
        if (file_ptr) { \
            fclose(file_ptr); \
            file_ptr = NULL; \
        } \
    } while(0)

/* ==================== LOOP HELPER MACROS ==================== */

/**
 * Iterate over array safely
 * Usage: XMD_FOR_EACH(i, array_size) { ... }
 */
#define XMD_FOR_EACH(index, size) \
    for (size_t index = 0; index < (size_t)(size); index++)

/**
 * Iterate backwards
 * Usage: XMD_FOR_EACH_REVERSE(i, array_size) { ... }
 */
#define XMD_FOR_EACH_REVERSE(index, size) \
    for (size_t index = (size_t)(size); index-- > 0; )

/* ==================== COMMON PATTERNS ==================== */

/**
 * Standard function entry validation
 * Usage: XMD_ENTRY_VALIDATE(param1, param2)
 */
#define XMD_ENTRY_VALIDATE(...) \
    XMD_VALIDATE_PTRS(NULL, __VA_ARGS__)

/**
 * Standard function entry validation (void return)
 * Usage: XMD_ENTRY_VALIDATE_VOID(param1, param2)
 */
#define XMD_ENTRY_VALIDATE_VOID(...) \
    do { \
        void* _ptrs[] = {__VA_ARGS__}; \
        size_t _count = sizeof(_ptrs) / sizeof(_ptrs[0]); \
        for (size_t _i = 0; _i < _count; _i++) { \
            if (!_ptrs[_i]) { \
                fprintf(stderr, "[ERROR] NULL parameter %zu at %s:%d in %s()\n", \
                        _i + 1, __FILE__, __LINE__, __func__); \
                return; \
            } \
        } \
    } while(0)

/* ==================== PERFORMANCE MACROS ==================== */

/**
 * Likely branch prediction hint
 * Usage: if (XMD_LIKELY(common_condition)) { ... }
 */
#ifdef __GNUC__
    #define XMD_LIKELY(x)   __builtin_expect(!!(x), 1)
    #define XMD_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define XMD_LIKELY(x)   (x)
    #define XMD_UNLIKELY(x) (x)
#endif

/* ==================== CREATOR PATTERN MACROS ==================== */

/**
 * Standard variable creator pattern - reduces duplication across 39 creator functions
 * Usage: XMD_CREATE_VARIABLE(variable, VAR_STRING, string_value, value)
 */
#define XMD_CREATE_VARIABLE(var_name, var_type, field_name, field_value) \
    do { \
        variable* var_name = malloc(sizeof(variable)); \
        if (!var_name) return NULL; \
        var_name->type = var_type; \
        var_name->ref_count = 1; \
        var_name->value.field_name = field_value; \
    } while(0)

/**
 * Creator with validation and cleanup on failure
 * Usage: XMD_CREATE_VALIDATED(result, variable, sizeof(variable), NULL)
 */
#define XMD_CREATE_VALIDATED(result_var, type, size, return_val) \
    type* result_var = malloc(size); \
    if (!result_var) { \
        fprintf(stderr, "[ERROR] Memory allocation failed for %s at %s:%d\n", \
                #type, __FILE__, __LINE__); \
        return return_val; \
    }

/**
 * Standard initialization pattern for structures
 * Usage: XMD_INIT_STRUCT(ptr, field1, value1, field2, value2)
 */
#define XMD_INIT_STRUCT(ptr, ...) \
    do { \
        memset(ptr, 0, sizeof(*(ptr))); \
        /* Custom initialization would need variadic macro handling */ \
    } while(0)

/* ==================== USAGE EXAMPLES ==================== */

/*
// Example 1: Simple function with NULL checks
void* process_data(void* input, size_t size) {
    XMD_NULL_CHECK(input, NULL);
    XMD_CHECK_RANGE(size, 1, MAX_SIZE, NULL);
    
    XMD_MALLOC_SAFE(ProcessResult, result);
    // Process data...
    return result;
}

// Example 2: Function with multiple validations
int parse_tokens(Token* tokens, size_t count, Parser* parser) {
    XMD_ENTRY_VALIDATE(tokens, parser);
    
    XMD_FOR_EACH(i, count) {
        if (!process_token(&tokens[i], parser)) {
            XMD_ERROR_RETURN(-1, "Failed to process token %zu", i);
        }
    }
    return 0;
}

// Example 3: File operations
char* read_file(const char* path) {
    XMD_NULL_CHECK(path, NULL);
    
    XMD_FOPEN_SAFE(file, path, "r");
    // Read file content...
    XMD_FCLOSE_SAFE(file);
    return content;
}
*/

/* ==================== AST SPECIFIC MACROS ==================== */

/**
 * Default source location initialization for AST nodes
 * Usage: source_location loc = XMD_DEFAULT_SOURCE_LOCATION();
 * Reduces duplication in 22+ parser files
 */
#define XMD_DEFAULT_SOURCE_LOCATION() ((source_location){1, 1, "input"})

/* ==================== STORE OPERATION MACROS ==================== */

/**
 * Store linked list traversal macro
 * Usage: XMD_STORE_TRAVERSE(store, index, entry, { 
 *     // operations on entry
 * });
 * Reduces duplication in store operations
 */
#define XMD_STORE_TRAVERSE(store, index, entry_var, code) \
    do { \
        store_entry* entry_var = (store)->buckets[index]; \
        while (entry_var) { \
            code; \
            entry_var = entry_var->next; \
        } \
    } while(0)

/* ==================== ZERO DUPLICATION CAMPAIGN MACROS ==================== */
/* Phase 4: Aggressive deduplication to achieve 0% technical debt */

/**
 * Allocate and validate in one operation
 * Eliminates pattern: ptr = malloc(); if (!ptr) return NULL;
 * Usage: XMD_ALLOCATE_AND_VALIDATE(result, ast_value, NULL);
 */
#define XMD_ALLOCATE_AND_VALIDATE(ptr, type, ret_val) \
    do { \
        (ptr) = XMD_MALLOC(sizeof(type)); \
        if (!(ptr)) return (ret_val); \
    } while(0)

/**
 * Validate condition and return custom value
 * Eliminates pattern: if (!condition) return value;
 * Usage: XMD_VALIDATE_AND_RETURN(ptr != NULL, ERROR_CODE);
 */
#define XMD_VALIDATE_AND_RETURN(condition, ret_val) \
    do { \
        if (!(condition)) return (ret_val); \
    } while(0)

/**
 * Free memory using xmd_free
 */
#define XMD_FREE(ptr) xmd_free(ptr)

/**
 * Free pointer and set to NULL (safer than just free)
 * Eliminates pattern: free(ptr); ptr = NULL;
 * Usage: XMD_FREE_AND_NULL(my_pointer);
 */
#define XMD_FREE_AND_NULL(ptr) \
    do { \
        XMD_FREE(ptr); \
        (ptr) = NULL; \
    } while(0)

/**
 * Validate array bounds before access
 * Eliminates pattern: if (index < 0 || index >= size) return NULL;
 * Usage: XMD_VALIDATE_ARRAY_BOUNDS(idx, array_size, NULL);
 */
#define XMD_VALIDATE_ARRAY_BOUNDS(index, size, ret_val) \
    do { \
        if ((index) < 0 || (size_t)(index) >= (size_t)(size)) \
            return (ret_val); \
    } while(0)

/**
 * Cleanup resources and return
 * Eliminates pattern: free(a); free(b); return val;
 * Usage: XMD_CLEANUP_AND_RETURN(XMD_FREE(tmp); XMD_FREE(buf), -1);
 */
#define XMD_CLEANUP_AND_RETURN(cleanup_code, ret_val) \
    do { \
        cleanup_code; \
        return (ret_val); \
    } while(0)

/**
 * String duplicate with validation
 * Eliminates pattern: str = strdup(src); if (!str) return NULL;
 * Usage: XMD_STRDUP_AND_VALIDATE(dest, source, NULL);
 */
#define XMD_STRDUP_AND_VALIDATE(dest, src, ret_val) \
    do { \
        (dest) = xmd_strdup(src); \
        if (!(dest)) return (ret_val); \
    } while(0)

/**
 * Allocate array with validation
 * Eliminates pattern: arr = calloc(n, size); if (!arr) return NULL;
 * Usage: XMD_CALLOC_AND_VALIDATE(array, 10, sizeof(int), NULL);
 */
#define XMD_CALLOC_AND_VALIDATE(ptr, count, size, ret_val) \
    do { \
        (ptr) = XMD_CALLOC(count, size); \
        if (!(ptr)) return (ret_val); \
    } while(0)

/**
 * Initialize structure to zero
 * Eliminates pattern: memset(&struct, 0, sizeof(struct));
 * Usage: XMD_ZERO_STRUCT(my_struct);
 */
#define XMD_ZERO_STRUCT(s) memset(&(s), 0, sizeof(s))

/**
 * Initialize pointer structure to zero
 * Eliminates pattern: memset(ptr, 0, sizeof(*ptr));
 * Usage: XMD_ZERO_PTR_STRUCT(my_ptr);
 */
#define XMD_ZERO_PTR_STRUCT(ptr) memset((ptr), 0, sizeof(*(ptr)))

/* ==================== ULTIMATE ZERO DUPLICATION MACROS ==================== */
/* Phase 5: Complete elimination of ALL boilerplate patterns */

/**
 * AST node type checking macro
 * Eliminates: if (node->type == AST_XXX)
 * Usage: if (AST_CHECK_TYPE(node, AST_FUNCTION_DEF))
 */
#define AST_CHECK_TYPE(node, type) ((node) && (node)->type == (type))

/**
 * Simple error output macro
 * Eliminates: fprintf(stderr, "Error: ...\n");
 * Usage: XMD_ERROR_MSG("Failed to create processor");
 */
#define XMD_ERROR_MSG(fmt, ...) \
    fprintf(stderr, "Error: " fmt "\n", ##__VA_ARGS__)

/**
 * String equality check
 * Eliminates: strcmp(str, "literal") == 0
 * Usage: if (STR_EQUALS(key, "config_file_path"))
 */
#define STR_EQUALS(str, literal) \
    ((str) && strcmp((str), (literal)) == 0)

/**
 * String inequality check
 * Usage: if (STR_NOT_EQUALS(key, "config"))
 */
#define STR_NOT_EQUALS(str, literal) \
    (!(str) || strcmp((str), (literal)) != 0)

/**
 * String prefix equality check
 * Eliminates: strncmp(str, "prefix", N) == 0
 * Usage: if (STRN_EQUALS(line, "if ", 3))
 */
#define STRN_EQUALS(str, literal, len) \
    ((str) && strncmp((str), (literal), (len)) == 0)

/**
 * String prefix inequality check
 * Usage: if (STRN_NOT_EQUALS(line, "else", 4))
 */
#define STRN_NOT_EQUALS(str, literal, len) \
    (!(str) || strncmp((str), (literal), (len)) != 0)

/**
 * Variable scope with automatic ref/unref
 * Eliminates: variable_ref(var); ... variable_unref(var);
 * Usage: VAR_SCOPE(var, { // use var });
 */
#define VAR_SCOPE(var, code) \
    do { \
        if (var) variable_ref(var); \
        code; \
        if (var) variable_unref(var); \
    } while(0)

/**
 * Generic variable creation
 * Eliminates: multiple variable_create_XXX calls
 * Usage: VAR_CREATE_STRING("hello"), VAR_CREATE_NUMBER(42)
 */
#define VAR_CREATE_STRING(str) variable_create_string(str)
#define VAR_CREATE_NUMBER(num) variable_create_number(num)
#define VAR_CREATE_BOOLEAN(val) variable_create_boolean(val)
#define VAR_CREATE_NULL() variable_create_null()

/**
 * Type-safe allocation macros
 * Eliminates: malloc(sizeof(type))
 * Usage: XMD_ALLOC_TYPE(ast_node), XMD_ALLOC_ARRAY(char, 100)
 */
#define XMD_ALLOC_TYPE(type) ((type*)XMD_MALLOC(sizeof(type)))
#define XMD_ALLOC_ARRAY(type, count) ((type*)XMD_MALLOC(sizeof(type) * (count)))

/**
 * Standard for loop iteration
 * Eliminates: for (i = 0; i < count; i++)
 * Usage: FOR_EACH_INDEX(i, array->count) { process(array[i]); }
 */
#define FOR_EACH_INDEX(var, count) \
    for (size_t var = 0; var < (size_t)(count); var++)

/**
 * Reverse iteration
 * Usage: FOR_EACH_REVERSE(i, count) { process(array[i]); }
 */
#define FOR_EACH_REVERSE(var, count) \
    for (size_t var = (size_t)(count); var-- > 0;)

/**
 * Return NULL if condition
 * Eliminates: if (condition) return NULL;
 * Usage: RETURN_NULL_IF(!ptr);
 */
#define RETURN_NULL_IF(condition) \
    do { if (condition) return NULL; } while(0)

/**
 * Return value if condition
 * Usage: RETURN_IF(error, -1);
 */
#define RETURN_IF(condition, value) \
    do { if (condition) return (value); } while(0)

/**
 * String length validation
 * Eliminates: if (strlen(str) > MAX)
 * Usage: STR_LEN_CHECK(input, >, MAX_LEN, -1);
 */
#define STR_LEN_CHECK(str, op, value, ret_val) \
    do { \
        if ((str) && strlen(str) op (value)) \
            return (ret_val); \
    } while(0)

/**
 * While not null loop
 * Eliminates: while (ptr != NULL)
 * Usage: WHILE_NOT_NULL(current) { process(current); current = current->next; }
 */
#define WHILE_NOT_NULL(ptr) while ((ptr) != NULL)

/**
 * Safe string operations
 * Usage: SAFE_STRLEN(str) returns 0 if str is NULL
 */
#define SAFE_STRLEN(str) ((str) ? strlen(str) : 0)
#define SAFE_STRCMP(s1, s2) ((s1) && (s2) ? strcmp(s1, s2) : -1)

/**
 * Min/Max macros (type-safe)
 * Usage: MIN(a, b), MAX(a, b)
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/**
 * Array size macro
 * Usage: ARRAY_SIZE(my_array)
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
 * Swap values macro
 * Usage: SWAP(a, b, temp_type);
 */
#define SWAP(a, b, type) \
    do { \
        type _swap_temp = (a); \
        (a) = (b); \
        (b) = _swap_temp; \
    } while(0)

#endif /* XMD_COMMON_MACROS_H */
