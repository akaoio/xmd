# Phase 2: JSON/YAML Import Functionality

## Objective
Enable XMD to import JSON and YAML files with unified data handling using libyaml and json-c libraries.

## Tasks

### 1. JSON/YAML Parser Integration
- Add json-c dependency to CMakeLists.txt
- Create JSON parser wrapper
- Create YAML parser wrapper
- Implement unified data structure converter

### 2. Enhanced Import Directive
- Extend existing import functionality
- Add file type detection (json/yaml/yml)
- Create import processor for structured data
- Handle import errors gracefully

### 3. Data Structure Unification
- Define internal data representation
- Convert JSON objects to XMD variables
- Convert YAML maps to XMD variables
- Handle arrays and primitive types

### 4. Variable System Enhancement
- Support nested object access
- Add object property navigation
- Implement array indexing
- Create data type validation

## File Structure
```
src/
├── import/
│   ├── import_json/
│   │   └── import_json.c           # JSON file import
│   ├── import_yaml/
│   │   └── import_yaml.c           # YAML file import
│   ├── detect_file_type/
│   │   └── detect_file_type.c      # File type detection
│   └── unified_data_converter/
│       └── unified_data_converter.c # Convert to XMD format
├── parsers/
│   ├── json_parser/
│   │   └── json_parser.c           # json-c wrapper
│   └── yaml_parser/
│   │   └── yaml_parser.c           # libyaml wrapper (already exists)
├── data_structures/
│   ├── xmd_object/
│   │   └── xmd_object.c            # Object representation
│   ├── xmd_array/
│   │   └── xmd_array.c             # Array representation
│   └── data_converter/
│       └── data_converter.c        # Type conversion utilities
```

## Tests
- test/import/test_import_json.c
- test/import/test_import_yaml.c
- test/import/test_detect_file_type.c
- test/parsers/test_json_parser.c
- test/data_structures/test_xmd_object.c
- test/data_structures/test_xmd_array.c

## Dependencies
- json-c for JSON parsing
- libyaml for YAML parsing (already added in phase 1)
- Existing import system

## Data Format Examples

### JSON Import
```json
{
  "name": "Alice",
  "age": 30,
  "skills": ["programming", "design"],
  "address": {
    "city": "New York",
    "zip": "10001"
  }
}
```

### YAML Import
```yaml
name: Alice
age: 30
skills:
  - programming
  - design
address:
  city: New York
  zip: "10001"
```

### XMD Usage
```xmd



Name: 
Age: 
First skill: 
City: 

Config value: 
```

## Acceptance Criteria
1. Import JSON files with `import "file.json" as varname`
2. Import YAML files with `import "file.yaml" as varname`
3. Access nested properties with dot notation
4. Access array elements with bracket notation
5. Both JSON and YAML create identical XMD data structures
6. Comprehensive error handling for malformed files
7. Memory management for imported data structures
8. All functions follow one-function-per-file rule
9. Complete test coverage
10. Backward compatibility with existing import system