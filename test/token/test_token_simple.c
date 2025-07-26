/**
 * @file test_token_simple.c
 * @brief Simple token tests matching actual implementation
 * @author XMD Team
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "token.h"

void test_token_create_basic(void) {
    printf("Testing token creation...\n");
    
    token* t1 = token_create(TOKEN_TEXT, "Hello World", 1, 5);
    assert(t1 != NULL);
    assert(t1->type == TOKEN_TEXT);
    assert(strcmp(t1->value, "Hello World") == 0);
    assert(t1->line == 1);
    assert(t1->column == 5);
    assert(t1->next == NULL);
    token_free(t1);
    
    printf("✓ Basic token creation passed\n");
}

void test_token_type_validation(void) {
    printf("Testing token type validation...\n");
    
    assert(token_type_is_valid(TOKEN_TEXT) == true);
    assert(token_type_is_valid(TOKEN_HEADING) == true);
    assert(token_type_is_valid(TOKEN_XMD_DIRECTIVE) == true);
    assert(token_type_is_valid(TOKEN_EOF) == true);
    assert(token_type_is_valid(-1) == false);
    
    printf("✓ Token type validation passed\n");
}

void test_token_type_to_string(void) {
    printf("Testing token type to string...\n");
    
    assert(strcmp(token_type_to_string(TOKEN_TEXT), "TEXT") == 0);
    assert(strcmp(token_type_to_string(TOKEN_HEADING), "HEADING") == 0);
    assert(strcmp(token_type_to_string(TOKEN_XMD_DIRECTIVE), "XMD_DIRECTIVE") == 0);
    assert(strcmp(token_type_to_string(-1), "UNKNOWN") == 0);
    
    printf("✓ Token type to string passed\n");
}

void test_token_duplicate(void) {
    printf("Testing token duplication...\n");
    
    token* original = token_create(TOKEN_TEXT, "Original Content", 5, 10);
    assert(original != NULL);
    
    token* duplicate = token_duplicate(original);
    assert(duplicate != NULL);
    assert(duplicate != original);
    assert(duplicate->type == original->type);
    assert(strcmp(duplicate->value, original->value) == 0);
    assert(duplicate->line == original->line);
    assert(duplicate->column == original->column);
    
    token_free(original);
    token_free(duplicate);
    
    printf("✓ Token duplication passed\n");
}

void test_token_equals(void) {
    printf("Testing token equality...\n");
    
    token* t1 = token_create(TOKEN_TEXT, "Same Content", 1, 1);
    token* t2 = token_create(TOKEN_TEXT, "Same Content", 1, 1);
    token* t3 = token_create(TOKEN_TEXT, "Different Content", 1, 1);
    
    assert(token_equals(t1, t2) == true);
    assert(token_equals(t1, t3) == false);
    assert(token_equals(NULL, NULL) == true);
    assert(token_equals(t1, NULL) == false);
    
    token_free(t1);
    token_free(t2);
    token_free(t3);
    
    printf("✓ Token equality passed\n");
}

void test_token_list_length(void) {
    printf("Testing token list length...\n");
    
    token* t1 = token_create(TOKEN_TEXT, "First", 1, 1);
    token* t2 = token_create(TOKEN_TEXT, "Second", 2, 1);
    token* t3 = token_create(TOKEN_TEXT, "Third", 3, 1);
    
    // Link manually
    t1->next = t2;
    t2->next = t3;
    
    assert(token_list_length(t1) == 3);
    assert(token_list_length(NULL) == 0);
    
    token_list_free(t1);
    
    printf("✓ Token list length passed\n");
}

int main(void) {
    printf("Running simple token tests...\n\n");
    
    test_token_create_basic();
    test_token_type_validation();
    test_token_type_to_string();
    test_token_duplicate();
    test_token_equals();
    test_token_list_length();
    
    printf("\n✓ All simple token tests passed!\n");
    return 0;
}
