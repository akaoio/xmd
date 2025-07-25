/**
 * @file error_handling.c
 * @brief Error handling implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/error.h"

/**
 * @brief Error context structure
 */
struct error_context {
    XMDError* current_error;    /**< Current error */
    int in_try_block;           /**< Whether in try block */
    int in_catch_block;         /**< Whether in catch block */
    ErrorType catch_type;       /**< Type of error being caught */
    int error_caught;           /**< Whether error was caught */
};

/**
 * @brief Create a new error context
 * @return New error context or NULL on error
 */
ErrorContext* error_context_new(void) {
    ErrorContext* ctx = malloc(sizeof(ErrorContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->current_error = NULL;
    ctx->in_try_block = 0;
    ctx->in_catch_block = 0;
    ctx->catch_type = ERROR_NONE;
    ctx->error_caught = 0;
    
    return ctx;
}

/**
 * @brief Free XMDError structure
 * @param error Error to free
 */
static void free_xmd_error(XMDError* error) {
    if (!error) {
        return;
    }
    
    free(error->message);
    free(error->file);
    free(error);
}

/**
 * @brief Free an error context
 * @param ctx Error context to free
 */
void error_context_free(ErrorContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free_xmd_error(ctx->current_error);
    free(ctx);
}

/**
 * @brief Begin a try block
 * @param ctx Error context
 * @return 0 on success, non-zero on error
 */
int try_block_begin(ErrorContext* ctx) {
    if (!ctx) {
        return -1;
    }
    
    ctx->in_try_block = 1;
    ctx->error_caught = 0;
    
    return 0;
}

/**
 * @brief End a try block
 * @param ctx Error context
 * @return 0 on success, non-zero on error
 */
int try_block_end(ErrorContext* ctx) {
    if (!ctx) {
        return -1;
    }
    
    ctx->in_try_block = 0;
    
    return 0;
}

/**
 * @brief Begin a catch block
 * @param ctx Error context
 * @param error_type Type of error to catch
 * @return 0 on success, non-zero on error
 */
int catch_block_begin(ErrorContext* ctx, ErrorType error_type) {
    if (!ctx) {
        return -1;
    }
    
    ctx->in_catch_block = 1;
    ctx->catch_type = error_type;
    
    // Check if we have a matching error
    if (ctx->current_error && ctx->current_error->type == error_type) {
        ctx->error_caught = 1;
    }
    
    return 0;
}

/**
 * @brief End a catch block
 * @param ctx Error context
 * @return 0 on success, non-zero on error
 */
int catch_block_end(ErrorContext* ctx) {
    if (!ctx) {
        return -1;
    }
    
    ctx->in_catch_block = 0;
    ctx->catch_type = ERROR_NONE;
    
    return 0;
}

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
                const char* file, int line) {
    if (!ctx) {
        return -1;
    }
    
    // Clean up any existing error
    free_xmd_error(ctx->current_error);
    
    // Create new error
    XMDError* error = malloc(sizeof(XMDError));
    if (!error) {
        return -1;
    }
    
    error->type = type;
    error->message = message ? strdup(message) : strdup("Unknown error");
    error->file = file ? strdup(file) : strdup("unknown");
    error->line = line;
    
    ctx->current_error = error;
    ctx->error_caught = 0;
    
    return 1; // Error thrown
}

/**
 * @brief Get current error
 * @param ctx Error context
 * @return Current error or NULL if none
 */
XMDError* error_get_current(ErrorContext* ctx) {
    if (!ctx) {
        return NULL;
    }
    
    return ctx->current_error;
}

/**
 * @brief Check if error is caught
 * @param ctx Error context
 * @return 1 if caught, 0 if not
 */
int error_is_caught(ErrorContext* ctx) {
    if (!ctx) {
        return 0;
    }
    
    return ctx->error_caught;
}

/**
 * @brief Clear current error
 * @param ctx Error context
 */
void error_clear(ErrorContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free_xmd_error(ctx->current_error);
    ctx->current_error = NULL;
    ctx->error_caught = 0;
}