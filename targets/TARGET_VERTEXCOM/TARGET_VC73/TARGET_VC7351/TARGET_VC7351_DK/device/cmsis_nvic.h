#ifndef MBED_CMSIS_NVIC_H
#define MBED_CMSIS_NVIC_H

#if !defined(MBED_ROM_START)
#define MBED_ROM_START  0x4000000
#endif

#if !defined(MBED_ROM_SIZE)
#define MBED_ROM_SIZE  0x200000  // 2MB
#endif

#if !defined(MBED_RAM_START)
#define MBED_RAM_START  0x20000000
#endif

#if !defined(MBED_RAM_SIZE)
#define MBED_RAM_SIZE  0x40000  // 256 KB
#endif

#define NVIC_NUM_VECTORS        64
#define NVIC_RAM_VECTOR_ADDRESS MBED_RAM_START

#endif /* MBED_CMSIS_NVIC_H */
