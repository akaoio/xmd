# XMD Language Design Blueprint

## Overview
XMD is a mobile-first programming language designed for simplicity and power, optimized for typing on phone keyboards while being capable of complex computational tasks.

## Core Philosophy
- **Mobile-First**: Minimal special characters, natural language-like syntax
- **Powerful**: More expressive than JavaScript
- **Concise**: More compact than Python
- **Deep**: Type safety and memory control like Rust
- **Accessible**: As easy as Scratch for beginners
- **Scientific**: Capable of formal proofs and theorem verification
- **Smart**: Automatic type inference and variable declaration
- **Lazy-Friendly**: No keyboard layout switching, everything typeable with standard keys

## File Format Support

### Markdown Files (.md)
```markdown
<!-- xmd
set message "Hello World"
print message
-->

Regular markdown content here...

<!-- XMD
// Multi-line XMD blocks
function greet name
    print "Hello, {{name}}!"
greet "Alice"
-->
```

### XMD Files (.xmd)
```xmd
// Pure XMD code without wrapper
set title "My Document"

```markdown
# {{title}}
This is markdown content inside XMD file
```

```md
Another markdown block
```
```

## Evolution from Current XMD System

The language evolves to eliminate unnecessary punctuation:

### Syntax Evolution
```xmd
// Current XMD syntax
<!-- xmd: set name = "Alice" -->
<!-- xmd: exec echo "Hello, {{name}}" -->
<!-- xmd: for i in [1, 2, 3] -->

// Evolved XMD syntax - no equal signs, commas, or brackets needed
set name "Alice"
exec echo "Hello, {{name}}"
for i in 1 2 3
    print i

// Arrays without brackets or commas
set colors "red" "green" "blue"
set numbers 1 2 3 4 5
set range 1..10

// Function calls without parentheses
print "Hello world"
sqrt 16
max 10 20 30

// Object/map creation without brackets
set person
    name "Alice"
    age 30
    city "New York"
```

### Enhanced Directive Processing
```xmd
// Process XMD directives in strings
template = """
<!-- xmd: set title = "{{page_title}}" -->
# {{title}}
"""
result = xmd.process(template, {page_title: "Welcome"})

// Chain XMD files
pipeline = [
    "./preprocess.md",
    "./transform.md", 
    "./postprocess.md"
]
output = xmd.chain(pipeline, initial_data)
```

### URL Imports (Deno-style)

```xmd
// Import from CDN
import utils from "https://unpkg.com/xmd-utils@1.0.0/mod.xmd"
import { DateTime } from "https://cdn.skypack.dev/luxon"

// Import from GitHub
import config from "https://raw.githubusercontent.com/user/repo/main/config.xmd"

// Import with permissions (security)
import fs from "https://xmd.dev/std/fs/mod.xmd" 
    permissions ["read", "write:./output"]

// Import and cache
import data from "https://api.example.com/data.json"
    cache "1h"  // Cache for 1 hour

// Import XMD markdown templates from URL
template = await import("https://example.com/templates/report.md")
rendered = xmd.render(template, data)
```

### Data File Imports (JSON, YAML, CSV)

```xmd
// Import JSON files - auto-parsed into objects/arrays
import config from "./config.json"
import users from "https://api.example.com/users.json"
import package from "./package.json"

// Import YAML files - auto-parsed
import settings from "./settings.yaml" 
import docker from "./docker-compose.yml"
import ci from "./.github/workflows/ci.yaml"

// Import CSV - auto-parsed to array of objects
import data from "./data.csv"
    headers true  // First row as headers
    delimiter ","

// Import with type validation
import config from "./config.json" as ConfigType
import users from "./users.json" as Array<User>

// Dynamic imports
config = await import("./config.json")
settings = await import("./settings.yaml")

// Import and transform
import raw_data from "./data.json"
    transform json => json.users.filter(u => u.active)

// Multiple format support
data = match file_extension
    ".json" => import "./data.json"
    ".yaml" => import "./data.yaml"
    ".yml"  => import "./data.yml"
    ".csv"  => import "./data.csv"

// Pro syntax variations
config = require("./config.json")          // Node.js style
{users, settings} = import("./data.json")  // Destructuring
data := import!("./data.yaml")             // Must exist
```

### Security Model

```xmd
// Sandboxed execution by default
sandbox
    untrusted_code = import("https://unknown.com/script.xmd")
    result = untrusted_code.run()
    // Limited access to system resources

// Permission system
@permissions(network: ["example.com"], fs: ["read:./data"])
function fetch_and_save url
    data = http.get(url)
    file.write("./data/cache.json", data)

// Resource limits
@limits(memory: "100MB", timeout: "5s")
function process_data input
    // Function will be killed if limits exceeded
```

## Language Features

### 1. Variables and Types

```xmd
// Mobile/Natural syntax:
set name "Alice"              
set age 30                    
set active true               
set data null                 

// Pro/Hacker syntax:
name="Alice"
age=30
active=true
data=null

// Ultra-short declaration
name:"Alice", age:30, active:true  // Multiple declarations

// Type annotations - choose your style
set count Int 0          // Natural
count:Int=0             // TypeScript-like
Int count=0             // C-like
count∈ℤ=0               // Mathematical

// Smart type inference
result = 10+20          // Classic
result = add 10 20      // Natural
result = 10.add(20)     // OOP style

// Constants
const PI 3.14159        // Natural
PI=3.14159!            // Exclamation marks constant
π=3.14159              // Unicode allowed
```

### 2. Collections

```xmd
// Mobile/Natural syntax:
numbers 1 2 3 4 5
range 1..100            
stepped 0..100..2       

// Pro/Hacker syntax:
numbers=[1,2,3,4,5]
range=[1..100]
stepped=[0:100:2]

// Objects - multiple styles
// Natural/Mobile:
person
    name "Alice"
    age 30
    skills "coding" "design"

// Pro/JSON style:
person={name:"Alice", age:30, skills:["coding","design"]}

// Ruby/Swift style:
person={:name=>"Alice", :age=>30, :skills=>["coding","design"]}

// Sets
unique = {1,2,3,3,3}    // Mathematical set notation
unique = Set(1,2,3,3,3) // Function style
unique set 1 2 3 3 3    // Natural style

// Tuples
coords = (10,20)        // Classic
coords = 10,20          // Minimal
coords = ⟨10,20⟩        // Mathematical

// Array operations
a = [1,2,3] + [4,5,6]   // Concatenation
b = [1,2,3] * 3         // Repeat: [1,2,3,1,2,3,1,2,3]
c = arr[0:5]            // Slice
d = arr[-1]             // Last element
```

### 3. Functions

```xmd
// Natural/Mobile syntax:
function add a b
    return add a b

// Pro/Classic syntax:
fn add(a,b) = a+b           // Rust-like
add(a,b) => a+b            // Arrow function
λ(a,b).a+b                 // Lambda calculus
add = (a,b) -> a+b         // CoffeeScript
def add(a,b): a+b          // Python-like

// Type annotations - all styles work
function divide a Number b Number returns Float    // Natural
fn divide(a:Number, b:Number)->Float              // Rust-like
divide :: Number -> Number -> Float               // Haskell-like
divide(a:ℝ, b:ℝ):ℝ                              // Mathematical

// Default parameters
greet(name="World", excited=false)               // Classic
greet name:"World" excited:false                 // Ruby-like
greet{name?="World", excited?=false}            // Optional syntax

// Variable arguments
sum(...nums) = nums.reduce(+)                    // Spread operator
sum(*args) = sum(args)                           // Python-like
sum :: [Number] -> Number                        // Type signature

// One-liners and shortcuts
double = x => x*2                                // Arrow
double(x) = 2x                                   // Mathematical
double = (*2)                                    // Partial application
double = _.multiply(2)                           // Placeholder syntax

// Pattern matching functions
factorial(0) = 1                                 // Base case
factorial(n) = n * factorial(n-1)                // Recursive case

// Guards
abs(x) | x>=0 = x                               // When x is positive
abs(x) | x<0 = -x                               // When x is negative
```

### 4. Classes and Objects

```xmd
// Class definition
class Person
    // Properties with defaults
    name: String = "Unknown"
    age: Number = 0
    private id: String
    
    // Constructor
    constructor name age=0
        self.name = name
        self.age = age
        self.id = generate_uuid()
    
    // Methods
    greet
        return "Hi, I'm {{self.name}}"
    
    // Property getter/setter
    get birth_year
        return current_year() - self.age
    
    set birth_year year
        self.age = current_year() - year
    
    // Static methods
    static from_json data
        return Person(data.name, data.age)

// Inheritance
class Employee extends Person
    role: String
    salary: Number
    
    constructor name age role salary
        super(name, age)
        self.role = role
        self.salary = salary
    
    work
        print "{{self.name}} is working as {{self.role}}"

// Traits/Interfaces
trait Drawable
    draw canvas
    get_bounds -> Rectangle

// Multiple traits
class Circle implements Drawable, Serializable
    center: Point
    radius: Number
    
    draw canvas
        canvas.circle(self.center, self.radius)
    
    get_bounds
        return Rectangle(
            self.center.x - self.radius,
            self.center.y - self.radius,
            self.radius * 2,
            self.radius * 2
        )
```

### 5. Control Flow

```xmd
// If/Else without symbols
if age greater than or equal 18
    print "Adult"
else if age greater than or equal 13
    print "Teenager"
else
    print "Child"

// Pattern matching with words
match value
    when 0 then "Zero"
    when 1 to 10 then "Small"
    when 11 to 100 then "Medium"
    otherwise "Large"

// Advanced pattern matching
match person
    when name is "Alice" with any age then "Alice is {{age}}"
    when any name with age 30 then "{{name}} is thirty"
    when any name with age greater than 50 then "{{name}} is senior"
    otherwise "Unknown"

// Loops
for i in 1 to 10
    print i

while condition is true
    process

// Loop with index
for each item with index in array
    print "{{index}}: {{item}}"

// Break and continue
for n in numbers
    if n less than 0
        continue
    if n greater than 100
        break
    print n
```

### 6. Error Handling

```xmd
// Try/Catch
try
    result = risky_operation()
    print result
catch error
    print "Error: {{error}}"
finally
    cleanup()

// Result type (Rust-like)
function divide a b -> Result<Number, String>
    if b == 0
        return Err("Division by zero")
    return Ok(a / b)

// Using Result
match divide(10, 2)
    Ok(value) => print "Result: {{value}}"
    Err(msg) => print "Error: {{msg}}"

// Option type
function find_user id -> Option<User>
    user = database.get(id)
    if user
        return Some(user)
    return None

// Propagating errors
function calculate -> Result<Number, String>
    x = divide(10, 2)?  // ? operator propagates error
    y = divide(x, 3)?
    return Ok(y)
```

### 7. Async/Concurrent Programming

```xmd
// Async functions
async function fetch_data url
    response = await http.get(url)
    return response.json()

// Parallel execution
async function fetch_all urls
    tasks = urls.map(url => fetch_data(url))
    results = await Promise.all(tasks)
    return results

// Channels (Go-like)
channel = Channel<Number>()

// Producer
spawn
    for i in 1..10
        channel.send(i)
        sleep(100)
    channel.close()

// Consumer
spawn
    for value in channel
        print "Received: {{value}}"

// Actor model
actor Counter
    count = 0
    
    receive message
        match message
            Increment => self.count += 1
            Decrement => self.count -= 1
            Get => reply(self.count)
```

### 8. Modules and Imports

```xmd
// Import XMD modules
import math.{sqrt, pow}
import utils.{Logger, Config}

// Import from URLs
import server from "https://xmd.dev/std@1.0.0/http/server.xmd"
import { parse } from "https://xmd.dev/std@1.0.0/flags/mod.xmd"

// Import data files - automatically parsed
import config from "./config.json"
import settings from "./settings.yaml"
import database from "./database.yml"
import users from "./users.csv"

// Import with type checking
import api_config from "./api.json" as APIConfig
import user_list from "./users.json" as Array<User>

// Import from URLs with auto-detection
import remote_config from "https://api.example.com/config"  // Auto-detects JSON
import yaml_data from "https://raw.githubusercontent.com/user/repo/main/data.yaml"

// Dynamic imports
module = await import("https://cdn.example.com/module.xmd")
config = await import("./config.json")

// Import with transformations
import users from "./users.json"
    filter active
    map name, email
    sort by name

// Glob imports
import tests from "./tests/*.json" as TestSuite[]
import configs from "./config/*.{json,yaml,yml}" as ConfigMap

// Import and merge
import base from "./base.yaml"
import overrides from "./overrides.json"
config = {...base, ...overrides}

// Pro syntax variations
const {db, api} = require("./config.json")     // Node.js style
users := import!("./users.json")               // Must exist
data ?= import("./optional.json")              // Optional import

// Export data
export config = {
    name: "MyApp",
    version: "1.0.0",
    settings: import("./settings.yaml")
}

// Re-export
export * from "./config.json"
export {users, admins} from "./users.json"
```

### 9. Metaprogramming and Macros

```xmd
// Macros
macro repeat times body
    for _ in 1..times
        body

// Usage
repeat 3
    print "Hello!"

// Compile-time function
const function factorial n
    if n <= 1
        return 1
    return n * factorial(n - 1)

// Compile-time evaluation
const LOOKUP_TABLE = [factorial(i) for i in 0..10]

// Attributes/Decorators
@memoize
function expensive_calculation x
    // ...

@serialize
class Data
    // ...
```

### 10. Memory Management

```xmd
// Automatic reference counting by default
obj = LargeObject()
// obj automatically freed when out of scope

// Manual memory management (optional)
unsafe
    ptr = alloc(1024)
    write(ptr, data)
    free(ptr)

// Ownership (Rust-like)
function transfer_ownership data: owned MyData
    // data is moved, not copied
    return process(data)

// Borrowing
function borrow_data data: &MyData
    // data is borrowed, read-only
    print data.value

function borrow_mut data: &mut MyData
    // data is borrowed, mutable
    data.value += 1
```

### 11. Type System

```xmd
// Generic types
class Container<T>
    items: Array<T> = []
    
    add item: T
        self.items.push(item)
    
    get index -> Option<T>
        if index < self.items.length
            return Some(self.items[index])
        return None

// Type constraints
function sort<T: Comparable> items: Array<T>
    // T must implement Comparable trait

// Union types
type StringOrNumber = String | Number

// Type aliases
type Point2D = {x: Number, y: Number}
type Vector3D = {x: Number, y: Number, z: Number}

// Enum types
enum Color
    Red
    Green
    Blue
    RGB(r: Int, g: Int, b: Int)

// Algebraic data types
type Tree<T>
    = Leaf(value: T)
    | Branch(left: Tree<T>, right: Tree<T>)
```

### 12. Scientific Computing

```xmd
// Mathematical notation
 = sum
 = product
 = sqrt
 = Infinity

// Matrix operations
A = [[1, 2], [3, 4]]
B = [[5, 6], [7, 8]]
C = A @ B  // Matrix multiplication

// Symbolic math
symbolic x y z
equation = x� + 2*x*y + y� == z�
solution = solve(equation, x)

// Theorem proving
theorem pythagorean a b c
    requires a > 0, b > 0, c > 0
    proves a� + b� == c�
    
    // Proof steps
    step1 = a� + b�
    step2 = (step1)�
    step3 = step2 == c�
    qed

// Formal verification
verify function is_sorted arr
    ensures  i in 0..arr.length-1: arr[i] <= arr[i+1]
```

### 13. DSL Support

```xmd
// Define custom DSL
dsl sql
    SELECT * FROM users WHERE age > 18

// Use in code
query = sql`
    SELECT name, email 
    FROM users 
    WHERE active = true
`
results = database.execute(query)

// GraphQL DSL
query = graphql`
    query GetUser($id: ID!) {
        user(id: $id) {
            name
            email
            posts {
                title
                content
            }
        }
    }
`
```

### 14. Mobile-Optimized Features

```xmd
// Voice input hints
@voice("set timer for five minutes")
function set_timer duration
    // ...

// Gesture shortcuts
@gesture(swipe_right)
function next_page
    // ...

// Auto-completion hints
name = input("Enter your name")  // Shows keyboard with name suggestions
email = input.email("Email")     // Shows email keyboard
number = input.number("Age")     // Shows number pad
```

## Standard Library

### File I/O and Serialization

```xmd
// Read files - multiple styles
content = read "data.txt"                    // Natural
content = file.read("data.txt")             // OOP
content = readFile("data.txt")              // Camel case
content = fs.readFileSync("data.txt")       // Node.js style

// Write files
write "output.txt" with content             // Natural
file.write("output.txt", content)           // OOP
writeFile("output.txt", content)            // Function

// Append to file
append "log.txt" with message
file.append("log.txt", message)

// JSON serialization/deserialization
// Serialize to JSON
json_string = to_json data                   // Natural
json_string = JSON.stringify(data)          // JavaScript style
json_string = json.dumps(data)              // Python style
json_string = serialize data to json        // Verbose

// Deserialize from JSON
data = from_json json_string                // Natural
data = JSON.parse(json_string)             // JavaScript style
data = json.loads(json_string)             // Python style
data = deserialize json_string from json   // Verbose

// YAML serialization/deserialization
yaml_string = to_yaml data
yaml_string = YAML.dump(data)
yaml_string = serialize data to yaml

data = from_yaml yaml_string
data = YAML.load(yaml_string)
data = deserialize yaml_string from yaml

// File operations with auto-serialization
// Save object as JSON
save data to "config.json"                  // Auto-detects format
save data to "config.json" as json
file.save_json("config.json", data)

// Save object as YAML
save settings to "settings.yaml"
save settings to "settings.yml" as yaml
file.save_yaml("settings.yaml", settings)

// Load with auto-detection
data = load from "config.json"             // Auto-parses JSON
settings = load from "settings.yaml"       // Auto-parses YAML

// CSV operations
save users to "users.csv" with headers
data = load from "data.csv" as array

// Binary files
bytes = read binary from "image.png"
write binary to "output.bin" with bytes

// Stream operations
stream = open "large.txt" for reading
for line in stream.lines()
    process line
stream.close()

// Async file operations
content = await read async from "data.txt"
await write async to "output.txt" with content

// File utilities
if file exists "config.json"
    config = load from "config.json"

size = file size of "data.txt"
modified = file modified time of "data.txt"
delete file "temp.txt"
rename file "old.txt" to "new.txt"
copy file "source.txt" to "dest.txt"

// Directory operations
files = list files in "./data"
create directory "./output"
delete directory "./temp" recursively

// Pro shortcuts
data = <"config.json"                      // Read operator
>"output.json" data                        // Write operator
>>"log.txt" message                        // Append operator
```

### Network and HTTP

```xmd
// HTTP requests
response = http.get("https://api.example.com/data")
data = response.json()

// POST with JSON
response = http.post("https://api.example.com/users", {
    name: "Alice",
    email: "alice@example.com"
})

// With headers
response = http.get(url, headers: {
    "Authorization": "Bearer " + token
})
```

### Database

```xmd
// Database connections
db = Database("sqlite:myapp.db")
db = Database("postgres://user:pass@localhost/mydb")

// Queries
users = db.query("SELECT * FROM users WHERE active = ?", true)
db.execute("INSERT INTO logs (message) VALUES (?)", message)

// ORM-style
user = db.users.find(id: 123)
users = db.users.where(active: true).limit(10)
```

### Other Utilities

```xmd
// Date/Time
now = DateTime.now()
tomorrow = now.add(days: 1)
formatted = now.format("YYYY-MM-DD")

// Crypto
hash = sha256 of "data"
hash = crypto.sha256("data")
encrypted = encrypt data with key using "AES"

// Regular expressions
matches = regex.match(pattern, text)
result = text.replace(regex: pattern, with: replacement)

// UUID generation
id = generate uuid
id = UUID.v4()
```

## Transpilation

```xmd
// Command line
xmd transpile input.md output.xmd
xmd transpile input.xmd output.md

// In code
transpiled = xmd.transpile(source, target_format)
```

## Examples

### Example 1: Todo App
```xmd
class Todo
    id generate_id
    text String
    completed false
    created_at now
    
    constructor text
        self text is text
    
    toggle
        self completed is not self completed

todos empty list

function add_todo text
    todo new Todo with text
    add todo to todos
    save_todos

function save_todos
    write "todos.json" with json of todos

function load_todos
    if file exists "todos.json"
        data read from "todos.json"
        todos parse json data then map each t to new Todo with t text
```

### Example 2: Mathematical Proof
```xmd
theorem fermat_little a p
    requires is_prime(p), gcd(a, p) == 1
    proves a^(p-1) a 1 (mod p)
    
    // Proof by induction
    base_case = verify(1^(p-1) a 1 (mod p))
    
    inductive_step =  k: 
        assume k^(p-1) a 1 (mod p)
        prove (k+1)^(p-1) a 1 (mod p)
    
    qed
```

### Example 3: Web Server
```xmd
server = WebServer(port: 8080)

server.route "GET" "/"
    return html`
        <h1>Welcome to XMD Server</h1>
        <p>Current time: {{now()}}</p>
    `

server.route "GET" "/api/users"
    users = db.query("SELECT * FROM users")
    return json(users)

server.route "POST" "/api/users"
    data = request.json()
    user = User(data.name, data.email)
    db.insert("users", user)
    return json({success: true, id: user.id})

server.start()
print "Server running on http://localhost:8080"
```

### Example 4: URL Import Example
```xmd
// Import XMD utilities from CDN
import { DateTime, Duration } from "https://xmd.dev/lib/datetime@1.0.0/mod.xmd"
import { http } from "https://xmd.dev/std/http@1.0.0/mod.xmd"

// Import XMD template from GitHub
import template from "https://raw.githubusercontent.com/xmd-lang/templates/main/report.md"

// Import JSON data with caching
import prices from "https://api.coinbase.com/v2/prices/BTC-USD/spot"
    cache "5m"  // Cache for 5 minutes

// Import another XMD module
import { Chart, Table } from "https://xmd.dev/lib/visualization@2.1.0/mod.xmd"

// Use imported modules
async function generate_report
    // Use XMD DateTime
    today = DateTime.now().format("yyyy-MM-dd")
    
    // Fetch additional data using XMD http module
    response = await http.get("https://api.example.com/data")
    
    // Create chart
    chart = Chart.line(response.data.values)
    
    // Process template with data
    report = xmd.render(template, {
        date: today,
        price: prices.data.amount,
        chart: chart.to_svg(),
        data: response.data
    })
    
    return report

// Import and execute XMD directives from URL
exec import("https://example.com/scripts/data-processor.md")
```

### Example 5: Mobile App with Gestures
```xmd
// Import UI framework optimized for mobile
import { App, View, Text } from "https://xmd.dev/ui/mobile"

app = App("My Mobile App")

@gesture(swipe_up)
function refresh_data
    data = await fetch_latest()
    app.update(data)

@voice("show me the chart")
function show_chart
    app.navigate("/chart")

// Natural language input
@input(type: "voice", hints: ["add task", "remove task", "show all"])
function handle_command command
    match parse_intent(command)
        AddTask(text) => tasks.add(text)
        RemoveTask(id) => tasks.remove(id)
        ShowAll => app.show_all_tasks()

app.run()
```

### Example 6: Working with JSON/YAML Data
```xmd
// Import configuration files
import db_config from "./database.yaml"
import api_keys from "./secrets.json"
import translations from "./i18n/en.json"

// Use imported YAML config
db = Database(
    host: db_config.database.host,
    port: db_config.database.port,
    user: db_config.database.credentials.username,
    pass: api_keys.database_password  // From JSON
)

// Read, modify, and save config
config = load from "config.json"
config.last_updated = DateTime.now()
config.version += 1
save config to "config.json"

// Create new YAML config
new_config = {
    app: {
        name: "MyApp",
        version: "2.0.0",
        features: ["auth", "api", "ui"]
    },
    database: {
        host: "localhost",
        port: 5432
    }
}
save new_config to "app.yaml"

// Bulk process JSON files
for file in list files in "./data/*.json"
    data = load from file
    data.processed = true
    data.timestamp = now()
    
    // Save with backup
    backup_name = file.replace(".json", ".backup.json")
    copy file to backup_name
    save data to file

// Log serialization
log_entry = {
    timestamp: DateTime.now(),
    level: "INFO",
    message: "User logged in",
    user_id: 123
}
append to_json(log_entry) + "\n" to "app.log"

// Read and parse logs
logs = read("app.log")
    .split("\n")
    .filter(line => line.length > 0)
    .map(line => from_json(line))

// CSV export
users = db.query("SELECT * FROM users")
csv_content = users.map(u => 
    [u.id, u.name, u.email, u.created_at].join(",")
).join("\n")
write "users.csv" with "id,name,email,created_at\n" + csv_content

// Configuration migration
if file exists "config.json"
    old_config = load from "config.json"
    new_config = migrate_config(old_config)
    save new_config to "config.yaml"
    delete file "config.json"
    print "Migrated config from JSON to YAML"

// Template processing
template = read "email_template.html"
data = {
    user_name: "Alice",
    order_id: "12345",
    items: load from "order_items.json"
}
rendered = template.render(data)
write "email_output.html" with rendered

// API response caching
cache_file = "cache/api_{{endpoint}}.json"
if file exists cache_file and file age of cache_file < 3600
    data = load from cache_file
else
    data = http.get("https://api.example.com/{{endpoint}}").json()
    save data to cache_file
```

## Leveraging Current XMD Features

The new language extends the existing XMD system:

```xmd
// Use current exec functionality
result = exec("ls -la")
output = exec("git status")

// Enhanced exec with structured output
files = exec("ls -la").parse_table()
for file in files
    print "{{file.name}}: {{file.size}}"

// Current variable substitution enhanced
name = "World"
message = "Hello, {{name}}!"  // Current XMD style
formatted = f"Hello, {name}!"  // Python-style alternative

// Build on current for loops
<!-- xmd: for item in ["a", "b", "c"] -->
    {{item}}
<!-- xmd: endfor -->

// New syntax sugar
for item in ["a", "b", "c"]
    print item

// Current if/else enhanced
<!-- xmd: if condition -->
    <!-- xmd: set result = "yes" -->
<!-- xmd: else -->
    <!-- xmd: set result = "no" -->
<!-- xmd: endif -->

// New cleaner syntax
result = if condition then "yes" else "no"
```

## Future Considerations

1. **IDE Support**: Auto-completion, syntax highlighting, refactoring tools
2. **Package Manager**: `xmd install package_name`
3. **REPL**: Interactive XMD shell
4. **Compilation Targets**: JavaScript, WebAssembly, Native
5. **Mobile IDE**: Touch-optimized editor with gesture support
6. **Voice Programming**: Natural language to XMD code
7. **Visual Programming**: Block-based mode for beginners
8. **Formal Verification**: Built-in proof assistant
9. **Quantum Computing**: Quantum circuit DSL
10. **AR/VR Support**: 3D programming environment
11. **URL Package Registry**: Central registry for XMD modules
12. **Hot Module Reloading**: Live code updates from URLs

## Dual Syntax Philosophy: Mobile-First + Pro Shorthands

```xmd
// BOTH minimal AND shorthand syntax supported
// Mobile/Voice syntax:
set x 10
set arr 1 2 3
for i in arr
    print "Value: " i

// Pro/Hacker shorthand (same code):
x=10
arr=[1,2,3]
for i∈arr
    print("Value: "+i)

// All operators have BOTH forms:
x equals 10           // x == 10 or x=10
x not equals 10       // x != 10 or x≠10
x greater than 10     // x > 10
x less than or equal 10  // x <= 10 or x≤10

// Logical operations - pick your style
if x greater than 5 and y less than 10    // Mobile
if x>5 && y<10                            // Classic
if x>5 ∧ y<10                             // Mathematical

// Mathematical notation - ALL forms work
forall x in set       // ∀x∈set or all x in set
exists x where p      // ∃x:p or some x where p
sum of array          // Σarray or sum(array) or array.sum()
product of array      // Πarray or prod(array)
sqrt of 16            // √16 or sqrt(16) or 16^0.5
x to the power of 2   // x² or x^2 or x**2 or pow(x,2)

// Pro shortcuts
x++ // increment x or x+=1 or x=x+1
y-- // decrement y
z*=2 // z=z*2
a/=b // a=a/b

// Lambda shortcuts
arr.map(x=>x*2)  // Classic arrow
arr.map{x->x*2}  // Kotlin style
arr.map(λx.x*2)  // Mathematical
arr map each x to x times 2  // Natural language

// Ternary and conditionals
result = age>=18 ? "adult" : "minor"  // Classic
result = if age≥18 then "adult" else "minor"  // Functional
result if age greater than or equal 18 then "adult" else "minor"  // Natural

// Array/List comprehensions
[x*2 for x in 1..10]  // Python style
[x*2 | x←[1..10]]     // Haskell style
[1..10].map(x=>x*2)   // JavaScript style
```

## Pro Hacker Shortcuts

```xmd
// Chain operations without intermediate variables
[1..100]
  |> filter(isPrime)      // Pipe operator
  |> map(x => x²)         
  |> reduce(+)
  |> println

// Same in different styles:
[1..100].filter(isPrime).map(x=>x²).reduce(+).println()  // Dot chaining
println $ reduce (+) $ map (^2) $ filter isPrime [1..100]  // Haskell $
[1..100] >>= filter(isPrime) >>= map(sqr) >>= sum        // Monadic bind

// Destructuring
{name, age, city:"location"} = person  // Rename city to location
[head, ...tail] = list                  // First and rest
[a,b,c,...,x,y,z] = array              // First 3 and last 3

// Multiple assignment
a,b = b,a                               // Swap
x,y,z = 1,2,3                          // Multiple assign
{sin:s, cos:c} = trig(angle)          // Named returns

// Operator sections
add5 = (+5)                            // Partial application
halve = (/2)                           
isPositive = (>0)

// Custom operators
infix ∘ = compose                      // f∘g means compose(f,g)
infix × = cross_product
infix ⊗ = tensor_product

// Unicode operators for math
A × B                                  // Cross product
A ⊗ B                                  // Tensor product  
A ∩ B                                  // Intersection
A ∪ B                                  // Union
x ∈ S                                  // Element of
∅                                      // Empty set
```

## Design Principles

1. **Minimal Punctuation**: Reduce special characters for mobile typing
2. **Natural Language**: Read like English where possible
3. **Smart Defaults**: Sensible behavior without configuration
4. **Progressive Disclosure**: Simple things simple, complex things possible
5. **Error Prevention**: Catch mistakes at compile time
6. **Performance**: Zero-cost abstractions where possible
7. **Interoperability**: Easy integration with existing code
8. **Documentation**: Self-documenting code style
9. **Testing**: Built-in test framework
10. **Security**: Safe by default, explicit unsafe blocks
11. **No Special Keyboards**: Everything works with standard QWERTY
12. **Voice-Friendly**: Syntax that's easy to dictate
13. **Multi-Paradigm**: Supports functional, OOP, and procedural styles
14. **Power User Features**: Full unicode, custom operators, advanced shortcuts
15. **Don't Reinvent the Wheel**: Leverage existing C libraries (json-c, libyaml, etc.)

## Implementation Strategy - Leverage Existing Libraries

### Core Libraries to Use

```xmd
// JSON handling - use json-c or cJSON
#include <json-c/json.h>
// Wrapper for XMD natural syntax
function to_json data
    return json_object_to_json_string(data)

// YAML handling - use libyaml
#include <yaml.h>
// Wrapper for XMD natural syntax  
function to_yaml data
    return yaml_emit_document(data)

// HTTP - use libcurl
#include <curl/curl.h>
// Wrapper for XMD syntax
function http.get url
    return curl_easy_perform(url)

// Regular expressions - use PCRE2
#include <pcre2.h>
// Wrapper for natural syntax
function match pattern in text
    return pcre2_match(pattern, text)

// SQLite - use sqlite3
#include <sqlite3.h>
// Wrapper for XMD syntax
function db.query sql params
    return sqlite3_exec(db, sql, params)

// Crypto - use OpenSSL/LibreSSL
#include <openssl/sha.h>
// Wrapper for natural syntax
function sha256 of data
    return SHA256(data)

// Date/Time - use standard C time functions
#include <time.h>
// Enhanced with natural syntax wrappers

// File operations - use standard C stdio
#include <stdio.h>
// Wrapped with XMD natural syntax
```

### Integration Approach

1. **Thin Wrappers**: Create thin wrapper functions around existing libraries
2. **Natural Syntax**: Map XMD's natural language syntax to library calls
3. **Error Handling**: Consistent error handling across all wrapped libraries
4. **Memory Management**: Ensure proper cleanup of library resources
5. **Type Conversion**: Convert between XMD types and C library types

### Example Implementation

```c
// src/json/to_json/to_json.c
#include <json-c/json.h>
#include "../../../include/xmd_types.h"

/**
 * @brief Convert XMD value to JSON string
 * @param value XMD value to serialize
 * @return JSON string (caller must free)
 */
char* to_json(xmd_value* value) {
    json_object* obj = xmd_to_json_object(value);
    const char* json_str = json_object_to_json_string_ext(obj, 
        JSON_C_TO_STRING_PRETTY);
    char* result = strdup(json_str);
    json_object_put(obj);
    return result;
}
```

### Benefits

1. **Proven Code**: Use battle-tested libraries
2. **Performance**: Optimized C libraries
3. **Maintenance**: Bug fixes from upstream
4. **Focus**: Concentrate on XMD language features
5. **Compatibility**: Industry-standard formats

## Development Principles
1. IMPORTANT: One file per folder
2. IMPORTANT: One function per file
3. IMPORTANT: File / folder naming: grand_parent/parent/<snake_case>/<snake_case>.c (folder name = file name = function name)
4. Test driven: write the full test for the whole desired system first -> write logic code for system later
5. Maximum line of code per file: 200 lines
6. Reusable logic: no duplicated code
7. Real implementation: no mock, no "simplified", no "TODO", no tech debts
8. Write note before working: docs/notes/<YYYYMMDD-HHMM-topic>.md -> no more than 100 lines
9. Leverage existing C libraries: json-c, libyaml, libcurl, sqlite3, etc.
10. Always comment code in Doxygen compatible style with metas @brief, @struct, @param, @return etc...
11. Always update docs, and update tests, before implementation -> first steps of any plan.
12. Planning before any implementation: docs/plans/<YYYYMMDD-HHMM-plan>/<phase>/phase-instructions.md -> each plan has phases separated into each folder with short comprehensive doc.
13. Error handling: all functions must return meaningful error codes and handle edge cases
14. Memory management: always free allocated memory, check for null pointers
15. Use CMake -> auto generate Makefile -> do not manually edit Makefile
16. All build artifacts in build/
17. All official tests must be in test/ (not sandbox, not trash test, not temporary test)
18. All temporary tests must be in sandbox/ (not official test, will be deleted without announcements)