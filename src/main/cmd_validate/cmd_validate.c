/**
 * @file cmd_validate.c
 * @brief Validate command implementation function
 * @author XMD Team
 *
 * Implementation of validate command for the XMD main module.
 */

#include "../../../include/main_internal.h"

/**
 * @brief Validate command implementation
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code
 */
int cmd_validate(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: No input file specified\n");
        return 1;
    }
    
    const char* input_file = argv[2];
    
    // Read file
    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", input_file);
        return 1;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Read content
    char* content = malloc(file_size + 1);
    if (content == NULL) {
        fprintf(stderr, "Error: Out of memory\n");
        fclose(file);
        return 1;
    }
    
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    fclose(file);
    
    // Validate syntax
    xmd_error_code error = xmd_validate_syntax(content, bytes_read);
    free(content);
    
    if (error == XMD_SUCCESS) {
        printf("✓ Syntax is valid\n");
        return 0;
    } else {
        fprintf(stderr, "✗ Syntax error: %s\n", xmd_error_string(error));
        return 1;
    }
}