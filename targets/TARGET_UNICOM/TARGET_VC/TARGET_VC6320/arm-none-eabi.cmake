set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(CMAKE_RANLIB arm-none-eabi-ranlib)

execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE COMPILER_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)

set(COMMON_C_FLAGS "-mcpu=cortex-m4 -mthumb -fdata-sections -ffunction-sections")

set(CMAKE_C_FLAGS_INIT "${COMMON_C_FLAGS} -std=gnu99 -mno-unaligned-access")
set(CMAKE_CXX_FLAGS_INIT "${COMMON_C_FLAGS} -fno-exceptions -fno-rtti")
set(CMAKE_ASM_FLAGS_INIT "-mcpu=cortex-m4 -mthumb")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${COMMON_C_FLAGS} -specs=nosys.specs")

set(CMAKE_C_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_ASM_FLAGS_DEBUG "-g")

set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_ASM_FLAGS_RELEASE "")
