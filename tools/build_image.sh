#!/bin/bash

cd boot && \
mkdir -p bootimage/boot/grub && \
cp ../../bin/hybridos.bin bootimage/boot && \
cp grub.cfg bootimage/boot/grub && \
grub-mkrescue -o ../../bin/hybridos.iso bootimage