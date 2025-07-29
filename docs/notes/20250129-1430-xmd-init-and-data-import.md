# XMD Init Command and Data Import Features

## Overview
Implementing two major features:
1. `xmd init` command with .xmd/xmd.yaml configuration
2. JSON/YAML import functionality with unified data handling

## Feature 1: xmd init Command

### Purpose
- Create .xmd directory and xmd.yaml configuration file
- Allow multiple entry points and targets
- Support `xmd`, `xmd process`, and `xmd watch` without arguments

### Configuration Structure (xmd.yaml)
```yaml
version: "1.0"
projects:
  default:
    entry: 
      - "src/main.md"
      - "src/components/*.md"
    output: "dist/index.md"
    watch: true
  
  docs:
    entry: "docs/**/*.md"
    output: "build/docs.md"
    
  api:
    entry: "api/spec.md"
    output: "public/api.html"
    process:
      - import: "api/config.yaml"
      - import: "api/endpoints.json"
```

### Implementation Steps
1. Add `init` command to CLI
2. Create .xmd directory structure
3. Generate default xmd.yaml
4. Modify existing commands to read configuration
5. Support project selection

## Feature 2: JSON/YAML Import

### Purpose
- Import JSON and YAML files seamlessly
- Provide unified data structure for both formats
- Add built-in functions for data manipulation

### Unified Data Structure
- Use XMD's variable system as the unified format
- JSON objects → XMD objects (store)
- JSON arrays → XMD arrays
- YAML maps → XMD objects
- YAML sequences → XMD arrays

### Built-in Functions
```xmd
# File I/O
write "./output.md" "content"
append "./log.md" "new line"
exists "./file.md"

# Data serialization
to_json data
from_json string
to_yaml data
from_yaml string

# Data manipulation
keys object
values object
merge obj1 obj2
filter array condition
map array transform
```

## Implementation Plan

### Phase 1: xmd init command
1. Update CLI to handle init command
2. Create directory and file generators
3. Add YAML parsing with libyaml
4. Create configuration reader

### Phase 2: Import functionality
1. Add JSON parsing with json-c
2. Create unified data converters
3. Implement import directive enhancement
4. Add file type detection

### Phase 3: Built-in functions
1. Implement file I/O functions
2. Add serialization functions
3. Create data manipulation functions
4. Update documentation

## Technical Considerations
- Use libyaml for YAML parsing
- Use json-c for JSON parsing
- Maintain backward compatibility
- Follow existing code structure
- One function per file rule
- Comprehensive testing