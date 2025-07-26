# XMD Range Edge Case Tests

## Test 1: Single value range (same start and end)
<!-- xmd:for i in 5..5 -->
Single: {{i}}
<!-- xmd:endfor -->

## Test 2: Empty range (invalid)
<!-- xmd:for i in 5..3 -->
This should not appear
<!-- xmd:endfor -->

## Test 3: Large range (limited to 1000 iterations)
<!-- xmd:set huge_end=2000 -->
<!-- xmd:for i in 1..huge_end -->
Large: {{i}}
<!-- xmd:endfor -->

## Test 4: String variable substitution
<!-- xmd:set start_str=7 -->
<!-- xmd:set end_str=9 -->
<!-- xmd:for i in start_str..end_str -->
String vars: {{i}}
<!-- xmd:endfor -->