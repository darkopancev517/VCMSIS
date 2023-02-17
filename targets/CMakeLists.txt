add_executable(vc-main
  main.c
)

set_target_properties(vc-main
  PROPERTIES
    C_STANDARD 99
    CXX_STANDARD 11
)

target_include_directories(vc-main
  PRIVATE
    ${VC_PUBLIC_INCLUDES}
)

target_compile_options(vc-main
  PRIVATE
    ${VC_CFLAGS}
)

string(TOLOWER "${VC_TARGET_MCU}" VC_TARGET_MCU_LOWERCASE)

set(LD_FILE "${CMAKE_CURRENT_SOURCE_DIR}/TARGET_UNICOM/TARGET_VC/TARGET_${VC_TARGET_MCU}/CMSIS/TOOLCHAIN_GCC_ARM/gcc_arm_${VC_TARGET_MCU_LOWERCASE}.ld")

target_link_libraries(vc-main
  PUBLIC
    -Wl,--whole-archive
    vc-hal
    vc-driver
    -Wl,--no-whole-archive
    -Wl,--gc-sections
    -Wl,--wrap,_malloc_r -Wl,--wrap,_free_r -Wl,--wrap,_realloc_r -Wl,--wrap,_calloc_r
    -T${LD_FILE}
    -Wl,-Map=$<TARGET_PROPERTY:NAME>.map
  PRIVATE
    vc-config
)

add_subdirectory(TARGET_UNICOM/TARGET_VC)
