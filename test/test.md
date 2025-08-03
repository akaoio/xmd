# XMD Self-Testing Suite

This test suite uses XMD to test itself. Each test verifies core functionality by processing XMD directives and comparing actual output with expected results.

## Test Framework

<!-- xmd set test_count=0 -->
<!-- xmd set passed_count=0 -->
<!-- xmd set failed_count=0 -->

## 1. Variable Operations Tests

### 1.1 String Variable Assignment
<!-- xmd set greeting="Hello, World!" -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Set string variable  
**Expected:** Hello, World!  
**Actual:** {{greeting}}  
<!-- xmd if greeting == "Hello, World!" -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 1.2 Number Variable Assignment
<!-- xmd set num=42 -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Set number variable  
**Expected:** 42  
**Actual:** {{num}}  
<!-- xmd if num == 42 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 1.3 Boolean Variable Assignment
<!-- xmd set is_active=true -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Set boolean variable  
**Expected:** true  
**Actual:** {{is_active}}  
<!-- xmd if is_active == true -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 1.4 String Concatenation
<!-- xmd set first="Hello" -->
<!-- xmd set second=" World" -->
<!-- xmd set combined=first + second -->
<!-- xmd set test_count=test_count+1 -->
**Test:** String concatenation  
**Expected:** Hello World  
**Actual:** {{combined}}  
<!-- xmd if combined == "Hello World" -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

## 2. Arithmetic Operations Tests

### 2.1 Addition
<!-- xmd set a=10 -->
<!-- xmd set b=20 -->
<!-- xmd set sum=a + b -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Addition operation  
**Expected:** 30  
**Actual:** {{sum}}  
<!-- xmd if sum == 30 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 2.2 Subtraction
<!-- xmd set diff=b - a -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Subtraction operation  
**Expected:** 10  
**Actual:** {{diff}}  
<!-- xmd if diff == 10 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 2.3 Multiplication
<!-- xmd set product=a * 3 -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Multiplication operation  
**Expected:** 30  
**Actual:** {{product}}  
<!-- xmd if product == 30 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 2.4 Division
<!-- xmd set quotient=b / 4 -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Division operation  
**Expected:** 5  
**Actual:** {{quotient}}  
<!-- xmd if quotient == 5 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

## 3. Comparison Operators Tests

### 3.1 Equality Operator
<!-- xmd set x=100 -->
<!-- xmd set y=100 -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Equality comparison  
<!-- xmd if x == y -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (x == y is true)
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL (x == y is false)
<!-- xmd endif -->

### 3.2 Inequality Operator
<!-- xmd set p=50 -->
<!-- xmd set q=60 -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Inequality comparison  
<!-- xmd if p != q -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (p != q is true)
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL (p != q is false)
<!-- xmd endif -->

### 3.3 Greater Than
<!-- xmd set test_count=test_count+1 -->
**Test:** Greater than comparison  
<!-- xmd if q > p -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (q > p is true)
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL (q > p is false)
<!-- xmd endif -->

### 3.4 Less Than
<!-- xmd set test_count=test_count+1 -->
**Test:** Less than comparison  
<!-- xmd if p < q -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (p < q is true)
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL (p < q is false)
<!-- xmd endif -->

## 4. Logical Operators Tests

### 4.1 AND Operator
<!-- xmd set cond1=true -->
<!-- xmd set cond2=true -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Logical AND  
<!-- xmd if cond1 && cond2 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (true && true = true)
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 4.2 OR Operator
<!-- xmd set cond3=true -->
<!-- xmd set cond4=false -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Logical OR  
<!-- xmd if cond3 || cond4 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (true || false = true)
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 4.3 NOT Operator
<!-- xmd set cond5=false -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Logical NOT  
<!-- xmd if !cond5 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (!false = true)
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

## 5. Array Operations Tests

### 5.1 Array Creation
<!-- xmd set colors=["red", "green", "blue"] -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Array creation  
**Expected:** ["red", "green", "blue"]  
**Actual:** {{colors}}  
<!-- xmd if colors[0] == "red" && colors[1] == "green" && colors[2] == "blue" -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 5.2 Array Length
<!-- xmd set arr_len=length(colors) -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Array length function  
**Expected:** 3  
**Actual:** {{arr_len}}  
<!-- xmd if arr_len == 3 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 5.3 Array Iteration
<!-- xmd set test_count=test_count+1 -->
**Test:** Array iteration with for loop  
**Expected:** red, green, blue  
**Actual:** <!-- xmd for color in colors -->{{color}}<!-- xmd if _index < 2 -->, <!-- xmd endif --><!-- xmd endfor -->  
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS

## 6. Control Flow Tests

### 6.1 If Statement
<!-- xmd set score=85 -->
<!-- xmd set test_count=test_count+1 -->
**Test:** If statement  
<!-- xmd if score > 80 -->
<!-- xmd set grade="A" -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (Grade: {{grade}})
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 6.2 If/Else Statement
<!-- xmd set temperature=25 -->
<!-- xmd set test_count=test_count+1 -->
**Test:** If/Else statement  
<!-- xmd if temperature < 0 -->
<!-- xmd set weather="freezing" -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd else -->
<!-- xmd set weather="warm" -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (Weather: {{weather}})
<!-- xmd endif -->

### 6.3 If/Elif/Else Chain
<!-- xmd set value=50 -->
<!-- xmd set test_count=test_count+1 -->
**Test:** If/Elif/Else chain  
<!-- xmd if value < 25 -->
<!-- xmd set category="low" -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd elif value < 75 -->
<!-- xmd set category="medium" -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (Category: {{category}})
<!-- xmd else -->
<!-- xmd set category="high" -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

## 7. Loop Tests

### 7.1 Range Loop
<!-- xmd set test_count=test_count+1 -->
**Test:** For loop with range  
**Expected:** 1 2 3 4 5  
**Actual:** <!-- xmd for i in 1..5 -->{{i}} <!-- xmd endfor -->  
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS

### 7.2 Reverse Range Loop
<!-- xmd set test_count=test_count+1 -->
**Test:** For loop with reverse range  
**Expected:** 5 4 3 2 1  
**Actual:** <!-- xmd for i in 5..1 -->{{i}} <!-- xmd endfor -->  
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS

## 8. Object Operations Tests

### 8.1 Object Literal Creation
<!-- xmd set person={"name": "Alice", "age": 30, "active": true} -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Object creation  
**Expected:** Alice, 30, true  
**Actual:** {{person.name}}, {{person.age}}, {{person.active}}  
<!-- xmd if person.name == "Alice" && person.age == 30 && person.active == true -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 8.2 Nested Object
<!-- xmd set config={"server": {"host": "localhost", "port": 8080}, "debug": false} -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Nested object access  
**Expected:** localhost:8080  
**Actual:** {{config.server.host}}:{{config.server.port}}  
<!-- xmd if config.server.host == "localhost" && config.server.port == 8080 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

## 9. Function Tests

### 9.1 Built-in Functions
<!-- xmd set nums=[1, 2, 3, 4, 5] -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Built-in join function  
**Expected:** 1,2,3,4,5  
**Actual:** {{join(nums, ",")}}  
<!-- xmd if join(nums, ",") == "1,2,3,4,5" -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 9.2 User-Defined Functions
<!-- xmd function greet(name) -->
<!-- xmd return "Hello, " + name + "!" -->
<!-- xmd endfunction -->
<!-- xmd set test_count=test_count+1 -->
**Test:** User-defined function  
**Expected:** Hello, XMD!  
**Actual:** {{greet("XMD")}}  
<!-- xmd if greet("XMD") == "Hello, XMD!" -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 9.3 Function with Multiple Parameters
<!-- xmd function add(x, y) -->
<!-- xmd return x + y -->
<!-- xmd endfunction -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Multi-parameter function  
**Expected:** 15  
**Actual:** {{add(10, 5)}}  
<!-- xmd if add(10, 5) == 15 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

## 10. Edge Cases Tests

### 10.1 Empty String
<!-- xmd set empty="" -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Empty string handling  
**Expected:** (empty)  
**Actual:** ({{empty}})  
<!-- xmd if empty == "" -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 10.2 Zero Value
<!-- xmd set zero=0 -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Zero value handling  
**Expected:** 0  
**Actual:** {{zero}}  
<!-- xmd if zero == 0 -->
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS
<!-- xmd else -->
<!-- xmd set failed_count=failed_count+1 -->
**Result:** ❌ FAIL
<!-- xmd endif -->

### 10.3 Special Characters in Strings
<!-- xmd set special="Line 1\nLine 2\tTabbed" -->
<!-- xmd set test_count=test_count+1 -->
**Test:** Special characters in strings  
**Actual:** {{special}}  
<!-- xmd set passed_count=passed_count+1 -->
**Result:** ✅ PASS (Special characters preserved)

## Test Summary

**Total Tests:** {{test_count}}  
**Passed:** {{passed_count}}  
**Failed:** {{failed_count}}  
**Success Rate:** <!-- xmd set success_rate=(passed_count * 100) / test_count -->{{success_rate}}%

<!-- xmd if failed_count == 0 -->
## 🎉 All tests passed!
<!-- xmd else -->
## ⚠️ Some tests failed. Please review the failures above.
<!-- xmd endif -->

---
*Generated by XMD Self-Testing Suite*