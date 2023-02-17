set(DEVICE_DIR ${PROJECT_SOURCE_DIR}/targets/TARGET_UNICOM/TARGET_VC/device)

list(APPEND VC_TARGET_INCLUDES
  ${DEVICE_DIR}/lib
  ${DEVICE_DIR}/atcmd
  ${DEVICE_DIR}/plc
  ${DEVICE_DIR}/plc/hplc
  ${DEVICE_DIR}/crypto
  ${DEVICE_DIR}/crypto/osr_crypto
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_common
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_hal
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_include
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_include/hash_hmac
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_include/pke
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_include/ske
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/hash_hmac
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/pke
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/ske
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
  "DEVICE_MCU_VC6330=1"
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

list(APPEND VC_CRYPTO_DRIVER_SOURCES
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_common/eccp_curve.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_common/utility.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_hal/hash_basic.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_hal/pke.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_hal/pke_common.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_hal/ske_basic.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_hal/trng.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/hash_hmac/hash.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/hash_hmac/hmac.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/hash_hmac/hmac_sha1.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/hash_hmac/hmac_sha256.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/hash_hmac/hmac_sm3.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/hash_hmac/sha1.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/hash_hmac/sha256.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/hash_hmac/sm3.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/pke/ecdh.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/pke/ecdsa.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/pke/sm2.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/pke/sm2_basic.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/ske/ske.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/ske/ske_cbc.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/ske/ske_cfb.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/ske/ske_ctr.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/ske/ske_ecb.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/ske/ske_gcm_gmac.c
  ${DEVICE_DIR}/crypto/osr_crypto/crypto_lib/ske/ske_ofb.c
)

list(APPEND VC_CRYPTO_TEST_SOURCES
  ${DEVICE_DIR}/crypto/tests/hplc_crypto/hplc_aes_cbc_test.c
  ${DEVICE_DIR}/crypto/tests/hplc_crypto/hplc_aes_gcm_test.c
  ${DEVICE_DIR}/crypto/tests/hplc_crypto/hplc_ecc_test.c
  ${DEVICE_DIR}/crypto/tests/hplc_crypto/hplc_sha256_test.c
  ${DEVICE_DIR}/crypto/tests/hplc_crypto/hplc_sm2_test.c
  ${DEVICE_DIR}/crypto/tests/hplc_crypto/hplc_sm3_test.c
  ${DEVICE_DIR}/crypto/tests/hplc_crypto/hplc_sm4_test.c

  ${DEVICE_DIR}/crypto/tests/osr_crypto/hash_hmac_test/hash_test.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/hash_hmac_test/hmac_test.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/hash_hmac_test/sample_test_hash_hmac.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/hash_hmac_test/sample_test_hmac_sha1.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/hash_hmac_test/sample_test_hmac_sha256.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/hash_hmac_test/sample_test_hmac_sm3.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/hash_hmac_test/sample_test_sha1.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/hash_hmac_test/sample_test_sha256.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/hash_hmac_test/sample_test_sm3.c

  ${DEVICE_DIR}/crypto/tests/osr_crypto/pke_test/eccp_get_curve_paras_test.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/pke_test/eccp_get_key_test.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/pke_test/ecdh_test.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/pke_test/ecdsa_test.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/pke_test/sm2_test.c

  ${DEVICE_DIR}/crypto/tests/osr_crypto/ske_test/ske_gcm_test.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/ske_test/ske_sample_test.c
  ${DEVICE_DIR}/crypto/tests/osr_crypto/ske_test/ske_test.c
)

list(APPEND VC_PLC_DRIVER_SOURCES
  ${DEVICE_DIR}/plc/hplc/hplc.c
  ${DEVICE_DIR}/plc/hplc/hplc_bbp.c
  ${DEVICE_DIR}/plc/hplc/hplc_dma.c
  ${DEVICE_DIR}/plc/hplc/hplc_pll.c
  ${DEVICE_DIR}/plc/hplc/hplc_rx.c
  ${DEVICE_DIR}/plc/hplc/hplc_tx.c
)

# Specific driver sources

add_library(vc-driver
  ${VC_SOC_DRIVER_SOURCES}
  ${VC_CMSIS_SOURCES}
  ${VC_LIB_SOURCES}
  ${VC_ATCMD_SOURCES}
  ${VC_PLC_DRIVER_SOURCES}
  ${VC_CRYPTO_DRIVER_SOURCES}
  ${VC_CRYPTO_TEST_SOURCES}
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
