/**
 * @file test_brutal_nesting.c
 * @brief Brutal panic battle tests for extreme nesting scenarios
 * @author XMD Team
 * @date 2025-07-27
 * 
 * Stress tests for nested loops, conditionals, and resource limits
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/resource.h>
#include "../../include/store.h"
#include "../../include/variable.h"

// External functions from unified processor
char* ast_process_xmd_content(const char* input, store* variables);

/**
 * @brief Generate deep nested for loops (50+ levels)
 * Tests memory management and stack limits
 */
void test_infinite_depth_nested_loops(void) {
    printf("🔥 Testing infinite depth nested loops...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    // Generate 50-level nested for loops
    char* brutal_input = malloc(50000);
    strcpy(brutal_input, "# Brutal Nesting Test\n\n");
    
    // Create nested structure
    char* pos = brutal_input + strlen(brutal_input);
    for (int depth = 0; depth < 50; depth++) {
        pos += sprintf(pos, "<!-- xmd set array%d=\"1,2,3\" -->\n", depth);
        pos += sprintf(pos, "<!-- xmd for item%d in array%d -->\n", depth, depth);
        pos += sprintf(pos, "Level %d: {{item%d}}\n", depth, depth);
    }
    
    // Add content in deepest level
    pos += sprintf(pos, "🎯 **DEEPEST LEVEL REACHED** 🎯\n");
    
    // Close all loops
    for (int depth = 49; depth >= 0; depth--) {
        pos += sprintf(pos, "<!-- xmd endfor -->\n");
    }
    
    pos += sprintf(pos, "\nTest completed.\n");
    
    printf("Generated input size: %zu bytes\n", strlen(brutal_input));
    
    // Measure processing time
    clock_t start = clock();
    char* result = ast_process_xmd_content(brutal_input, vars);
    clock_t end = clock();
    
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Processing time: %.3f seconds\n", cpu_time);
    
    if (result) {
        printf("✅ Survived deep nesting (output: %zu bytes)\n", strlen(result));
        
        // Verify deepest level was reached
        if (strstr(result, "DEEPEST LEVEL REACHED")) {
            printf("✅ Deepest level successfully processed\n");
        } else {
            printf("❌ Deepest level not found in output\n");
        }
        
        free(result);
    } else {
        printf("❌ Deep nesting caused failure\n");
    }
    
    free(brutal_input);
    store_destroy(vars);
}

/**
 * @brief Test complex mixed nesting: for + if + while combinations
 */
void test_mixed_brutal_nesting(void) {
    printf("🔥 Testing mixed brutal nesting (for+if+while)...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* mixed_brutal = 
        "# Mixed Brutal Nesting Test\n\n"
        "<!-- xmd set numbers=\"1,2,3,4,5,6,7,8,9,10\" -->\n"
        "<!-- xmd set conditions=\"true,false,true,false,true\" -->\n"
        
        // Level 1: for loop
        "<!-- xmd for num in numbers -->\n"
        "Level 1 - Number: {{num}}\n"
        
        // Level 2: if statement  
        "<!-- xmd if num > 5 -->\n"
        "  High number detected: {{num}}\n"
        
        // Level 3: nested for loop
        "  <!-- xmd for cond in conditions -->\n"
        "    Level 3 - Condition: {{cond}}\n"
        
        // Level 4: nested if
        "    <!-- xmd if cond == \"true\" -->\n"
        "      Level 4 - TRUE branch\n"
        
        // Level 5: another for loop
        "      <!-- xmd for inner_num in numbers -->\n"
        "        Level 5 - Inner: {{inner_num}}\n"
        
        // Level 6: complex if/elif/else
        "        <!-- xmd if inner_num < 3 -->\n"
        "          Level 6 - Small: {{inner_num}}\n"
        "        <!-- xmd elif inner_num > 7 -->\n"
        "          Level 6 - Large: {{inner_num}}\n"
        "        <!-- xmd else -->\n"
        "          Level 6 - Medium: {{inner_num}}\n"
        "        <!-- xmd endif -->\n"
        
        "      <!-- xmd endfor -->\n"
        "    <!-- xmd else -->\n"
        "      Level 4 - FALSE branch\n"
        "    <!-- xmd endif -->\n"
        "  <!-- xmd endfor -->\n"
        
        "<!-- xmd elif num < 3 -->\n"
        "  Low number: {{num}}\n"
        "<!-- xmd else -->\n"
        "  Medium number: {{num}}\n"
        "<!-- xmd endif -->\n"
        "<!-- xmd endfor -->\n"
        
        "\n✅ Mixed nesting completed!\n";
    
    clock_t start = clock();
    char* result = ast_process_xmd_content(mixed_brutal, vars);
    clock_t end = clock();
    
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Mixed nesting processing time: %.3f seconds\n", cpu_time);
    
    if (result) {
        printf("✅ Mixed nesting survived (output: %zu bytes)\n", strlen(result));
        
        // Count occurrences of each level
        int level1_count = 0, level6_count = 0;
        char* pos = result;
        while ((pos = strstr(pos, "Level 1")) != NULL) {
            level1_count++;
            pos++;
        }
        pos = result;
        while ((pos = strstr(pos, "Level 6")) != NULL) {
            level6_count++;
            pos++;
        }
        
        printf("Level 1 executions: %d, Level 6 executions: %d\n", level1_count, level6_count);
        free(result);
    } else {
        printf("❌ Mixed nesting caused failure\n");
    }
    
    store_destroy(vars);
}

/**
 * @brief Test memory stress with large arrays and variables
 */
void test_memory_stress_brutal(void) {
    printf("🔥 Testing memory stress with massive arrays...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    // Generate large array (1000 elements)
    char* large_array = malloc(20000);
    strcpy(large_array, "1");
    for (int i = 2; i <= 1000; i++) {
        sprintf(large_array + strlen(large_array), ",%d", i);
    }
    
    // Set the large array
    variable* big_var = variable_create_string(large_array);
    store_set(vars, "massive_array", big_var);
    variable_unref(big_var);
    
    const char* memory_brutal = 
        "# Memory Stress Test\n\n"
        "Processing massive array with 1000 elements...\n\n"
        "<!-- xmd for num in massive_array -->\n"
        "  <!-- xmd if num % 100 == 0 -->\n"
        "    **Milestone {{num}}** reached!\n"
        "    <!-- xmd for inner in \"a,b,c,d,e\" -->\n"
        "      Sub-item {{inner}} for {{num}}\n"
        "    <!-- xmd endfor -->\n"
        "  <!-- xmd elif num % 50 == 0 -->\n"
        "    Half-century: {{num}}\n"
        "  <!-- xmd endif -->\n"
        "<!-- xmd endfor -->\n"
        "\n✅ Memory stress test completed!\n";
    
    // Monitor memory usage
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);
    
    clock_t start = clock();
    char* result = ast_process_xmd_content(memory_brutal, vars);
    clock_t end = clock();
    
    getrusage(RUSAGE_SELF, &usage_end);
    
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    long memory_used = usage_end.ru_maxrss - usage_start.ru_maxrss;
    
    printf("Memory stress processing time: %.3f seconds\n", cpu_time);
    printf("Memory usage delta: %ld KB\n", memory_used);
    
    if (result) {
        printf("✅ Memory stress survived (output: %zu bytes)\n", strlen(result));
        
        // Count milestones
        int milestone_count = 0;
        char* pos = result;
        while ((pos = strstr(pos, "**Milestone")) != NULL) {
            milestone_count++;
            pos++;
        }
        printf("Milestones processed: %d/10\n", milestone_count);
        
        free(result);
    } else {
        printf("❌ Memory stress caused failure\n");
    }
    
    free(large_array);
    store_destroy(vars);
}

/**
 * @brief Test malformed nested structures (error handling)
 */
void test_malformed_nesting_brutal(void) {
    printf("🔥 Testing malformed nesting (error resilience)...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* malformed_brutal = 
        "# Malformed Nesting Test\n\n"
        
        // Missing endif
        "<!-- xmd if true -->\n"
        "Missing endif content\n"
        
        // Extra endfor
        "<!-- xmd endfor -->\n"
        
        // Nested without opening
        "<!-- xmd else -->\n"
        "Orphaned else\n"
        
        // Mixed up nesting
        "<!-- xmd for item in \"1,2,3\" -->\n"
        "  <!-- xmd if true -->\n"
        "    Content\n"
        "  <!-- xmd endfor -->  <!-- Wrong closer! -->\n"
        "<!-- xmd endif -->     <!-- Wrong closer! -->\n"
        
        "\nMalformed test completed.\n";
    
    char* result = ast_process_xmd_content(malformed_brutal, vars);
    
    if (result) {
        printf("✅ Malformed nesting handled gracefully\n");
        printf("Output length: %zu bytes\n", strlen(result));
        
        // Check for error messages in output
        if (strstr(result, "Error:") || strstr(result, "error") || strstr(result, "ERROR")) {
            printf("✅ Error messages properly included in output\n");
        }
        
        free(result);
    } else {
        printf("❌ Malformed nesting caused complete failure\n");
    }
    
    store_destroy(vars);
}

/**
 * @brief Main brutal test runner
 */
int main(void) {
    printf("🚀 Starting Brutal Panic Battle Tests\n");
    printf("=====================================\n\n");
    
    test_infinite_depth_nested_loops();
    printf("\n");
    
    test_mixed_brutal_nesting();
    printf("\n");
    
    test_memory_stress_brutal();
    printf("\n");
    
    test_malformed_nesting_brutal();
    printf("\n");
    
    printf("🎉 Brutal Panic Battle Tests Completed!\n");
    printf("💀 If you see this message, XMD engine survived the brutality! 💀\n");
    
    return 0;
}