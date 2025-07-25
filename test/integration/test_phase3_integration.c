/**
 * @file test_phase3_integration.c
 * @brief Integration tests for Phase 3 control flow system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/variable.h"
#include "../include/store.h"
#include "../include/template.h"
#include "../include/lexer.h"

// Include all forward declarations from individual test files
typedef struct conditional_context ConditionContext;
typedef struct loop_context LoopContext;
typedef struct flow_context FlowContext;
typedef struct error_context ErrorContext;

// Forward declarations for integration functions
int control_flow_process_xmd(const char* xmd_content, VariableStore* store, char** result);
int parse_control_flow_directive(const char* directive, char** type, char** params);

/**
 * @brief Test integration of conditionals with template system
 */
void test_conditional_template_integration(void) {
    printf("Testing conditional template integration...\n");
    
    VariableStore* store = variable_store_new();
    
    // Set up test variables
    Variable* is_admin = variable_new_boolean(1);
    Variable* username = variable_new_string("admin");
    variable_store_set(store, "is_admin", is_admin);
    variable_store_set(store, "username", username);
    
    // Test XMD conditional syntax
    const char* xmd_content = 
        "# Welcome Page\n"
        "<!-- XMD:if condition=\"{{is_admin}}\" -->\n"
        "Welcome back, Administrator {{username}}!\n"
        "<!-- XMD:else -->\n"
        "Welcome, {{username}}!\n"
        "<!-- XMD:endif -->\n";
    
    char* result = NULL;
    int status = control_flow_process_xmd(xmd_content, store, &result);
    
    assert(status == 0);
    assert(result != NULL);
    assert(strstr(result, "Welcome back, Administrator admin!") != NULL);
    assert(strstr(result, "Welcome, admin!") == NULL); // Should not include else branch
    
    free(result);
    variable_unref(is_admin);
    variable_unref(username);
    variable_store_free(store);
    
    printf("✓ Conditional template integration test passed\n");
}

/**
 * @brief Test integration of loops with variable system
 */
void test_loop_variable_integration(void) {
    printf("Testing loop variable integration...\n");
    
    VariableStore* store = variable_store_new();
    
    // Create array of blog posts
    Variable* post1 = variable_new_object();
    variable_object_set(post1, "title", variable_new_string("First Post"));
    variable_object_set(post1, "author", variable_new_string("John"));
    
    Variable* post2 = variable_new_object();
    variable_object_set(post2, "title", variable_new_string("Second Post"));
    variable_object_set(post2, "author", variable_new_string("Jane"));
    
    Variable* posts[2] = {post1, post2};
    Variable* posts_array = variable_new_array(posts, 2);
    variable_store_set(store, "blog_posts", posts_array);
    
    // Test XMD loop syntax
    const char* xmd_content = 
        "# Blog Posts\n"
        "<!-- XMD:for item=\"post\" in=\"{{blog_posts}}\" -->\n"
        "## {{post.title}}\n"
        "By: {{post.author}}\n"
        "<!-- XMD:endfor -->\n";
    
    char* result = NULL;
    int status = control_flow_process_xmd(xmd_content, store, &result);
    
    assert(status == 0);
    assert(result != NULL);
    assert(strstr(result, "## First Post") != NULL);
    assert(strstr(result, "By: John") != NULL);
    assert(strstr(result, "## Second Post") != NULL);
    assert(strstr(result, "By: Jane") != NULL);
    
    free(result);
    variable_unref(post1);
    variable_unref(post2);
    variable_unref(posts_array);
    variable_store_free(store);
    
    printf("✓ Loop variable integration test passed\n");
}

/**
 * @brief Test nested control flow structures
 */
void test_nested_control_flow(void) {
    printf("Testing nested control flow...\n");
    
    VariableStore* store = variable_store_new();
    
    // Set up test data
    Variable* users[2];
    
    Variable* user1 = variable_new_object();
    variable_object_set(user1, "name", variable_new_string("Alice"));
    variable_object_set(user1, "is_active", variable_new_boolean(1));
    users[0] = user1;
    
    Variable* user2 = variable_new_object();
    variable_object_set(user2, "name", variable_new_string("Bob"));
    variable_object_set(user2, "is_active", variable_new_boolean(0));
    users[1] = user2;
    
    Variable* users_array = variable_new_array(users, 2);
    variable_store_set(store, "users", users_array);
    
    // Test nested XMD structures
    const char* xmd_content = 
        "# User Status\n"
        "<!-- XMD:for item=\"user\" in=\"{{users}}\" -->\n"
        "<!-- XMD:if condition=\"{{user.is_active}}\" -->\n"
        "✅ {{user.name}} is active\n"
        "<!-- XMD:else -->\n"
        "❌ {{user.name}} is inactive\n"
        "<!-- XMD:endif -->\n"
        "<!-- XMD:endfor -->\n";
    
    char* result = NULL;
    int status = control_flow_process_xmd(xmd_content, store, &result);
    
    assert(status == 0);
    assert(result != NULL);
    assert(strstr(result, "✅ Alice is active") != NULL);
    assert(strstr(result, "❌ Bob is inactive") != NULL);
    
    free(result);
    variable_unref(user1);
    variable_unref(user2);
    variable_unref(users_array);
    variable_store_free(store);
    
    printf("✓ Nested control flow test passed\n");
}

/**
 * @brief Test error handling in control flow
 */
void test_control_flow_error_handling(void) {
    printf("Testing control flow error handling...\n");
    
    VariableStore* store = variable_store_new();
    
    // Test error handling with invalid condition
    const char* xmd_content = 
        "# Error Test\n"
        "<!-- XMD:try -->\n"
        "<!-- XMD:if condition=\"{{undefined_variable}}\" -->\n"
        "This should cause an error\n"
        "<!-- XMD:endif -->\n"
        "<!-- XMD:catch type=\"variable\" -->\n"
        "Error: Variable not found\n"
        "<!-- XMD:endtry -->\n";
    
    char* result = NULL;
    int status = control_flow_process_xmd(xmd_content, store, &result);
    
    // Should handle error gracefully
    assert(status == 0);
    assert(result != NULL);
    assert(strstr(result, "Error: Variable not found") != NULL);
    
    free(result);
    variable_store_free(store);
    
    printf("✓ Control flow error handling test passed\n");
}

/**
 * @brief Test lexer integration with control flow directives
 */
void test_lexer_control_flow_integration(void) {
    printf("Testing lexer control flow integration...\n");
    
    Lexer* lexer = lexer_new();
    assert(lexer != NULL);
    
    const char* input = 
        "<!-- XMD:if condition=\"{{user.is_admin}}\" -->\n"
        "Admin panel\n"
        "<!-- XMD:endif -->\n";
    
    lexer_set_input(lexer, input);
    
    Token* token = lexer_next_token(lexer);
    assert(token != NULL);
    assert(token_get_type(token) == TOKEN_TYPE_XMD_DIRECTIVE);
    
    const char* directive_content = token_get_content(token);
    assert(strstr(directive_content, "XMD:if") != NULL);
    assert(strstr(directive_content, "condition=") != NULL);
    
    token_free(token);
    lexer_free(lexer);
    
    printf("✓ Lexer control flow integration test passed\n");
}

/**
 * @brief Test directive parsing
 */
void test_directive_parsing(void) {
    printf("Testing directive parsing...\n");
    
    char* type = NULL;
    char* params = NULL;
    
    // Test if directive parsing
    int status = parse_control_flow_directive("XMD:if condition=\"{{user.active}}\"", &type, &params);
    assert(status == 0);
    assert(strcmp(type, "if") == 0);
    assert(strstr(params, "condition=") != NULL);
    
    free(type);
    free(params);
    
    // Test for directive parsing
    status = parse_control_flow_directive("XMD:for item=\"post\" in=\"{{posts}}\"", &type, &params);
    assert(status == 0);
    assert(strcmp(type, "for") == 0);
    assert(strstr(params, "item=") != NULL);
    assert(strstr(params, "in=") != NULL);
    
    free(type);
    free(params);
    
    printf("✓ Directive parsing test passed\n");
}

/**
 * @brief Test complete pipeline with all phases
 */
void test_complete_pipeline(void) {
    printf("Testing complete pipeline...\n");
    
    VariableStore* store = variable_store_new();
    
    // Set up comprehensive test data
    Variable* config = variable_new_object();
    variable_object_set(config, "site_name", variable_new_string("My Blog"));
    variable_object_set(config, "show_sidebar", variable_new_boolean(1));
    
    Variable* articles[2];
    Variable* article1 = variable_new_object();
    variable_object_set(article1, "title", variable_new_string("Getting Started"));
    variable_object_set(article1, "published", variable_new_boolean(1));
    articles[0] = article1;
    
    Variable* article2 = variable_new_object();
    variable_object_set(article2, "title", variable_new_string("Draft Article"));
    variable_object_set(article2, "published", variable_new_boolean(0));
    articles[1] = article2;
    
    Variable* articles_array = variable_new_array(articles, 2);
    
    variable_store_set(store, "config", config);
    variable_store_set(store, "articles", articles_array);
    
    // Complex XMD template combining all features
    const char* xmd_content = 
        "# {{config.site_name}}\n"
        "\n"
        "## Published Articles\n"
        "<!-- XMD:for item=\"article\" in=\"{{articles}}\" -->\n"
        "<!-- XMD:if condition=\"{{article.published}}\" -->\n"
        "- [{{article.title}}](#)\n"
        "<!-- XMD:endif -->\n"
        "<!-- XMD:endfor -->\n"
        "\n"
        "<!-- XMD:if condition=\"{{config.show_sidebar}}\" -->\n"
        "## Sidebar\n"
        "Welcome to the blog!\n"
        "<!-- XMD:endif -->\n";
    
    char* result = NULL;
    int status = control_flow_process_xmd(xmd_content, store, &result);
    
    assert(status == 0);
    assert(result != NULL);
    assert(strstr(result, "# My Blog") != NULL);
    assert(strstr(result, "- [Getting Started]") != NULL);
    assert(strstr(result, "Draft Article") == NULL); // Should be filtered out
    assert(strstr(result, "## Sidebar") != NULL);
    assert(strstr(result, "Welcome to the blog!") != NULL);
    
    free(result);
    variable_unref(config);
    variable_unref(article1);
    variable_unref(article2);
    variable_unref(articles_array);
    variable_store_free(store);
    
    printf("✓ Complete pipeline test passed\n");
}

/**
 * @brief Main test runner
 */
int main(void) {
    printf("=== Phase 3 Integration Tests ===\n");
    
    test_conditional_template_integration();
    test_loop_variable_integration();
    test_nested_control_flow();
    test_control_flow_error_handling();
    test_lexer_control_flow_integration();
    test_directive_parsing();
    test_complete_pipeline();
    
    printf("\n✅ All Phase 3 integration tests passed!\n");
    return 0;
}