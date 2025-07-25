# XMD Working Features Demo

## 1. Import Feature
xmd:import(assets/logo/ascii_logo.md)

## 2. Command Execution

### System Information
- **Operating System:** xmd:exec(uname -o)
- **Architecture:** xmd:exec(uname -m)
- **Hostname:** xmd:exec(hostname)
- **Current User:** xmd:exec(whoami)

### Date and Time
- **Current Date:** xmd:exec(date +"%Y-%m-%d")
- **Current Time:** xmd:exec(date +"%H:%M:%S")
- **Timezone:** xmd:exec(date +%Z)

## 3. Variable Management

xmd:set(project_name, XMD - eXtended MarkDown)
xmd:set(version, 1.0.0)
xmd:set(author, XMD Team)

### Project Information
- **Project:** xmd:get(project_name)
- **Version:** xmd:get(version)
- **Author:** xmd:get(author)

## 4. File Operations

### Current Directory Contents
```
xmd:exec(ls -la | head -10)
```

### Count Files
Total files in current directory: xmd:exec(ls -1 | wc -l)

## 5. Mathematical Operations

### Basic Math
- 10 + 20 = xmd:exec(echo $((10 + 20)))
- 100 - 37 = xmd:exec(echo $((100 - 37)))
- 6 × 7 = xmd:exec(echo $((6 * 7)))
- 100 ÷ 4 = xmd:exec(echo $((100 / 4)))

### Advanced Calculations
- 2^10 = xmd:exec(echo $((2**10)))
- sqrt(144) = xmd:exec(echo "sqrt(144)" | bc)
- π ≈ xmd:exec(echo "scale=5; 4*a(1)" | bc -l)

## 6. Text Processing

### Word Count
This README has xmd:exec(wc -w < README.md) words.

### Line Count  
This file has xmd:exec(wc -l < demo_working.md) lines.

## 7. System Resources

### Memory Info
xmd:exec(free -h | grep Mem)

### Disk Usage
xmd:exec(df -h . | tail -1)

## 8. Git Information

### Current Branch
xmd:exec(git branch --show-current)

### Last Commit
xmd:exec(git log -1 --oneline)

### Git Status
```
xmd:exec(git status --short)
```

---
*Generated with XMD on xmd:exec(date)*