#!/bin/bash
# RIGOROUS DEVELOPER WORK AUDIT - Independent verification
echo "=== INDEPENDENT DEVELOPER WORK VERIFICATION ==="
echo "Conducting thorough audit of Developer's claimed fixes..."

cd /data/data/com.termux/files/home/xmd

VERIFIED_FIXES=0
QUESTIONABLE_FIXES=0
FAILED_FIXES=0

echo "🔍 RIGOROUS FILE-BY-FILE AUDIT:"
echo

# Check every file Developer claims to have fixed
find src/ast src/misc -name "*.c" | while read -r file; do
    echo "Auditing: $file"
    
    # Check 1: Does file have proper comment structure?
    if grep -q "^/\*\*$" "$file" && grep -q "^ \*/$" "$file"; then
        echo "  ✅ Comment structure: CORRECT"
        COMMENT_OK=true
    else
        echo "  ❌ Comment structure: BROKEN"
        COMMENT_OK=false
    fi
    
    # Check 2: Does file actually compile?
    if gcc -c -Iinclude "$file" -o /tmp/audit_$$.o 2>/dev/null; then
        echo "  ✅ Compilation: SUCCESS"
        rm -f /tmp/audit_$$.o
        COMPILE_OK=true
    else
        echo "  ❌ Compilation: FAILED"
        echo "     Error details:"
        gcc -c -Iinclude "$file" 2>&1 | head -2 | sed 's/^/     /'
        COMPILE_OK=false
    fi
    
    # Check 3: Proper newline at end of file?
    if [ "$(tail -c1 "$file" | wc -l)" -eq 1 ]; then
        echo "  ✅ Newline: CORRECT"
        NEWLINE_OK=true
    else
        echo "  ❌ Newline: MISSING"
        NEWLINE_OK=false
    fi
    
    # Overall assessment
    if [ "$COMMENT_OK" = true ] && [ "$COMPILE_OK" = true ] && [ "$NEWLINE_OK" = true ]; then
        echo "  🎯 VERDICT: PROPERLY FIXED"
        ((VERIFIED_FIXES++))
    elif [ "$COMMENT_OK" = true ] && [ "$COMPILE_OK" = true ]; then
        echo "  ⚠️  VERDICT: MOSTLY FIXED (minor issues)"
        ((QUESTIONABLE_FIXES++))
    else
        echo "  ❌ VERDICT: NOT PROPERLY FIXED"
        ((FAILED_FIXES++))
    fi
    
    echo "  ---"
done

echo
echo "=== INDEPENDENT AUDIT SUMMARY ==="
echo "Properly Fixed: $VERIFIED_FIXES"
echo "Questionable: $QUESTIONABLE_FIXES"  
echo "Failed: $FAILED_FIXES"
echo
echo "SYSTEMS ENGINEER: Maintaining independent oversight"