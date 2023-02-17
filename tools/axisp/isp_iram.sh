#!/bin/sh

if [ -z ${ROM} ]; then
    ROM=./rom.bin
fi

if [ -z ${IMG} ]; then
    IMG=./magpie_iram.bin
fi

echo ""
echo "ROM = ${ROM}"
echo "IMG = ${IMG}"
echo ""

if [ ! -f ${ROM} ]; then
    echo ""
    echo "invlaid rom file!"
    echo ""
    exit 1
fi

if [ ! -f ${IMG} ]; then
    echo ""
    echo "invlaid image file!"
    echo ""
    exit 1
fi

./out/axisp isp ${ROM}

if [ $? -ne 0 ]; then
    exit 1
fi

./out/axisp -p1 isp ${IMG} 0x20000000

if [ $? -ne 0 ]; then
    exit 1
fi

./out/axisp -p1 reb 2

if [ $? -ne 0 ]; then
    exit 1
fi

