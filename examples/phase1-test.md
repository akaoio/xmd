# Phase 1 Test Document

This is a simple markdown document to test Phase 1 functionality.

## Features to Test

### Basic Markdown
- This is a list item
- Another list item
- Third item

### XMD Directives
<!-- xmd:set name="World" -->
<!-- xmd:set version="1.0.0" -->

Hello {{name}}! Welcome to XMD version {{version}}.

### Code Blocks
```c
int main() {
    printf("Hello, World!\n");
    return 0;
}
```

### HTML Comments
<!-- This is a regular HTML comment -->
<!-- xmd:if name == "World" -->
This should be conditional content.
<!-- xmd:endif -->

### Variable References
The project name is {{name}} and version is {{version}}.