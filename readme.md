# HybridOS
The goal of this project is to create a basic operating system in 32-bit x86 protected mode with text video output on a command line, booting from an external multiboot-compatible bootloader such as grub.

The system should be able to be built on posix systems such as Linux.

## Dependencies
<sub>Seperated by whitespace</sub>
> grub curl grep cut tar xorriso qemu

gcc and binutils including the as assembler are required, however are built from source as follows which is done by using the makefile linking to scripts from the tools directory.

Please note: the grub package on your os distribution must contain the `grub-mkrescue` executable in your path in order to run the os, and the `xorriso` package may differ depending on your host. The package should contain the following:
`libburn` `libisofs` `libisoburn`

The packages for `qemu` will also be os dependent, as the **qemu-system-i386** executable target must be in your path to run. See the below for examples on different distributions:

Arch Linux: `qemu` `qemu-arch-extra` [You may have to enable the extra multilib for pacman!]


## Building
Please run these commands from the project root.

To install the required toolchain and cross-compiler for the i686-elf target:
`make install`

This should build and install binutils and gcc from source.

To remove the downloaded source after install:
`make clean-install`

To build the OS:
`make`

To run the OS in qemu:
`make run`

Cheers and have a brilliant rest of your day.
