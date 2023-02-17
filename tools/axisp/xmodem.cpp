
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "xmodem.h"

#if 0
void xmodem16::can()
{
    struct xmodem_packet x_pkt = {0};

    x_pkt.header = XMODEM_CAN;
    x_pkt.dir    = XMODEM_CAN;
    x_pkt.size   = 0;
    x_pkt.ack    = 0;

    ::printf("send out cancel request ... ");

    int r = ::write(h_dev, &x_pkt, 2);
    if (r != 2) {
        ::printf("failed (%d)\n", r);
        return;
    }

    ::printf("done\n");

    ::usleep(5000);

    // ----------------------------

    uint8_t ack[256] = { 0 };
    int i = 0;

    ::printf("waiting ack/nak ... ");

    while (i < 256) {
        r = ::read(h_dev, &ack[i], 1);
        if (r != 1)
            break;
        ++i;
    }

    if (ack[0] == XMODEM_ACK) {
        ::printf("0x%02x (acked)\n", (uint32_t)ack[0]);
    } else if (ack[0] == XMODEM_NAK) {
        ::printf("0x%02x (nacked)\n", (uint32_t)ack[0]);
    } else {
        ::printf("0x%02x (unknown)\n", (uint32_t)ack[0]);
    }

    if (i > 1) {
        ::printf("ack-msg: %s\n", (const char *)&ack[1]);
    }
}

void xmodem16::eot()
{
    x_pkt.header = XMODEM_EOT;
    x_pkt.dir    = 0;
    x_pkt.size   = 0;
    x_pkt.ack    = 0;

    ::printf("send out end-of-transmission request ... ");

    int r = ::write(h_dev, &x_pkt, 1);
    if (r != 1) {
        ::printf("failed (%d)\n", r);
        return;
    }

    ::printf("done\n");

    ::usleep(5000);

    // ----------------------------

    uint8_t ack[256] = { 0 };
    int i = 0;

    ::printf("waiting ack/nak ... ");

    while (i < 256) {
        r = ::read(h_dev, &ack[i], 1);
        if (r != 1)
            break;
        ++i;
    }

    if (ack[0] == XMODEM_ACK) {
        ::printf("0x%02x (acked)\n", (uint32_t)ack[0]);
    } else if (ack[0] == XMODEM_NAK) {
        ::printf("0x%02x (nacked)\n", (uint32_t)ack[0]);
    } else {
        ::printf("0x%02x (unknown)\n", (uint32_t)ack[0]);
    }

    if (i > 1) {
        ::printf("ack-msg: %s\n", (const char *)&ack[1]);
    }
}
#endif

void xmodem16::do_crc()
{
    uint8_t *data_iter = (uint8_t *)&pkt_out.cmd;
    int data_len = pkt_out.size;

    uint32_t crc;
    uint8_t i;

    crc = 0;

    while (--data_len >= 0) {

        crc = crc ^ (uint32_t)*data_iter++ << 8;
        i = 8;

        do {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while (--i);
    }

    pkt_out.data.out[pkt_out.size - 12] = (uint8_t)(crc >> 8);
    pkt_out.data.out[pkt_out.size - 11] = (uint8_t)crc;

    pkt_out_size = XMODEM_PKT_OUT_SIZE(pkt_out.size);
}
