#!/usr/bin/env python3
"""
File Modification Counter - EVIDENCE-BASED VERIFICATION
Count actual files modified by Systems Engineer
"""

import os
import subprocess
from pathlib import Path

def count_files_with_macro_includes():
    """Count files that actually include common_macros.h"""
    src_dir = Path("src")
    macro_files = []
    
    for c_file in src_dir.rglob("*.c"):
        try:
            with open(c_file, 'r') as f:
                content = f.read()
                if 'common_macros.h' in content:
                    macro_files.append(c_file)
        except:
            continue
            
    return macro_files

def count_files_with_xmd_macros():
    """Count files that actually use XMD_* macros"""
    src_dir = Path("src")
    xmd_macro_files = []
    
    for c_file in src_dir.rglob("*.c"):
        try:
            with open(c_file, 'r') as f:
                content = f.read()
                if 'XMD_' in content:
                    xmd_macro_files.append(c_file)
        except:
            continue
            
    return xmd_macro_files

def get_recently_modified_files():
    """Get files modified in last few hours"""
    try:
        result = subprocess.run(['find', 'src', '-name', '*.c', '-mtime', '-1'], 
                              capture_output=True, text=True)
        if result.returncode == 0:
            return result.stdout.strip().split('\n') if result.stdout.strip() else []
    except:
        pass
    return []

def main():
    print("📊 EVIDENCE-BASED FILE MODIFICATION ANALYSIS")
    print("=" * 50)
    
    # Count files with macro includes
    macro_include_files = count_files_with_macro_includes()
    print(f"📁 Files including common_macros.h: {len(macro_include_files)}")
    
    # Count files with XMD macro usage
    xmd_macro_files = count_files_with_xmd_macros()
    print(f"🔧 Files using XMD_* macros: {len(xmd_macro_files)}")
    
    # Recently modified files
    recent_files = get_recently_modified_files()
    print(f"⏰ Recently modified files (24h): {len(recent_files)}")
    
    # Show examples
    print(f"\n📋 SAMPLE FILES WITH MACRO INCLUDES:")
    for i, file_path in enumerate(macro_include_files[:10]):
        print(f"  {i+1}. {file_path}")
    if len(macro_include_files) > 10:
        print(f"  ... and {len(macro_include_files) - 10} more")
        
    print(f"\n🔧 SAMPLE FILES WITH XMD MACROS:")
    for i, file_path in enumerate(xmd_macro_files[:10]):
        print(f"  {i+1}. {file_path}")
    if len(xmd_macro_files) > 10:
        print(f"  ... and {len(xmd_macro_files) - 10} more")
    
    # Save results
    results = {
        'macro_include_files': len(macro_include_files),
        'xmd_macro_files': len(xmd_macro_files),
        'recent_files': len(recent_files)
    }
    
    with open('scripts/systems/file_modification_results.txt', 'w') as f:
        f.write("EVIDENCE-BASED FILE MODIFICATION ANALYSIS\n")
        f.write(f"Files with common_macros.h include: {results['macro_include_files']}\n")
        f.write(f"Files with XMD_* macro usage: {results['xmd_macro_files']}\n")
        f.write(f"Recently modified files: {results['recent_files']}\n")
        
    print(f"\n✅ VERIFIED FILE COUNT: {len(xmd_macro_files)} files actually use XMD macros")
    return results

if __name__ == "__main__":
    main()