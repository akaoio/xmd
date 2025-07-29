#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "xmd.h"

// Helper functions (same as in test_import_xmd_nested.c)
static void create_directory(const char *path) {
    if (mkdir(path, 0755) != 0 && errno != EEXIST) {
        fprintf(stderr, "Failed to create directory: %s\n", path);
        exit(1);
    }
}

static void write_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Failed to create file: %s\n", filename);
        exit(1);
    }
    fprintf(file, "%s", content);
    fclose(file);
}

static void remove_file(const char *filename) {
    if (unlink(filename) != 0 && errno != ENOENT) {
        fprintf(stderr, "Warning: Failed to remove file: %s\n", filename);
    }
}

// Test Case 1: Direct circular import (A imports B, B imports A)
static void test_direct_circular_import() {
    printf("Test 1: Direct circular import detection...\n");
    
    create_directory("test_import_edge");
    
    // Create file A that imports B
    write_file("test_import_edge/a.md",
        "# File A\n"
        "@import(test_import_edge/b.md)\n"
        "Content from A\n");
    
    // Create file B that imports A (circular)
    write_file("test_import_edge/b.md",
        "# File B\n"
        "@import(test_import_edge/a.md)\n"
        "Content from B\n");
    
    xmd_result* result = xmd_process_file(NULL, "test_import_edge/a.md");
    
    // The system should either:
    // 1. Detect and report the circular dependency
    // 2. Handle it gracefully by preventing infinite recursion
    // We'll accept either behavior as long as it doesn't crash
    
    // Clean up
    xmd_result_free(result);
    remove_file("test_import_edge/a.md");
    remove_file("test_import_edge/b.md");
    rmdir("test_import_edge");
    
    printf("✓ Test 1 passed (no crash on circular import)\n");
}

// Test Case 2: Indirect circular import (A->B->C->A)
static void test_indirect_circular_import() {
    printf("Test 2: Indirect circular import detection...\n");
    
    create_directory("test_import_edge");
    
    write_file("test_import_edge/a.md",
        "@import(test_import_edge/b.md)\n"
        "Content A\n");
    
    write_file("test_import_edge/b.md",
        "@import(test_import_edge/c.md)\n"
        "Content B\n");
    
    write_file("test_import_edge/c.md",
        "@import(test_import_edge/a.md)\n"
        "Content C\n");
    
    xmd_result* result = xmd_process_file(NULL, "test_import_edge/a.md");
    
    // Should handle circular dependency gracefully
    xmd_result_free(result);
    
    // Clean up
    remove_file("test_import_edge/a.md");
    remove_file("test_import_edge/b.md");
    remove_file("test_import_edge/c.md");
    rmdir("test_import_edge");
    
    printf("✓ Test 2 passed (no crash on indirect circular import)\n");
}

// Test Case 3: Self import
static void test_self_import() {
    printf("Test 3: Self import detection...\n");
    
    create_directory("test_import_edge");
    
    write_file("test_import_edge/self.md",
        "# Self Import Test\n"
        "@import(test_import_edge/self.md)\n"
        "This file imports itself\n");
    
    xmd_result* result = xmd_process_file(NULL, "test_import_edge/self.md");
    
    // Should handle self-import gracefully
    xmd_result_free(result);
    
    // Clean up
    remove_file("test_import_edge/self.md");
    rmdir("test_import_edge");
    
    printf("✓ Test 3 passed (no crash on self import)\n");
}

// Test Case 4: Import with empty file
static void test_empty_file_import() {
    printf("Test 4: Import empty file...\n");
    
    create_directory("test_import_edge");
    
    // Create empty file
    write_file("test_import_edge/empty.md", "");
    
    // Create file that imports empty file
    write_file("test_import_edge/main.md",
        "Before import\n"
        "@import(test_import_edge/empty.md)\n"
        "After import\n");
    
    xmd_result* result = xmd_process_file(NULL, "test_import_edge/main.md");
    
    assert(result && result->error_code == XMD_SUCCESS);
    assert(strstr(result->output, "Before import") != NULL);
    assert(strstr(result->output, "After import") != NULL);
    
    xmd_result_free(result);
    
    // Clean up
    remove_file("test_import_edge/main.md");
    remove_file("test_import_edge/empty.md");
    rmdir("test_import_edge");
    
    printf("✓ Test 4 passed\n");
}

// Test Case 5: Import with malformed paths
static void test_malformed_import_paths() {
    printf("Test 5: Malformed import paths...\n");
    
    create_directory("test_import_edge");
    
    // Test various malformed paths
    const char *test_cases[] = {
        "@import()\n",                          // Empty path
        "@import(   )\n",                       // Whitespace only
        "@import(../../../../../etc/passwd)\n", // Path traversal attempt
        "@import(/etc/passwd)\n",               // Absolute path outside project
        "@import(test_import_edge/\n",          // Unclosed parenthesis
        "@import test_import_edge/file.md)\n",  // Missing opening parenthesis
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        char filename[256];
        snprintf(filename, sizeof(filename), "test_import_edge/malformed%d.md", i);
        
        write_file(filename, test_cases[i]);
        
        xmd_result* result = xmd_process_file(NULL, filename);
        
        // Should handle malformed imports gracefully (either fail or ignore)
        xmd_result_free(result);
        
        remove_file(filename);
    }
    
    rmdir("test_import_edge");
    
    printf("✓ Test 5 passed (handled malformed paths gracefully)\n");
}

// Test Case 6: Performance test with many imports
static void test_many_imports_performance() {
    printf("Test 6: Performance test with many imports...\n");
    
    create_directory("test_import_edge");
    create_directory("test_import_edge/fragments");
    
    const int num_fragments = 50;
    
    // Create many small fragment files
    for (int i = 0; i < num_fragments; i++) {
        char filename[256];
        char content[256];
        snprintf(filename, sizeof(filename), "test_import_edge/fragments/fragment%d.md", i);
        snprintf(content, sizeof(content), "Fragment %d content\n", i);
        write_file(filename, content);
    }
    
    // Create main file that imports all fragments
    FILE *main_file = fopen("test_import_edge/main.md", "w");
    fprintf(main_file, "# Main file with many imports\n\n");
    for (int i = 0; i < num_fragments; i++) {
        fprintf(main_file, "@import(test_import_edge/fragments/fragment%d.md)\n", i);
    }
    fclose(main_file);
    
    // Measure processing time
    clock_t start = clock();
    xmd_result* result = xmd_process_file(NULL, "test_import_edge/main.md");
    clock_t end = clock();
    
    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("  Processed %d imports in %.3f seconds\n", num_fragments, time_spent);
    
    assert(result && result->error_code == XMD_SUCCESS);
    // Verify all fragments were imported
    for (int i = 0; i < num_fragments; i++) {
        char expected[256];
        snprintf(expected, sizeof(expected), "Fragment %d content", i);
        assert(strstr(result->output, expected) != NULL);
    }
    
    xmd_result_free(result);
    
    // Clean up
    remove_file("test_import_edge/main.md");
    for (int i = 0; i < num_fragments; i++) {
        char filename[256];
        snprintf(filename, sizeof(filename), "test_import_edge/fragments/fragment%d.md", i);
        remove_file(filename);
    }
    rmdir("test_import_edge/fragments");
    rmdir("test_import_edge");
    
    printf("✓ Test 6 passed\n");
}

// Test Case 7: Import with special characters in filenames
static void test_special_char_filenames() {
    printf("Test 7: Import files with special characters...\n");
    
    create_directory("test_import_edge");
    
    // Test filenames with spaces and special chars
    const char *filenames[] = {
        "test_import_edge/file with spaces.md",
        "test_import_edge/file-with-dashes.md",
        "test_import_edge/file_with_underscores.md",
        "test_import_edge/file.multiple.dots.md",
        NULL
    };
    
    // Create files
    for (int i = 0; filenames[i] != NULL; i++) {
        char content[256];
        snprintf(content, sizeof(content), "Content from file %d\n", i);
        write_file(filenames[i], content);
    }
    
    // Create main file that imports them
    FILE *main = fopen("test_import_edge/main.md", "w");
    fprintf(main, "# Special character import test\n");
    for (int i = 0; filenames[i] != NULL; i++) {
        fprintf(main, "@import(%s)\n", filenames[i]);
    }
    fclose(main);
    
    xmd_result* result = xmd_process_file(NULL, "test_import_edge/main.md");
    
    // Should handle special characters in filenames
    xmd_result_free(result);
    
    // Clean up
    remove_file("test_import_edge/main.md");
    for (int i = 0; filenames[i] != NULL; i++) {
        remove_file(filenames[i]);
    }
    rmdir("test_import_edge");
    
    printf("✓ Test 7 passed\n");
}

// Test Case 8: Import depth limit test
static void test_import_depth_limit() {
    printf("Test 8: Import depth limit test...\n");
    
    create_directory("test_import_edge");
    
    const int max_depth = 100; // Create a very deep import chain
    
    // Create a chain of files, each importing the next
    for (int i = max_depth; i >= 0; i--) {
        char filename[256];
        char content[512];
        snprintf(filename, sizeof(filename), "test_import_edge/level%d.md", i);
        
        if (i == max_depth) {
            snprintf(content, sizeof(content), "Bottom level %d\n", i);
        } else {
            snprintf(content, sizeof(content), 
                "@import(test_import_edge/level%d.md)\nLevel %d\n", i + 1, i);
        }
        
        write_file(filename, content);
    }
    
    // Process the top-level file
    xmd_result* result = xmd_process_file(NULL, "test_import_edge/level0.md");
    
    // Should either process all levels or gracefully limit depth
    xmd_result_free(result);
    
    // Clean up
    for (int i = 0; i <= max_depth; i++) {
        char filename[256];
        snprintf(filename, sizeof(filename), "test_import_edge/level%d.md", i);
        remove_file(filename);
    }
    rmdir("test_import_edge");
    
    printf("✓ Test 8 passed (handled deep nesting)\n");
}

int main() {
    printf("Running XMD import edge case tests...\n\n");
    
    test_direct_circular_import();
    test_indirect_circular_import();
    test_self_import();
    test_empty_file_import();
    test_malformed_import_paths();
    test_many_imports_performance();
    test_special_char_filenames();
    test_import_depth_limit();
    
    printf("\nAll edge case tests passed! ✓\n");
    return 0;
}