/**
 * @file print_usage.c
 * @brief Print XMD usage information
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Extracted from: src/main.c
 */

#include <stdio.h>

/**
 * @brief Print XMD usage information
 * @param program_name Name of the program executable
 */
void print_usage(const char* program_name) {
    printf("Usage: %s [command] [options] [file]\n", program_name);
    printf("Commands:\n");
    printf("  process <file>    Process XMD file using pure AST system\n");
    printf("  version           Show version information\n");
    printf("  help              Show this help message\n");
}
