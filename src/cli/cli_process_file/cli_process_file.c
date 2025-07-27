/**
 * @file cli_process_file.c
 * @brief CLI file processing function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "../../../include/cli.h"
#include "../../../include/lexer.h"
#include "../../../include/variable.h"
#include "../../../include/store.h"

/**
 * @brief Process a markdown file
 * @param input_file Input file path
 * @param output_file Output file path (NULL for stdout)
 * @param verbose Verbose output
 * @return Exit code
 */
int cli_process_file(const char* input_file, const char* output_file, bool verbose) {
    if (!input_file) {
        fprintf(stderr, "Error: No input file specified\n");
        return 1;
    }
    
    if (verbose) {
        printf("Processing file: %s\n", input_file);
        if (output_file) {
            printf("Output file: %s\n", output_file);
        }
    }
    
    // Check if input file exists
    struct stat st;
    if (stat(input_file, &st) != 0) {
        fprintf(stderr, "Error: Cannot access input file '%s'\n", input_file);
        return 1;
    }
    
    // Read input file
    FILE* input = fopen(input_file, "r");
    if (!input) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", input_file);
        return 1;
    }
    
    // Get file size
    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    // Read content
    char* content = malloc(size + 1);
    if (!content) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(input);
        return 1;
    }
    
    size_t read_size = fread(content, 1, size, input);
    content[read_size] = '\0';
    fclose(input);
    
    // Process content with XMD
    lexer* lex = lexer_create(content);
    if (!lex) {
        fprintf(stderr, "Error: Failed to create lexer\n");
        free(content);
        return 1;
    }
    
    // Process content through XMD pipeline
    void* xmd_handle = xmd_init(NULL);
    if (!xmd_handle) {
        fprintf(stderr, "Error: Failed to initialize XMD processor\n");
        lexer_free(lex);
        free(content);
        return 1;
    }
    
    xmd_result* result = xmd_process_string(xmd_handle, content, read_size);
    if (!result || !result->output) {
        fprintf(stderr, "Error: XMD processing failed\n");
        xmd_processor_free(xmd_handle);
        lexer_free(lex);
        free(content);
        return 1;
    }
    
    FILE* output = stdout;
    if (output_file) {
        output = fopen(output_file, "w");
        if (!output) {
            fprintf(stderr, "Error: Cannot create output file '%s'\n", output_file);
            xmd_result_free(result);
            xmd_processor_free(xmd_handle);
            lexer_free(lex);
            free(content);
            return 1;
        }
    }
    
    fprintf(output, "%s", result->output);
    
    if (output_file && output != stdout) {
        fclose(output);
        if (verbose) {
            printf("Output written to: %s\n", output_file);
        }
    }
    
    // Cleanup
    xmd_result_free(result);
    xmd_processor_free(xmd_handle);
    lexer_free(lex);
    free(content);
    
    return 0;
}