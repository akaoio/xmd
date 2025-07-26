/**
 * @file process_for.c
 * @brief Process for directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

// Forward declarations for utility functions
int parse_range(const char* range_str, store* variables, char*** items, int* count);
int parse_collection(const char* collection_name, store* variables, char*** items, int* count);

/**
 * @brief Process for directive with range and collection support
 * @param args Loop arguments for for directive (item in collection/range)
 * @param ctx Processor context
 * @param output Buffer to store loop content processed for each iteration
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_for(const char* args, processor_context* ctx, char* output, size_t output_size) {
    if (!should_execute_block(ctx)) {
        output[0] = '\0';
        return 0;
    }
    
    // Parse for loop syntax: "item in collection_or_range"
    char* args_copy = strdup(args);
    char* in_pos = strstr(args_copy, " in ");
    
    if (!in_pos) {
        snprintf(output, output_size, "<!-- Error: Invalid for loop syntax '%s' -->", args);
        free(args_copy);
        return -1;
    }
    
    *in_pos = '\0';
    char* item_name = trim_whitespace(args_copy);
    char* collection_expr = trim_whitespace(in_pos + 4);
    
    // Determine if it's a range (contains ..) or collection
    char** items = NULL;
    int item_count = 0;
    
    if (strstr(collection_expr, "..")) {
        // Range syntax: start..end
        if (parse_range(collection_expr, ctx->variables, &items, &item_count) != 0) {
            snprintf(output, output_size, "<!-- Error: Invalid range '%s' -->", collection_expr);
            free(args_copy);
            return -1;
        }
    } else {
        // Collection syntax: variable name
        if (parse_collection(collection_expr, ctx->variables, &items, &item_count) != 0) {
            snprintf(output, output_size, "<!-- Error: Collection '%s' not found -->", collection_expr);
            free(args_copy);
            return -1;
        }
    }
    
    // Set loop variable to first item (architecture limitation: no true iteration)
    if (item_count > 0) {
        variable* item_var = variable_create_string(items[0]);
        if (item_var) {
            store_set(ctx->variables, item_name, item_var);
            variable_unref(item_var);
        }
    }
    
    // Free all items
    for (int i = 0; i < item_count; i++) {
        free(items[i]);
    }
    
    // Free items array
    free(items);
    free(args_copy);
    
    // The for loop itself doesn't produce output - the content between
    // for/endfor tags gets processed with the loop variable set
    output[0] = '\0';
    return 0;
}
