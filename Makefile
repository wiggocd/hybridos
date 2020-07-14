export PREFIX=/usr/local/
export TARGET=i686-elf

ASMINPUT=src/boot.asm
C_INPUT=src/kernel.cpp

ASM_OBJ_OUT=bin/obj/boot.o
C_OBJ_OUT=bin/obj/kernel.o
C_BIN_OUT=bin/kernel.bin

LD_SCRIPT=linker.ld
CFLAGS= -std=c++98 -O2 -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS= -ffreestanding -nostdlib

LD_OBJECTS=bin/obj/*

all:
	cd tools && \
	./checkbintree.sh && \
	cd .. && \
	nasm ${ASMINPUT} -o ${ASM_OBJ_OUT}
	${TARGET}-gcc -c ${C_INPUT} -o ${C_OBJ_OUT} ${CFLAGS}
	${TARGET}-gcc -T ${LD_SCRIPT} ${LD_OBJECTS} -o ${C_BIN_OUT} ${LDFLAGS}

run:


.PHONY: install
install:
	cd tools && \
	mkdir src && \
	./getbinutils.sh && \
	./install_binutils.sh && \
	./getgcc.sh && \
	./install_gcc.sh && \
	make clean-install

clean:
	cd tools && \
	./clean-bin.sh

clean-bin:
	cd tools && \
	./clean-bin.sh

clean-install:
	cd tools && \
	./clean-install.sh

clean-all:
	cd tools && \
	./clean-all.sh