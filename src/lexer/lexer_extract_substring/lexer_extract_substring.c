/**
 * @file lexer_extract_substring.c
 * @brief Lexer substring extraction function
 * @author XMD Team
 *
 * Implementation of substring extraction for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Extract a substring from lexer input
 * 
 * Extracts a substring from the lexer's input buffer starting at the given
 * position with the specified length. The returned string is null-terminated
 * and must be freed by the caller.
 * 
 * @param lex The lexer instance
 * @param start_pos Starting position in the input buffer
 * @param length Number of characters to extract
 * @return New substring on success, NULL if lex is NULL, position is invalid, or allocation fails
 */
char* lexer_extract_substring(const lexer* lex, size_t start_pos, size_t length) {
    if (lex == NULL || lex->input == NULL) {
        return NULL;
    }
    
    // Check bounds
    if (start_pos >= lex->length) {
        return NULL;
    }
    
    // Adjust length if it extends beyond input
    size_t available = lex->length - start_pos;
    if (length > available) {
        length = available;
    }
    
    // Allocate memory for result
    char* result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    
    // Copy substring
    memcpy(result, &lex->input[start_pos], length);
    result[length] = '\0';
    
    return result;
}