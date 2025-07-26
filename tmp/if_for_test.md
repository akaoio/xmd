# If and For Test

<!-- xmd:set name="World" -->
<!-- xmd:set enabled=true -->
<!-- xmd:set items=["apple", "banana", "cherry"] -->
<!-- xmd:set count=3 -->

## If Statement Tests

### Basic If
<!-- xmd:if enabled -->
This should show because enabled is true.
<!-- xmd:endif -->

### If-Else
<!-- xmd:if name == "World" -->
Hello {{name}}!
<!-- xmd:else -->
Hello stranger!
<!-- xmd:endif -->

### If-Elif-Else
<!-- xmd:if count > 5 -->
Many items
<!-- xmd:elif count > 2 -->
Some items ({{count}})
<!-- xmd:else -->
Few items
<!-- xmd:endif -->

### Nested If
<!-- xmd:if enabled -->
Outer condition true
<!-- xmd:if count == 3 -->
Inner condition also true: {{count}}
<!-- xmd:endif -->
<!-- xmd:endif -->

## For Loop Tests

### Basic For Loop
<!-- xmd:for item in items -->
- Item: {{item}}
<!-- xmd:endfor -->

### For Loop with Range
<!-- xmd:for i in range(1, 4) -->
Number: {{i}}
<!-- xmd:endfor -->

### For Loop with Index
<!-- xmd:for item, index in items -->
{{index}}: {{item}}
<!-- xmd:endfor -->

### Nested For Loops
<!-- xmd:for i in range(1, 3) -->
## Level {{i}}
<!-- xmd:for item in items -->
- {{i}}.{{item}}
<!-- xmd:endfor -->
<!-- xmd:endfor -->

## Combined If and For

<!-- xmd:for item in items -->
<!-- xmd:if item == "banana" -->
**Special item: {{item}}**
<!-- xmd:else -->
Regular item: {{item}}
<!-- xmd:endif -->
<!-- xmd:endfor -->

## End Test