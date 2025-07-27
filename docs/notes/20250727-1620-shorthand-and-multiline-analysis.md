# XMD Shorthand và Multiline Directive Analysis

**Date:** 2025-07-27 16:20  
**Author:** Claude  
**Status:** Analysis of current capabilities and requirements

## Objectives

1. Phân tích shorthand CLI hiện tại
2. Test multiline XMD directives với if/elif/else/endif
3. Kiểm tra import/export functionality
4. Đánh giá XMD như một ngôn ngữ lập trình

## Current Shorthand Support Analysis

Từ `/src/main.c` và `/src/main/convert_shorthand_to_process/`:

**✅ Đã support:**
- `xmd input.md output.md` → `xmd process input.md -o output.md`
- `echo "content" | xmd` → `xmd process` (stdin)
- `echo "content" | xmd output.md` → `xmd process -o output.md`
- Auto-detect file patterns vs stdin

**❓ Cần test:**
- `xmd "string content"` (string literal)
- `xmd "string" output.md`
- Stdin/pipe compatibility

## Multiline Directive Questions

```html
<!-- xmd:
set var="value"
if condition
-->
content
<!-- xmd:endif -->
```

**Cần kiểm tra:**
1. Multiline directive parsing
2. If/elif/else/endif hoạt động cross-comment
3. Nested conditionals
4. Variable scope across directives

## Import/Export Investigation

**Cần test:**
1. Export multiple symbols from one file
2. Import selective symbols from multiple files
3. Re-export imported symbols
4. Circular import handling

## Programming Language Features

XMD cần các feature để trở thành ngôn ngữ lập trình mạnh mẽ:
- ✅ Variables (có)
- ✅ Conditionals (có if/elif/else/endif)
- ✅ Loops (có for/while)
- ✅ Functions (qua import/export)
- ❓ Arrays/objects
- ❓ Error handling (try/catch)
- ❓ Module system

## Next Steps

1. Test shorthand patterns
2. Test multiline directives
3. Test import/export comprehensively
4. Đánh giá completeness của language features