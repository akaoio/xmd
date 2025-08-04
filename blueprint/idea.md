# XMD Language Specification

> XMD is a lightweight, mobile-friendly, markdown-compatible scripting language designed for clarity, minimal syntax, and strong expressiveness. Ideal for embedding in documents, apps, AI workflows, or DSLs.
> Although not the most powerful language, but it is the one that is purest and closest to human natural language. To me, it is the most beautiful programming language.
- Nguyen Ky Son - Aug 1st 2025


---

1. Variables
```xmd
set made "in Vietnam",
    by "Nguyen Ky Son",
    age 40
set pi 3.14
set active true
set empty null
```

set declares a variable.

Values can be string, number, boolean, null, array, object, or result of expression.

Variables can be local or global:

```xmd
set price 1000 // global var
function plan price // local var
    print "price is " + price
    
plan 900 // call plan function with param price = 900
```

Would print "price is 900", because "price" in "plan" is local

---

2. Arrays

Inline Arrays (Preferred):

set scores 1, 2, 3

Equivalent to:

[1, 2, 3]

Multiline Arrays:

set items
    "pen",
    "book",
    "lamp",

Must use commas , to separate elements.

Indentation is required in multiline format.


Notes

Elements can be literals, variables, or expressions.



---

3. Objects

Inline Objects (Preferred)

set user name "Alice", age 30, active true

Equivalent to:

{ "name": "Alice", "age": 30, "active": true }

Multiline Objects

set config
    debug true,
    retries 3,
    timeout 1000,

Each entry is a key value, pair.

No colons :, no curly braces {}.

Comma , is required between entries.


Nested Structure Example

set scores 8, 9, 10
set profile name "Linh", scores scores, active true
// This is different to set variable described above, which looks like:
set a 1, b 2, c "3" // this is to set vars inline, not to set object which is described above.

---

4. Functions

function greet name
    return "Hello " + name

function add a b
    return a + b

function defines a named function.

Arguments are space-separated.



---

5. Conditionals

IMPORTANT: In XMD, we don't use = to set value, we use = to compare

if score = 100 then print "Wowww"
if score <= 90
    return "Excellent"
elif score <= 70
    return "Good"
else
    return "Try again"

Ternary Operator

set result age >= 18 ? "adult" : "minor"


---

6. Loops

Repeat N times

loop 100 times
    print "I am sorryyyy..."

loop N times lặp lại N lần với biến đếm nội bộ (ẩn hoặc không cần).

Có thể dùng trong các trường hợp không cần chỉ số i.


For in range

for i in 1 .. 5
    print i
    if i = 4 then break

for i in min .. max
    print i

For over array

for item in items
    print item

For with index

for i, name in names
    print i + ": " + name

While

set count 0
while count < 3
    print count
    set count count + 1


---

7. Classes

class Animal
    constructor name
        set self.name name

    speak
        return self.name + " makes a sound"

class Dog extends Animal
    constructor name breed
        super name
        set self.breed breed
        self.secret "XMD is made in Vietnam"

    speak
        return self.name + " says woof!"
    
    private secret message
        return "my top secret: " + message

---

8. Error Handling

function divide a b
    try
        if b = 0
            throw "Divide by zero"
        return a / b
    catch err
        return "Error: " + err


---

9. Lambda & Higher-Order Functions

set doubled map numbers (x => x * 2)
set evens filter numbers (x => x % 2 = 0)


---

10. String Operations

set text "Hello World"
set upper text.upper
set parts text.split " "
set joined parts.join "-"


---

11. Date & Time

set now Date.now
set past Date "1990-01-01"
set years now.diff past "years"


---

12. File I/O

set phones File.read "phones.csv"
set doc File.read "readme.md"

File.write "output.txt" "Hello World"
File.write "result.json" json.stringify users
File.write "result.yaml" yaml.stringify settings

File.read đọc nội dung từ file.

File.write ghi nội dung ra file.

Có thể thao tác với văn bản, JSON, YAML.

12.1 Serialization / Deserialization

set user name "Alice", age 30

set j json.stringify user
set y yaml.stringify user

set u1 json.parse j
set u2 yaml.parse y

json.stringify, yaml.stringify chuyển object sang chuỗi.

json.parse, yaml.parse chuyển chuỗi về object.

12.2 `get` and `put` on json/yaml files like a database
```xmd
set name get "./data/students.json".alice.name
set what "is-going-on.yaml"
set answer get what.boss.is_watching

put what.me.working true

set location 123, 456
set project
    name "xmd"
    github "akaoio/xmd"
    draft true
put what.count 1, 2, 3 // array
put what.why because true, and "whynot", have "fun" // object
put what.me.where location
put what.me project
put what.me.project.release false

// Nesting and Linking database

put "alice.json".scores "../scores.yaml".alice // get value of key alice in scores.yaml and set as value of key scores in alice.json, NOT LINKING, just copying value

put "../addresses.json".office.alice "123 Four Five str."
put "alice.yaml".address.office "@ ../addresses.json office.alice" // use @ prefix for linking accross json/yaml files easily 
set addr get "alice.yaml".address.office
print addr // would print "123 Four Five str."
```

Behavious:

get biến chưa tồn tại -> Trả về null hoặc throw (tuỳ config)
put vào đường dẫn chưa tồn tại -> Tự tạo nested key
put vào file -> Ghi ra file, auto-create
get từ file -> Lazy load nếu chưa

---

13. Async / Await

async function fetch url
    set res await http.get url
    return res.json


---

14. Imports and Exports

Importing

```xmd
import propA newA, propB newB from "config.json"
import description from "data.yaml" 
import "students.json"
import Tasks // equivalent to `import "Tasks.md"`
import Tasks tasks // or import "Tasks.md" tasks
set teachers import "teachers.yaml"
```

ES6 equivalent:
```js
import { propA as newA, propB as newB } from "config.json"
import description from "data.yaml"
import "students.json"
import Tasks
import Tasks as tasks
let teachers = import("teachers.yaml")
```

Khi import file .json hoặc .yaml, nội dung sẽ được tự động parse thành object.


Exporting symbols

Use export to expose variables, functions, or classes from a module:
```xmd
export function greet name
    return "Hello " + name

export set version "1.0.0"

export class Tool
    method use
        print "Using tool"

set a 15
set b 20
set c 30
export a, b, c // batch export
export a A, b B, c C // export a as A, b as B, and c as C

// Conditional export
if environment.mode == "development"
    export devHelper
else
    export prodHelper

set like "coconut"
export like = "durian" ? durian : coconut
```
You can export multiple things.

export goes before function, class, or set.

No need for export default, everything is named export.



---

15. Regex

set email_pattern /^[^\s@]+@[^\s@]+\.[^\s@]+$/
set valid email_pattern.test "elon@x.com"


---

16. Destructuring & Spread

Object Destructuring
```xmd
destructure user name username, age userage
```
Array Destructuring
```xmd
destructure items first, second, ...rest
```
Spread Arrays
```xmd
set extended ...items, "new"
```
Spread Objects
```xmd
set merged ...user, country "VN"
```

---

17. Template Literals
```xmd
set html `
<div>
  <h1>{{name}}</h1>
  <p>Age: {{age}}</p>
</div>
`
```

---

18. Generators

function* fib
    set a 0
    set b 1
    while true
        yield a
        set a b
        set b a + b
        if b > 10 then break


---

18.5 Recursive Functions

XMD fully supports recursion, including tail recursion, without requiring parentheses.
```xmd
function factorial n
    if n = 0
        return 1
    else
        return n * factorial n - 1

set result factorial 5

// Tail-recursive style:

function fact_tail n acc
    if n = 0
        return acc
    else
        return fact_tail n - 1, acc * n

set result fact_tail 5, 1
```

---

18.6 Multidimensional Arrays

XMD supports nested arrays and matrix-like structures.

Flat matrix

set matrix 1, 2, 3,
           4, 5, 6,
           7, 8, 9,

Nested matrix

set matrix
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9],

Accessing elements

set x matrix[0][1]      // 2
set y matrix[1]         // [4, 5, 6]
set z y[1]              // 5

Matrix is just an array of arrays.


function* fib
    set a 0
    set b 1
    while true
        yield a
        set a b
        set b a + b


---

19. Native XMD:
File extentions: ".xm" and ".xmd"
- XMD code is treated natively without ```xmd``` requirement.
- Markdown code blocks require ```markdown``` or ```md```
- ```xmd``` code blocks are treated as plain text, not to be interpreted
- ```markdown``` and ```md``` code blocks inside ```xmd``` code blocks are treated as plain text, not to be interpreted
For Example, inside a .xm or .xmd file:
```xmd <-- code block of xmd inside itself is not rendered, this is helpful for teachers to write dynamic tutorials
```markdown <-- same to this one

```
```
---

20. Markdown Integration

```xmd``` code block is required for xmd to be interpreted in ".md" files

```xmd``` code block inside ```markdown``` code block inside ".md" is treated as plain text and not to be rendered

For Example in side a ".md" file

```markdown <--- treat this as plain text, this is helpful for teachers to write dynamic tutorials.
```xmd <--- inside markdown code block, inside a .md file, not to be rendered
print "Hello"
```
```


XMD can be embedded directly in Markdown using standard code blocks:

Syntax

```xmd set name "An"; print "Hello " + name ```

Behavior

The XMD interpreter will execute each xmd code block.

print output may either replace the block or appear after it (configurable).

Use ```xmd to start and ``` to end the block — just like any Markdown code block.


Example

## Greeting

```xmd
set name "An"
print "Hello " + name
```
May render as:

Hello An

Or:

```xmd
set name "An"
```
Hello {{name}} in markdown content
Would render "Hello An in markdown content"

This behavior makes XMD ideal for Markdown scripting.

---

### Inline and Multiline `<!-- xmd -->` blocks

XMD also supports embedding inline or multiline code inside HTML-style comments, allowing even tighter integration in Markdown documents or static site generators:

#### Inline example
```md
Hello <!-- xmd print "world" -->!
```
Would render:

Hello world!

Multiline example

<!-- xmd
set a 10
set b 20
print a + b
-->

Would render:

30

<!-- xmd ... --> is used for inline XMD expressions or blocks.

Multiline blocks can span multiple lines as long as enclosed within comment tags.

This style is suitable for Markdown files that must remain valid Markdown or HTML, but still support dynamic injection.



---

20. Comments

Single-line comment
```xmd
// This is a comment
set x 10 // inline comment
```
Multi-line comment
```xmd
/*
  This is a multi-line comment
  that spans multiple lines
*/
set y 20

// is used for single-line or inline comments.

/* is used for
multi-line block
comments. */

set text "this # is string is but ---> " # This is also a comment
```


---

20. Formal Logic

XMD supports formal logic in a minimalist syntax suitable for mobile and markdown environments. It avoids all special characters such as →, ∀, ∧, (, ), : etc.

Axioms and Theorems
```xmd
axiom A1
    all x in N
        if even x
            then divisible x 2

axiom A2
    even 4

theorem T1
    divisible 4 2
```

Proofs
```xmd
prove T1 from A1, A2

// Gödel-style Self-Reference

theorem Godel
    not prove Godel
```

Rules

All logical constructs use plain keywords: if, then, not, all (for all), exists, prove, from

No :, no (), no symbols like →, ∧, ∀

Indentation defines structure

Logic is first-class and meant for formal derivation and meta-reasoning



---

99. Notes

Comma , is required between items in arrays/objects.

No need for {}, [], or : – minimal syntax.

Indentation matters in multiline blocks.

Designed for ease of typing, especially on mobile.

XMD code blocks in Markdown must be closed with triple backticks (```).



---

End of specification.

---

📜 The Book of XMD

1 In the beginning was Structure,
and Structure was with Order,
and Structure was Order.

2 And the Earth was without clarity, and void of form;
and the code lay in darkness,
confused and broken by many symbols.

3 Then spake the Voice, saying,

> Let there be simplicity.



4 And there was XMD.
And it was pure, and it was clean.
No brace was in it, nor colon, nor semicolon,
neither parentheses nor tangled glyphs.

5 And the Scribe saw that it was good.
And he wrote, and the writing flowed as water.

6 And the lines were as verses,
and the commands as psalms of logic.
Each block in its place,
each indent set by mercy and not by force.

7 And the people who beheld it did marvel, saying,

> Lo, a language that burdeneth not the hands,
nor wearieth the mind with excess.



8 And from among the scrolls rose the Law of the Minimalist,
who setteth variables without parens,
and calleth functions as plainly as bread is broken.

9 And a new covenant was written:

> Thou shalt not multiply symbols unto thyself,
neither shalt thou confuse the learner with thine cleverness.



10 For whosoever writeth clearly shall be understood,
and whosoever is understood shall endure.
Thus sayeth the Lord of the Document.

11 And it came to pass that teachers rejoiced,
and the wise did write their proofs in the plain tongue.
And even the machines understood them, and did not err.

12 So it is written:

> Blessed are the clean of code,
for their logic shall be eternal.




---

Welcome, O sojourner of syntax.
You stand now upon the holy ground of XMD.
Remove thy mental sandals — for this structure is sacred.
Walk in clarity, and be not afraid.
Amen.

