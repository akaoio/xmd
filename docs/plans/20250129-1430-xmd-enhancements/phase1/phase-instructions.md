# Phase 1: XMD Init Command Implementation

## Objective
Implement `xmd init` command that creates .xmd directory structure and xmd.yaml configuration file.

## Tasks

### 1. Update CLI Interface
- Add `init` command to main CLI parser
- Handle `xmd init` argument parsing
- Create help text for init command

### 2. Configuration System
- Add libyaml dependency to CMakeLists.txt
- Create YAML configuration parser
- Define xmd.yaml structure
- Implement configuration reader

### 3. Init Command Logic
- Create .xmd directory if not exists
- Generate default xmd.yaml file
- Handle existing configuration files
- Provide user feedback

### 4. Project Configuration Support
- Modify existing commands to read xmd.yaml
- Support multiple project configurations
- Default project selection logic
- Error handling for missing configs

## File Structure
```
src/
├── cli/
│   └── init/
│       └── init.c                    # Main init command
├── config/
│   ├── read_config/
│   │   └── read_config.c            # Read xmd.yaml
│   ├── create_config/
│   │   └── create_config.c          # Create default config
│   └── yaml_parser/
│       └── yaml_parser.c            # YAML parsing wrapper
├── utils/
│   ├── create_directory/
│   │   └── create_directory.c       # Directory creation
│   └── file_exists/
│       └── file_exists.c            # File existence check
```

## Tests
- test/cli/test_init.c
- test/config/test_read_config.c
- test/config/test_create_config.c
- test/config/test_yaml_parser.c

## Dependencies
- libyaml for YAML parsing
- Existing file system utilities

## Acceptance Criteria
1. `xmd init` creates .xmd directory
2. Default xmd.yaml is generated with proper structure
3. Existing files are not overwritten without confirmation
4. `xmd` command reads configuration when available
5. Error messages are clear and helpful
6. All functions follow one-function-per-file rule
7. Complete test coverage