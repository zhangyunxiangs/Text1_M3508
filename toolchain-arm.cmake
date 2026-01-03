# arm-gcc-toolchain.cmake - 适用于STM32的交叉编译工具链配置

# 设置系统信息
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# 指定编译器（使用绝对路径）
set(CMAKE_C_COMPILER "D:/Clion/Environment/STM32/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc.exe")
set(CMAKE_CXX_COMPILER "D:/Clion/Environment/STM32/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-g++.exe")

# 设置编译器为可工作（避免CMake测试）
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

# 禁用编译器测试，使用静态库测试
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 编译标志
set(COMMON_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=gnu++14")
set(CMAKE_ASM_FLAGS_INIT "${COMMON_FLAGS} -x assembler-with-cpp")

# 链接标志
set(CMAKE_EXE_LINKER_FLAGS_INIT
        "${COMMON_FLAGS} -specs=nosys.specs -specs=nano.specs -Wl,--gc-sections -Wl,-Map=output.map"
)

# 查找程序设置
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)