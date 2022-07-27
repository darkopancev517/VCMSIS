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

#include "i2c_api.h"

#if DEVICE_I2C

#include "vc_i2c.h"

typedef struct {
    struct i2c_s *owner;
} vci2c_state_t;

static vci2c_state_t vci2c_state[3] = { 0 };

static void i2c_configure_driver_instance(i2c_t *obj);

void i2c_init(i2c_t *obj, PinName sda, PinName scl)
{
    struct i2c_s *i2c_inst = obj;
    int instance = pin_instance_i2c(scl, sda);
    if (instance == NC) {
        return; /* Invalid I2C Pin */
    }

    /* Initialize I2C object */
    i2c_inst->instance = instance;
    i2c_inst->sda = sda;
    i2c_inst->scl = scl;
    i2c_inst->frequency = 62500; /* 62.5 KHz - default */
    i2c_inst->update = true;
    i2c_inst->is_slave = false;
    i2c_inst->is_enabled = false;

    i2c_configure_driver_instance(obj);
}

void i2c_frequency(i2c_t *obj, int hz)
{
    struct i2c_s *i2c_inst = obj;

#if DEVICE_I2CSLAVE
    /* Slaves automatically get frequency from master */
    if (i2c_inst->is_slave) {
        return;
    }
#endif

    i2c_inst->frequency = hz;
    i2c_inst->update = true;

    i2c_configure_driver_instance(obj);
}

/* Send START command */
int i2c_start(i2c_t *obj)
{
    struct i2c_s *i2c_inst = obj;
    int instance = i2c_inst->instance;
    int res = I2C_ERROR_NO_SLAVE;
    uint8_t status = 0;

    if (!i2c_inst->is_enabled) {
        i2c_inst->is_enabled = true;
        vci2c_enable(instance);
    }

    res = vci2c_send_start(instance);

    if (res != I2C_ERROR_NO_SLAVE) {
        // expected status: 0x8 - start condition has been transmitted
        status = vci2c_get_status(instance);
        if (status != 0x8) {
            return I2C_ERROR_BUS_BUSY;
        }
    }

    return res;
}

/* Send STOP command */
int i2c_stop(i2c_t *obj)
{
    struct i2c_s *i2c_inst = obj;
    int instance = i2c_inst->instance;
    int res = vci2c_send_stop(instance);
    return res;
}

/* Write one byte */
int i2c_byte_write(i2c_t *obj, int data)
{
    struct i2c_s *i2c_inst = obj;
    int instance = i2c_inst->instance;
    int res = I2C_ERROR_NO_SLAVE;
    uint8_t status = 0;

    res = vci2c_send_byte(instance, (uint8_t)data);

    if (res != I2C_ERROR_NO_SLAVE) {
        status = vci2c_get_status(instance);
        switch (status) {
        case 0x18: // SLA write has been transmitted, ACK received
            break;
        case 0x28: // Data byte has been transmitted, ACK received
            break;
        case 0x40: // SLA read has been transmitted, ACK received
            break;
        default:
            return I2C_ERROR_BUS_BUSY;
        }
    }

    return res;
}

/* Read one byte */
int i2c_byre_read(i2c_t *obj, int last)
{
    struct i2c_s *i2c_inst = obj;
    int instance = i2c_inst->instance;
    int res = I2C_ERROR_NO_SLAVE;
    uint8_t status = 0;

    res = vci2c_read_byte(instance);

    if (res != I2C_ERROR_NO_SLAVE) {
        // expected status: 0x58 - Data byte has been received, No ACK has been returned
        status = vci2c_get_status(instance);
        if (status != 0x58) {
            return I2C_ERROR_BUS_BUSY;
        }
    }

    return res;
}

/* Reset I2C peripheral */
void i2c_reset(i2c_t *obj)
{
    (void) obj;
}

/** Blocking reading data
 *
 *  @param obj     The I2C object
 *  @param address 7-bit address (last bit is 1)
 *  @param data    The buffer for receiving
 *  @param length  Number of bytes to read
 *  @param stop    Stop to be generated after the transfer is done
 *  @return Number of read bytes
 */
int i2c_read(i2c_t *obj, int address, char *data, int length, int stop)
{
    struct i2c_s *i2c_inst = obj;
    int instance = i2c_inst->instance;
    uint8_t status = 0;

    /* NOTE: - assume i2c_start() has been called before this functions
     *       - assume the `address` is (7-bit address) and last bit is 1 */

    // send slave read address
    vci2c_send_byte(instance, address);
    status = vci2c_get_status(instance);
    // expected status: 0x40 - SLA read has been transmitted. ACK has been received
    if (status != 0x40) {
        return I2C_ERROR_BUS_BUSY;
    }

    uint8_t byte = 0;

    // check if it just send one byte or not
    if (length > 1) {
        vci2c_ack_enable(instance);
        for (int i = 0; i < (length - 1); i++) {
            byte = vci2c_read_byte(instance);
            // expected status: 0x50 - Data byte has been received. ACK has been returned
            status = vci2c_get_status(instance);
            if (status != 0x50) {
                return I2C_ERROR_BUS_BUSY;
            }
            // update buffer
            *data = byte;
            data++;
        }
        vci2c_ack_disable(instance);
    }

    // this is last byte or if it was only send one byte
    byte = vci2c_read_byte(instance);
    status = vci2c_get_status(instance);
    // expected status: 0x58 - Data byte has been received. No ACK has been returned
    if (status != 0x58) {
        return I2C_ERROR_BUS_BUSY;
    }

    // update last byte or last data
    *data = byte;

    // send stop command if necessary
    if (stop) {
        vci2c_send_stop(instance);
    }

    return 0;
}

/** Blocking sending data
 *
 *  @param obj     The I2C object
 *  @param address 7-bit address (last bit is 0)
 *  @param data    The buffer for sending
 *  @param length  Number of bytes to write
 *  @param stop    Stop to be generated after the transfer is done
 *  @return
 *      zero or non-zero - Number of written bytes
 *      negative - I2C_ERROR_XXX status
 */
int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop)
{
    struct i2c_s *i2c_inst = obj;
    int instance = i2c_inst->instance;
    uint8_t status = 0;

    /* NOTE: - assume i2c_start() has been called before this functions */

    // send slave write address
    vci2c_send_byte(instance, address);
    // expected status: 0x18 - SLA write has been transmitted. ACK has been received
    status = vci2c_get_status(instance);
    if (status != 0x18) {
        return I2C_ERROR_BUS_BUSY;
    }

    // send data
    for (int i = 0; i < length; i++) {
        vci2c_send_byte(instance, *data);
        // expected status: 0x28 - Data byte has been transmitted. ACK has been received
        status = vci2c_get_status(instance);
        if (status != 0x28) {
            return I2C_ERROR_BUS_BUSY;
        }
        data++;
    }

    // send stop command if necessary
    if (stop) {
        vci2c_send_stop(instance);
    }

    return 0;
}

static void i2c_configure_driver_instance(i2c_t *obj)
{
    struct i2c_s *i2c_inst = obj;
    int instance = i2c_inst->instance;
    if ((i2c_inst != vci2c_state[instance].owner) || (i2c_inst->update)) {
        i2c_inst->update = false;
        vci2c_init(instance, &i2c_inst->frequency);
        vci2c_state[instance].owner = i2c_inst;
    }
}

#endif /* #if DEVICE_I2C */
