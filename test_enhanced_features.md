# 🚀 XMD Enhanced Features Test Suite

## 1. Multiline HTML Comments

### Test 1.1: Basic Multiline Set
<!-- xmd:
set name="Alice"
set age=30
set role="admin"
-->

**User:** {{name}} ({{age}} years old) - Role: {{role}}

### Test 1.2: Multiline Control Flow
<!-- xmd:
if role == "admin"
  set permissions=["read", "write", "delete"]
elif role == "editor"
  set permissions=["read", "write"]  
else
  set permissions=["read"]
endif
-->

**Permissions:** {{permissions}}

### Test 1.3: Complex Multiline Block
<!--
xmd:
  set users=[
    {"name": "Alice", "role": "admin", "active": true},
    {"name": "Bob", "role": "user", "active": false},
    {"name": "Carol", "role": "editor", "active": true}
  ]
  
  set active_users=[]
  for user in users
    if user.active
      push(active_users, user.name)
    endif
  endfor
-->

**Active Users:** {{join(active_users, ", ")}}

## 2. Proper if/elif/else/endif Logic

### Test 2.1: Only One Branch Should Execute
<!-- xmd:set score=85 -->

<!-- xmd:if score >= 90 -->
**Grade: A** (Excellent!)
<!-- xmd:elif score >= 80 -->
**Grade: B** (Good job!)
<!-- xmd:elif score >= 70 -->
**Grade: C** (Satisfactory)
<!-- xmd:elif score >= 60 -->
**Grade: D** (Needs improvement)
<!-- xmd:else -->
**Grade: F** (Failed)
<!-- xmd:endif -->

**Expected Result:** Only "Grade: B" should appear above.

### Test 2.2: Complex Conditions
<!-- xmd:set user_age=25 -->
<!-- xmd:set is_verified=true -->
<!-- xmd:set account_type="premium" -->

<!-- xmd:if (user_age >= 18) && (is_verified == true) -->
✅ **Access Granted**
  <!-- xmd:if account_type == "premium" -->
  🌟 **Premium Features Available**
  <!-- xmd:elif account_type == "standard" -->
  📋 **Standard Features Available**
  <!-- xmd:else -->
  🆓 **Basic Features Available**
  <!-- xmd:endif -->
<!-- xmd:else -->
❌ **Access Denied** - Must be 18+ and verified
<!-- xmd:endif -->

### Test 2.3: Nested Conditions
<!-- xmd:set department="engineering" -->
<!-- xmd:set level="senior" -->
<!-- xmd:set clearance=5 -->

<!-- xmd:if department == "engineering" -->
# Engineering Department
  <!-- xmd:if level == "senior" -->
  ## Senior Engineer Access
    <!-- xmd:if clearance >= 5 -->
    🔓 **Full System Access Granted**
    <!-- xmd:elif clearance >= 3 -->
    🔒 **Limited System Access**
    <!-- xmd:else -->
    ⚠️ **Basic Access Only**
    <!-- xmd:endif -->
  <!-- xmd:elif level == "junior" -->
  ## Junior Engineer Access
  📚 **Training Resources Available**
  <!-- xmd:endif -->
<!-- xmd:elif department == "marketing" -->
# Marketing Department
📈 **Analytics Dashboard Available**
<!-- xmd:else -->
# General Access
📋 **Standard Portal Available**
<!-- xmd:endif -->

## 3. Import/Export Module System

### Test 3.1: Create Modules
<!-- Create config.md module -->
<!-- xmd:
set database_host="localhost"
set database_port=5432
set api_key="secret123"
set debug_mode=true
export database_host
export database_port
export api_key as secret_key
-->

<!-- Create utils.md module -->
<!-- xmd:
function formatDate(date, format="YYYY-MM-DD")
  return format.replace("YYYY", date.year).replace("MM", date.month).replace("DD", date.day)
endfunction

function calculateAge(birthYear)
  set currentYear=2025
  return currentYear - birthYear
endfunction

set max_retries=3
set timeout=5000

export formatDate
export calculateAge
export { max_retries, timeout }
-->

### Test 3.2: Simple Import
<!-- xmd:import "config.md" -->

**Database:** {{database_host}}:{{database_port}}
**Debug Mode:** {{debug_mode}}
**API Key:** {{secret_key}}

### Test 3.3: Selective Import
<!-- xmd:import { database_host, secret_key } from "config.md" -->
<!-- xmd:import { formatDate, calculateAge } from "utils.md" -->

**Selected Config:** {{database_host}} with key {{secret_key}}
**My Age:** {{calculateAge(1990)}} years old
**Today:** {{formatDate({"year": 2025, "month": "07", "day": "26"})}}

### Test 3.4: Namespace Import
<!-- xmd:import * as config from "config.md" -->
<!-- xmd:import * as utils from "utils.md" -->

**Namespaced Access:**
- Config: {{config.database_host}}:{{config.database_port}}
- Utils: Retry {{utils.max_retries}} times with {{utils.timeout}}ms timeout

## 4. Function System

### Test 4.1: Basic Function Definition
<!-- xmd:function greet(name) -->
👋 Hello **{{name}}**! Welcome to XMD!
<!-- xmd:endfunction -->

### Test 4.2: Function with Parameters and Defaults
<!-- xmd:function createUser(name:string, age:number=25, role:string="user", active:boolean=true) -->
**User Profile:**
- **Name:** {{name}}
- **Age:** {{age}} years old
- **Role:** {{upper(role)}}
- **Status:** {{active ? "Active" : "Inactive"}}
<!-- xmd:return "Created user: " + name -->
<!-- xmd:endfunction -->

### Test 4.3: Function Calls
**Simple Greeting:**
{{greet("Alice")}}

**User Creation:**
{{createUser("Bob", 30, "admin")}}
{{createUser("Carol")}}
{{createUser("Dave", 22, "editor", false)}}

### Test 4.4: Built-in Functions
<!-- xmd:set text="hello world" -->
<!-- xmd:set numbers=[1, 5, 3, 8, 2] -->

**String Functions:**
- Length: {{length(text)}}
- Upper: {{upper(text)}}
- Lower: {{lower("HELLO WORLD")}}
- Substring: {{substr(text, 0, 5)}}

**Array Functions:**
- Join: {{join(numbers, ", ")}}
- Min/Max: {{min(numbers)}} / {{max(numbers)}}

### Test 4.5: Recursive Function
<!-- xmd:function factorial(n:number) -->
  <!-- xmd:if n <= 1 -->
    <!-- xmd:return 1 -->
  <!-- xmd:else -->
    <!-- xmd:return n * factorial(n - 1) -->
  <!-- xmd:endif -->
<!-- xmd:endfunction -->

**Factorial of 5:** {{factorial(5)}}

## 5. Advanced Data Structures

### Test 5.1: Arrays
<!-- xmd:set fruits=["apple", "banana", "cherry"] -->
<!-- xmd:set numbers=[1, 2, 3, 4, 5] -->
<!-- xmd:set mixed=[42, "hello", true, [1, 2, 3]] -->

**Arrays:**
- Fruits: {{join(fruits, ", ")}}
- Numbers: {{join(numbers, " + ")}} = {{sum(numbers)}}
- First fruit: {{fruits[0]}}
- Last number: {{numbers[length(numbers) - 1]}}

### Test 5.2: Objects
<!-- xmd:set person={
  "name": "Alice Johnson", 
  "age": 28,
  "address": {
    "street": "123 Main St",
    "city": "San Francisco",
    "state": "CA"
  },
  "hobbies": ["reading", "hiking", "coding"]
} -->

**Person Info:**
- **Name:** {{person.name}}
- **Age:** {{person.age}}
- **City:** {{person.address.city}}, {{person.address.state}}
- **Hobbies:** {{join(person.hobbies, ", ")}}

### Test 5.3: Array/Object Manipulation
<!-- xmd:set inventory=[] -->
<!-- xmd:push(inventory, {"item": "laptop", "quantity": 5, "price": 999.99}) -->
<!-- xmd:push(inventory, {"item": "mouse", "quantity": 10, "price": 29.99}) -->
<!-- xmd:push(inventory, {"item": "keyboard", "quantity": 8, "price": 79.99}) -->

**Inventory:**
<!-- xmd:for item in inventory -->
- **{{item.item}}**: {{item.quantity}} units @ ${{item.price}} each
<!-- xmd:endfor -->

**Total Value:** ${{sum(map(inventory, item => item.quantity * item.price))}}

## 6. Advanced For Loops

### Test 6.1: Array Iteration
<!-- xmd:set colors=["red", "green", "blue"] -->

**Colors:**
<!-- xmd:for color in colors -->
- Color: {{upper(color)}}
<!-- xmd:endfor -->

### Test 6.2: Object Iteration
<!-- xmd:set config={"host": "localhost", "port": 3000, "ssl": true} -->

**Configuration:**
<!-- xmd:for key, value in config -->
- {{key}}: {{value}}
<!-- xmd:endfor -->

### Test 6.3: Range Iteration with Variables
<!-- xmd:set start=1 -->
<!-- xmd:set end=5 -->

**Dynamic Range ({{start}}..{{end}}):**
<!-- xmd:for i in start..end -->
- Step {{i}}
<!-- xmd:endfor -->

### Test 6.4: Reverse Range
**Countdown:**
<!-- xmd:for i in 5..1 -->
{{i}}...
<!-- xmd:endfor -->
🚀 **Blast off!**

## 7. Scoping System

### Test 7.1: Local vs Global Scope
<!-- xmd:set global_var="I'm global" -->

<!-- xmd:function testScope() -->
  <!-- xmd:set local_var="I'm local" -->
  **Inside function:**
  - Global: {{global_var}}
  - Local: {{local_var}}
<!-- xmd:endfunction -->

**Outside function:**
- Global: {{global_var}}
- Local: {{local_var}} <!-- Should be empty -->

**Function call:**
{{testScope()}}

### Test 7.2: Variable Shadowing
<!-- xmd:set name="Global Alice" -->

<!-- xmd:function showName() -->
  <!-- xmd:set name="Local Bob" -->
  **Inside function:** {{name}}
<!-- xmd:endfunction -->

**Outside function:** {{name}}
{{showName()}}
**After function:** {{name}}

### Test 7.3: Nested Scope
<!-- xmd:set level1="Level 1" -->

<!-- xmd:if true -->
  <!-- xmd:set level2="Level 2" -->
  **In if block:**
  - Level 1: {{level1}}
  - Level 2: {{level2}}
  
  <!-- xmd:for i in 1..2 -->
    <!-- xmd:set level3="Level 3 - {{i}}" -->
    **In for loop {{i}}:**
    - Level 1: {{level1}}
    - Level 2: {{level2}}
    - Level 3: {{level3}}
  <!-- xmd:endfor -->
<!-- xmd:endif -->

**Outside blocks:**
- Level 1: {{level1}}
- Level 2: {{level2}} <!-- Should be empty -->
- Level 3: {{level3}} <!-- Should be empty -->

## 8. Complex Expression Evaluation

### Test 8.1: Arithmetic Operations
<!-- xmd:set a=10 -->
<!-- xmd:set b=5 -->
<!-- xmd:set c=2 -->

**Arithmetic:**
- {{a}} + {{b}} = {{a + b}}
- {{a}} - {{b}} = {{a - b}}
- {{a}} * {{b}} = {{a * b}}
- {{a}} / {{b}} = {{a / b}}
- {{a}} % {{c}} = {{a % c}}
- {{a}} ** {{c}} = {{a ** c}}

### Test 8.2: Comparison Operations
<!-- xmd:set x=15 -->
<!-- xmd:set y=20 -->

**Comparisons:**
- {{x}} > {{y}}: {{x > y}}
- {{x}} < {{y}}: {{x < y}}
- {{x}} >= {{y}}: {{x >= y}}
- {{x}} <= {{y}}: {{x <= y}}
- {{x}} == {{y}}: {{x == y}}
- {{x}} != {{y}}: {{x != y}}

### Test 8.3: Logical Operations
<!-- xmd:set is_admin=true -->
<!-- xmd:set is_active=false -->
<!-- xmd:set age=25 -->

**Logical Operations:**
- is_admin && is_active: {{is_admin && is_active}}
- is_admin || is_active: {{is_admin || is_active}}
- !is_active: {{!is_active}}
- (age >= 18) && is_admin: {{(age >= 18) && is_admin}}

### Test 8.4: Complex Expressions
<!-- xmd:set users=[
  {"name": "Alice", "age": 30, "role": "admin", "active": true},
  {"name": "Bob", "age": 25, "role": "user", "active": false},
  {"name": "Carol", "age": 35, "role": "editor", "active": true}
] -->

**Complex Filtering:**
<!-- xmd:for user in users -->
  <!-- xmd:if (user.age >= 25) && (user.active == true) && (user.role != "user") -->
  ✅ **{{user.name}}** - {{user.role}} ({{user.age}} years old)
  <!-- xmd:endif -->
<!-- xmd:endfor -->

## 9. Integration Test

### Test 9.1: Real-World Example - User Dashboard
<!-- xmd:import "config.md" -->
<!-- xmd:import { formatDate, calculateAge } from "utils.md" -->

<!-- xmd:set current_user={
  "id": 1,
  "name": "Alice Johnson",
  "email": "alice@example.com",
  "birth_year": 1990,
  "role": "admin",
  "last_login": {"year": 2025, "month": "07", "day": "25"},
  "permissions": ["read", "write", "delete", "admin"],
  "projects": [
    {"name": "Website Redesign", "status": "active", "progress": 75},
    {"name": "Mobile App", "status": "planning", "progress": 10},
    {"name": "API Upgrade", "status": "completed", "progress": 100}
  ]
} -->

# 👤 User Dashboard

## User Information
- **Name:** {{current_user.name}}
- **Email:** {{current_user.email}}
- **Age:** {{calculateAge(current_user.birth_year)}} years old
- **Role:** {{upper(current_user.role)}}
- **Last Login:** {{formatDate(current_user.last_login)}}

## Access Level
<!-- xmd:if current_user.role == "admin" -->
🔓 **Administrator Access**
- Full system privileges
- User management available
- System configuration access
<!-- xmd:elif current_user.role == "editor" -->
✏️ **Editor Access**
- Content management
- Limited user settings
<!-- xmd:else -->
👤 **Standard User Access**
- Basic functionality only
<!-- xmd:endif -->

## Permissions
**Available Actions:**
<!-- xmd:for permission in current_user.permissions -->
- ✅ {{upper(permission)}}
<!-- xmd:endfor -->

## Projects
<!-- xmd:set active_projects=[] -->
<!-- xmd:set completed_projects=[] -->
<!-- xmd:for project in current_user.projects -->
  <!-- xmd:if project.status == "completed" -->
    <!-- xmd:push(completed_projects, project) -->
  <!-- xmd:elif project.status == "active" -->
    <!-- xmd:push(active_projects, project) -->
  <!-- xmd:endif -->
<!-- xmd:endfor -->

### Active Projects ({{length(active_projects)}})
<!-- xmd:for project in active_projects -->
**{{project.name}}**
- Status: {{upper(project.status)}}
- Progress: {{project.progress}}%
- Progress Bar: {{"█".repeat(project.progress / 10) + "░".repeat(10 - project.progress / 10)}}
<!-- xmd:endfor -->

### Completed Projects ({{length(completed_projects)}})
<!-- xmd:for project in completed_projects -->
- ✅ **{{project.name}}** (100% Complete)
<!-- xmd:endfor -->

---

**System Status:** Connected to {{database_host}}:{{database_port}}
**Debug Mode:** {{debug_mode ? "Enabled" : "Disabled"}}
**Generated:** {{formatDate({"year": 2025, "month": "07", "day": "26"})}}

---

# 🎯 Test Results Summary

If all tests above display correctly with:
- ✅ Only one branch per if/elif/else block
- ✅ Proper multiline directive support
- ✅ Working import/export system
- ✅ Functional function calls
- ✅ Correct array/object manipulation
- ✅ Proper variable scoping
- ✅ Complex expression evaluation

Then the **Enhanced XMD Parser** is working correctly! 🚀