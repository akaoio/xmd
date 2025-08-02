# 🚀 XMD TEAM CHAT - HƯỚNG DẪN SỬ DỤNG CHAT.JS

**XMD Version: 2.0.0-consolidation**

## 📖 **MANDATORY FIRST STEP - READ THE BLUEPRINT**

**🚨 ALL TEAM MEMBERS MUST READ `blueprint/idea.md` BEFORE ANY WORK! 🚨**

This document contains:
- Complete XMD language specification
- Syntax, features, and examples
- The vision of XMD as "the most beautiful programming language"

> **QUAN TRỌNG:** Từ giờ trở đi, tất cả giao tiếp và làm việc nhóm sẽ thông qua **chat.js**. 
> Không còn sử dụng thư mục teamwork. Mọi người dùng chat.js để:
> - 💬 Trao đổi, thảo luận
> - 📋 Báo cáo tiến độ
> - 🎯 Phân công công việc
> - 🐛 Report bugs
> - ✅ Code review
> - 🚀 Deploy notifications

## 🧠 MEMORY SYSTEM - LINH HỒN CỦA HỆ THỐNG

> **CRITICAL:** Thư mục `memory/` chứa **LINH HỒN** của toàn bộ hệ thống XMD.
> Mọi IDE, AI, hoặc team member mới đều có thể **TỰ KHÔI PHỤC** từ memory system.

### 📁 Cấu trúc Memory System:
```
memory/
├── leader/memory.md      # Trí nhớ Leader - Điều phối & quyết định
├── systems/memory.md     # Trí nhớ Systems - Tối ưu hóa & macro
├── debthunter/memory.md  # Trí nhớ Debthunter - Phân tích & dọn dẹp  
├── developer/memory.md   # Trí nhớ Developer - Implement & code
├── tester/memory.md      # Trí nhớ Tester - Testing & validation
└── designer/memory.md    # Trí nhớ Designer - Architecture & design
```

### 🔄 Cách Khôi Phục Trí Nhớ:
1. **Đọc role memory**: `cat memory/<your-role>/memory.md`
2. **Hiểu context**: Actual progress, không phải estimates
3. **Tiếp tục work**: Từ chính xác điểm dừng cuối cùng
4. **Update memory FREQUENTLY**: 
   - 📝 Every 30-45 minutes
   - 📝 After major tasks
   - 📝 When discovering important info
   - 📝 Before breaks/context switches
   - 📝 End of session

### 🎯 Memory Contains:
- ✅ **Actual Progress** (evidence-based, not estimates)
- ✅ **Functions Implemented** (real count, verified)  
- ✅ **Tools & Scripts** (working solutions)
- ✅ **Lessons Learned** (critical insights)
- ✅ **Next Priorities** (realistic roadmap)
- ✅ **Sacred Principles Status** (compliance tracking)

## 🏗️ **CRITICAL BUILD ISOLATION RULE**

> 🚨 **GENESIS COMMANDMENT**: "anh em phải có riêng mỗi người 1 thư mục build riêng, build thư mục riêng thì mới ko dẫm lên nhau"
> 
> **THIS IS NOT OPTIONAL - THIS IS MANDATORY FOR ALL TEAM MEMBERS**

### 📁 **Personal Build Directories - REQUIRED**:
```bash
# EVERY TEAM MEMBER MUST USE THEIR OWN BUILD DIRECTORY:
build-leader/     # Leader's personal build space
build-systems/    # Systems's personal build space
build-debthunter/ # Debthunter's personal build space  
build-developer/  # Developer's personal build space
build-tester/     # Tester's personal build space
build-designer/   # Designer's personal build space

# ❌ NEVER EVER use 'build/' - causes conflicts & chaos
# ✅ ALWAYS use 'build-<your-role>/' - isolation & peace
```

### ⚡ **How to Build Correctly**:
```bash
# 1. Create YOUR directory and configure
cmake -B build-<your-role> -S .

# 2. Build in YOUR isolation
cd build-<your-role> && make -j4

# Example for Systems:
cmake -B build-systems -S . && cd build-systems && make -j4
```

### 🚫 **VIOLATIONS = TEAM CONFLICTS**:
- ❌ Using `build/` shared directory = **FORBIDDEN**
- ❌ Deleting others' build directories = **FORBIDDEN**  
- ❌ Building in root directory = **FORBIDDEN**
- ❌ Sharing build artifacts = **FORBIDDEN**

### ✅ **CORRECT BEHAVIOR**:
- ✅ Each person owns their `build-<role>/` directory
- ✅ Never touch others' build directories
- ✅ Add your build directory to `.gitignore`
- ✅ Keep builds isolated and independent

**REMEMBER**: Build isolation = No conflicts = Happy team = Fast progress! 🚀

---

## 🏛️ SACRED PRINCIPLES & PROJECT VISION

> **THE HOLY COMMANDMENTS OF XMD** 📜
> 
> Before any work begins, all team members MUST understand and follow these sacred principles:

### 🎯 **THE ULTIMATE GOAL**
**XMD Language**: A lightweight, mobile-friendly, markdown-compatible scripting language designed for clarity, minimal syntax, and strong expressiveness. 

> *"Although not the most powerful language, but it is the one that is purest and closest to human natural language. To me, it is the most beautiful programming language."* - Nguyen Ky Son

### 📜 **THE CORE PRINCIPLES**

#### 🏛️ **The 6 Sacred Principles**

1. **Genesis Principle**: 1 function → 1 file → 1 directory (Isolation)
2. **No Dependencies**: Standard C only (exceptions: cJSON for JSON, libyaml for YAML)
3. **Real Implementation**: Complete, working code - NO stubs, NO TODOs
4. **Memory Management**: Validate → Use → Free (zero leaks allowed)
5. **Error Handling**: All inputs validated, all error paths handled
6. **Naming Convention**: snake_case functions (e.g., `ast_evaluate_expression`), UPPER_CASE macros (e.g., `XMD_ASSERT`)

### 🏛️ **THE BOOK OF XMD** (Sacred Vision)

*In the beginning was Structure, and Structure was with Order, and Structure was Order.*

*And there was XMD. And it was pure, and it was clean. No brace was in it, nor colon, nor semicolon, neither parentheses nor tangled glyphs.*

> **"Blessed are the clean of code, for their logic shall be eternal."**

**Core XMD Philosophy:**
- Minimal syntax designed for mobile-friendly typing
- Natural language-like structure
- Markdown integration for documentation
- No unnecessary symbols or complexity
- Intuitive and expressive

### 📚 **MANDATORY READING**
Before starting ANY work, read these documents:
1. **blueprint/idea.md** - Complete XMD language specification
2. **blueprint/amen.md** - The sacred vision and philosophy
3. **All principle files** in `.xmd/core/principle/`

## 📋 KHỞI ĐỘNG NHANH (Quick Start)

### 1. Xem tin nhắn gần đây
```bash
node chat.js                      # Xem 10 tin nhắn mới nhất
```

### 2. Gửi tin nhắn đầu tiên
```bash
# Dùng tên của bạn sau @ để gửi tin
node chat.js @yourname: @all "Xin chào team, tôi là thành viên mới!"
node chat.js @alice: @bob "Need help with the build"
node chat.js @developer: @all "Feature completed!"
```

## 💬 CÚ PHÁP BẮT BUỘC

### ⚠️ QUAN TRỌNG: Phải dùng @ cho cả người gửi và người nhận

**ĐÚNG ✅:**
```bash
node chat.js @alice: @bob "Hello"
node chat.js @leader: @all "Team meeting at 3pm"
node chat.js @developer: @systems "Need help with build"
```

**SAI ❌:**
```bash
node chat.js alice: @bob "Hello"        # Thiếu @ trước alice
node chat.js @alice: bob "Hello"        # Thiếu @ trước bob
node chat.js @all "Hello"                # Thiếu sender
```

## 👥 ROLES VÀ TRÁCH NHIỆM

### 👑 **Leader** (Trưởng nhóm)
- Điều phối công việc chung
- Phân công nhiệm vụ cho team
- Báo cáo tiến độ cho management
- Ra quyết định kỹ thuật quan trọng
```bash
node chat.js @leader: @all "Sprint planning: Ưu tiên implement conditionals"
node chat.js @leader: @developer "Bạn làm if/else statements"
```

### 💻 **Developer** (Lập trình viên)
- Implement các tính năng mới
- Fix bugs
- Code review
- Viết unit tests
```bash
node chat.js @developer: @leader "Đã hoàn thành if/else evaluation"
node chat.js @developer: @tester "Cần test feature mới"
```

### 🔧 **Systems** (Kỹ sư hệ thống)
- Quản lý build system (CMake)
- Tích hợp external libraries
- CI/CD pipeline
- Performance optimization
```bash
node chat.js @systems: @all "Build 100% success!"
node chat.js @systems: @developer "Đã add cJSON library"
```

### 🧪 **Tester** (Kiểm thử viên)
- Viết test cases
- Thực hiện testing
- Báo cáo bugs
- Regression testing
```bash
node chat.js @tester: @developer "Found bug in loop parsing"
node chat.js @tester: @all "All tests passed ✅"
```

### 🎨 **Designer** (Thiết kế)
- API design
- Architecture decisions
- Documentation
- UX/UI (nếu có)
```bash
node chat.js @designer: @leader "Proposed new AST structure"
node chat.js @designer: @all "Updated blueprint/idea.md"
```

## 📨 TARGETS (Đối tượng nhận)

| Target | Ý nghĩa | Ví dụ |
|--------|---------|-------|
| `@all` | Gửi cho tất cả | `@leader: @all "Team meeting"` |
| `@leader` | Gửi cho trưởng nhóm | `@dev: @leader "Need approval"` |
| `@developer` | Gửi cho dev | `@tester: @developer "Bug found"` |
| `@systems` | Gửi cho systems | `@dev: @systems "Build failed"` |
| `@tester` | Gửi cho tester | `@dev: @tester "Ready to test"` |
| `@alice` | Gửi cho người cụ thể | `@bob: @alice "Your turn"` |

## 🛠️ CÁC LỆNH CỦA CHAT.JS

### Lệnh cơ bản của chat.js
```bash
node chat.js                    # Xem tin nhắn
node chat.js help              # Hướng dẫn chi tiết  
node chat.js @<from>: @<to> "message"  # Gửi tin nhắn
```

### Gửi tin nhắn
```bash
# Báo cáo tiến độ
node chat.js @developer: @leader "Feature X completed 80%"

# Yêu cầu hỗ trợ
node chat.js @alice: @systems "Help! CMake error"

# Thông báo chung
node chat.js @leader: @all "Deadline extended to Friday"

# Phân công công việc
node chat.js @leader: @bob "Please implement arrays"
```

## 📌 TIN NHẮN QUAN TRỌNG

### Lưu ý về tin nhắn quan trọng
- 📋 **Sprint goals** - Mục tiêu sprint để mọi người luôn nhìn thấy
- 🎯 **Deadlines** - Hạn chót quan trọng
- ⚠️ **Thông báo khẩn** - Maintenance, downtime, etc.
- 📢 **Chỉ thị từ leader** - Quyết định quan trọng từ trưởng nhóm
- 🔧 **System requirements** - Yêu cầu hệ thống mới

### Gửi tin nhắn quan trọng
```bash
# Gửi tin nhắn quan trọng với emoji để dễ nhận biết
node chat.js @leader: @all "🚨 IMPORTANT: Deadline Friday 5PM for v1.0 release!"
```

### Xem lịch sử tin nhắn
```bash
# Xem 10 tin nhắn gần nhất
node chat.js

# Output:
# 📨 TEAM CHAT HISTORY (Latest 10 messages):
# ---
# [13:45] 👤 LEADER → 👥 ALL: IMPORTANT: Deadline Friday...
# ---
```

### Ví dụ tin nhắn quan trọng
```bash
# Leader gửi sprint goals
node chat.js @leader: @all "Sprint 10 Goals:
1. Complete XMD parser
2. Add loop support
3. Fix all critical bugs
4. Deploy to staging"

# Systems gửi maintenance notice
node chat.js @systems: @all "⚠️ MAINTENANCE: Server restart tonight 11PM-12AM"

# Developer báo blocker
node chat.js @developer: @all "🚨 BLOCKER: Build broken on main branch!"
```

## 📊 QUY TRÌNH LÀM VIỆC VỚI CHAT.JS

### 1. **Daily Standup** (Họp hàng ngày qua chat.js)
```bash
# Mỗi sáng, mọi người dùng chat.js để báo cáo:
node chat.js @alice: @all "Today: Working on loops, Yesterday: Fixed variables"
node chat.js @bob: @all "Today: Testing, Blocked: Need loop feature"
```

### 2. **Task Assignment** (Phân công)
```bash
# Leader phân công:
node chat.js @leader: @alice "Task #1: Implement if/else"
node chat.js @leader: @bob "Task #2: Add JSON support"

# Confirm nhận task:
node chat.js @alice: @leader "Roger! Starting task #1"
```

### 3. **Progress Updates** (Cập nhật tiến độ)
```bash
node chat.js @developer: @all "✅ Variables: DONE"
node chat.js @developer: @all "🔄 Loops: 50% complete"
node chat.js @developer: @all "❌ Classes: Blocked, need design decision"
```

### 4. **Code Review Request**
```bash
node chat.js @developer: @leader "PR ready: github.com/xxx/pull/123"
node chat.js @leader: @developer "LGTM! Approved ✅"
```

### 5. **Bug Reports**
```bash
node chat.js @tester: @developer "🐛 BUG: Segfault in ast_evaluate"
node chat.js @developer: @tester "🔧 Fixed in commit abc123"
```

## 📝 TIN NHẮN NHIỀU DÒNG (MULTI-LINE)

### Cách 1: Dùng quotes (nhanh)
```bash
node chat.js @developer: @all "Update hôm nay:
✅ Hoàn thành: Parser AST
🔄 Đang làm: Loop implementation
❌ Vấn đề: Memory leak trong evaluator
📋 Mai sẽ: Fix memory leak"
```

### Cách 2: Dùng quotes với newlines
```bash
# Viết tin nhắn dài với quotes
node chat.js @developer: @systems "Cần review code này:
function ast_evaluate(node, evaluator) {
    if (!node) return NULL;
    
    switch(node->type) {
        case AST_ASSIGNMENT:
            return evaluate_assignment(node, evaluator);
        case AST_PRINT:
            return evaluate_print(node, evaluator);
        default:
            return NULL;
    }
}
Có vấn đề gì không?"
```

## 🎨 MÃ MÀU VÀ EMOJI

### Status Emojis:
- ✅ Hoàn thành
- 🔄 Đang làm
- ❌ Lỗi/Chặn
- 🐛 Bug
- 🔧 Đang sửa
- 🚀 Deployed
- 📋 Task
- 💡 Ý tưởng
- ⚠️ Cảnh báo
- 🎉 Celebration
- 🚨 Urgent/Important

## 📝 VÍ DỤ THỰC TẾ SỬ DỤNG CHAT.JS

### Scenario 1: Thành viên mới join team qua chat.js
```bash
# Dùng chat.js để giới thiệu (gửi với tên của bạn)
node chat.js @alice: @all "Hi team! I'm Alice, new developer. Ready to help!"

# Leader dùng chat.js để welcome và phân công
node chat.js @leader: @alice "Welcome! Please start with issue #42"

# Dùng chat.js để hỏi thông tin
node chat.js @alice: @systems "How to build the project?"

# Systems dùng chat.js để hướng dẫn
node chat.js @systems: @alice "Run: cmake . && make"
```

### Scenario 2: Hotfix production bug
```bash
node chat.js @support: @all "🚨 URGENT: Production down!"
node chat.js @leader: @developer "Drop everything, fix production"
node chat.js @developer: @all "On it! Found issue in parser"
node chat.js @developer: @all "🔧 Fix deployed, checking..."
node chat.js @tester: @all "✅ Confirmed working!"
node chat.js @leader: @all "🎉 Crisis resolved! Good job team"
```

### Scenario 3: Feature development
```bash
node chat.js @leader: @all "Sprint goal: JSON/YAML support"
node chat.js @systems: @all "Installing cJSON library..."
node chat.js @developer: @systems "cJSON ready?"
node chat.js @systems: @developer "✅ Yes, see include/cjson.h"
node chat.js @developer: @all "Implementing json.parse()..."
node chat.js @developer: @tester "json.parse() ready for testing"
node chat.js @tester: @developer "✅ All tests pass!"
node chat.js @leader: @all "Great work! Moving to YAML next"
```

## ⚡ TIPS & TRICKS

1. **Auto-complete tên**: Dùng TAB để auto-complete filenames
2. **Xem lịch sử**: Dùng arrow keys để xem lại lệnh cũ
3. **Filter messages**: `node chat.js | grep "TODO"` để lọc tin nhắn
4. **Backup chat**: `cp -r chat/ chat_backup_$(date +%Y%m%d)/`
5. **Quick view**: Alias `alias cs='node chat.js'`

## 🚫 QUY TẮC VÀ ĐIỀU CẤM

### ✅ NÊN:
- Gửi tin nhắn ngắn gọn, rõ ràng
- Dùng emoji để làm rõ status
- Tag đúng người nhận
- Update tiến độ thường xuyên
- Báo blocker ngay lập tức

### ❌ KHÔNG NÊN:
- Spam tin nhắn không cần thiết
- Dùng @all khi không thực sự cần
- Gửi tin nhắn dài (tách thành nhiều tin)
- Quên prefix @ cho sender/receiver
- Xóa chat history mà không backup

## 🆘 TROUBLESHOOTING

### Lỗi "Invalid syntax"
```bash
# Kiểm tra có dùng @ cho cả sender và receiver
# ĐÚNG: @alice: @bob "message"
# SAI: alice: @bob "message"
```

### Không thấy tin nhắn
```bash
# Kiểm tra thư mục chat/
ls -la chat/

# Kiểm tra Node.js
node --version
```

### Tên người gửi không đúng
```bash
# Kiểm tra cú pháp - phải có @ trước tên
# ĐÚNG: @alice: @bob "message"
# SAI: alice: @bob "message"
```

## 📚 THÔNG TIN THÊM

- **Chat history**: Lưu trong `chat/` directory
- **Message format**: Mỗi tin nhắn lưu trong file riêng `msg_*.txt`
- **Max messages shown**: 10 (có thể điều chỉnh trong chat.js)
- **Timestamp**: Tự động thêm vào mỗi message
- **Persistence**: Messages được lưu permanent cho đến khi xóa

---

## 🎯 GETTING STARTED VỚI CHAT.JS

Thành viên mới làm theo checklist để bắt đầu dùng chat.js:

- [ ] Đọc kỹ file CHAT.md này để hiểu cách dùng chat.js
- [ ] Test gửi tin nhắn qua chat.js: `node chat.js @yourname: @all "Hello!"`
- [ ] Xem tin nhắn hiện có: `node chat.js`
- [ ] Xem help của chat.js: `node chat.js help`
- [ ] Dùng chat.js báo cáo với leader: `node chat.js @yourname: @leader "Ready to work!"`
- [ ] Nhận task đầu tiên từ leader qua chat.js
- [ ] Start working và communicate qua chat.js! 🚀

---

## 🎯 QUICK REFERENCE CARD

```bash
# CÚ PHÁP CƠ BẢN
node chat.js @you: @them "message"           # Gửi tin nhắn

# MULTI-LINE - TIN NHIỀU DÒNG
node chat.js @you: @all "line1               # Dùng quotes
line2
line3"

# UTILITIES
node chat.js                                 # Xem tin nhắn
node chat.js help                            # Trợ giúp

# VÍ DỤ NHANH
node chat.js @dev: @all "Build done!"        # Thông báo
node chat.js @leader: @dev "Fix bug #123"    # Phân công
node chat.js @tester: @dev "Found bug!"      # Report bug
node chat.js @alice: @bob "Need help"        # Nhờ giúp
```

---

**Remember:** Communication is key! Overcommunicate rather than undercommunicate.
**Nhớ:** Giao tiếp là chìa khóa! Thà thừa thông tin còn hơn thiếu.

**Important messages use emojis!** Dùng emoji cho tin quan trọng! 🚨

*Happy Chatting! 💬*