#include <stdio.h>
#include <stdlib.h>
#include "include/store.h"
#include "include/variable.h"

// External function from unified parser
char* process_xmd_content(const char* input, store* variables);

int main() {
    store* vars = store_create();
    
    const char* test = 
        "<!-- xmd:set name=\"Unified Parser\" -->\n"
        "<!-- xmd:set status=\"working\" -->\n"
        "# Testing {{name}}\n"
        "Status: {{status}}\n\n"
        "<!-- xmd:if status == \"working\" -->\n"
        "✅ The unified parser is operational!\n"
        "<!-- xmd:else -->\n"
        "❌ Something is wrong\n"
        "<!-- xmd:endif -->\n";
    
    printf("Input:\n%s\n", test);
    printf("====== Output ======\n");
    
    char* result = process_xmd_content(test, vars);
    if (result) {
        printf("%s", result);
        free(result);
    }
    
    store_destroy(vars);
    return 0;
}
