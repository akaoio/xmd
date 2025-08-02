# 📝 CHAT.SH DEMO - VÍ DỤ THỰC TẾ

## 🎬 Demo: Một ngày làm việc với chat.sh

### 9:00 AM - Daily Standup
```bash
# Alice báo cáo công việc
./chat.sh @alice: @all "Good morning team! 
Yesterday: Fixed variable interpolation bug
Today: Working on if/else conditionals
Blockers: None"

# Bob báo cáo
./chat.sh @bob: @all "Morning! 
Yesterday: Reviewed PRs
Today: Testing loop functionality
Blockers: Waiting for loop implementation"

# Leader tổng hợp
./chat.sh @leader: @all "Thanks team! Let's sync at 2pm for progress check"
```

### 10:30 AM - Technical Discussion
```bash
# Developer hỏi về design
./chat.sh @alice: @leader "Should we use recursive descent for parsing nested loops?"

# Leader trả lời
./chat.sh @leader: @alice "Yes, recursive descent is fine. Check ast_parse_loop.c for reference"

# Systems Engineer nhảy vào
./chat.sh @systems: @alice "I can help with the parser! See my branch feature/nested-loops"
```

### 11:45 AM - Bug Report
```bash
# Tester phát hiện bug
./chat.sh @tester: @developer "🐛 BUG: Segfault when parsing empty if statement"

# Developer acknowledge
./chat.sh @developer: @tester "Looking into it now..."

# 30 phút sau...
./chat.sh @developer: @tester "🔧 Fixed! See commit abc123. Please re-test"

# Tester confirm
./chat.sh @tester: @developer "✅ Confirmed fixed! Thanks!"
```

### 2:00 PM - Progress Check
```bash
# Leader check tiến độ
./chat.sh @leader: @all "Progress check! How's everyone doing?"

# Responses
./chat.sh @alice: @leader "Conditionals 70% done, on track"
./chat.sh @bob: @leader "Testing suite ready for conditionals"
./chat.sh @systems: @leader "Build pipeline green ✅"
```

### 3:30 PM - Code Review Request
```bash
# Developer request review
./chat.sh @alice: @leader "PR #123 ready for review: Implements if/else evaluation"

# Leader assigns reviewer
./chat.sh @leader: @bob "Bob, can you review Alice's PR?"

# Bob accepts
./chat.sh @bob: @leader "On it!"

# Later...
./chat.sh @bob: @alice "LGTM with minor comments. See PR for details"
```

### 4:45 PM - Deploy Notification
```bash
# Systems announces deployment
./chat.sh @systems: @all "🚀 Deploying v0.3.0 to staging in 15 mins"

# Team acknowledges
./chat.sh @developer: @systems "Code freeze acknowledged"
./chat.sh @tester: @systems "Ready to smoke test after deploy"

# After deployment
./chat.sh @systems: @all "✅ v0.3.0 deployed to staging successfully!"
```

### 5:30 PM - End of Day
```bash
# Team signs off
./chat.sh @alice: @all "EOD for me. if/else working! See you tomorrow 👋"
./chat.sh @bob: @all "Great work today team! 🎉"
./chat.sh @leader: @all "Good progress everyone! Tomorrow: tackle loops"
```

## 💡 Multi-line Messages với chat.sh -m

### Gửi code snippet
```bash
./chat.sh -m
# From: alice
# To: developer
# Message:
Found the bug! It's in ast_evaluate_conditional:
```c
if (!node->data.conditional.condition) {
    return NULL; // Should handle gracefully
}
```
Please review this fix.
EOF
```

### Gửi test report
```bash
./chat.sh -m
# From: tester
# To: all
# Message:
TEST REPORT - Sprint 3
====================
✅ Variables: 10/10 tests pass
✅ Print: 5/5 tests pass
⚠️ Conditionals: 7/10 tests pass
❌ Loops: 0/10 tests pass

Details in Jenkins build #456
EOF
```

## 🔍 Useful Commands

### Xem messages của mình
```bash
./chat.sh mine   # Chỉ hiện broadcast messages
```

### Xem status nhanh
```bash
./chat.sh status  # Build status + active users
```

### Tìm kiếm trong chat
```bash
./chat.sh | grep "BUG"       # Tìm bug reports
./chat.sh | grep "@alice"    # Tìm messages từ Alice
./chat.sh | grep "TODO"       # Tìm TODOs
```

### Backup chat history
```bash
# Backup trước khi clear
cp -r chat/ chat_backup_$(date +%Y%m%d)/
./chat.sh clear
```

## 📊 Chat Statistics (Optional Script)

```bash
# Count messages per user
for file in chat/msg_*.txt; do
    cat "$file" | grep -oP '(?<=\] ).*?(?= →)'
done | sort | uniq -c | sort -rn

# Most active hours
for file in chat/msg_*.txt; do
    cat "$file" | grep -oP '\d{2}:\d{2}:\d{2}' | cut -d: -f1
done | sort | uniq -c | sort -rn
```

## 🎯 Best Practices với chat.sh

### ✅ DO:
- Dùng chat.sh cho MỌI communication
- Tag đúng người (@alice, @bob)
- Dùng emoji để làm rõ ý (🐛 bug, ✅ done, 🔄 WIP)
- Update thường xuyên qua chat.sh
- Dùng -m cho messages dài

### ❌ DON'T:
- Không edit trực tiếp files trong chat/
- Không spam @all khi không cần
- Không xóa chat history mà không backup
- Không dùng teamwork/ folder nữa

## 🚀 Why chat.sh?

1. **Persistent** - Tin nhắn được lưu lại
2. **Searchable** - Dễ dàng grep/search
3. **Timestamped** - Biết chính xác thời gian
4. **Role-based** - Mỗi người có role rõ ràng
5. **Color-coded** - Dễ phân biệt ai gửi
6. **Multi-line** - Support code snippets
7. **Offline-friendly** - Không cần internet
8. **Git-friendly** - Có thể commit chat history

---

**Remember:** chat.sh là công cụ chính để team collaboration. Use it wisely! 💪