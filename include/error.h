/**
 * @file error.h
 * @brief Error handling system for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef ERROR_H
#define ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Error handling context
 */
typedef struct error_context ErrorContext;

/**
 * @brief Error types
 */
typedef enum {
    ERROR_NONE = 0,        /**< No error */
    ERROR_RUNTIME = 1,     /**< Runtime error */
    ERROR_VARIABLE = 2,    /**< Variable-related error */
    ERROR_TEMPLATE = 3,    /**< Template processing error */
    ERROR_LOOP = 4,        /**< Loop-related error */
    ERROR_CONDITION = 5,   /**< Condition evaluation error */
    ERROR_CUSTOM = 6       /**< Custom error */
} ErrorType;

/**
 * @brief Error information structure
 */
typedef struct {
    ErrorType type;        /**< Error type */
    char* message;         /**< Error message */
    char* file;            /**< Source file where error occurred */
    int line;              /**< Line number where error occurred */
} XMDError;

/**
 * @brief Create a new error context
 * @return New error context or NULL on error
 */
ErrorContext* error_context_new(void);

/**
 * @brief Free an error context
 * @param ctx Error context to free
 */
void error_context_free(ErrorContext* ctx);

/**
 * @brief Begin a try block
 * @param ctx Error context
 * @return 0 on success, non-zero on error
 */
int try_block_begin(ErrorContext* ctx);

/**
 * @brief End a try block
 * @param ctx Error context
 * @return 0 on success, non-zero on error
 */
int try_block_end(ErrorContext* ctx);

/**
 * @brief Begin a catch block
 * @param ctx Error context
 * @param error_type Type of error to catch
 * @return 0 on success, non-zero on error
 */
int catch_block_begin(ErrorContext* ctx, ErrorType error_type);

/**
 * @brief End a catch block
 * @param ctx Error context
 * @return 0 on success, non-zero on error
 */
int catch_block_end(ErrorContext* ctx);

/**
 * @brief Throw an error
 * @param ctx Error context
 * @param type Error type
 * @param message Error message
 * @param file Source file
 * @param line Line number
 * @return Non-zero on error
 */
int error_throw(ErrorContext* ctx, ErrorType type, const char* message, 
                const char* file, int line);

/**
 * @brief Get current error
 * @param ctx Error context
 * @return Current error or NULL if none
 */
XMDError* error_get_current(ErrorContext* ctx);

/**
 * @brief Check if error is caught
 * @param ctx Error context
 * @return 1 if caught, 0 if not
 */
int error_is_caught(ErrorContext* ctx);

/**
 * @brief Clear current error
 * @param ctx Error context
 */
void error_clear(ErrorContext* ctx);

#ifdef __cplusplus
}
#endif

#endif /* ERROR_H */
