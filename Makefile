export PREFIX=/usr/local
export TARGET=i686-elf

ASM_INPUT=src/boot.asm
C_INPUT=src/kernel.cpp

ASM_OBJ_OUT=bin/obj/boot.o
C_OBJ_OUT=bin/obj/kernel.o
C_BIN_OUT=bin/hybridos.bin

LD_SCRIPT=linker.ld
ASM_FLAGS=-f elf32
C_FLAGS=-std=c++98 -O2 -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti
LD_FLAGS=-ffreestanding -nostdlib

LD_OBJECTS=bin/obj/*

.SILENT:
all:
	cd tools && \
	./clean_bin.sh && \
	./create_tree.sh && \
	cd .. && \
	nasm -felf32 ${ASM_INPUT} -o ${ASM_OBJ_OUT} && \
	${TARGET}-gcc -c ${C_INPUT} -o ${C_OBJ_OUT} ${C_FLAGS} && \
	${TARGET}-gcc -T ${LD_SCRIPT} ${LD_OBJECTS} -o ${C_BIN_OUT} ${LD_FLAGS} && \
	make build-image

# nasm ${ASM_FLAGS} ${ASM_INPUT} -o ${ASM_OBJ_OUT}

.SILENT:
build-image:
	cd tools && \
	./build_image.sh

.SILENT:
run:
	# qemu-system-i686 -cdrom bin/hybridos.iso
	qemu-system-x86_64 -cdrom bin/hybridos.iso

.SILENT:
build-run:
	make
	make run

.PHONY: install
.SILENT:
install:
	cd tools && \
	./install_tools.sh && \
	cd .. && \
	make clean-tools

.SILENT:
clean:
	cd tools && \
	./clean_all.sh

.SILENT:
clean-bin:
	cd tools && \
	./clean_bin.sh

.SILENT:
clean-tools:
	cd tools && \
	./clean_install.sh