/*
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved.
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

#if DEVICE_SERIAL

/* TODO: support asynchronous serial api */

#include "serial_api.h"
#include "pinmap.h"
#include "pinmap_ex.h"

#include "vc_uart.h"

#define UART_RX_BUFFER_SIZE   16

typedef struct {
    struct serial_s *owner;
    char rxbuf[UART_RX_BUFFER_SIZE];
} vcuart_state_t;

typedef struct {
    char *buf;
    unsigned int size;
    unsigned int start;
    unsigned int avail;
} vcuart_rb_t;

#define RINGBUFFER_INIT(BUF)  { (BUF), sizeof (BUF), 0, 0 }

static void _uart_serial_configure(serial_t *obj);
static void _uart_irq_handler(int uart_id);

static vcuart_state_t vcuart_state[7] = { 0 }; /* UART0 - UART6 */

static vcuart_rb_t vcuart_rbuf[7] = {
    RINGBUFFER_INIT(vcuart_state[0].rxbuf),
    RINGBUFFER_INIT(vcuart_state[1].rxbuf),
    RINGBUFFER_INIT(vcuart_state[2].rxbuf),
    RINGBUFFER_INIT(vcuart_state[3].rxbuf),
    RINGBUFFER_INIT(vcuart_state[4].rxbuf),
    RINGBUFFER_INIT(vcuart_state[5].rxbuf),
    RINGBUFFER_INIT(vcuart_state[6].rxbuf)
};

static int _uart_rbuf_add(vcuart_rb_t *rb, char c);
static int _uart_rbuf_get(vcuart_rb_t *rb);

/**
 * Global variables expected by mbed_retarget.cpp for STDOUT.
 */
int stdio_uart_inited = 0;
serial_t stdio_uart = { 0 };

void serial_init(serial_t *obj, PinName tx, PinName rx)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;

    uart_object->instance = pin_instance_uart(tx, rx);

    if (obj->instance == -1) {
        return;
    }

    /* Uart default parameter */
    uart_object->baudrate = 115200UL;
    uart_object->databits = 8UL;
    uart_object->stopbits = 1UL;
    uart_object->parity = VCUART_PARITY_NONE;
    uart_object->pin_tx = tx;
    uart_object->pin_rx = rx;

    /* Uart IRQ default setting */
    uart_object->handler = 0;
    uart_object->context = 0;
    uart_object->irq_mask = 0;

    if (obj == &stdio_uart) {
        stdio_uart_inited = 1;
    }

    uart_object->update = true;
    _uart_serial_configure(obj);
}

void serial_free(serial_t *obj)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;
    int instance = uart_object->instance;
    vcuart_power_off(instance);
    // TODO: release UART GPIO peripheral and reset UART register
}

void serial_baud(serial_t *obj, int baudrate)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;
    int instance = uart_object->instance;
    vcuart_set_baudrate(instance, baudrate);
    uart_object->baudrate = baudrate;
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;
    int instance = uart_object->instance;
    vcuart_set_mode(instance, data_bits, (uint8_t)parity, stop_bits);
    uart_object->databits = data_bits;
    uart_object->parity = (uint32_t)parity;
    uart_object->stopbits = stop_bits;
}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;
    uart_object->handler = (uint32_t)handler;
    uart_object->context = id;
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;
    int instance = uart_object->instance;
    int type = (irq == TxIrq) ? VCUART_TX_IRQ : VCUART_RX_IRQ;
    if (enable) {
        uart_object->irq_mask |= type;
        _uart_serial_configure(obj);
        vcuart_set_irq(instance, type);
    } else {
        uart_object->irq_mask &= ~type;
    }
}

int  serial_getc(serial_t *obj)
{
    //MBED_ASSERT(obj);
    int res = -1;
    struct serial_s *uart_object = obj;
    int instance = uart_object->instance;

    /* Take ownership and configure UART if necessary. */
    _uart_serial_configure(obj);

    /* serial_getc is a blocking call */
    while ((res = _uart_rbuf_get(&vcuart_rbuf[instance])) == -1);

    return res;
}

void serial_putc(serial_t *obj, int c)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;
    int instance = uart_object->instance;
    vcuart_putchar(instance, (char)c);
}

int  serial_readable(serial_t *obj)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;
    int instance = uart_object->instance;

    /* Take ownership and configure UART if necessary. */
    _uart_serial_configure(obj);

    vcuart_rb_t *rb = &vcuart_rbuf[instance];

    return (rb->avail != 0);
}

int  serial_writable(serial_t *obj)
{
    (void) obj;
    return 1; /* not uart asynchronous: always asume it's writeable */
}

void serial_clear(serial_t *obj)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;
    uart_object->update = true;
    _uart_serial_configure(obj);
}

void serial_break_set(serial_t *obj)
{
    (void) obj;
    /* TODO: set uart TX pin to low */
}

void serial_break_clear(serial_t *obj)
{
    (void) obj;
    /* TODO: set uart TX pin to high (default). */
}

void serial_pinout_tx(PinName tx)
{
    (void) tx;
    /**
     * Legacy API. Not used by Mbed.
     */
}

// Helper functions

static void _uart_serial_configure(serial_t *obj)
{
    //MBED_ASSERT(obj);
    struct serial_s *uart_object = obj;
    int instance = uart_object->instance;
    /* Only configure if instance owner has changed or an update is forced. */
    if ((uart_object != vcuart_state[instance].owner) || (uart_object->update)) {
        uart_object->update = false;
        uint32_t baudrate = uart_object->baudrate;
        uint8_t parity = uart_object->parity;
        uint8_t databits = uart_object->databits;
        uint8_t stopbits = uart_object->stopbits;
        vcuart_init(instance, baudrate, parity, databits, stopbits);
        vcuart_state[instance].owner = uart_object;
    }
}

static void _uart_irq_handler(int uart_id)
{
    if ((VC_UART(uart_id)->INTSTS & VC_UART_INTSTS_RXIF_Msk) != 0) {
        uint32_t temp = VC_UART(uart_id)->INTSTS;
        temp |= (1UL << VC_UART_INTSTS_RXIF_Pos);
        VC_UART(uart_id)->INTSTS = temp;
        _uart_rbuf_add(&vcuart_rbuf[uart_id], (char)VC_UART(uart_id)->DATA);
        if (vcuart_state[uart_id].owner->handler != 0) {
            uart_irq_handler callback = (uart_irq_handler)vcuart_state[uart_id].owner->handler;
            uint32_t mask = vcuart_state[uart_id].owner->irq_mask;
            if (callback && (mask & VCUART_RX_IRQ)) {
                uint32_t context = vcuart_state[uart_id].owner->context;
                callback(context, RxIrq);
            }
        }
    }
}

static void _rbuf_add_tail(vcuart_rb_t *rb, char c)
{
    unsigned pos = rb->start + rb->avail++;
    if (pos >= rb->size) {
        pos -= rb->size;
    }
    rb->buf[pos] = c;
}

static char _rbuf_get_head(vcuart_rb_t *rb)
{
    char res = rb->buf[rb->start];
    if ((--rb->avail == 0) || (++rb->start == rb->size)) {
        rb->start = 0;
    }
    return res;
}

static int _uart_rbuf_add(vcuart_rb_t *rb, char c)
{
    int res = -1;
    if (rb->avail == rb->size) {
        res = (unsigned char)_rbuf_get_head(rb);
    }
    _rbuf_add_tail(rb, c);
    return res;
}

static int _uart_rbuf_get(vcuart_rb_t *rb)
{
    if (rb->avail != 0) {
        return (unsigned char)_rbuf_get_head(rb);
    } else {
        return -1;
    }
}

void UART0_Handler(void)
{
    _uart_irq_handler(0);
}

void UART1_Handler(void)
{
    _uart_irq_handler(1);
}

void UART2_Handler(void)
{
    _uart_irq_handler(2);
}

void UART3_Handler(void)
{
    _uart_irq_handler(3);
}

void UART4_Handler(void)
{
    _uart_irq_handler(4);
}

void UART5_Handler(void)
{
    _uart_irq_handler(5);
}

void UART6_Handler(void)
{
    _uart_irq_handler(6);
}

#endif /* DEVICE_SERIAL */
