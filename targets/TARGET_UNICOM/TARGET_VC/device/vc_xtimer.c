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

#include "vc_xtimer.h"

#define WIDTH_TO_MAXVAL(width) (UINT32_MAX >> (32 - width))
static xtimer_clock_t _xtimer_usec;
xtimer_clock_t *const XTIMER_USEC = &_xtimer_usec;

static void _add_entry_to_list(xtimer_clock_t *clock, xtimer_base_t *entry);
static void _del_entry_from_list(xtimer_clock_t *clock, xtimer_base_t *entry);
static void _xtimer_update(xtimer_clock_t *clock);

static unsigned int _cpu_irq_disable(void)
{
  uint32_t mask = __get_PRIMASK();
  __disable_irq();
  return mask;
}

static void _cpu_irq_restore(unsigned int state)
{
  __set_PRIMASK(state);
}

#if XTIMER_CONFIG_EXTEND
static inline uint32_t _min_u32(uint32_t a, uint32_t b)
{
  return a < b ? a : b;
}
#endif

static unsigned _is_set(const xtimer_clock_t *clock, const xtimer_t *t)
{
  if (!clock->list.next) {
    return 0;
  } else {
    return (t->base.next || &t->base == clock->last);
  }
}

void xtimer_remove(xtimer_clock_t *clock, xtimer_t *timer)
{
  unsigned int state = _cpu_irq_disable();
  if (_is_set(clock, timer)) {
    xtimer_update_head_offset(clock);
    _del_entry_from_list(clock, &timer->base);
    _xtimer_update(clock);
  }
  _cpu_irq_restore(state);
}

void xtimer_set(xtimer_clock_t *clock, xtimer_t *timer, uint32_t value)
{
  unsigned int state = _cpu_irq_disable();
  xtimer_update_head_offset(clock);
  if (_is_set(clock, timer)) {
    _del_entry_from_list(clock, &timer->base);
  }
  if (value > clock->adjust) {
    value -= clock->adjust;
  } else {
    value = 0;
  }
  timer->base.offset = value;
  _add_entry_to_list(clock, &timer->base);
  if (clock->list.next == &timer->base) {
#if XTIMER_CONFIG_EXTEND
    if (clock->max_value < UINT32_MAX) {
      value = _min_u32(value, clock->max_value >> 1);
    }
#endif
    clock->ops->set(clock, value);
  }
  _cpu_irq_restore(state);
}

static void _add_entry_to_list(xtimer_clock_t *clock, xtimer_base_t *entry)
{
  uint32_t delta_sum = 0;
  xtimer_base_t *list = &clock->list;
  while (list->next) {
    xtimer_base_t *list_entry = list->next;
    if ((list_entry->offset + delta_sum) > entry->offset) {
      break;
    }
    delta_sum += list_entry->offset;
    list = list->next;
  }
  entry->next = list->next;
  entry->offset -= delta_sum;
  if (entry->next) {
    entry->next->offset -= entry->offset;
  } else {
    clock->last = entry;
  }
  list->next = entry;
}

#if XTIMER_CONFIG_EXTEND
static uint32_t _add_modulo(uint32_t a, uint32_t b, uint32_t mod)
{
  if (a < b) {
    a += mod + 1;
  }
  return a - b;
}

xtimer_now_t _xtimer_now_extend(xtimer_clock_t *clock)
{
  unsigned int state = _cpu_irq_disable();
  uint32_t lower_now = clock->ops->now(clock);
  clock->checkpoint += _add_modulo(lower_now, clock->lower_last, clock->max_value);
  clock->lower_last = lower_now;
  xtimer_now_t now = clock->checkpoint;
  _cpu_irq_restore(state);
  return now;
}
#endif

void xtimer_update_head_offset(xtimer_clock_t *clock)
{
  uint32_t old_base = clock->list.offset;
  uint32_t now = xtimer_now(clock);
  uint32_t diff = now - old_base;
  xtimer_base_t *entry = clock->list.next;
  if (entry) {
    do {
      if (diff <= entry->offset) {
        entry->offset -= diff;
        break;
      } else {
        diff -= entry->offset;
        entry->offset = 0;
        if (diff) {
          /* skip timers with offset == 0 */
          do {
            entry = entry->next;
          } while (entry && (entry->offset == 0));
        }
      }
    } while (diff && entry);
  }
  clock->list.offset = now;
}

static void _del_entry_from_list(xtimer_clock_t *clock, xtimer_base_t *entry)
{
  xtimer_base_t *list = &clock->list;
  while (list->next) {
    xtimer_base_t *list_entry = list->next;
    if (list_entry == entry) {
      if (entry == clock->last) {
        /* if entry was the last timer, set the clocks last to the
         * previous entry, or NULL if that was the list ptr */
        clock->last = (list == &clock->list) ? NULL : list;
      }
      list->next = entry->next;
      if (list->next) {
        list_entry = list->next;
        list_entry->offset += entry->offset;
      }
      /* reset the entry's next pointer so _is_set() considers it unset */
      entry->next = NULL;
      break;
    }
    list = list->next;
  }
}

static xtimer_t *_now_next(xtimer_clock_t *clock)
{
  xtimer_base_t *entry = clock->list.next;
  if (entry && (entry->offset == 0)) {
    clock->list.next = entry->next;
    if (!entry->next) {
      /* The last timer just got removed from the clock's linked list */
      clock->last = NULL;
    }
    return (xtimer_t *)entry;
  } else {
    return NULL;
  }
}

static void _xtimer_update(xtimer_clock_t *clock)
{
#if XTIMER_CONFIG_EXTEND
  if (clock->max_value < UINT32_MAX) {
    if (clock->list.next) {
      clock->ops->set(clock, _min_u32(clock->list.next->offset, clock->max_value >> 1));
    } else {
      clock->ops->set(clock, clock->max_value >> 1);
    }
#else
  if (0) {
#endif
  } else {
    if (clock->list.next) {
      clock->ops->set(clock, clock->list.next->offset);
    } else {
      clock->ops->cancel(clock);
    }
  }
}

void xtimer_handler(xtimer_clock_t *clock)
{
#if XTIMER_CONFIG_EXTEND || XTIMER_CONFIG_NOW64
  if ((sizeof(xtimer_clock_t) == 8) || clock->max_value < UINT32_MAX) {
    /* calling now triggers checkpointing */
    uint32_t now = xtimer_now(clock);
    if (clock->list.next) {
      uint32_t target = clock->list.offset + clock->list.next->offset;
      int32_t diff = (int32_t)(target - now);
      if (diff > 0) {
        clock->ops->set(clock, _min_u32(diff, clock->max_value >> 1));
        return;
      }
    } else {
      clock->ops->set(clock, clock->max_value >> 1);
      return;
    }
  }
#endif
  clock->list.offset += clock->list.next->offset;
  clock->list.next->offset = 0;
  xtimer_t *entry = _now_next(clock);
  while (entry) {
    entry->callback(entry->arg);
    entry = _now_next(clock);
    if (!entry) {
      /* See if any more alarms expired during callback processing */
      /* This reduces the number of implicit calls to clock->ops->now() */
      xtimer_update_head_offset(clock);
      entry = _now_next(clock);
    }
  }
  _xtimer_update(clock);
}

static void _xtimer_usticker_set(xtimer_clock_t *clock, uint32_t value)
{
  if (clock != XTIMER_USEC) {
    return;
  }
  if (value < XTIMER_CONFIG_USEC_MIN) {
    value = XTIMER_CONFIG_USEC_MIN;
  }
  unsigned int state = _cpu_irq_disable();
  vc_usticker_set(value);
  _cpu_irq_restore(state);
}

static uint32_t _xtimer_usticker_now(xtimer_clock_t *clock)
{
  if (clock != XTIMER_USEC) {
    return 0;
  }
  return vc_usticker_read();
}

static void _xtimer_usticker_cancel(xtimer_clock_t *clock)
{
  if (clock != XTIMER_USEC) {
    return;
  }
  vc_usticker_clear();
}

static const xtimer_ops_t _xtimer_usticker_ops = {
  .set = _xtimer_usticker_set,
  .now = _xtimer_usticker_now,
  .cancel = _xtimer_usticker_cancel,
};

void xtimer_init(xtimer_clock_t *clock)
{
  clock->ops = &_xtimer_usticker_ops;
  clock->max_value = WIDTH_TO_MAXVAL(XTIMER_CONFIG_USEC_WIDTH);
  vc_usticker_init();
#if XTIMER_CONFIG_EXTEND
  xtimer_init_extend(clock);
#endif
}
