/**
 * @file template_context_destroy.c
 * @brief Destroy template context and free memory
 * @author XMD Team
 */

#include "../../../include/template_internal.h"

/**
 * @brief Destroy template context and free memory
 * @param ctx Template context to destroy (can be NULL)
 */
void template_context_destroy(template_context* ctx) {
    free(ctx);
}