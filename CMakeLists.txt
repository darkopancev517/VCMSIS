cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.20.2)

file(READ .default-version VC_DEFAULT_VERSION)
string(STRIP ${VC_DEFAULT_VERSION} VC_DEFAULT_VERSION)

project(vcmsis VERSION ${VC_DEFAULT_VERSION})
project(assembler C ASM)

add_library(vc-config INTERFACE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

message(STATUS "VCMSIS Source Directory: ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_TOOLCHAIN_FILE='${CMAKE_TOOLCHAIN_FILE}'")

# List of supported MCU

set(TARGETS_MCU "VC6320" "VC6330" "VC7351")

# List of supported BOARD based on it's MCU

set(VC6320_BOARDS "VC6320_MTR")
set(VC6330_BOARDS "VC6330_FPGA" "VC6330_EVB")
set(VC7351_BOARDS "VC7351_DK")

# Make sure MCU and BOARD target is correct

if (NOT VC_TARGET_MCU IN_LIST TARGETS_MCU)
  if ("${VC_TARGET_MCU}" STREQUAL "")
    message(FATAL_ERROR "Please specify -DVC_TARGET_MCU, supported mcu: ${TARGETS_MCU}")
  else()
    message(FATAL_ERROR "Target MCU unknown: ${VC_TARGET_MCU}")
  endif()
endif()

if (VC_TARGET_MCU STREQUAL "VC6320")
  if (NOT VC_TARGET_BOARD IN_LIST VC6320_BOARDS)
    if ("${VC_TARGET_BOARD}" STREQUAL "")
      message(FATAL_ERROR "Please specify -DVC_TARGET_BOARD, supported board: ${VC6320_BOARDS}")
    else()
      message(FATAL_ERROR "Target BOARD unknown: ${VC_TARGET_BOARD}")
    endif()
  endif()
endif()

if (VC_TARGET_MCU STREQUAL "VC6330")
  if (NOT VC_TARGET_BOARD IN_LIST VC6330_BOARDS)
    if ("${VC_TARGET_BOARD}" STREQUAL "")
      message(FATAL_ERROR "Please specify -DVC_TARGET_BOARD, supported board: ${VC6330_BOARDS}")
    else()
      message(FATAL_ERROR "Target BOARD unknown: ${VC_TARGET_BOARD}")
    endif()
  endif()
endif()

if (VC_TARGET_MCU STREQUAL "VC7351")
  if (NOT VC_TARGET_BOARD IN_LIST VC7351_BOARDS)
    if ("${VC_TARGET_BOARD}" STREQUAL "")
      message(FATAL_ERROR "Please specify -DVC_TARGET_BOARD, supported board: ${VC7351_BOARDS}")
    else()
      message(FATAL_ERROR "Target BOARD unknown: ${VC_TARGET_BOARD}")
    endif()
  endif()
endif()

list(APPEND VC_PUBLIC_INCLUDES
  ${PROJECT_SOURCE_DIR}/CMSIS_5/CMSIS/Core/Include
  ${PROJECT_SOURCE_DIR}/hal/include
  ${PROJECT_SOURCE_DIR}/hal/include/hal
  ${PROJECT_SOURCE_DIR}/targets
  ${PROJECT_SOURCE_DIR}/targets/TARGET_UNICOM/TARGET_VC
  ${PROJECT_SOURCE_DIR}/targets/TARGET_UNICOM/TARGET_VC/device
  ${PROJECT_SOURCE_DIR}/targets/TARGET_UNICOM/TARGET_VC/TARGET_${VC_TARGET_MCU}
  ${PROJECT_SOURCE_DIR}/targets/TARGET_UNICOM/TARGET_VC/TARGET_${VC_TARGET_MCU}/CMSIS
  ${PROJECT_SOURCE_DIR}/targets/TARGET_UNICOM/TARGET_VC/TARGET_${VC_TARGET_MCU}/TARGET_${VC_TARGET_BOARD}
)

target_compile_definitions(vc-config INTERFACE ${VC_TARGET_DEFINES})

set(VC_CFLAGS
  $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -Wno-format>
  $<$<COMPILE_LANGUAGE:CXX>:-Wall -Werror -Wno-c++14-compat -fno-exceptions>
)

add_subdirectory(targets)

add_custom_target(print-vc-config ALL
                  COMMAND ${CMAKE_COMMAND}
                  -DLIST="$<TARGET_PROPERTY:vc-config,INTERFACE_COMPILE_DEFINITIONS>"
                  -P ${PROJECT_SOURCE_DIR}/etc/cmake/print.cmake
)
