#\!/bin/bash
# Fix header conflicts between ast.h and ast_parser.h
# Systems Engineer - Header Conflict Resolution

echo "=== FIXING HEADER CONFLICTS ==="
echo "Resolving function signature conflicts..."
echo

# Fix ast_parser.h to match ast.h signatures
if [ -f "include/ast_parser.h" ]; then
    echo "Updating ast_parser.h..."
    
    # Backup
    cp include/ast_parser.h include/ast_parser.h.bak
    
    # Fix ast_parse_object_creation to match ast.h (2 parameters)
    sed -i 's/ast_node\* ast_parse_object_creation(const char\*\* pos);/ast_node* ast_parse_object_creation(const char** pos, const char* first_name);/' include/ast_parser.h
    
    # Fix ast_parse_multiple_variables_handler to match ast.h (2 parameters)  
    sed -i 's/ast_node\* ast_parse_multiple_variables_handler(const char\*\* pos);/ast_node* ast_parse_multiple_variables_handler(const char** pos, const char* first_name);/' include/ast_parser.h
    
    echo "✓ Updated function signatures in ast_parser.h"
fi

echo
echo "=== HEADER CONFLICT FIX COMPLETE ==="
echo "Testing build..."

cd /data/data/com.termux/files/home/xmd/build
make 2>&1 | grep -E "(\[.*%\]|error:)" | head -15
EOF < /dev/null
