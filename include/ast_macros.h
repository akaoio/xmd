/**
 * @file ast_macros.h
 * @brief AST evaluation and parsing macros for duplication reduction
 * @date 2025-08-03
 * 
 * PRIORITY 1: Code Quality Optimization - Duplication reduction 57.7% → 45%
 * Reduces duplication across AST evaluator and parser functions
 * Following Genesis principles while improving maintainability
 */

#ifndef AST_MACROS_H
#define AST_MACROS_H

#include "ast.h"
#include "ast_evaluator.h"
#include "utils.h"
#include "utils/common/common_macros.h"
#include <ctype.h>

/**
 * SECTION 1: AST NODE CREATION MACROS (Original - 51 functions)
 */

/**
 * @brief Standard AST node creation macro
 * 
 * This macro encapsulates the common pattern found in all 51 AST creation functions:
 * 1. Allocate memory for node
 * 2. Check allocation success
 * 3. Set node type
 * 4. Initialize location
 * 
 * Usage:
 *   AST_CREATE_NODE(node, AST_LOOP, loc);
 *   // Then set specific fields
 *   node->data.loop.variable = ...;
 */
#define AST_CREATE_NODE(node_var, node_type, location) \
    ast_node* node_var = xmd_malloc(sizeof(ast_node)); \
    if (!node_var) { \
        return NULL; \
    } \
    node_var->type = (node_type); \
    node_var->location = (location); \
    memset(&node_var->data, 0, sizeof(node_var->data))

/**
 * @brief AST node creation with validation macro
 * 
 * Similar to AST_CREATE_NODE but with additional parameter validation
 * 
 * Usage:
 *   AST_CREATE_NODE_VALIDATED(node, AST_LOOP, loc, variable && iterable);
 */
#define AST_CREATE_NODE_VALIDATED(node_var, node_type, location, validation) \
    if (!(validation)) { \
        return NULL; \
    } \
    AST_CREATE_NODE(node_var, node_type, location)

/**
 * @brief Cleanup helper for AST node creation failures
 * 
 * Frees allocated strings and returns NULL
 * Useful in creation functions that allocate strings before node
 */
#define AST_CLEANUP_AND_RETURN(...) \
    do { \
        __VA_ARGS__; \
        return NULL; \
    } while(0)

/**
 * @brief Add element to array/block with error checking
 */
#define AST_ADD_ELEMENT_SAFE(container, element, cleanup_code) \
    if (ast_add_element(container, element) != 0) { \
        cleanup_code; \
        return NULL; \
    }

/**
 * @brief Set string field with duplication
 */
#define AST_SET_STRING_FIELD(node, field, value) \
    do { \
        (node)->field = xmd_strdup(value); \
        if (!(node)->field) { \
            XMD_FREE_SAFE(node); \
            return NULL; \
        } \
    } while(0)

/**
 * SECTION 2: AST EVALUATOR MACROS (NEW - 40+ functions)
 */

/**
 * @brief Standard AST evaluator function header validation
 * Validates node and evaluator pointers, checks node type
 * @param expected_type AST node type expected (e.g., AST_FUNCTION_CALL)
 * @param func_name Function name for error messages
 */
#define AST_EVALUATOR_VALIDATE(expected_type, func_name) \
    do { \
        XMD_VALIDATE_PTRS(NULL, node, evaluator); \
        if (node->type != expected_type) { \
            XMD_ERROR_RETURN(NULL, func_name ": Invalid node type %d, expected " #expected_type, node->type); \
        } \
    } while(0)

/**
 * @brief Standard function return value creation for empty/success cases
 * Returns empty string ast_value for functions that don't produce output
 */
#define AST_RETURN_EMPTY_SUCCESS() \
    return ast_value_create_string("")

/**
 * SECTION 3: AST PARSER MACROS (NEW - 30+ functions)
 */

/**
 * @brief Standard AST parser function header validation  
 * Validates position pointer and advances past keyword
 * @param keyword_len Length of keyword to skip (e.g., 9 for "function ")
 * @param func_name Function name for error messages
 */
#define AST_PARSER_VALIDATE_AND_SKIP(keyword_len, func_name) \
    do { \
        if (!pos || !*pos) { \
            XMD_ERROR_RETURN(NULL, func_name ": NULL position pointer"); \
        } \
        const char* start = *pos; \
        start += keyword_len; \
        while (*start && isspace(*start)) { \
            start++; \
        } \
        if (*start == '\0') { \
            XMD_ERROR_RETURN(NULL, func_name ": Unexpected end of input after keyword"); \
        } \
    } while(0)

/**
 * @brief Standard memory allocation with error handling
 * @param var Variable name to store allocated memory
 * @param size Size to allocate
 * @param func_name Function name for error messages
 */
#define AST_MALLOC_OR_RETURN(var, size, func_name) \
    do { \
        var = xmd_malloc(size); \
        if (!var) { \
            XMD_ERROR_RETURN(NULL, func_name ": Failed to allocate memory"); \
        } \
    } while(0)

/**
 * @brief Standard string duplication with length and null termination
 * @param dest Destination variable name
 * @param src Source string pointer  
 * @param len Length to copy
 * @param func_name Function name for error messages
 */
#define AST_STRDUP_WITH_LEN(dest, src, len, func_name) \
    do { \
        dest = xmd_malloc(len + 1); \
        if (!dest) { \
            XMD_ERROR_RETURN(NULL, func_name ": Failed to allocate memory for string"); \
        } \
        strncpy(dest, src, len); \
        dest[len] = '\0'; \
    } while(0)

/**
 * @brief Standard whitespace skipping pattern
 * @param ptr Pointer to advance
 */
#define AST_SKIP_WHITESPACE(ptr) \
    do { \
        while (*ptr && isspace(*ptr) && *ptr != '\n') { \
            ptr++; \
        } \
    } while(0)

/**
 * @brief Standard identifier parsing pattern
 * Extracts identifier until whitespace, parentheses, or special chars
 * @param start Start position pointer
 * @param end End position pointer (will be updated)
 * @param len Length variable to store result length
 */
#define AST_PARSE_IDENTIFIER(start, end, len) \
    do { \
        end = start; \
        while (*end && !isspace(*end) && *end != '\n' && *end != '(' && *end != ')' && *end != ',') { \
            end++; \
        } \
        len = end - start; \
    } while(0)

/**
 * @brief Safe AST node creation with error handling
 * @param result Variable to store created node
 * @param create_func AST creation function call
 * @param func_name Function name for error messages
 */
#define AST_CREATE_NODE_OR_RETURN(result, create_func, func_name) \
    do { \
        result = create_func; \
        if (!result) { \
            XMD_ERROR_RETURN(NULL, func_name ": Failed to create AST node"); \
        } \
    } while(0)

#endif /* AST_MACROS_H */
