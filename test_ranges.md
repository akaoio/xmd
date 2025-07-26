# XMD Range Syntax Test

## Test 1: Basic integer range (1..3)
<!-- xmd:for i in 1..3 -->
Number: {{i}}
<!-- xmd:endfor -->

## Test 2: Variable to integer (var..5)
<!-- xmd:set start=2 -->
<!-- xmd:for i in start..5 -->
Value: {{i}}
<!-- xmd:endfor -->

## Test 3: Integer to variable (3..var)
<!-- xmd:set end=6 -->
<!-- xmd:for i in 3..end -->
Count: {{i}}
<!-- xmd:endfor -->

## Test 4: Variable to variable (var..var)
<!-- xmd:set begin=1 -->
<!-- xmd:set finish=4 -->
<!-- xmd:for i in begin..finish -->
Range: {{i}}
<!-- xmd:endfor -->

## Test 5: Negative ranges
<!-- xmd:for i in -2..2 -->
Negative to positive: {{i}}
<!-- xmd:endfor -->

## Test 6: Range with spaces
<!-- xmd:for i in 10 .. 12 -->
Spaced: {{i}}
<!-- xmd:endfor -->