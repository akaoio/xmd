/**
 * @file test_advanced_scripting.c
 * @brief Test advanced XMD scripting features
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "../../include/xmd_processor_internal.h"
#include "../../include/variable.h"
#include "../../include/store.h"

void test_array_literal_parsing(void) {
    printf("Testing array literal parsing...\n");
    
    // Test basic array literal parsing
    variable* array = parse_array_literal("[\"apple\", \"banana\", \"cherry\"]");
    assert(array != NULL);
    assert(array->type == VAR_ARRAY);
    assert(variable_array_size(array) == 3);
    
    variable* item0 = variable_array_get(array, 0);
    assert(item0 != NULL);
    assert(item0->type == VAR_STRING);
    assert(strcmp(item0->value.string_value, "apple") == 0);
    
    variable* item1 = variable_array_get(array, 1);
    assert(item1 != NULL);
    assert(strcmp(item1->value.string_value, "banana") == 0);
    
    variable* item2 = variable_array_get(array, 2);
    assert(item2 != NULL);
    assert(strcmp(item2->value.string_value, "cherry") == 0);
    
    variable_unref(array);
    
    // Test empty array
    variable* empty_array = parse_array_literal("[]");
    assert(empty_array != NULL);
    assert(empty_array->type == VAR_ARRAY);
    assert(variable_array_size(empty_array) == 0);
    variable_unref(empty_array);
    
    // Test single item array
    variable* single_array = parse_array_literal("[\"single\"]");
    assert(single_array != NULL);
    assert(variable_array_size(single_array) == 1);
    variable* single_item = variable_array_get(single_array, 0);
    assert(strcmp(single_item->value.string_value, "single") == 0);
    variable_unref(single_array);
    
    printf("✓ Array literal parsing tests passed\n");
}

void test_script_block_detection(void) {
    printf("Testing script block detection...\n");
    
    store* variables = store_create();
    
    // Test array literal detection
    const char* array_content = "set items = [\"a\", \"b\", \"c\"]";
    process_multiline_directive_enhanced(array_content, variables, NULL);
    
    variable* items_var = store_get(variables, "items");
    assert(items_var != NULL);
    assert(items_var->type == VAR_ARRAY);
    assert(variable_array_size(items_var) == 3);
    
    // Test for loop detection
    const char* loop_content = "set arr = [\"x\", \"y\"]\nset result = \"\"\nfor item in arr\n    result += item";
    process_multiline_directive_enhanced(loop_content, variables, NULL);
    
    variable* result_var = store_get(variables, "result");
    assert(result_var != NULL);
    assert(result_var->type == VAR_STRING);
    assert(strcmp(result_var->value.string_value, "xy") == 0);
    
    store_destroy(variables);
    printf("✓ Script block detection tests passed\n");
}

void test_for_loop_iteration(void) {
    printf("Testing for loop iteration with bodies...\n");
    
    store* variables = store_create();
    
    // Test basic for loop iteration
    const char* simple_loop = "set numbers = [\"1\", \"2\", \"3\"]\nset count = \"\"\nfor num in numbers\n    count += \"x\"";
    process_multiline_directive_enhanced(simple_loop, variables, NULL);
    
    variable* count_var = store_get(variables, "count");
    assert(count_var != NULL);
    assert(count_var->type == VAR_STRING);
    assert(strcmp(count_var->value.string_value, "xxx") == 0);
    
    // Test loop with string concatenation
    const char* concat_loop = "set items = [\"apple\", \"banana\"]\nset list = \"\"\nfor item in items\n    list += \"- \" + item + \"\\n\"";
    process_multiline_directive_enhanced(concat_loop, variables, NULL);
    
    variable* list_var = store_get(variables, "list");
    assert(list_var != NULL);
    assert(list_var->type == VAR_STRING);
    assert(strcmp(list_var->value.string_value, "- apple\n- banana\n") == 0);
    
    store_destroy(variables);
    printf("✓ For loop iteration tests passed\n");
}

void test_string_concatenation(void) {
    printf("Testing string concatenation with + operator...\n");
    
    store* variables = store_create();
    
    // Test basic string concatenation
    const char* basic_concat = "set prefix = \"Hello\"\nset suffix = \"World\"\nset result = prefix + \" \" + suffix";
    process_multiline_directive_enhanced(basic_concat, variables, NULL);
    
    variable* result_var = store_get(variables, "result");
    assert(result_var != NULL);
    assert(result_var->type == VAR_STRING);
    assert(strcmp(result_var->value.string_value, "Hello World") == 0);
    
    // Test concatenation with escape sequences
    const char* escape_concat = "set text = \"Line1\" + \"\\n\" + \"Line2\"";
    process_multiline_directive_enhanced(escape_concat, variables, NULL);
    
    variable* text_var = store_get(variables, "text");
    assert(text_var != NULL);
    assert(strstr(text_var->value.string_value, "\n") != NULL);
    
    store_destroy(variables);
    printf("✓ String concatenation tests passed\n");
}

void test_compound_assignment(void) {
    printf("Testing compound assignment += operator...\n");
    
    store* variables = store_create();
    
    // Test basic += operator
    const char* compound_test = "set result = \"Start\"\nresult += \" Middle\"\nresult += \" End\"";
    process_multiline_directive_enhanced(compound_test, variables, NULL);
    
    variable* result_var = store_get(variables, "result");
    assert(result_var != NULL);
    assert(result_var->type == VAR_STRING);
    assert(strcmp(result_var->value.string_value, "Start Middle End") == 0);
    
    // Test += with empty initialization
    const char* empty_init = "set content\ncontent += \"First\"\ncontent += \" Second\"";
    process_multiline_directive_enhanced(empty_init, variables, NULL);
    
    variable* content_var = store_get(variables, "content");
    assert(content_var != NULL);
    assert(strcmp(content_var->value.string_value, "First Second") == 0);
    
    store_destroy(variables);
    printf("✓ Compound assignment tests passed\n");
}

void test_dynamic_imports(void) {
    printf("Testing dynamic imports with variables...\n");
    
    // Create test files
    mkdir("test_imports", 0755);
    
    FILE* test_file1 = fopen("test_imports/file1.md", "w");
    fprintf(test_file1, "Content from file 1");
    fclose(test_file1);
    
    FILE* test_file2 = fopen("test_imports/file2.md", "w");
    fprintf(test_file2, "Content from file 2");
    fclose(test_file2);
    
    store* variables = store_create();
    
    // Test dynamic import
    const char* dynamic_import = "set files = [\"test_imports/file1.md\", \"test_imports/file2.md\"]\nset content = \"\"\nfor file in files\n    content += import file + \"\\n\"";
    process_multiline_directive_enhanced(dynamic_import, variables, NULL);
    
    variable* content_var = store_get(variables, "content");
    assert(content_var != NULL);
    assert(content_var->type == VAR_STRING);
    assert(strstr(content_var->value.string_value, "Content from file 1") != NULL);
    assert(strstr(content_var->value.string_value, "Content from file 2") != NULL);
    
    store_destroy(variables);
    
    // Cleanup test files
    unlink("test_imports/file1.md");
    unlink("test_imports/file2.md");
    rmdir("test_imports");
    
    printf("✓ Dynamic import tests passed\n");
}

void test_multiline_directive_formatting(void) {
    printf("Testing multiline directive line break handling...\n");
    
    store* variables = store_create();
    
    // Test that script blocks don't create extra line breaks
    const char* input = "<!-- xmd:\nset items = [\"a\", \"b\"]\nset result = \"\"\nfor item in items\n    result += item\n-->\n# Title\n\nContent here.";
    
    char* output = process_xmd_content_enhanced(input, variables);
    assert(output != NULL);
    
    // Should start with "# Title" not with empty line
    assert(output[0] == '#');
    assert(strncmp(output, "# Title", 7) == 0);
    
    // Should not have extra empty lines at the start
    assert(output[0] != '\n');
    
    free(output);
    store_destroy(variables);
    printf("✓ Multiline directive formatting tests passed\n");
}

void test_complex_integration_scenario(void) {
    printf("Testing complex integration scenario...\n");
    
    // Create test documentation files
    // Remove test_docs if it exists as a file to avoid conflicts
    struct stat st;
    if (stat("test_docs", &st) == 0 && !S_ISDIR(st.st_mode)) {
        unlink("test_docs");
    }
    
    mkdir("test_docs", 0755);
    
    FILE* intro = fopen("test_docs/intro.md", "w");
    assert(intro != NULL);
    fprintf(intro, "Introduction Section");
    fclose(intro);
    
    FILE* setup = fopen("test_docs/setup.md", "w");
    assert(setup != NULL);
    fprintf(setup, "Setup Instructions");
    fclose(setup);
    
    FILE* usage = fopen("test_docs/usage.md", "w");
    assert(usage != NULL);
    fprintf(usage, "Usage Examples");
    fclose(usage);
    
    store* variables = store_create();
    
    // Complex scenario: dynamic documentation generation
    const char* complex_script = 
        "set sections = [\"test_docs/intro.md\", \"test_docs/setup.md\", \"test_docs/usage.md\"]\n"
        "set documentation = \"# Complete Guide\\n\\n\"\n"
        "set counter = \"\"\n"
        "for section in sections\n"
        "    counter += \"x\"\n"
        "    documentation += \"## Section \" + counter + \"\\n\\n\"\n"
        "    documentation += import section + \"\\n\\n\"";
    
    process_multiline_directive_enhanced(complex_script, variables, NULL);
    
    variable* doc_var = store_get(variables, "documentation");
    assert(doc_var != NULL);
    assert(doc_var->type == VAR_STRING);
    
    const char* doc_content = doc_var->value.string_value;
    assert(strstr(doc_content, "# Complete Guide") != NULL);
    assert(strstr(doc_content, "Section x") != NULL);
    assert(strstr(doc_content, "Section xx") != NULL);
    assert(strstr(doc_content, "Section xxx") != NULL);
    assert(strstr(doc_content, "Introduction Section") != NULL);
    assert(strstr(doc_content, "Setup Instructions") != NULL);
    assert(strstr(doc_content, "Usage Examples") != NULL);
    
    variable* counter_var = store_get(variables, "counter");
    assert(counter_var != NULL);
    assert(strcmp(counter_var->value.string_value, "xxx") == 0);
    
    store_destroy(variables);
    
    // Cleanup
    unlink("test_docs/intro.md");
    unlink("test_docs/setup.md");
    unlink("test_docs/usage.md");
    rmdir("test_docs");
    
    printf("✓ Complex integration scenario tests passed\n");
}

void test_edge_cases(void) {
    printf("Testing edge cases and error handling...\n");
    
    store* variables = store_create();
    
    // Test malformed array literal
    variable* bad_array = parse_array_literal("[\"unclosed");
    assert(bad_array == NULL);
    
    // Test empty for loop
    const char* empty_for = "set empty_arr = []\nset result = \"start\"\nfor item in empty_arr\n    result += item\nresult += \"end\"";
    process_multiline_directive_enhanced(empty_for, variables, NULL);
    
    variable* result_var = store_get(variables, "result");
    assert(result_var != NULL);
    assert(strcmp(result_var->value.string_value, "startend") == 0);
    
    // Test import of non-existent file (should handle gracefully)
    const char* bad_import = "set files = [\"nonexistent.md\"]\nset content = \"\"\nfor file in files\n    content += import file";
    process_multiline_directive_enhanced(bad_import, variables, NULL);
    
    variable* content_var = store_get(variables, "content");
    assert(content_var != NULL);
    // Should handle missing file gracefully (empty or error message)
    
    store_destroy(variables);
    printf("✓ Edge case tests passed\n");
}

int main() {
    printf("=== Advanced XMD Scripting Test Suite ===\n\n");
    
    test_array_literal_parsing();
    test_script_block_detection();
    test_for_loop_iteration();
    test_string_concatenation();
    test_compound_assignment();
    test_dynamic_imports();
    test_multiline_directive_formatting();
    test_complex_integration_scenario();
    test_edge_cases();
    
    printf("\n=== All Advanced Scripting Tests Passed! ===\n");
    return 0;
}