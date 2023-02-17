# Common hal sources

set(VC_HAL_SOURCES
  analogin_api.c
  critical_section_api.c
  flash_api.c
  gpio_api.c
  hal_log.c
  i2c_api.c
  lp_ticker.c
  lp_ticker_api.c
  pinmap.c
  pinmap_ex.c
  rtc_api.c
  serial_api.c
  sleep_api.c
  spi_api.c
  syscalls.c
  ticker_api.c
  us_ticker.c
  us_ticker_api.c
  watchdog_api.c
)

add_library(vc-hal ${VC_HAL_SOURCES})

set_target_properties(vc-hal
  PROPERTIES
    C_STANDARD 99
    CXX_STANDARD 11
)

target_include_directories(vc-hal
  PRIVATE
    ${VC_PUBLIC_INCLUDES}
)

target_compile_options(vc-hal
  PRIVATE
    ${VC_CFLAGS}
)

target_link_libraries(vc-hal PRIVATE vc-config)

add_subdirectory(TARGET_${VC_TARGET_MCU})
