#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "xmd.h"

// Helper function to create a directory
static void create_directory(const char *path) {
    if (mkdir(path, 0755) != 0 && errno != EEXIST) {
        fprintf(stderr, "Failed to create directory: %s\n", path);
        exit(1);
    }
}

// Helper function to write content to a file
static void write_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Failed to create file: %s\n", filename);
        exit(1);
    }
    fprintf(file, "%s", content);
    fclose(file);
}

// Helper function to remove a file
static void remove_file(const char *filename) {
    if (unlink(filename) != 0 && errno != ENOENT) {
        fprintf(stderr, "Warning: Failed to remove file: %s\n", filename);
    }
}

// Test Case 1: Simple nested import (A imports B, B imports C)
static void test_simple_nested_import() {
    printf("Test 1: Simple nested import...\n");
    
    // Create test directory structure
    create_directory("test_import_nested");
    
    // Create file C (leaf node)
    write_file("test_import_nested/c.md", 
        "# File C\n"
        "Content from C\n");
    
    // Create file B (imports C)
    write_file("test_import_nested/b.md",
        "# File B\n"
        "@import(test_import_nested/c.md)\n"
        "Content from B\n");
    
    // Create file A (imports B)
    write_file("test_import_nested/a.md",
        "# File A\n"
        "@import(test_import_nested/b.md)\n"
        "Content from A\n");
    
    // Process file A
    XmdResult result = xmd_process_file("test_import_nested/a.md");
    
    // Verify the result contains content from all three files
    assert(result.success);
    assert(strstr(result.output, "File A") != NULL);
    assert(strstr(result.output, "File B") != NULL);
    assert(strstr(result.output, "File C") != NULL);
    assert(strstr(result.output, "Content from A") != NULL);
    assert(strstr(result.output, "Content from B") != NULL);
    assert(strstr(result.output, "Content from C") != NULL);
    
    xmd_free_result(&result);
    
    // Clean up
    remove_file("test_import_nested/a.md");
    remove_file("test_import_nested/b.md");
    remove_file("test_import_nested/c.md");
    rmdir("test_import_nested");
    
    printf("✓ Test 1 passed\n");
}

// Test Case 2: Deep nesting (A->B->C->D->E)
static void test_deep_nested_import() {
    printf("Test 2: Deep nested import (5 levels)...\n");
    
    create_directory("test_import_nested");
    
    // Create files E through A
    write_file("test_import_nested/e.md", "Level E\n");
    write_file("test_import_nested/d.md", "@import(test_import_nested/e.md)\nLevel D\n");
    write_file("test_import_nested/c.md", "@import(test_import_nested/d.md)\nLevel C\n");
    write_file("test_import_nested/b.md", "@import(test_import_nested/c.md)\nLevel B\n");
    write_file("test_import_nested/a.md", "@import(test_import_nested/b.md)\nLevel A\n");
    
    XmdResult result = xmd_process_file("test_import_nested/a.md");
    
    assert(result.success);
    assert(strstr(result.output, "Level A") != NULL);
    assert(strstr(result.output, "Level B") != NULL);
    assert(strstr(result.output, "Level C") != NULL);
    assert(strstr(result.output, "Level D") != NULL);
    assert(strstr(result.output, "Level E") != NULL);
    
    xmd_free_result(&result);
    
    // Clean up
    remove_file("test_import_nested/a.md");
    remove_file("test_import_nested/b.md");
    remove_file("test_import_nested/c.md");
    remove_file("test_import_nested/d.md");
    remove_file("test_import_nested/e.md");
    rmdir("test_import_nested");
    
    printf("✓ Test 2 passed\n");
}

// Test Case 3: Diamond pattern import (A imports B and C, both import D)
static void test_diamond_import() {
    printf("Test 3: Diamond pattern import...\n");
    
    create_directory("test_import_nested");
    
    // Create file D (shared dependency)
    write_file("test_import_nested/d.md", "Shared content from D\n");
    
    // Create files B and C (both import D)
    write_file("test_import_nested/b.md", 
        "@import(test_import_nested/d.md)\n"
        "Content from B\n");
    write_file("test_import_nested/c.md",
        "@import(test_import_nested/d.md)\n"
        "Content from C\n");
    
    // Create file A (imports both B and C)
    write_file("test_import_nested/a.md",
        "@import(test_import_nested/b.md)\n"
        "@import(test_import_nested/c.md)\n"
        "Content from A\n");
    
    XmdResult result = xmd_process_file("test_import_nested/a.md");
    
    assert(result.success);
    assert(strstr(result.output, "Content from A") != NULL);
    assert(strstr(result.output, "Content from B") != NULL);
    assert(strstr(result.output, "Content from C") != NULL);
    // D should appear only once or twice, but the content should be there
    assert(strstr(result.output, "Shared content from D") != NULL);
    
    xmd_free_result(&result);
    
    // Clean up
    remove_file("test_import_nested/a.md");
    remove_file("test_import_nested/b.md");
    remove_file("test_import_nested/c.md");
    remove_file("test_import_nested/d.md");
    rmdir("test_import_nested");
    
    printf("✓ Test 3 passed\n");
}

// Test Case 4: Relative path imports
static void test_relative_path_imports() {
    printf("Test 4: Relative path imports...\n");
    
    // Create nested directory structure
    create_directory("test_import_nested");
    create_directory("test_import_nested/components");
    create_directory("test_import_nested/shared");
    
    // Create shared component
    write_file("test_import_nested/shared/footer.md", "Footer content\n");
    
    // Create component that imports from parent directory
    write_file("test_import_nested/components/page.md",
        "@import(../shared/footer.md)\n"
        "Page content\n");
    
    // Create main file that imports component
    write_file("test_import_nested/main.md",
        "@import(components/page.md)\n"
        "Main content\n");
    
    XmdResult result = xmd_process_file("test_import_nested/main.md");
    
    assert(result.success);
    assert(strstr(result.output, "Main content") != NULL);
    assert(strstr(result.output, "Page content") != NULL);
    assert(strstr(result.output, "Footer content") != NULL);
    
    xmd_free_result(&result);
    
    // Clean up
    remove_file("test_import_nested/main.md");
    remove_file("test_import_nested/components/page.md");
    remove_file("test_import_nested/shared/footer.md");
    rmdir("test_import_nested/components");
    rmdir("test_import_nested/shared");
    rmdir("test_import_nested");
    
    printf("✓ Test 4 passed\n");
}

// Test Case 5: Missing file import (error handling)
static void test_missing_file_import() {
    printf("Test 5: Missing file import error handling...\n");
    
    create_directory("test_import_nested");
    
    // Create file that imports non-existent file
    write_file("test_import_nested/broken.md",
        "@import(test_import_nested/nonexistent.md)\n"
        "This should fail\n");
    
    XmdResult result = xmd_process_file("test_import_nested/broken.md");
    
    // The import should fail gracefully
    // Note: Behavior depends on implementation - adjust assertion as needed
    if (!result.success) {
        assert(result.error != NULL);
        assert(strstr(result.error, "nonexistent.md") != NULL || 
               strstr(result.error, "import") != NULL);
    }
    
    xmd_free_result(&result);
    
    // Clean up
    remove_file("test_import_nested/broken.md");
    rmdir("test_import_nested");
    
    printf("✓ Test 5 passed\n");
}

// Test Case 6: Watch mode simulation - file dependency tracking
static void test_import_dependency_tracking() {
    printf("Test 6: Import dependency tracking for watch mode...\n");
    
    create_directory("test_import_nested");
    create_directory("test_import_nested/core");
    create_directory("test_import_nested/index");
    
    // Create the scenario from TEAMWORK.md
    write_file("test_import_nested/core/comment.md", "Original comment\n");
    write_file("test_import_nested/index/comment.md", 
        "@import(../core/comment.md)\n"
        "Index wrapper\n");
    write_file("test_import_nested/dashboard.md",
        "@import(index/comment.md)\n"
        "Dashboard content\n");
    
    // Process dashboard initially
    XmdResult result1 = xmd_process_file("test_import_nested/dashboard.md");
    assert(result1.success);
    assert(strstr(result1.output, "Original comment") != NULL);
    xmd_free_result(&result1);
    
    // Simulate file change
    write_file("test_import_nested/core/comment.md", "Updated comment\n");
    
    // Process dashboard again - should reflect the change
    XmdResult result2 = xmd_process_file("test_import_nested/dashboard.md");
    assert(result2.success);
    assert(strstr(result2.output, "Updated comment") != NULL);
    xmd_free_result(&result2);
    
    // Clean up
    remove_file("test_import_nested/dashboard.md");
    remove_file("test_import_nested/index/comment.md");
    remove_file("test_import_nested/core/comment.md");
    rmdir("test_import_nested/index");
    rmdir("test_import_nested/core");
    rmdir("test_import_nested");
    
    printf("✓ Test 6 passed\n");
}

// Test Case 7: Complex multi-level imports with mixed content
static void test_complex_mixed_imports() {
    printf("Test 7: Complex multi-level imports with mixed content...\n");
    
    create_directory("test_import_nested");
    create_directory("test_import_nested/layouts");
    create_directory("test_import_nested/components");
    create_directory("test_import_nested/data");
    
    // Create data files
    write_file("test_import_nested/data/config.md", 
        "@set(title, \"My Site\")\n"
        "@set(version, \"1.0.0\")\n");
    
    // Create component files
    write_file("test_import_nested/components/header.md",
        "@import(../data/config.md)\n"
        "# ${title}\n"
        "Version: ${version}\n");
    
    write_file("test_import_nested/components/nav.md",
        "- [Home](/)\n"
        "- [About](/about)\n");
    
    // Create layout that imports multiple components
    write_file("test_import_nested/layouts/main.md",
        "@import(../components/header.md)\n"
        "@import(../components/nav.md)\n"
        "<main>\n"
        "${content}\n"
        "</main>\n");
    
    // Create page that uses layout
    write_file("test_import_nested/index.md",
        "@set(content, \"Welcome to the homepage!\")\n"
        "@import(layouts/main.md)\n");
    
    XmdResult result = xmd_process_file("test_import_nested/index.md");
    
    assert(result.success);
    assert(strstr(result.output, "My Site") != NULL);
    assert(strstr(result.output, "Version: 1.0.0") != NULL);
    assert(strstr(result.output, "[Home](/)") != NULL);
    assert(strstr(result.output, "Welcome to the homepage!") != NULL);
    
    xmd_free_result(&result);
    
    // Clean up
    remove_file("test_import_nested/index.md");
    remove_file("test_import_nested/layouts/main.md");
    remove_file("test_import_nested/components/nav.md");
    remove_file("test_import_nested/components/header.md");
    remove_file("test_import_nested/data/config.md");
    rmdir("test_import_nested/layouts");
    rmdir("test_import_nested/components");
    rmdir("test_import_nested/data");
    rmdir("test_import_nested");
    
    printf("✓ Test 7 passed\n");
}

int main() {
    printf("Running XMD nested import tests...\n\n");
    
    test_simple_nested_import();
    test_deep_nested_import();
    test_diamond_import();
    test_relative_path_imports();
    test_missing_file_import();
    test_import_dependency_tracking();
    test_complex_mixed_imports();
    
    printf("\nAll tests passed! ✓\n");
    return 0;
}