# XMD If and For Directive Tests

This document tests the if and for functionality of XMD.

## Test 1: Basic If Directive with String Comparison

<!-- xmd:set name="World" -->
<!-- xmd:if name == "World" -->
Hello, {{name}}! The condition is true.
<!-- xmd:else -->
Hello, stranger! The condition is false.
<!-- xmd:endif -->

## Test 2: If Directive with Variable Existence Check

<!-- xmd:set existing_var="test" -->
<!-- xmd:if existing_var -->
Variable exists: {{existing_var}}
<!-- xmd:else -->
Variable does not exist
<!-- xmd:endif -->

## Test 3: If Directive with Non-Existing Variable

<!-- xmd:if non_existing_var -->
This should not appear
<!-- xmd:else -->
Variable non_existing_var does not exist
<!-- xmd:endif -->

## Test 4: If Directive with Numeric Comparison

<!-- xmd:set count=5 -->
<!-- xmd:if count > 3 -->
Count ({{count}}) is greater than 3
<!-- xmd:else -->
Count is not greater than 3
<!-- xmd:endif -->

## Test 5: If Directive with False Condition

<!-- xmd:set status=false -->
<!-- xmd:if status -->
Status is true
<!-- xmd:else -->
Status is false
<!-- xmd:endif -->

## Test 6: Basic For Loop with Integer Range

<!-- xmd:for i in range(1, 4) -->
Iteration {{i}}: Hello from loop!
<!-- xmd:endfor -->

## Test 7: For Loop with Array

<!-- xmd:set items=["apple", "banana", "cherry"] -->
<!-- xmd:for item in items -->
- {{item}}
<!-- xmd:endfor -->

## Test 8: Nested If Inside For Loop

<!-- xmd:for num in range(1, 4) -->
<!-- xmd:if num == 2 -->
Number {{num}} is special!
<!-- xmd:else -->
Number {{num}} is regular.
<!-- xmd:endif -->
<!-- xmd:endfor -->

## Test 9: Complex If with Multiple Comparisons

<!-- xmd:set x=10 -->
<!-- xmd:if x >= 10 -->
x ({{x}}) is greater than or equal to 10
<!-- xmd:else -->
x is less than 10
<!-- xmd:endif -->

## Test 10: If with String Inequality

<!-- xmd:set name="Alice" -->
<!-- xmd:if name != "Bob" -->
Name is not Bob, it's {{name}}
<!-- xmd:else -->
Name is Bob
<!-- xmd:endif -->
