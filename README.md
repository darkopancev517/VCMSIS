# ARM CMSIS + MbedOS HAL driver

## Supported MCU:

1. **VC6320** (Phoenix1)
2. **VC6330** (Phoenix2)
3. **VC7351** (Sonata)

## Supported BOARD:
Phoenix1 (VC6320):
- **VC6320_MTR** (Phoenix2 HPLC meter board)

Phoenix2 (VC6330):
- **VC6330_FPGA** (Phoenix2 VCU118 FPGA board)

Sonata (VC7351):
- **VC7351_DK** (Sonata EVB)

## Prerequisites

### Minimal GCC toolchain version:
```
gcc-arm-none-eabi-6-2017-q2-update
```

### Set your toolchain PATH:
Download ARM toolchain from: [arm-toolchain-download](https://developer.arm.com/downloads/-/gnu-rm)

Create new script file: envsetup.sh
```
#!/bin/bash

TOOLCHAIN_PATH=<your_toolchain_path>/gcc-arm-none-eabi-6-2017-q2-update/bin
export PATH=$TOOLCHAIN_PATH:$PATH
```

Change envsetup.sh file permission: **chmod +x envsetup.sh**

Run: **source envsetup.sh**

### Install dependencies (Only for CMAKE build):
```
sudo apt-get install cmake
```

## FAQ

### How to build?

**CMAKE:**
```
./script/cmake-build <board_name>

./script/cmake-build VC6330_FPGA (for Phoenix2 FPGA board)
./script/cmake-build V7351_DK (for Sonata EVB)
./script/cmake-build VC6320_MTR (for Phoenix1 Meter board)
```

**Makefile:**
```
./script/make-build <board_name>

./script/make-build VC6330_FPGA (for Phoenix2 FPGA board)
./script/make-build V7351_DK (for Sonata EVB)
./script/make-build VC6320_MTR (for Phoenix1 Meter board)
```

### How to update Phoenix BBP image?
- Copy your new DSP file to **targets/TARGET_UNICOM/TARGET_VC/device/plc/hplc/bbp/TARGET_MCU**
- Move old dsp file from the bbp directory to backup (OPTIONAL)
- Run image *split_image.sh* script (Note: you should see the results in **output** and **infom** directory)
- Make sure your toolchain PATH is set, otherwise the *split_image.sh* will not generate correct image

Example:
```
cd targets/TARGET_UNICOM/TARGET_VC/device/plc/hplc/bbp/<TARGET_MCU>
./split_image.sh <your_dsp_file>.dat
```

### How to update sonata RF firmware image?
Copy sonata firmware image: **sonata_radio.bin sonata_dsp_iram.bin sonata_dsp_dram0.bin sonata_dsp_dram1.bin**

Destination: **targets/TARGET_UNICOM/TARGET_VC/device/rf**

### Where is my build results?
```
build/<board_name>/<board_name>_soc.bin (for soc only image)
build/<board_name>/<board_name>_with_rf.bin (for soc + rf image)
build/<board_name>/<board_name>_with_plc.bin (for soc + plc image)
```
