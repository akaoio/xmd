/**
 * @file test_advanced_integration.c
 * @brief End-to-end integration tests for advanced XMD features
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

void test_documentation_generation_pipeline(void) {
    printf("Testing complete documentation generation pipeline...\n");
    
    // Setup test environment
    mkdir("test_integration", 0755);
    mkdir("test_integration/docs", 0755);
    
    // Create source documentation files
    FILE* intro = fopen("test_integration/docs/intro.md", "w");
    fprintf(intro, "Welcome to XMD\nThis is the introduction section.");
    fclose(intro);
    
    FILE* features = fopen("test_integration/docs/features.md", "w");
    fprintf(features, "Key Features\n- Advanced scripting\n- Array processing\n- Dynamic imports");
    fclose(features);
    
    FILE* examples = fopen("test_integration/docs/examples.md", "w");
    fprintf(examples, "Usage Examples\nHere are some examples of XMD in action.");
    fclose(examples);
    
    // Create the main template file
    FILE* template = fopen("test_integration/template.md", "w");
    fprintf(template, 
        "<!-- xmd:\n"
        "set title = \"XMD Documentation\"\n"
        "set version = \"v1.1.0\"\n"
        "set sections = [\"test_integration/docs/intro.md\", \"test_integration/docs/features.md\", \"test_integration/docs/examples.md\"]\n"
        "set toc = \"# Table of Contents\\n\\n\"\n"
        "set content = \"\"\n"
        "set counter = \"\"\n"
        "for section in sections\n"
        "    counter += \"x\"\n"
        "    toc += \"- Section \" + counter + \"\\n\"\n"
        "    content += \"## Section \" + counter + \"\\n\\n\"\n"
        "    content += import section + \"\\n\\n\"\n"
        "-->\n"
        "\n"
        "# {{title}} {{version}}\n"
        "\n"
        "{{toc}}\n"
        "\n"
        "{{content}}\n"
        "\n"
        "---\n"
        "Generated automatically with XMD.\n");
    fclose(template);
    
    // Process the template
    store* variables = store_create();
    
    FILE* input_file = fopen("test_integration/template.md", "r");
    assert(input_file != NULL);
    
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    
    char* input_content = malloc(file_size + 1);
    fread(input_content, 1, file_size, input_file);
    input_content[file_size] = '\0';
    fclose(input_file);
    
    char* output = process_xmd_content_enhanced(input_content, variables);
    assert(output != NULL);
    
    // Verify the output contains expected content
    assert(strstr(output, "# XMD Documentation v1.1.0") != NULL);
    assert(strstr(output, "# Table of Contents") != NULL);
    assert(strstr(output, "- Section x") != NULL);
    assert(strstr(output, "- Section xx") != NULL);
    assert(strstr(output, "- Section xxx") != NULL);
    assert(strstr(output, "Welcome to XMD") != NULL);
    assert(strstr(output, "Key Features") != NULL);
    assert(strstr(output, "Usage Examples") != NULL);
    assert(strstr(output, "Advanced scripting") != NULL);
    assert(strstr(output, "Generated automatically") != NULL);
    
    // Save output for verification
    FILE* output_file = fopen("test_integration/output.md", "w");
    fprintf(output_file, "%s", output);
    fclose(output_file);
    
    // Cleanup
    free(input_content);
    free(output);
    store_destroy(variables);
    
    unlink("test_integration/docs/intro.md");
    unlink("test_integration/docs/features.md");
    unlink("test_integration/docs/examples.md");
    unlink("test_integration/template.md");
    unlink("test_integration/output.md");
    rmdir("test_integration/docs");
    rmdir("test_integration");
    
    printf("✓ Documentation generation pipeline tests passed\n");
}

void test_configuration_management_scenario(void) {
    printf("Testing configuration management scenario...\n");
    
    mkdir("test_config", 0755);
    
    // Create environment-specific configs
    FILE* dev_config = fopen("test_config/dev.md", "w");
    fprintf(dev_config, "server: localhost\nport: 3000\ndebug: true");
    fclose(dev_config);
    
    FILE* prod_config = fopen("test_config/prod.md", "w");
    fprintf(prod_config, "server: production.example.com\nport: 80\ndebug: false");
    fclose(prod_config);
    
    // Create deployment template
    FILE* deploy_template = fopen("test_config/deploy.md", "w");
    fprintf(deploy_template,
        "<!-- xmd:\n"
        "set environments = [\"dev\", \"prod\"]\n"
        "set configs = [\"test_config/dev.md\", \"test_config/prod.md\"]\n"
        "set deployment_guide = \"# Deployment Guide\\n\\n\"\n"
        "set env_index = \"\"\n"
        "for env in environments\n"
        "    env_index += \"x\"\n"
        "    deployment_guide += \"## \" + env + \" Environment\\n\\n\"\n"
        "    deployment_guide += \"Configuration for \" + env + \" environment:\\n\\n\"\n"
        "    deployment_guide += \"```\\n\"\n"
        "for config in configs\n"
        "    deployment_guide += import config + \"\\n\"\n"
        "deployment_guide += \"```\\n\\n\"\n"
        "-->\n"
        "\n"
        "{{deployment_guide}}\n");
    fclose(deploy_template);
    
    store* variables = store_create();
    
    FILE* template_file = fopen("test_config/deploy.md", "r");
    fseek(template_file, 0, SEEK_END);
    long size = ftell(template_file);
    fseek(template_file, 0, SEEK_SET);
    
    char* template_content = malloc(size + 1);
    fread(template_content, 1, size, template_file);
    template_content[size] = '\0';
    fclose(template_file);
    
    char* result = process_xmd_content_enhanced(template_content, variables);
    assert(result != NULL);
    
    // Verify configuration processing
    assert(strstr(result, "# Deployment Guide") != NULL);
    assert(strstr(result, "## dev Environment") != NULL);
    assert(strstr(result, "## prod Environment") != NULL);
    assert(strstr(result, "localhost") != NULL);
    assert(strstr(result, "production.example.com") != NULL);
    assert(strstr(result, "port: 3000") != NULL);
    assert(strstr(result, "port: 80") != NULL);
    
    free(template_content);
    free(result);
    store_destroy(variables);
    
    unlink("test_config/dev.md");
    unlink("test_config/prod.md");
    unlink("test_config/deploy.md");
    rmdir("test_config");
    
    printf("✓ Configuration management scenario tests passed\n");
}

void test_report_generation_with_commands(void) {
    printf("Testing report generation with command execution...\n");
    
    store* variables = store_create();
    
    // Create a report template with command execution
    const char* report_template = 
        "# System Report\n"
        "\n"
        "<!-- xmd:\n"
        "set sections = [\"System Info\", \"Disk Usage\", \"Process Count\"]\n"
        "set commands = [\"uname -a\", \"df -h | head -3\", \"ps aux | wc -l\"]\n"
        "set report = \"\"\n"
        "set section_count = \"\"\n"
        "for section in sections\n"
        "    section_count += \"1\"\n"
        "    report += \"## \" + section + \"\\n\\n\"\n"
        "    report += \"Section number: \" + section_count + \"\\n\\n\"\n"
        "-->\n"
        "\n"
        "{{report}}\n"
        "\n"
        "Report generated on: <!-- xmd: exec date -->\n";
    
    char* output = process_xmd_content_enhanced(report_template, variables);
    assert(output != NULL);
    
    // Verify report structure
    assert(strstr(output, "# System Report") != NULL);
    assert(strstr(output, "## System Info") != NULL);
    assert(strstr(output, "## Disk Usage") != NULL);
    assert(strstr(output, "## Process Count") != NULL);
    assert(strstr(output, "Section number: 1") != NULL);
    assert(strstr(output, "Section number: 11") != NULL);
    assert(strstr(output, "Section number: 111") != NULL);
    assert(strstr(output, "Report generated on:") != NULL);
    
    free(output);
    store_destroy(variables);
    
    printf("✓ Report generation with commands tests passed\n");
}

void test_api_documentation_generation(void) {
    printf("Testing API documentation generation...\n");
    
    mkdir("test_api", 0755);
    
    // Create API endpoint documentation files
    FILE* users_api = fopen("test_api/users.md", "w");
    fprintf(users_api, "**GET /api/users**\nReturns list of users\n\nParameters: none");
    fclose(users_api);
    
    FILE* posts_api = fopen("test_api/posts.md", "w");
    fprintf(posts_api, "**GET /api/posts**\nReturns list of posts\n\nParameters: limit, offset");
    fclose(posts_api);
    
    FILE* auth_api = fopen("test_api/auth.md", "w");
    fprintf(auth_api, "**POST /api/auth**\nAuthenticate user\n\nParameters: username, password");
    fclose(auth_api);
    
    // Create API documentation template
    const char* api_template =
        "# API Documentation\n"
        "\n"
        "<!-- xmd:\n"
        "set endpoints = [\"test_api/users.md\", \"test_api/posts.md\", \"test_api/auth.md\"]\n"
        "set api_docs = \"## Available Endpoints\\n\\n\"\n"
        "set endpoint_count = \"\"\n"
        "for endpoint in endpoints\n"
        "    endpoint_count += \"*\"\n"
        "    api_docs += \"### Endpoint \" + endpoint_count + \"\\n\\n\"\n"
        "    api_docs += import endpoint + \"\\n\\n\"\n"
        "    api_docs += \"---\\n\\n\"\n"
        "-->\n"
        "\n"
        "{{api_docs}}\n"
        "\n"
        "Total endpoints documented: <!-- xmd: set total = \"3\" -->{{total}}\n";
    
    store* variables = store_create();
    char* result = process_xmd_content_enhanced(api_template, variables);
    assert(result != NULL);
    
    // Verify API documentation
    assert(strstr(result, "# API Documentation") != NULL);
    assert(strstr(result, "## Available Endpoints") != NULL);
    assert(strstr(result, "### Endpoint *") != NULL);
    assert(strstr(result, "### Endpoint **") != NULL);
    assert(strstr(result, "### Endpoint ***") != NULL);
    assert(strstr(result, "GET /api/users") != NULL);
    assert(strstr(result, "GET /api/posts") != NULL);
    assert(strstr(result, "POST /api/auth") != NULL);
    assert(strstr(result, "Total endpoints documented: 3") != NULL);
    
    free(result);
    store_destroy(variables);
    
    unlink("test_api/users.md");
    unlink("test_api/posts.md");
    unlink("test_api/auth.md");
    rmdir("test_api");
    
    printf("✓ API documentation generation tests passed\n");
}

void test_project_structure_analysis(void) {
    printf("Testing project structure analysis...\n");
    
    mkdir("test_project", 0755);
    mkdir("test_project/src", 0755);
    mkdir("test_project/docs", 0755);
    mkdir("test_project/tests", 0755);
    
    // Create project files
    FILE* readme = fopen("test_project/README.md", "w");
    fprintf(readme, "# Test Project\nA sample project for testing.");
    fclose(readme);
    
    FILE* main_c = fopen("test_project/src/main.c", "w");
    fprintf(main_c, "// Main application file");
    fclose(main_c);
    
    FILE* utils_c = fopen("test_project/src/utils.c", "w");
    fprintf(utils_c, "// Utility functions");
    fclose(utils_c);
    
    FILE* test_c = fopen("test_project/tests/test_main.c", "w");
    fprintf(test_c, "// Test file");
    fclose(test_c);
    
    // Create project analysis template
    const char* analysis_template =
        "# Project Analysis\n"
        "\n"
        "<!-- xmd:\n"
        "set directories = [\"src\", \"docs\", \"tests\"]\n"
        "set analysis = \"## Project Structure\\n\\n\"\n"
        "set dir_count = \"\"\n"
        "for dir in directories\n"
        "    dir_count += \"📁\"\n"
        "    analysis += \"### Directory: \" + dir + \" \" + dir_count + \"\\n\\n\"\n"
        "    analysis += \"Analysis of \" + dir + \" directory.\\n\\n\"\n"
        "-->\n"
        "\n"
        "{{analysis}}\n"
        "\n"
        "<!-- xmd: set file_count = exec find test_project -type f | wc -l -->\n"
        "Total files found: {{file_count}}\n";
    
    store* variables = store_create();
    char* result = process_xmd_content_enhanced(analysis_template, variables);
    assert(result != NULL);
    
    // Verify analysis
    assert(strstr(result, "# Project Analysis") != NULL);
    assert(strstr(result, "## Project Structure") != NULL);
    assert(strstr(result, "### Directory: src 📁") != NULL);
    assert(strstr(result, "### Directory: docs 📁📁") != NULL);
    assert(strstr(result, "### Directory: tests 📁📁📁") != NULL);
    assert(strstr(result, "Total files found:") != NULL);
    
    free(result);
    store_destroy(variables);
    
    // Cleanup
    unlink("test_project/README.md");
    unlink("test_project/src/main.c");
    unlink("test_project/src/utils.c");
    unlink("test_project/tests/test_main.c");
    rmdir("test_project/src");
    rmdir("test_project/docs");
    rmdir("test_project/tests");
    rmdir("test_project");
    
    printf("✓ Project structure analysis tests passed\n");
}

int main() {
    printf("=== Advanced Integration Test Suite ===\n\n");
    
    test_documentation_generation_pipeline();
    test_configuration_management_scenario();
    test_report_generation_with_commands();
    test_api_documentation_generation();
    test_project_structure_analysis();
    
    printf("\n=== All Advanced Integration Tests Passed! ===\n");
    return 0;
}