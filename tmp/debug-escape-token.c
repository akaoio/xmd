#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/token.h"
#include "../include/lexer_enhanced.h"

int main() {
    const char* input = "\"string with \\\"quotes\\\" inside\"";
    token* tokens = lexer_enhanced_tokenize(input, "test.xmd");
    
    if (tokens) {
        printf("Token type: %d\n", tokens->type);
        printf("Token value: '%s'\n", tokens->value);
        printf("Token length: %zu\n", strlen(tokens->value));
        
        // Print each character
        for (int i = 0; tokens->value[i]; i++) {
            printf("  [%d]: '%c' (0x%02x)\n", i, tokens->value[i], (unsigned char)tokens->value[i]);
        }
        
        token_list_free(tokens);
    }
    
    return 0;
}