# XMD Core Architecture Design

## System Overview

XMD is structured as a pipeline of components that transform markdown input into processed output:

```
Input MD → Lexer → Parser → XMD Processor → Output MD
                     ↓
                   AST → Variable Store
                         ↓
                   Control Flow → Command Executor
                         ↓
                   Module System → Cache
```

## Component Architecture

### 1. Lexical Analysis Layer

```c
// Core token types
typedef enum {
    TOKEN_TEXT,
    TOKEN_HEADING,
    TOKEN_LIST_ITEM,
    TOKEN_CODE_BLOCK,
    TOKEN_HTML_COMMENT,
    TOKEN_XMD_DIRECTIVE,
    TOKEN_VARIABLE_REF,
    TOKEN_EOF
} token_type;

typedef struct token {
    token_type type;
    char* value;
    size_t line;
    size_t column;
    struct token* next;
} token;
```

**Key Functions:**
- `lexer_create(const char* input)`: Initialize lexer with input
- `lexer_next_token(lexer* lex)`: Get next token
- `lexer_peek_token(lexer* lex)`: Look ahead without consuming

### 2. Parser Layer

```c
// AST node types
typedef enum {
    NODE_DOCUMENT,
    NODE_HEADING,
    NODE_PARAGRAPH,
    NODE_LIST,
    NODE_CODE_BLOCK,
    NODE_XMD_DIRECTIVE,
    NODE_VARIABLE_REF
} node_type;

typedef struct ast_node {
    node_type type;
    char* content;
    struct ast_node** children;
    size_t child_count;
    size_t child_capacity;
    
    // XMD-specific data
    union {
        struct {
            char* directive_type;
            char* parameters;
        } xmd;
        struct {
            char* variable_name;
            char* expression;
        } variable;
    } data;
} ast_node;
```

**Key Functions:**
- `parser_create(token* tokens)`: Create parser from token stream
- `parser_parse_document(parser* p)`: Parse full document
- `ast_node_create(node_type type)`: Create AST node
- `ast_node_add_child(ast_node* parent, ast_node* child)`: Build tree

### 3. Variable System

```c
// Value types for XMD variables
typedef enum {
    VALUE_STRING,
    VALUE_NUMBER,
    VALUE_BOOLEAN,
    VALUE_ARRAY,
    VALUE_OBJECT,
    VALUE_NULL
} value_type;

typedef struct value {
    value_type type;
    union {
        char* string_val;
        double number_val;
        bool boolean_val;
        struct {
            struct value** items;
            size_t count;
        } array_val;
        struct {
            char** keys;
            struct value** values;
            size_t count;
        } object_val;
    } data;
} value;

// Variable storage with scoping
typedef struct variable_scope {
    char** keys;
    value** values;
    size_t count;
    size_t capacity;
    struct variable_scope* parent;
} variable_scope;

typedef struct variable_store {
    variable_scope* current_scope;
    variable_scope* global_scope;
} variable_store;
```

**Key Functions:**
- `variable_store_create()`: Initialize variable storage
- `variable_set(variable_store* store, const char* key, value* val)`
- `variable_get(variable_store* store, const char* key)`
- `variable_scope_push(variable_store* store)`: Enter new scope
- `variable_scope_pop(variable_store* store)`: Exit current scope

### 4. XMD Processor

```c
// XMD directive types
typedef enum {
    XMD_SET,      // <!-- xmd:set key="value" -->
    XMD_IF,       // <!-- xmd:if condition -->
    XMD_ELIF,     // <!-- xmd:elif condition -->
    XMD_ELSE,     // <!-- xmd:else -->
    XMD_ENDIF,    // <!-- xmd:endif -->
    XMD_FOR,      // <!-- xmd:for item in collection -->
    XMD_ENDFOR,   // <!-- xmd:endfor -->
    XMD_WHILE,    // <!-- xmd:while condition -->
    XMD_ENDWHILE, // <!-- xmd:endwhile -->
    XMD_EXEC,     // <!-- xmd:exec command -->
    XMD_IMPORT,   // <!-- xmd:import name from "file" -->
    XMD_EXPORT,   // <!-- xmd:export name -->
    XMD_TRY,      // <!-- xmd:try -->
    XMD_CATCH,    // <!-- xmd:catch -->
    XMD_ENDTRY    // <!-- xmd:endtry -->
} xmd_directive_type;

typedef struct xmd_directive {
    xmd_directive_type type;
    char* parameters;
    char* condition;  // for if/while
    char* variable;   // for for loops
    char* collection; // for for loops
    char* command;    // for exec
    char* import_name;
    char* import_path;
} xmd_directive;

typedef struct xmd_processor {
    variable_store* variables;
    module_registry* modules;
    command_executor* executor;
    cache_manager* cache;
} xmd_processor;
```

**Key Functions:**
- `xmd_processor_create(xmd_config* config)`: Initialize processor
- `xmd_process_ast(xmd_processor* proc, ast_node* root)`: Process AST
- `xmd_execute_directive(xmd_processor* proc, xmd_directive* dir)`
- `xmd_interpolate_variables(xmd_processor* proc, const char* text)`

### 5. Command Execution Layer

```c
// Security sandbox configuration
typedef struct sandbox_config {
    char** exec_whitelist;
    char** exec_blacklist;
    char** allowed_paths;
    char** blocked_paths;
    char** allowed_networks;
    uint32_t max_memory_mb;
    uint32_t max_cpu_time_ms;
    uint32_t max_wall_time_ms;
} sandbox_config;

typedef struct command_executor {
    sandbox_config* config;
    process_pool* pool;
    cache_manager* cache;
} command_executor;

typedef struct command_result {
    int exit_code;
    char* stdout_data;
    char* stderr_data;
    uint64_t execution_time_ms;
    uint64_t memory_used_bytes;
} command_result;
```

**Key Functions:**
- `executor_create(sandbox_config* config)`: Initialize executor
- `executor_run_command(command_executor* exec, const char* cmd)`
- `executor_check_permissions(command_executor* exec, const char* cmd)`
- `executor_format_output(command_result* result, const char* format)`

### 6. Module System

```c
// Module representation
typedef struct xmd_module {
    char* name;
    char* path;
    char* content;
    ast_node* ast;
    variable_store* exports;
    struct xmd_module** dependencies;
    size_t dependency_count;
    bool loaded;
    bool loading; // for circular dependency detection
} xmd_module;

typedef struct module_registry {
    xmd_module** modules;
    size_t count;
    size_t capacity;
    char** search_paths;
    size_t search_path_count;
} module_registry;
```

**Key Functions:**
- `module_registry_create()`: Initialize module system
- `module_load(module_registry* reg, const char* path)`
- `module_resolve_path(module_registry* reg, const char* relative_path)`
- `module_check_circular_deps(xmd_module* module)`

### 7. Caching Layer

```c
// Cache entry types
typedef enum {
    CACHE_COMMAND_OUTPUT,
    CACHE_MODULE_CONTENT,
    CACHE_TEMPLATE_RESULT,
    CACHE_FILE_CONTENT
} cache_entry_type;

typedef struct cache_entry {
    char* key;
    cache_entry_type type;
    void* data;
    size_t data_size;
    uint64_t timestamp;
    uint64_t ttl_ms;
    uint32_t access_count;
} cache_entry;

typedef struct cache_manager {
    cache_entry** entries;
    size_t count;
    size_t capacity;
    uint64_t max_memory_bytes;
    uint64_t current_memory_bytes;
} cache_manager;
```

**Key Functions:**
- `cache_manager_create(uint64_t max_memory)`
- `cache_get(cache_manager* cache, const char* key)`
- `cache_put(cache_manager* cache, const char* key, void* data, size_t size)`
- `cache_evict_lru(cache_manager* cache)`

## Data Flow

### 1. Parsing Phase
```
Markdown Input → Lexer → Token Stream → Parser → AST
```

### 2. Processing Phase
```
AST → XMD Processor → Variable Resolution → Control Flow → Output AST
```

### 3. Execution Phase
```
Commands → Sandbox → System Calls → Results → Cache
```

### 4. Module Phase
```
Import Directives → Path Resolution → Module Loading → Dependency Graph
```

### 5. Output Phase
```
Processed AST → Markdown Generator → Final Output
```

## Memory Management

### Reference Counting
- All major structures use reference counting
- Automatic cleanup when references reach zero
- Circular reference detection for modules

### Memory Pools
```c
typedef struct memory_pool {
    void** blocks;
    size_t* block_sizes;
    size_t block_count;
    size_t total_allocated;
} memory_pool;
```

### Error Handling
```c
typedef enum {
    XMD_SUCCESS = 0,
    XMD_ERROR_PARSE = 1,
    XMD_ERROR_SYNTAX = 2,
    XMD_ERROR_PERMISSION = 3,
    XMD_ERROR_MODULE_NOT_FOUND = 4,
    XMD_ERROR_CIRCULAR_DEPENDENCY = 5,
    XMD_ERROR_COMMAND_FAILED = 6,
    XMD_ERROR_OUT_OF_MEMORY = 7,
    XMD_ERROR_TIMEOUT = 8
} xmd_error_code;

typedef struct xmd_error {
    xmd_error_code code;
    char* message;
    char* file;
    size_t line;
    size_t column;
    struct xmd_error* cause;
} xmd_error;
```

## Threading Model

### Single-Threaded Core
- Main processing pipeline is single-threaded
- Simplifies memory management and debugging

### Multi-Threaded Execution
- Command execution uses thread pool
- Each command runs in isolated thread
- Results synchronized back to main thread

### Thread Safety
- All shared data structures are thread-safe
- Lock-free where possible (cache, counters)
- Minimal locking for critical sections

## Configuration System

```c
typedef struct xmd_config {
    // Execution settings
    sandbox_config* sandbox;
    uint32_t max_recursion_depth;
    uint32_t max_loop_iterations;
    
    // Cache settings
    uint64_t cache_max_memory;
    uint32_t cache_default_ttl_ms;
    
    // Module settings
    char** module_search_paths;
    size_t search_path_count;
    
    // Output settings
    bool preserve_comments;
    bool pretty_print;
    char* output_format; // "markdown", "html", "json"
    
    // Debug settings
    bool debug_mode;
    bool trace_execution;
    char* log_level;
} xmd_config;
```

## Performance Characteristics

### Time Complexity
- Lexing: O(n) where n is input size
- Parsing: O(n) for well-formed input
- Variable lookup: O(1) average case
- Template interpolation: O(m) where m is template size

### Space Complexity
- AST: O(n) where n is number of nodes
- Variable storage: O(v) where v is number of variables
- Module cache: O(m * s) where m is modules, s is average size

### Streaming Support
- Process large files without loading entirely into memory
- Incremental parsing and output generation
- Configurable buffer sizes for memory-constrained environments