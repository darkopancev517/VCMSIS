set(DEVICE_DIR ${PROJECT_SOURCE_DIR}/targets/TARGET_UNICOM/TARGET_VC/device)

list(APPEND VC_TARGET_INCLUDES
  ${DEVICE_DIR}/rf
  ${DEVICE_DIR}/rf/hal
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
  "CSR_ACCESS="
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
  ${DEVICE_DIR}/vc_rtc.c
  ${DEVICE_DIR}/vc_spi.c
  ${DEVICE_DIR}/vc_i2c.c
  ${DEVICE_DIR}/vc_mbox.c
  ${DEVICE_DIR}/vc_radio.c
)

list(APPEND VC_CMSIS_SOURCES
  CMSIS/TOOLCHAIN_GCC_ARM/startup_${VC_TARGET_MCU_LOWERCASE}.s
  CMSIS/system_${VC_TARGET_MCU_LOWERCASE}.c
)

list(APPEND VC_CLI_SOURCES
  ${DEVICE_DIR}/cli/commands.c
  ${DEVICE_DIR}/cli/cmd_mem.c
  ${DEVICE_DIR}/cli/cmd_timer.c
  ${DEVICE_DIR}/cli/cmd_rf.c
)

list(APPEND VC_RF_DRIVER_SOURCES
  ${DEVICE_DIR}/rf/hal_misc.c
  ${DEVICE_DIR}/rf/hal_rf.c
  ${DEVICE_DIR}/rf/hal_gpio.c
  ${DEVICE_DIR}/rf/rf_prober.c
  ${DEVICE_DIR}/rf/rf_cmd.c
  ${DEVICE_DIR}/rf/rf_cfg.c
  ${DEVICE_DIR}/rf/rf_host.c
  ${DEVICE_DIR}/rf/rf_mac.c
  ${DEVICE_DIR}/rf/rf_hwset.c
  ${DEVICE_DIR}/rf/rfmbx.c
  ${DEVICE_DIR}/rf/totctl.c
)

# Specific driver sources

add_library(vc-driver
  ${VC_SOC_DRIVER_SOURCES}
  ${VC_CMSIS_SOURCES}
  ${VC_CLI_SOURCES}
  ${VC_RF_DRIVER_SOURCES}
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
