/**
 * @file test_multiline_enhanced.c
 * @brief Test enhanced multiline directive processing
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../../include/xmd_processor_internal.h"
#include "../../include/variable.h"
#include "../../include/store.h"

void test_multiline_directive_basic(void) {
    printf("Testing basic multiline directive processing...\n");
    
    store* variables = store_create();
    
    // Test basic multiline processing
    const char* basic_multiline = "set name = \"Test\"\nset value = 42\nprint(name)\nprint(value)";
    process_multiline_directive_enhanced(basic_multiline, variables, NULL);
    
    variable* name_var = store_get(variables, "name");
    assert(name_var != NULL);
    assert(name_var->type == VAR_STRING);
    assert(strcmp(name_var->value.string_value, "Test") == 0);
    
    variable* value_var = store_get(variables, "value");
    assert(value_var != NULL);
    assert(value_var->type == VAR_STRING); // Numbers stored as strings in set
    assert(strcmp(value_var->value.string_value, "42") == 0);
    
    store_destroy(variables);
    printf("✓ Basic multiline directive tests passed\n");
}

void test_multiline_output_accumulation(void) {
    printf("Testing multiline output accumulation...\n");
    
    store* variables = store_create();
    
    // Test output accumulation
    const char* output_test = "print(\"Line 1\")\nprint(\"Line 2\")\nprint(\"Line 3\")";
    process_multiline_directive_enhanced(output_test, variables, NULL);
    
    variable* output_var = store_get(variables, "_multiline_output");
    assert(output_var != NULL);
    assert(output_var->type == VAR_STRING);
    assert(strstr(output_var->value.string_value, "Line 1") != NULL);
    assert(strstr(output_var->value.string_value, "Line 2") != NULL);
    assert(strstr(output_var->value.string_value, "Line 3") != NULL);
    
    store_destroy(variables);
    printf("✓ Multiline output accumulation tests passed\n");
}

void test_script_block_vs_regular_directives(void) {
    printf("Testing script block vs regular directive detection...\n");
    
    store* variables = store_create();
    
    // Test regular directives (should not use script processor)
    const char* regular_directives = "set simple = \"value\"\nprint(simple)";
    process_multiline_directive_enhanced(regular_directives, variables, NULL);
    
    variable* simple_var = store_get(variables, "simple");
    assert(simple_var != NULL);
    assert(strcmp(simple_var->value.string_value, "value") == 0);
    
    // Test script block (should use script processor)
    const char* script_block = "set arr = [\"a\", \"b\"]\nset result = \"\"\nfor item in arr\n    result += item";
    process_multiline_directive_enhanced(script_block, variables, NULL);
    
    variable* result_var = store_get(variables, "result");
    assert(result_var != NULL);
    assert(strcmp(result_var->value.string_value, "ab") == 0);
    
    store_destroy(variables);
    printf("✓ Script block vs regular directive detection tests passed\n");
}

void test_complex_multiline_scenario(void) {
    printf("Testing complex multiline scenario...\n");
    
    // Create test environment
    mkdir("test_multiline", 0755);
    
    FILE* header = fopen("test_multiline/header.md", "w");
    fprintf(header, "# Header Content");
    fclose(header);
    
    FILE* footer = fopen("test_multiline/footer.md", "w");
    fprintf(footer, "Footer Content");
    fclose(footer);
    
    store* variables = store_create();
    
    // Complex scenario with mixed directives
    const char* complex_multiline = 
        "set title = \"My Document\"\n"
        "set sections = [\"test_multiline/header.md\", \"test_multiline/footer.md\"]\n"
        "set document = \"<!-- Generated Document -->\\n\\n\"\n"
        "document += \"Title: \" + title + \"\\n\\n\"\n"
        "for section in sections\n"
        "    document += import section + \"\\n\\n\"\n"
        "print(\"Processing complete\")\n"
        "print(document)";
    
    process_multiline_directive_enhanced(complex_multiline, variables, NULL);
    
    variable* title_var = store_get(variables, "title");
    assert(title_var != NULL);
    assert(strcmp(title_var->value.string_value, "My Document") == 0);
    
    variable* document_var = store_get(variables, "document");
    assert(document_var != NULL);
    assert(strstr(document_var->value.string_value, "My Document") != NULL);
    assert(strstr(document_var->value.string_value, "Header Content") != NULL);
    assert(strstr(document_var->value.string_value, "Footer Content") != NULL);
    
    variable* output_var = store_get(variables, "_multiline_output");
    assert(output_var != NULL);
    assert(strstr(output_var->value.string_value, "Processing complete") != NULL);
    
    store_destroy(variables);
    
    // Cleanup
    unlink("test_multiline/header.md");
    unlink("test_multiline/footer.md");
    rmdir("test_multiline");
    
    printf("✓ Complex multiline scenario tests passed\n");
}

void test_multiline_error_handling(void) {
    printf("Testing multiline directive error handling...\n");
    
    store* variables = store_create();
    
    // Test malformed script blocks
    const char* malformed_script = "set arr = [\"incomplete\nfor item in arr\n    result += item";
    process_multiline_directive_enhanced(malformed_script, variables, NULL);
    
    // Should handle gracefully without crashing
    variable* arr_var = store_get(variables, "arr");
    // May or may not be set depending on error handling
    
    // Test undefined variable reference
    const char* undefined_ref = "set result = undefined_var + \"suffix\"";
    process_multiline_directive_enhanced(undefined_ref, variables, NULL);
    
    // Should handle undefined variables gracefully
    variable* result_var = store_get(variables, "result");
    // May be set to empty or error value
    
    store_destroy(variables);
    printf("✓ Multiline directive error handling tests passed\n");
}

void test_multiline_performance(void) {
    printf("Testing multiline directive performance...\n");
    
    store* variables = store_create();
    
    // Test with large array
    const char* large_script = 
        "set items = [\"item1\", \"item2\", \"item3\", \"item4\", \"item5\", \"item6\", \"item7\", \"item8\", \"item9\", \"item10\"]\n"
        "set result = \"\"\n"
        "for item in items\n"
        "    result += \"Processing \" + item + \"\\n\"";
    
    process_multiline_directive_enhanced(large_script, variables, NULL);
    
    variable* result_var = store_get(variables, "result");
    assert(result_var != NULL);
    assert(strstr(result_var->value.string_value, "item1") != NULL);
    assert(strstr(result_var->value.string_value, "item10") != NULL);
    
    // Count occurrences of "Processing"
    const char* content = result_var->value.string_value;
    int count = 0;
    const char* pos = content;
    while ((pos = strstr(pos, "Processing")) != NULL) {
        count++;
        pos++;
    }
    assert(count == 10); // Should process all 10 items
    
    store_destroy(variables);
    printf("✓ Multiline directive performance tests passed\n");
}

void test_multiline_nested_structures(void) {
    printf("Testing multiline nested structures...\n");
    
    store* variables = store_create();
    
    // Test nested loops (simulated with multiple arrays)
    const char* nested_script = 
        "set outer = [\"A\", \"B\"]\n"
        "set inner = [\"1\", \"2\"]\n"
        "set result = \"\"\n"
        "for o in outer\n"
        "    result += \"Outer: \" + o + \"\\n\"\n"
        "    for i in inner\n"
        "        result += \"  Inner: \" + i + \"\\n\"";
    
    process_multiline_directive_enhanced(nested_script, variables, NULL);
    
    variable* result_var = store_get(variables, "result");
    assert(result_var != NULL);
    
    const char* content = result_var->value.string_value;
    assert(strstr(content, "Outer: A") != NULL);
    assert(strstr(content, "Outer: B") != NULL);
    assert(strstr(content, "Inner: 1") != NULL);
    assert(strstr(content, "Inner: 2") != NULL);
    
    store_destroy(variables);
    printf("✓ Multiline nested structure tests passed\n");
}

void test_multiline_memory_management(void) {
    printf("Testing multiline directive memory management...\n");
    
    // Test memory usage with many operations
    for (int i = 0; i < 100; i++) {
        store* variables = store_create();
        
        const char* memory_test = 
            "set data = [\"test1\", \"test2\", \"test3\"]\n"
            "set output = \"\"\n"
            "for item in data\n"
            "    output += \"Item: \" + item + \"\\n\"";
        
        process_multiline_directive_enhanced(memory_test, variables, NULL);
        
        variable* output_var = store_get(variables, "output");
        assert(output_var != NULL);
        assert(strstr(output_var->value.string_value, "test1") != NULL);
        
        store_destroy(variables);
    }
    
    printf("✓ Multiline directive memory management tests passed\n");
}

int main() {
    printf("=== Enhanced Multiline Directive Test Suite ===\n\n");
    
    test_multiline_directive_basic();
    test_multiline_output_accumulation();
    test_script_block_vs_regular_directives();
    test_complex_multiline_scenario();
    test_multiline_error_handling();
    test_multiline_performance();
    test_multiline_nested_structures();
    test_multiline_memory_management();
    
    printf("\n=== All Enhanced Multiline Directive Tests Passed! ===\n");
    return 0;
}