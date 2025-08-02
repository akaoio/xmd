#\!/bin/bash
echo "Fixing include paths..."
find src/performance -name "*.c" -exec sed -i "s|../../../../include/performance_internal.h|../../../include/performance.h|g" {} \;
find src/performance -name "*.c" -exec sed -i "s|../../../../include/utils.h|../../../include/utils.h|g" {} \;
find src/performance -name "*.c" -exec sed -i "s|../../../../include/platform.h|../../../include/platform.h|g" {} \;
find src/resource -name "*.c" -exec sed -i "s|../../../../include/limiter_internal.h|../../../include/resource.h|g" {} \;
find src/resource -name "*.c" -exec sed -i "s|../../../../include/utils.h|../../../include/utils.h|g" {} \;
find src/resource -name "*.c" -exec sed -i "s|../../../../include/platform.h|../../../include/platform.h|g" {} \;
find src/variable -name "*.c" -exec sed -i "s|../../../../include/variable.h|../../../include/variable.h|g" {} \;
find src/variable -name "*.c" -exec sed -i "s|../../../../include/variable_extended_internal.h|../../../include/variable_internal.h|g" {} \;
find src/utils -name "*.c" -exec sed -i "s|../../../../include/utils.h|../../../include/utils.h|g" {} \;
echo "Include paths fixed\!"
