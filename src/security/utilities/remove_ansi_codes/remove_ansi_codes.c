/**
 * @file remove_ansi_codes.c
 * @brief Remove ANSI escape codes from output
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Part of security utilities subsystem
 */

#include <stddef.h>
/**
 * @brief Remove ANSI escape codes from output
 * @param input Input string with potential ANSI codes
 * @param output Output buffer for cleaned string
 * @param max_output_size Maximum size of output buffer
 * @return Length of cleaned string
 */
size_t remove_ansi_codes(const char* input, char* output, size_t max_output_size) {
    const char* src = input;
    char* dst = output;
    char* end = output + max_output_size - 1;
    
    while (*src && dst < end) {
        if (*src == '\033' || *src == '\x1b') {
            // Start of ANSI escape sequence
            src++; // Skip ESC
            if (*src == '[') {
                src++; // Skip [
                // Skip until we find the end character (usually m, but could be others)
                while (*src && *src != 'm' && *src != 'K' && *src != 'J' && 
                       *src != 'H' && *src != 'f' && dst < end) {
                    src++;
                }
                if (*src) src++; // Skip the end character
            }
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    return dst - output;
}
