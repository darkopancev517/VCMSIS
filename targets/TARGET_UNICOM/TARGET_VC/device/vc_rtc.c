/*
 * Copyright (c) 2022 Unicom Semiconductor, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "vc_rtc.h"

typedef enum {
  RTC_SECOND = 0,
  RTC_MINUTE,
  RTC_HOUR,
  RTC_DAY,
  RTC_WEEK,
  RTC_MONTH,
  RTC_YEAR
} vcrtc_time_t;

static bool m_rtc_initialized = false;
static bool m_rtc_ticker_initialized = false;
static bool m_rtc_int_irqn_enabled = false;
static bool m_rtc_ticker_set_interrupt = false;
static uint32_t m_rtc_ticker_set_timestamp = 0;

static volatile uint32_t m_rtc_tick_ns_counter = 0;
static volatile uint32_t m_rtc_tick_ms_counter = 0;
static volatile uint32_t m_rtc_tick_isr_flag = 0;
bool g_rtc_ticker_fire_interrupt = false;

static void vcrtc_wprot_disable(void);
static void vcrtc_wprot_enable(void);
static void vcrtc_reset(void);
static void vcrtc_write_time(vcrtc_time_t time, uint32_t value);
static void vcrtc_int_enable(uint8_t intnum);
static void vcrtc_int_disable(uint8_t intnum);
static uint32_t vcrtc_get_wkucntr(void);

void vcrtc_init(void)
{
  if (m_rtc_initialized)
    return;

  uint32_t temp = 0;

  /* RTC time value reset */
  vcrtc_reset();

  /* RTC clear all interrupt status */
  temp = (0x5ff << 0);
  VC_RTC->INTSTS = temp;

  /* RTC clock config */
  vcrtc_wprot_disable();
  temp = VC_RTC->PSCA;
  temp &= ~VC_RTC_PSCA_PSCA_Msk;
  temp |= (0UL << VC_RTC_PSCA_PSCA_Pos); /* No-prescaller, RTC clock is 32768 Hz */
  VC_RTC->PSCA = temp;
  vcrtc_wprot_enable();
  while ((VC_RTC->CE & VC_RTC_CE_BSY_Msk) != 0);

  m_rtc_initialized = true;
}

void vcrtc_ticker_enable(void)
{
  if (m_rtc_ticker_initialized)
    return;

  uint32_t temp = 0;
  /* RTC set wakeup counter - period = (cnt + 1)*CounterClock */
  vcrtc_wprot_disable();
  temp = VC_RTC->WKUCNT;
  temp &= ~VC_RTC_WKUCNT_WKUCNT_Msk;
  temp &= ~VC_RTC_WKUCNT_CNTSEL_Msk;
  temp |= (0UL << VC_RTC_WKUCNT_CNTSEL_Pos);          /* counter clock is 32768 Hz for PSCA 0 */
  temp |= ((32UL - 1) << VC_RTC_WKUCNT_WKUCNT_Pos);   /* Period = (31 + 1) * 32768 Hz */
  VC_RTC->WKUCNT = temp;
  vcrtc_wprot_enable();
  while ((VC_RTC->CE & VC_RTC_CE_BSY_Msk) != 0);
  vcrtc_int_enable(6); /* 6: WKUCNT INTEN */

  m_rtc_ticker_initialized = true;
}

void vcrtc_ticker_disable(void)
{
  vcrtc_int_disable(6);
}

void vcrtc_ticker_set_interrupt(uint32_t timestamp)
{
  m_rtc_ticker_set_interrupt = true;
  m_rtc_ticker_set_timestamp = timestamp;
}

uint32_t vcrtc_get_seconds(void)
{
  uint32_t temp = VC_RTC->LOAD;
  while ((VC_RTC->CE & VC_RTC_CE_BSY_Msk) != 0);
  (void) temp;
  return (VC_RTC->SEC & 0x7F);
}

uint32_t vcrtc_get_us_ticker(void)
{
  uint32_t tmp_rtc_tick_isr_flag;
  uint32_t tick;
  uint32_t ns;
  uint32_t ms;
usregetrtctick:
  tmp_rtc_tick_isr_flag = m_rtc_tick_isr_flag;
  ms = m_rtc_tick_ms_counter;
  ns = m_rtc_tick_ns_counter;
  tick = vcrtc_get_wkucntr();
  if (tmp_rtc_tick_isr_flag != m_rtc_tick_isr_flag)
    goto usregetrtctick;
  return (ms * 1000) + ((ns + (tick * 30517)) / 1000);
}

static void vcrtc_wprot_disable(void)
{
  VC_RTC->PWD = 0x5AA55AA5;
  VC_RTC->CE = 0xA55AA55B;
}

static void vcrtc_wprot_enable(void)
{
  VC_RTC->PWD = 0x5AA55AA5;
  VC_RTC->CE = 0xA55AA55A;
}

static void vcrtc_reset(void)
{
  vcrtc_wprot_disable();
  vcrtc_write_time(RTC_SECOND, 0);
  vcrtc_write_time(RTC_MINUTE, 0);
  vcrtc_write_time(RTC_HOUR, 0);
  vcrtc_write_time(RTC_DAY, 1);
  vcrtc_write_time(RTC_WEEK, 0);
  vcrtc_write_time(RTC_MONTH, 1);
  vcrtc_write_time(RTC_YEAR, 0);
  vcrtc_wprot_enable();
  while ((VC_RTC->CE & VC_RTC_CE_BSY_Msk) != 0);
}

static void vcrtc_write_time(vcrtc_time_t time, uint32_t value)
{
  switch (time) {
    case RTC_SECOND:
      VC_RTC->SEC = value;
      break;
    case RTC_MINUTE:
      VC_RTC->MIN = value;
      break;
    case RTC_HOUR:
      VC_RTC->HOUR = value;
      break;
    case RTC_DAY:
      VC_RTC->DAY = value;
      break;
    case RTC_WEEK:
      VC_RTC->WEEK = value;
      break;
    case RTC_MONTH:
      VC_RTC->MON = value;
      break;
    case RTC_YEAR:
      VC_RTC->YEAR = value;
      break;
    default:
      break;
  }
}

static void vcrtc_int_enable(uint8_t intnum)
{
  switch (intnum) {
    case 2:
      VC_RTC->INTEN |= (1UL << VC_RTC_INTEN_INTEN2_Pos); /* Enable WKUSEC interrupt */
      break;
    case 6:
      VC_RTC->INTEN |= (1UL << VC_RTC_INTEN_INTEN6_Pos); /* Enable WKUCNT interrupt */
      break;
    default:
      return;
  }

  if (VC_RTC->INTEN != 0 && !m_rtc_int_irqn_enabled) {
    NVIC_ClearPendingIRQ(RTC_IRQn);
    NVIC_EnableIRQ(RTC_IRQn);
    m_rtc_int_irqn_enabled = true;
  }
}

static void vcrtc_int_disable(uint8_t intnum)
{
  uint32_t temp = VC_RTC->INTEN;

  switch (intnum) {
    case 2:
      temp &= ~(VC_RTC_INTEN_INTEN2_Msk); /* Disable WKUSEC interrupt */
      break;
    case 6:
      temp &= ~(VC_RTC_INTEN_INTEN6_Msk); /* Disable WKUCNT interrupt */
      break;
    default:
      (void) temp;
      return;
  }

  VC_RTC->INTEN = temp;

  if (VC_RTC->INTEN == 0 && m_rtc_int_irqn_enabled) {
    NVIC_ClearPendingIRQ(RTC_IRQn);
    NVIC_DisableIRQ(RTC_IRQn);
    m_rtc_int_irqn_enabled = false;
  }
}

static uint32_t vcrtc_get_wkucntr(void)
{
  return VC_RTC->WKUCNTR;
}

static void _rtc_tick_counter_update(void)
{
  m_rtc_tick_isr_flag++;
  m_rtc_tick_ns_counter += 976562;
  if (m_rtc_tick_isr_flag % 2) {
    m_rtc_tick_ns_counter++;
  }
  if (m_rtc_tick_ns_counter == 125000000) {
    m_rtc_tick_ms_counter += 125;
    m_rtc_tick_ns_counter = 0;
  }
}

void RTC_Handler(void)
{
  if ((VC_RTC->INTSTS & VC_RTC_INTEN_INTEN6_Msk) != 0) {
    /* RTC WKUCNT interrupt */
    VC_RTC->INTSTS |= (1UL << VC_RTC_INTEN_INTEN6_Pos);
    _rtc_tick_counter_update();
  }

  if (g_rtc_ticker_fire_interrupt || m_rtc_ticker_set_interrupt) {
    if (g_rtc_ticker_fire_interrupt) {
      if (m_rtc_ticker_set_interrupt && m_rtc_ticker_set_timestamp != 0) {
        if (m_rtc_ticker_set_timestamp <= vcrtc_get_us_ticker()) {
          m_rtc_ticker_set_timestamp = 0;
          m_rtc_ticker_set_interrupt = false;
        }
      }
      g_rtc_ticker_fire_interrupt = false;
      vcrtc_ticker_callback();
    } else {
      if (m_rtc_ticker_set_interrupt && m_rtc_ticker_set_timestamp != 0) {
        if (m_rtc_ticker_set_timestamp <= vcrtc_get_us_ticker()) {
          m_rtc_ticker_set_timestamp = 0;
          m_rtc_ticker_set_interrupt = false;
          vcrtc_ticker_callback();
        }
      }
    }
  }
}
