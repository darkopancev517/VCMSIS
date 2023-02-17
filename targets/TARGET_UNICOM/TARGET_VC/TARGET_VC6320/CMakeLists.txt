set(DEVICE_DIR ${PROJECT_SOURCE_DIR}/targets/TARGET_UNICOM/TARGET_VC/device)

list(APPEND VC_TARGET_INCLUDES
  ${DEVICE_DIR}/lib
  ${DEVICE_DIR}/atcmd
  ${DEVICE_DIR}/plc
  ${DEVICE_DIR}/plc/bplc
)

list(APPEND VC_TARGET_DEFINES
  "DEVICE_INTERRUPTIN=1"
  "DEVICE_SERIAL=1"
  "DEVICE_SERIAL_ASYNCH=0"
  "DEVICE_FLASH=1"
  "DEVICE_LPTICKER=1"
  "DEVICE_RTC=1"
  "DEVICE_WATCHDOG=1"
  "DEVICE_SPI=1"
  "DEVICE_SPISLAVE=1"
  "DEVICE_SPI_ASYNCH=1"
  "DEVICE_I2C=1"
  "DEVICE_I2C_ASYNCH=1"
  "DEVICE_ANALOGIN=1"
  "DEVICE_MCU_VC6320=1"
  "CSR_ACCESS="
  "CHIP_IS_MP_VERSION=1"
)

target_include_directories(vc-config INTERFACE ${VC_TARGET_INCLUDES})
target_compile_definitions(vc-config INTERFACE ${VC_TARGET_DEFINES})

# Driver sources files definitions

list(APPEND VC_SOC_DRIVER_SOURCES
  ${DEVICE_DIR}/vc_ana.c
  ${DEVICE_DIR}/vc_flash.c
  ${DEVICE_DIR}/vc_gpio.c
  ${DEVICE_DIR}/vc_uart.c
  ${DEVICE_DIR}/vc_usticker.c
  ${DEVICE_DIR}/vc_misc.c
  ${DEVICE_DIR}/vc_xtimer.c
  ${DEVICE_DIR}/vc_wdt.c
)

list(APPEND VC_CMSIS_SOURCES
  CMSIS/TOOLCHAIN_GCC_ARM/startup_${VC_TARGET_MCU_LOWERCASE}.s
  CMSIS/system_${VC_TARGET_MCU_LOWERCASE}.c
)

list(APPEND VC_LIB_SOURCES
  ${DEVICE_DIR}/lib/heap.c
  ${DEVICE_DIR}/lib/wrap_malloc.c
  ${DEVICE_DIR}/lib/vc_lib.c
)

list(APPEND VC_ATCMD_SOURCES
  ${DEVICE_DIR}/atcmd/argpars.c
  ${DEVICE_DIR}/atcmd/cli.c
  ${DEVICE_DIR}/atcmd/commands.c
)

list(APPEND VC_PLC_DRIVER_SOURCES
  ${DEVICE_DIR}/plc/bplc/hal_pmu.c
  ${DEVICE_DIR}/plc/bplc/phy.c
  ${DEVICE_DIR}/plc/bplc/pll.c
  ${DEVICE_DIR}/plc/bplc/vc_lmac_init.c
  ${DEVICE_DIR}/plc/bplc/vc_lmac_main.c
  ${DEVICE_DIR}/plc/bplc/vc_lmac_txh.c
  ${DEVICE_DIR}/plc/bplc/vc_lmac_rxh.c
  ${DEVICE_DIR}/plc/bplc/vc_lmac_api.c
)

# Specific driver sources

add_library(vc-driver
  ${VC_SOC_DRIVER_SOURCES}
  ${VC_PLC_DRIVER_SOURCES}
  ${VC_CMSIS_SOURCES}
  ${VC_LIB_SOURCES}
  ${VC_ATCMD_SOURCES}
)

set_target_properties(vc-driver
  PROPERTIES
    C_STANDARD 99
    CXX_STANDARD 11
)

target_include_directories(vc-driver
  PRIVATE
    ${VC_PUBLIC_INCLUDES}
)

target_compile_options(vc-driver
  PRIVATE
    ${VC_CFLAGS}
)

target_link_libraries(vc-driver PRIVATE vc-config)
