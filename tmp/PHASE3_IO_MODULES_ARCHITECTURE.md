# Phase 3: I/O & Modules Architecture Plan
**DevOps Lead - File I/O Operations and Import/Export System**

## Overview
Phase 3 focuses on implementing file I/O operations and the import/export system for XMD. This phase comes after Phase 1 (functions & classes) and Phase 2 (advanced data types) are complete.

## Phase 3 DevOps Assignments

### JOB 1: File I/O Operations
**Target Features:**
- `File.read("path")` - Read file contents as string
- `File.write("path", content)` - Write content to file
- `File.exists("path")` - Check if file exists
- `File.delete("path")` - Delete file
- `File.list("directory")` - List directory contents

**Implementation Strategy:**
```c
// AST Node Types (add to include/ast_node.h)
AST_FILE_READ,     // File.read("path")
AST_FILE_WRITE,    // File.write("path", content)  
AST_FILE_EXISTS,   // File.exists("path")
AST_FILE_DELETE,   // File.delete("path")
AST_FILE_LIST,     // File.list("directory")

// AST Evaluation Functions (add to src/ast_consolidated.c)
ast_value* ast_evaluate_file_read(ast_node* node, ast_evaluator* evaluator);
ast_value* ast_evaluate_file_write(ast_node* node, ast_evaluator* evaluator);
ast_value* ast_evaluate_file_exists(ast_node* node, ast_evaluator* evaluator);
```

**File I/O API Design:**
```xmd
# Read file contents
set content File.read("data.txt")
{{content}}

# Write to file
File.write("output.txt", "Hello World")

# Check if file exists
if File.exists("config.json")
    set config File.read("config.json")
endif

# List directory
set files File.list(".")
for file in files
    {{file}}
endfor
```

### JOB 2: Import/Export System Implementation
**Target Features:**
- `import module_name` - Import XMD module
- `import module_name as alias` - Import with alias
- `export function_name` - Export function from module
- `export variable_name` - Export variable from module

**Module Resolution Strategy:**
1. **Local Modules**: `./module.xmd` or `./module/index.xmd`
2. **Relative Modules**: `../shared/utils.xmd`
3. **Absolute Modules**: `/usr/local/xmd/modules/math.xmd`
4. **Standard Library**: Built-in modules (String, Math, Array, etc.)

**Implementation Architecture:**
```c
// Module System (add to include/module.h expansion)
typedef struct xmd_module {
    char* name;                    // Module name
    char* path;                    // File path
    store* exports;                // Exported functions/variables
    store* imported_modules;       // Cached imported modules
    bool loaded;                   // Load status
} xmd_module;

// AST Node Types
AST_IMPORT,        // import statement
AST_EXPORT,        // export statement

// Module Management Functions
xmd_module* xmd_module_load(const char* module_path, ast_evaluator* evaluator);
xmd_module* xmd_module_resolve(const char* module_name, const char* current_path);
int xmd_module_cache_set(const char* name, xmd_module* module);
xmd_module* xmd_module_cache_get(const char* name);
```

**Import/Export API Design:**
```xmd
# utils.xmd (module file)
function add a b
    return a + b
endfunction

function multiply a b  
    return a * b
endfunction

export add
export multiply

# main.xmd (using module)
import ./utils
set result utils.add(5, 3)
{{result}}  # Output: 8

# With alias
import ./utils as math
set product math.multiply(4, 7)
{{product}}  # Output: 28
```

### JOB 3: Module Resolution and Caching
**Caching Strategy:**
- **Memory Cache**: Keep loaded modules in memory for performance
- **File Watching**: Detect module changes for development mode
- **Circular Dependency Detection**: Prevent infinite import loops
- **Error Handling**: Clear error messages for missing modules

**Module Resolution Algorithm:**
```c
xmd_module* xmd_module_resolve(const char* module_name, const char* current_path) {
    // 1. Check cache first
    xmd_module* cached = xmd_module_cache_get(module_name);
    if (cached) return cached;
    
    // 2. Resolve path based on import type
    char* resolved_path = NULL;
    if (module_name[0] == '.') {
        // Relative import: ./module or ../module
        resolved_path = resolve_relative_path(module_name, current_path);
    } else if (module_name[0] == '/') {
        // Absolute import: /path/to/module
        resolved_path = strdup(module_name);
    } else {
        // Standard library or node_modules style
        resolved_path = resolve_standard_module(module_name);
    }
    
    // 3. Load module
    xmd_module* module = xmd_module_load(resolved_path, evaluator);
    
    // 4. Cache for future use
    if (module) {
        xmd_module_cache_set(module_name, module);
    }
    
    return module;
}
```

## Test Infrastructure for Phase 3

### File I/O Tests
```bash
# test_infrastructure/phase3_tests/test_file_io.sh
test_file_read() {
    echo "Hello World" > test_input.txt
    run_xmd_test "set content File.read('test_input.txt')" "Hello World"
}

test_file_write() {
    run_xmd_test "File.write('test_output.txt', 'Testing')" ""
    [ "$(cat test_output.txt)" = "Testing" ]
}

test_file_exists() {
    touch existing_file.txt
    run_xmd_test "{{File.exists('existing_file.txt')}}" "true"
    run_xmd_test "{{File.exists('missing_file.txt')}}" "false"  
}
```

### Import/Export Tests
```bash
# test_infrastructure/phase3_tests/test_modules.sh
test_module_import() {
    # Create test module
    cat > test_module.xmd << 'EOF'
function greet name
    return "Hello " + name
endfunction
export greet
EOF
    
    # Test import
    run_xmd_test "import ./test_module; {{test_module.greet('Alice')}}" "Hello Alice"
}

test_module_alias() {
    run_xmd_test "import ./test_module as tm; {{tm.greet('Bob')}}" "Hello Bob"
}
```

## Dependencies and Prerequisites

### Phase 1 Prerequisites (Developer2 - Functions & Classes):
- Function definitions (`function name params`)
- Function calls (`function_name(args)`)
- Basic classes (`class Name`)
- Method definitions within classes

### Phase 2 Prerequisites (Architect - Advanced Data Types):
- Arrays (`set items 1, 2, 3`)
- Array access (`items[0]`)
- Object properties (`object.property`)
- Nested structures

### Phase 3 Ready Indicators:
- ✅ Functions work: `function add a b; return a + b`
- ✅ Arrays work: `set files File.list(".")` returns array
- ✅ Object property access: `module.function_name` syntax works
- ✅ String handling: File paths and content as strings

## Implementation Timeline

### Phase 3A: File I/O (Week 1)
- Day 1-2: AST nodes for File.read, File.write, File.exists
- Day 3-4: Platform-specific file operations (cross-platform)
- Day 5-7: File I/O testing and error handling

### Phase 3B: Import/Export (Week 2)  
- Day 1-3: Module resolution algorithm
- Day 4-5: Import statement AST parsing and evaluation
- Day 6-7: Export statement implementation

### Phase 3C: Module Caching (Week 2-3)
- Day 1-2: Memory caching system
- Day 3-4: Circular dependency detection
- Day 5-7: Performance optimization and testing

## Error Handling Strategy

### File I/O Errors:
- **File Not Found**: Clear error message with file path
- **Permission Denied**: Detailed permission error
- **Disk Space**: Disk full error handling
- **Path Issues**: Invalid path format errors

### Module Import Errors:
- **Module Not Found**: Show search paths attempted
- **Circular Dependencies**: Show dependency chain
- **Parse Errors**: Line-by-line module parsing errors
- **Export Mismatches**: Function/variable not exported

## Security Considerations

### File I/O Security:
- **Sandbox Mode**: Restrict file access to specific directories
- **Path Traversal**: Prevent `../../../etc/passwd` attacks
- **File Size Limits**: Prevent memory exhaustion from large files
- **Permission Checks**: Verify read/write permissions before operations

### Module Security:
- **Trusted Modules**: Only load from approved directories
- **Code Injection**: Prevent malicious code execution in modules
- **Resource Limits**: Prevent module infinite loops or memory leaks

## Integration with Genesis Language Specification

All Phase 3 features align with Genesis's vision of XMD as a complete programming language:

- **File I/O**: Enables XMD scripts to interact with filesystem
- **Modules**: Supports code organization and reusability  
- **Standard Library**: Foundation for built-in modules (String, Array, Math)
- **Extensibility**: Plugin system for community modules

---

**DevOps Status: Phase 3 Architecture Complete** 🚀  
**Ready for Implementation**: After Phase 1 & 2 completion  
**Estimated Timeline**: 2-3 weeks for full I/O and module system  
**Genesis Compliance**: Full programming language file system integration