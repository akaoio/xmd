/**
 * @file xmd_macros.h
 * @brief Common macros to reduce code duplication while honoring Genesis principle
 * 
 * IMPORTANT: These macros are for INTERNAL implementation only!
 * PUBLIC API functions must remain fully isolated (1 function → 1 file → 1 directory)
 * 
 * These macros help reduce the 70% code duplication in internal utilities
 * while maintaining the sacred principles for all public interfaces.
 */

#ifndef XMD_MACROS_H
#define XMD_MACROS_H

#include <stdlib.h>
#include <string.h>
#include "../../../include/utils.h"

/* ========================================================================
 * MEMORY MANAGEMENT MACROS
 * Reduce duplication in memory allocation/validation/freeing patterns
 * ======================================================================== */

/**
 * @brief Create function macro - standard creation pattern
 * @param type The type to create
 * @param name The variable name
 */
#define XMD_CREATE_FUNC(type, name) \
    type* name = (type*)xmd_calloc(1, sizeof(type)); \
    if (!name) { \
        return NULL; \
    }

/**
 * @brief Safe free macro with NULL check and pointer reset
 * @param ptr Pointer to free
 */
#define XMD_FREE_FUNC(ptr) \
    do { \
        if (ptr) { \
            free(ptr); \
            ptr = NULL; \
        } \
    } while(0)

/**
 * @brief Validate pointer and return on NULL
 * @param ptr Pointer to validate
 * @param ret Return value if NULL
 */
#define XMD_VALIDATE_PTR(ptr, ret) \
    if (!(ptr)) { \
        return ret; \
    }

/**
 * @brief Validate two pointers
 * @param ptr1 First pointer
 * @param ptr2 Second pointer  
 * @param ret Return value if either is NULL
 */
#define XMD_VALIDATE_PTRS(ptr1, ptr2, ret) \
    if (!(ptr1) || !(ptr2)) { \
        return ret; \
    }

/* ========================================================================
 * ERROR HANDLING MACROS
 * Standard error checking and cleanup patterns
 * ======================================================================== */

/**
 * @brief Check condition and cleanup on failure
 * @param cond Condition to check
 * @param cleanup Cleanup code to execute
 * @param ret Return value
 */
#define XMD_CHECK_CLEANUP(cond, cleanup, ret) \
    if (!(cond)) { \
        cleanup; \
        return ret; \
    }

/**
 * @brief Allocate and check memory
 * @param var Variable to allocate to
 * @param size Size to allocate
 * @param cleanup Cleanup on failure
 */
#define XMD_ALLOC_CHECK(var, size, cleanup) \
    var = xmd_malloc(size); \
    if (!var) { \
        cleanup; \
        return NULL; \
    }

/* ========================================================================
 * STRING OPERATION MACROS
 * Common string manipulation patterns
 * ======================================================================== */

/**
 * @brief Safe string duplicate with validation
 * @param dest Destination variable
 * @param src Source string
 * @param cleanup Cleanup on failure
 */
#define XMD_STRDUP_SAFE(dest, src, cleanup) \
    dest = xmd_strdup(src); \
    if (!dest) { \
        cleanup; \
        return NULL; \
    }

/**
 * @brief Safe string copy with length
 * @param dest Destination buffer
 * @param src Source string
 * @param len Length to copy
 */
#define XMD_STRNCPY_SAFE(dest, src, len) \
    do { \
        strncpy(dest, src, len); \
        dest[len] = '\\0'; \
    } while(0)

/* ========================================================================
 * STORE OPERATION MACROS
 * Common patterns for store operations
 * ======================================================================== */

/**
 * @brief Store entry iteration macro
 * @param store The store to iterate
 * @param entry Current entry variable name
 * @param code Code to execute for each entry
 */
#define XMD_STORE_FOREACH(store, entry, code) \
    for (size_t _i = 0; _i < (store)->capacity; _i++) { \
        store_entry* entry = (store)->buckets[_i]; \
        while (entry) { \
            store_entry* _next = entry->next; \
            code; \
            entry = _next; \
        } \
    }

/* ========================================================================
 * AST NODE MACROS
 * Common patterns for AST node creation and manipulation
 * ======================================================================== */

/**
 * @brief Create AST node with type
 * @param var Variable name for node
 * @param node_type AST node type
 * @param loc Source location
 */
#define XMD_CREATE_AST_NODE(var, node_type, loc) \
    ast_node* var = (ast_node*)xmd_calloc(1, sizeof(ast_node)); \
    if (!var) { \
        return NULL; \
    } \
    var->type = node_type; \
    var->location = loc;

/**
 * @brief Add child to AST node with validation
 * @param parent Parent node
 * @param child Child node to add
 */
#define XMD_AST_ADD_CHILD(parent, child) \
    do { \
        if (!(parent) || !(child)) { \
            return -1; \
        } \
        if (ast_add_child(parent, child) != 0) { \
            ast_free(child); \
            return -1; \
        } \
    } while(0)

/* ========================================================================
 * DEBUG MACROS
 * Conditional debug output
 * ======================================================================== */

#ifdef DEBUG
    #define XMD_DEBUG_PRINT(fmt, ...) \
        printf("DEBUG: " fmt "\\n", ##__VA_ARGS__)
#else
    #define XMD_DEBUG_PRINT(fmt, ...) ((void)0)
#endif

#endif /* XMD_MACROS_H */