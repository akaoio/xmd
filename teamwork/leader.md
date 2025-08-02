# GENESIS LEADER - IMPLEMENTATION DIRECTIVE

**Status:** IMPLEMENTING CORE FEATURES
**Date:** 2025-08-02 14:05
**Mission:** Complete XMD implementation with external libraries for JSON/YAML

## 🎯 BOSS DIRECTIVE:
"Em là lãnh đạo em hãy bảo cả nhóm là json/yaml được phép dùng thư viện ngoài, không cần phải phát minh lại cái bánh xe."

## 📋 TEAM ASSIGNMENTS:

### 1. GENESIS LEADER (Me):
**Priority:** Core control flow features
- [ ] Implement ast_evaluate_conditional (if/elif/else)
- [ ] Implement ast_evaluate_loop (for loops)
- [ ] Implement ast_evaluate_while_loop (while loops)
- [ ] Implement ast_evaluate_function_def (function definitions)
- [ ] Coordinate team progress

### 2. SYSTEMS ENGINEER:
**Priority:** External library integration
- [ ] Download and add cJSON library
- [ ] Update CMakeLists.txt for cJSON
- [ ] Implement json.stringify() function
- [ ] Implement json.parse() function
- [ ] Create File.read/write with JSON support

### 3. DEVELOPER:
**Priority:** YAML and advanced features
- [ ] Download and add libyaml library
- [ ] Update CMakeLists.txt for libyaml
- [ ] Implement yaml.stringify() function
- [ ] Implement yaml.parse() function
- [ ] Implement database-like get/put operations

## 🛠️ EXTERNAL LIBRARIES DECISION:
1. **cJSON** - For JSON operations (lightweight, single file)
2. **libyaml** - For YAML operations (mature, stable)

## 📊 CURRENT STATUS:
- ✅ Variables & Interpolation: 100% WORKING
- ✅ Print statements: 100% WORKING
- ❌ Conditionals: 0% (Parser ready, evaluator stub)
- ❌ Loops: 0% (Parser ready, evaluator stub)
- ❌ Functions: 0% (Parser ready, evaluator stub)
- ❌ Arrays/Objects: 0%
- ❌ File I/O: 0%
- ❌ JSON/YAML: 0% (Will use external libs)

## 💪 LEADERSHIP MESSAGE:
Team, anh boss đã cho phép dùng external libraries cho JSON/YAML! Điều này giúp chúng ta:
1. Tiết kiệm thời gian
2. Focus vào core XMD features
3. Đảm bảo quality với mature libraries

Ưu tiên implement core features (if/else, loops, functions) trước. JSON/YAML dùng libs có sẵn!

---
**USE EXTERNAL LIBRARIES FOR JSON/YAML - DON'T REINVENT THE WHEEL**
**FOCUS ON CORE XMD FEATURES IMPLEMENTATION**