# 🛡️ XMD VIOLATION DETECTION TOOLS - HƯỚNG DẪN SỬ DỤNG

**📅 Date:** 2025-08-02  
**👤 Author:** DEBTHUNTER Team  
**🎯 Purpose:** Hướng dẫn sử dụng các công cụ bắt vi phạm và lỗi trong XMD project

---

## 🚨 QUAN TRỌNG: PHÂN LOẠI CÔNG CỤ

### ⚠️ Công cụ NGOÀI LỀ (External Development Tools)
Các công cụ này **KHÔNG PHẢI** là core XMD project. Chúng là utility tools để hỗ trợ development process.

```
🏗️ XMD Core (src/)          🔧 Development Tools (tools/)
├── Language implementation  ├── Code analysis utilities
├── Runtime components      ├── Violation detection tools  
├── Production code         ├── Quality assurance helpers
└── Shipped với XMD        └── Development-only tools
```

---

## 🎯 CÁC CÔNG CỤ BẮT VI PHẠM HIỆN CÓ

### 1. 🗑️ DEAD FUNCTION DETECTOR
**Mục đích:** Phát hiện ghost functions, dead functions, và duplicate functions

#### 📂 Vị trí:
```
tools/analyzer/
├── dead_function_detector.c
├── function_usage_analyzer.c  
├── file_scanner/
│   └── file_scanner.c
├── function_finder/
│   └── function_finder.c
└── usage_tracker/
    └── usage_tracker.c
```

#### 🚀 Cách sử dụng:

##### Bước 1: Build tool
```bash
cd /data/data/com.termux/files/home/xmd
./build-tools/dead-function-detector.sh
```

##### Bước 2: Chạy analysis
```bash
# Scan toàn bộ src/ directory
./tools/analyzer/dead_function_detector

# Hoặc scan specific directory
./tools/analyzer/dead_function_detector src/specific_module/
```

##### Bước 3: Xem kết quả
```bash
# Kết quả sẽ được lưu trong:
cat dead_code_report.json
```

#### 📊 Format kết quả:
```json
{
  "summary": {
    "total_defined_functions": 313,
    "total_called_functions": 905,
    "dead_functions_count": 0,        // Functions defined nhưng không called
    "ghost_functions_count": 558,     // Functions called nhưng không defined
    "potential_duplicates": 18
  },
  "dead_functions": [...],           // Functions cần xóa
  "ghost_functions": [...],          // Functions cần implement
  "potential_duplicates": [...]      // Functions có thể trùng lặp
}
```

---

## 🔍 CÁC LOẠI VI PHẠM MÀ TOOLS PHÁT HIỆN

### 1. 👻 GHOST FUNCTIONS (Functions ma)
**Mô tả:** Functions được gọi nhưng không có implementation

**Ví dụ:**
```c
// main.c
int main() {
    xmd_get_version();  // ← Function được call
    return 0;
}

// Nhưng không có file nào implement xmd_get_version()
```

**Cách fix:**
```bash
# 1. Tạo directory theo Genesis principles
mkdir -p src/core/version/xmd_get_version/

# 2. Implement function
# src/core/version/xmd_get_version/xmd_get_version.c
```

### 2. 💀 DEAD FUNCTIONS (Functions chết)
**Mô tả:** Functions có implementation nhưng không ai gọi

**Ví dụ:**
```c
// src/utils/unused_function.c
int never_called_function() {  // ← Function không ai gọi
    return 42;
}
```

**Cách fix:**
```bash
# Xóa function và file nếu không cần thiết
rm src/utils/unused_function.c
```

### 3. 🔄 DUPLICATE FUNCTIONS (Functions trùng lặp)
**Mô tả:** Functions có implementation giống nhau ở nhiều nơi

**Ví dụ:**
```c
// src/moduleA/strlen_wrapper.c
int my_strlen(const char* str) { return strlen(str); }

// src/moduleB/string_length.c  
int string_len(const char* str) { return strlen(str); }  // ← Trùng lặp logic
```

**Cách fix:**
```bash
# Consolidate into single function theo Genesis principles
# Chọn 1 implementation, xóa các duplicates
```

---

## 🛠️ WORKFLOW SỬ DỤNG TOOLS

### 📋 Quy trình chuẩn:

#### 1. **Pre-Development Scan**
```bash
# Trước khi code, scan để hiểu current state
./tools/analyzer/dead_function_detector
```

#### 2. **Regular Monitoring** 
```bash
# Scan định kỳ mỗi khi có major changes
./tools/analyzer/dead_function_detector

# Check kết quả
cat dead_code_report.json | jq '.summary'
```

#### 3. **Pre-Commit Validation**
```bash
# Trước khi commit, đảm bảo không introduce violations
./tools/analyzer/dead_function_detector

# Verify ghost functions đã được resolved
echo "Ghost functions remaining: $(cat dead_code_report.json | jq '.summary.ghost_functions_count')"
```

#### 4. **Release Preparation**
```bash
# Đảm bảo clean codebase trước release
./tools/analyzer/dead_function_detector

# Target: 0 ghost functions, minimal dead functions
```

---

## 📈 METRICS VÀ TARGETS

### 🎯 Code Quality Targets:
- **Ghost Functions:** 0 (tất cả functions called phải có implementation)
- **Dead Functions:** < 5% of total functions
- **Duplicate Functions:** 0 (sau khi macro refactoring)
- **Code Duplication:** < 20% (historic target achieved)

### 📊 Tracking Progress:
```bash
# Check current metrics
cat dead_code_report.json | jq '{
  ghost_functions: .summary.ghost_functions_count,
  dead_functions: .summary.dead_functions_count,
  total_functions: .summary.total_defined_functions,
  duplicates: .summary.potential_duplicates
}'
```

---

## 🚨 TROUBLESHOOTING

### ❌ Common Issues:

#### 1. **Tool không compile**
```bash
# Check dependencies
gcc --version
make --version

# Rebuild tools
rm -rf build-tools/
./build-tools/dead-function-detector.sh
```

#### 2. **False positives trong ghost functions**
```bash
# Tool có thể detect standard library functions như 'strlen', 'malloc'
# Filter ra những functions này:
cat dead_code_report.json | jq '.ghost_functions[] | select(.name | test("^(strlen|malloc|free|printf)$") | not)'
```

#### 3. **Tool chạy chậm trên large codebase**
```bash
# Scan specific modules thay vì toàn bộ src/
./tools/analyzer/dead_function_detector src/specific_module/
```

---

## 🔧 ADVANCED USAGE

### 1. **Custom Filtering**
```bash
# Filter chỉ XMD-specific functions
cat dead_code_report.json | jq '.ghost_functions[] | select(.name | test("^(xmd_|ast_|config_)"))'
```

### 2. **Integration với CI/CD**
```bash
#!/bin/bash
# ci_check.sh
./tools/analyzer/dead_function_detector

GHOST_COUNT=$(cat dead_code_report.json | jq '.summary.ghost_functions_count')
if [ "$GHOST_COUNT" -gt 0 ]; then
    echo "❌ CI FAILED: $GHOST_COUNT ghost functions detected"
    exit 1
fi
echo "✅ CI PASSED: No ghost functions"
```

### 3. **Batch Processing**
```bash
# Process multiple modules
for module in ast config store token; do
    echo "Scanning $module..."
    ./tools/analyzer/dead_function_detector src/$module/
    mv dead_code_report.json "reports/${module}_report.json"
done
```

---

## 📚 GENESIS PRINCIPLES COMPLIANCE

### ✅ Tool Design Philosophy:
- **ISOLATION:** 1 function → 1 file → 1 directory (ngay cả trong tools/)
- **NO DEPENDENCIES:** Standard C only, không dùng external libs
- **REAL IMPLEMENTATION:** Complete code, không có stubs
- **MEMORY MANAGEMENT:** Proper malloc/free, validate pointers
- **ERROR HANDLING:** Handle tất cả error cases

### 🛡️ Tool Quality Assurance:
```c
// Example: Every tool function follows patterns
int analyze_function(const char* function_name) {
    XMD_VALIDATE_PTRS(-1, function_name);  // ← Macro validation
    
    // Implementation logic
    
    return 0;  // ← Explicit return
}
```

---

## 🎯 EXAMPLE WORKFLOWS

### Workflow 1: **Ghost Function Resolution**
```bash
# 1. Detect ghost functions
./tools/analyzer/dead_function_detector

# 2. Identify critical functions
cat dead_code_report.json | jq '.ghost_functions[] | select(.name | test("^xmd_"))'

# 3. Implement missing functions
mkdir -p src/core/missing_function/
# ... implement function ...

# 4. Verify resolution
./tools/analyzer/dead_function_detector
# Ghost count should decrease
```

### Workflow 2: **Code Cleanup**
```bash
# 1. Find dead functions
cat dead_code_report.json | jq '.dead_functions[]'

# 2. Verify they're truly unused
grep -r "function_name" src/

# 3. Remove if confirmed dead
rm src/path/to/dead_function.c

# 4. Verify cleanup
./tools/analyzer/dead_function_detector
```

---

## 📞 SUPPORT VÀ CONTACT

### 🆘 Khi cần help:
- **Issues:** Report tại project issue tracker
- **Questions:** Ask trong team chat
- **Bugs:** Tạo detailed bug report với logs

### 📋 Bug Report Template:
```
Tool: Dead Function Detector
Version: [version]
Command: [exact command used]
Error: [error message]
Environment: [OS, compiler version]
Steps to reproduce: [detailed steps]
```

---

## 🔄 UPDATES VÀ MAINTENANCE

### 📅 Regular Maintenance:
- **Weekly:** Run full codebase scan
- **Before releases:** Complete validation run
- **After major refactoring:** Comprehensive analysis

### 🚀 Tool Evolution:
- Tools được improve liên tục
- New violation types có thể được thêm
- Performance optimizations ongoing

---

**🏆 Remember:** These tools help maintain XMD code quality while following Genesis principles. Use them regularly để ensure clean, maintainable codebase!

**💪 Team Success:** With these tools, chúng ta đã achieve 42% duplication reduction (70% → 28%) và resolve 22+ ghost functions!