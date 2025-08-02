/**
 * @file error_internal.h
 * @brief Internal definitions for error handling system
 * @author XMD Development Team
 * @date 2025-07-31
 */

#ifndef ERROR_INTERNAL_H
#define ERROR_INTERNAL_H

#include <stdbool.h>
#include <setjmp.h>
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Maximum nested try depth
 */
#define MAX_TRY_DEPTH 16

/**
 * @brief Internal error structure
 */
typedef struct xmd_error {
    int code;           /**< Error code */
    char* message;      /**< Error message */
    char* file;         /**< Source file */
    int line;           /**< Line number */
    struct xmd_error* next; /**< Next error in chain */
} xmd_error;

/**
 * @brief Extended error context for internal use
 */
struct error_context_internal {
    XMDError* current_error;                /**< Current error */
    void* last_error;                       /**< Last error */
    int try_depth;                          /**< Current try depth */
    bool in_catch;                          /**< Currently in catch block */
    bool catch_executed[MAX_TRY_DEPTH];     /**< Whether catch was executed at each depth */
    jmp_buf jump_buffers[MAX_TRY_DEPTH];    /**< Jump buffers for try/catch */
};

/**
 * @brief Create new error
 */
xmd_error* xmd_error_new(int code, const char* message, const char* file, int line);

/**
 * @brief Free error
 */
void xmd_error_free(xmd_error* error);

#ifdef __cplusplus
}
#endif

#endif /* ERROR_INTERNAL_H */
