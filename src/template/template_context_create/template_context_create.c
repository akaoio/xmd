/**
 * @file template_context_create.c
 * @brief Create a new template context
 * @author XMD Team
 */

#include "../../../include/template_internal.h"

/**
 * @brief Create a new template context
 * @param store Variable store for lookups
 * @return New template context or NULL on failure
 */
template_context* template_context_create(store* store) {
    if (store == NULL) {
        return NULL;
    }
    
    template_context* ctx = malloc(sizeof(template_context));
    if (ctx == NULL) {
        return NULL;
    }
    
    ctx->variable_store = store;
    
    return ctx;
}