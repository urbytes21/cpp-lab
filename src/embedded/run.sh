#!/bin/bash

set -e

BUILD_DIR=build
TARGET=firmware

mkdir -p ${BUILD_DIR}

echo "[1/3] Building ELF..."

arm-none-eabi-gcc \
    -mcpu=cortex-m3 \
    -mthumb \
    -nostdlib \
    -ffreestanding \
    startup.c main.c \
    -T stm32_flash.ld \
    -Wl,-Map=${BUILD_DIR}/${TARGET}.map \
    -o ${BUILD_DIR}/${TARGET}.elf

echo "[2/3] Generating BIN..."

arm-none-eabi-objcopy \
    -O binary \
    ${BUILD_DIR}/${TARGET}.elf \
    ${BUILD_DIR}/${TARGET}.bin

QEMU_ARGS="
    -M stm32vldiscovery
    -kernel ${BUILD_DIR}/${TARGET}.elf
    -semihosting-config enable=on,target=native
"

case "$1" in
    gui)
        echo "[3/3] Starting QEMU (GUI)..."

        qemu-system-arm ${QEMU_ARGS}
        ;;

    debug)
        echo "[3/3] Starting QEMU (Debug Mode)..."
        echo "Connect with:"
        echo "  arm-none-eabi-gdb ${BUILD_DIR}/${TARGET}.elf"
        echo "  target remote :1234"

        qemu-system-arm \
            ${QEMU_ARGS} \
            -S \
            -gdb tcp::1234
        ;;

    *)
        echo "[3/3] Starting QEMU (Terminal)..."

        qemu-system-arm \
            ${QEMU_ARGS} \
            -nographic
        ;;
esac
