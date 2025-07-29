#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/import_tracker.h"

int main() {
    printf("=== Import Tracker Debug Test ===\n\n");
    
    // Create tracker
    import_tracker_t* tracker = import_tracker_create();
    if (!tracker) {
        printf("❌ Failed to create tracker\n");
        return 1;
    }
    printf("✅ Created tracker\n");
    
    // Test adding a dependency
    const char* importer = "/home/x/Projects/xmd/test_cascade/teamwork/dashboard.md";
    const char* imported = "/home/x/Projects/xmd/test_cascade/teamwork/index/comment.md";
    
    bool result = import_tracker_add_dependency(tracker, importer, imported);
    printf("Add dependency result: %s\n", result ? "✅ success" : "❌ failed");
    
    // Test retrieving importers
    char** importers = NULL;
    int count = 0;
    
    result = import_tracker_get_importers(tracker, imported, &importers, &count);
    printf("Get importers result: %s\n", result ? "✅ success" : "❌ failed");
    printf("Importer count: %d\n", count);
    
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            printf("  Importer %d: %s\n", i, importers[i]);
            free(importers[i]);
        }
        free(importers);
    } else {
        printf("⚠️  No importers found!\n");
    }
    
    // Test extract imports from HTML comment syntax
    const char* html_content = "# Dashboard\n\n<!-- xmd: import /home/x/Projects/xmd/test_cascade/teamwork/index/comment.md -->\n\nDashboard footer content.";
    
    char** extracted_imports = NULL;
    int extracted_count = 0;
    
    result = import_tracker_extract_imports(html_content, importer, &extracted_imports, &extracted_count);
    printf("\nExtract imports result: %s\n", result ? "✅ success" : "❌ failed");
    printf("Extracted count: %d\n", extracted_count);
    
    if (extracted_count > 0) {
        for (int i = 0; i < extracted_count; i++) {
            printf("  Extracted %d: %s\n", i, extracted_imports[i]);
            free(extracted_imports[i]);
        }
        free(extracted_imports);
    } else {
        printf("⚠️  No imports extracted!\n");
    }
    
    // Clean up
    import_tracker_free(tracker);
    printf("\n✅ Test completed\n");
    
    return 0;
}