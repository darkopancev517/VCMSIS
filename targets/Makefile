MCU_FAM_DIR    = TARGET_$(VENDOR)/TARGET_$(MCU_FAM)
MCU_DEVICE_DIR = $(MCU_FAM_DIR)/TARGET_$(MCU_DEVICE)
MCU_BOARD_DIR  = $(MCU_DEVICE_DIR)/TARGET_$(MCU_BOARD)

SRCS_HAL += $(MCU_FAM_DIR)/gpio_api.c
SRCS_HAL += $(MCU_FAM_DIR)/pinmap.c
SRCS_HAL += $(MCU_FAM_DIR)/pinmap_ex.c
SRCS_HAL += $(MCU_FAM_DIR)/serial_api.c
SRCS_HAL += $(MCU_FAM_DIR)/ticker_api.c
SRCS_HAL += $(MCU_FAM_DIR)/us_ticker_api.c
SRCS_HAL += $(MCU_FAM_DIR)/us_ticker.c
SRCS_HAL += $(MCU_FAM_DIR)/flash_api.c
SRCS_HAL += $(MCU_FAM_DIR)/rtc_api.c
SRCS_HAL += $(MCU_FAM_DIR)/lp_ticker.c
SRCS_HAL += $(MCU_FAM_DIR)/lp_ticker_api.c
SRCS_HAL += $(MCU_FAM_DIR)/watchdog_api.c
SRCS_HAL += $(MCU_FAM_DIR)/sleep_api.c
SRCS_HAL += $(MCU_FAM_DIR)/critical_section_api.c
SRCS_HAL += $(MCU_FAM_DIR)/spi_api.c
SRCS_HAL += $(MCU_FAM_DIR)/i2c_api.c
SRCS_HAL += $(MCU_FAM_DIR)/analogin_api.c
SRCS_HAL += $(MCU_FAM_DIR)/hal_log.c
SRCS_HAL += $(MCU_FAM_DIR)/syscalls.c

SRCS_HAL += $(MCU_FAM_DIR)/device/vc_ana.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_flash.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_gpio.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_uart.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_usticker.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_misc.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_xtimer.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_wdt.c
ifeq ($(MCU_DEVICE),VC7351)
#TODO:  need to fixed for vc6330 ------------
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_rtc.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_spi.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_i2c.c
#--------------------------------------------
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_mbox.c
SRCS_HAL += $(MCU_FAM_DIR)/device/vc_radio.c
endif

ifeq ($(MCU_DEVICE),VC7351)
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/hal_misc.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/hal_rf.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/hal_gpio.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/rf_prober.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/rf_cmd.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/rf_cfg.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/rf_host.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/rf_mac.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/rf_hwset.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/rfmbx.c
SRCS_HAL += $(MCU_FAM_DIR)/device/rf/totctl.c
endif

ifeq ($(MCU_DEVICE),VC6330)
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_common/eccp_curve.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_common/utility.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_hal/hash_basic.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_hal/pke.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_hal/pke_common.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_hal/ske_basic.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_hal/trng.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/hash_hmac/hash.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/hash_hmac/hmac.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/hash_hmac/hmac_sha1.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/hash_hmac/hmac_sha256.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/hash_hmac/hmac_sm3.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/hash_hmac/sha1.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/hash_hmac/sha256.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/hash_hmac/sm3.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/pke/ecdh.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/pke/ecdsa.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/pke/sm2.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/pke/sm2_basic.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/ske/ske.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/ske/ske_cbc.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/ske/ske_cfb.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/ske/ske_ctr.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/ske/ske_ecb.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/ske/ske_gcm_gmac.c
SRCS_HAL += $(MCU_FAM_DIR)/device/crypto/osr_crypto/crypto_lib/ske/ske_ofb.c
endif

ifneq (, $(filter $(MCU_DEVICE), VC6330 VC6320))
SRCS_HAL += $(MCU_FAM_DIR)/device/plc/hplc/hplc.c
SRCS_HAL += $(MCU_FAM_DIR)/device/plc/hplc/hplc_bbp.c
SRCS_HAL += $(MCU_FAM_DIR)/device/plc/hplc/hplc_dma.c
SRCS_HAL += $(MCU_FAM_DIR)/device/plc/hplc/hplc_pll.c
SRCS_HAL += $(MCU_FAM_DIR)/device/plc/hplc/hplc_rx.c
SRCS_HAL += $(MCU_FAM_DIR)/device/plc/hplc/hplc_tx.c
endif

SRCS_HAL += $(MCU_DEVICE_DIR)/CMSIS/system_$(MCU_DEVICE_LC).c

SRCS_HAL_STARTUP += $(MCU_DEVICE_DIR)/CMSIS/TOOLCHAIN_GCC_ARM/startup_$(MCU_DEVICE_LC).s

ifeq ($(MCU_DEVICE),VC6330)
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/hplc_crypto/hplc_aes_cbc_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/hplc_crypto/hplc_aes_gcm_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/hplc_crypto/hplc_ecc_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/hplc_crypto/hplc_sha256_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/hplc_crypto/hplc_sm2_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/hplc_crypto/hplc_sm3_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/hplc_crypto/hplc_sm4_test.c

SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/hash_hmac_test/hash_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/hash_hmac_test/hmac_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/hash_hmac_test/sample_test_hash_hmac.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/hash_hmac_test/sample_test_hmac_sha1.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/hash_hmac_test/sample_test_hmac_sha256.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/hash_hmac_test/sample_test_hmac_sm3.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/hash_hmac_test/sample_test_sha1.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/hash_hmac_test/sample_test_sha256.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/hash_hmac_test/sample_test_sm3.c

SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/pke_test/eccp_get_curve_paras_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/pke_test/eccp_get_key_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/pke_test/ecdh_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/pke_test/ecdsa_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/pke_test/sm2_test.c

SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/ske_test/ske_gcm_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/ske_test/ske_sample_test.c
SRCS_TESTS += $(MCU_FAM_DIR)/device/crypto/tests/osr_crypto/ske_test/ske_test.c
endif

SRCS_ATCMD += $(MCU_FAM_DIR)/device/atcmd/argpars.c
SRCS_ATCMD += $(MCU_FAM_DIR)/device/atcmd/cli.c
SRCS_ATCMD += $(MCU_FAM_DIR)/device/atcmd/commands.c

SRCS_LIB += $(MCU_FAM_DIR)/device/lib/heap.c
SRCS_LIB += $(MCU_FAM_DIR)/device/lib/wrap_malloc.c
SRCS_LIB += $(MCU_FAM_DIR)/device/lib/vc_lib.c

SRCS_MAIN += main.c

OBJS_HAL += $(addprefix $(BUILD)/, $(SRCS_HAL:.c=.o))
OBJS_HAL += $(addprefix $(BUILD)/, $(SRCS_ATCMD:.c=.o))
OBJS_HAL += $(addprefix $(BUILD)/, $(SRCS_LIB:.c=.o))
OBJS_HAL_STARTUP += $(addprefix $(BUILD)/, $(SRCS_HAL_STARTUP:.s=.o))
OBJS_MAIN += $(addprefix $(BUILD)/, $(SRCS_MAIN:.c=.o))
OBJS_TESTS += $(addprefix $(BUILD)/, $(SRCS_TESTS:.c=.o))

OBJS_DIR += $(sort $(dir $(OBJS_HAL)))
OBJS_DIR += $(sort $(dir $(OBJS_HAL_STARTUP)))
OBJS_DIR += $(sort $(dir $(OBJS_MAIN)))
OBJS_DIR += $(sort $(dir $(OBJS_TESTS)))

LIB_TARGET_HAL_A = $(BUILD)/$(LIB_TARGET_HAL)
LIB_TARGET_HAL_OBJS += $(OBJS_HAL)
LIB_TARGET_HAL_OBJS += $(OBJS_HAL_STARTUP)

LIB_TARGET_MAIN_A = $(BUILD)/$(LIB_TARGET_MAIN)
LIB_TARGET_MAIN_OBJS += $(OBJS_MAIN)

LIB_TARGET_TESTS_A = $(BUILD)/$(LIB_TARGET_TESTS)
LIB_TARGET_TESTS_OBJS += $(OBJS_TESTS)

A_FILES += $(LIB_TARGET_HAL_A)
A_FILES += $(LIB_TARGET_MAIN_A)
A_FILES += $(LIB_TARGET_TESTS_A)

all: | $(OBJS_DIR) $(A_FILES)

$(OBJS_DIR):
	$(MKDIR) -p $@

$(BUILD)/%.o: %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.o: %.s
	$(ECHO) "AS $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.a:
	$(ECHO) "AR $@"
	$(AR) -cr $@ $^

$(LIB_TARGET_HAL_A): $(LIB_TARGET_HAL_OBJS)

$(LIB_TARGET_MAIN_A): $(LIB_TARGET_MAIN_OBJS)

$(LIB_TARGET_TESTS_A): $(LIB_TARGET_TESTS_OBJS)

-include $(OBJS_HAL:%.o=%.d)
-include $(OBJS_MAIN:%.o=%.d)
-include $(OBJS_TESTS:%.o=%.d)
