## HybridOS

The goal of this project is to create a basic operating system in 32-bit x86 protected mode with text video output on a command line, booting from an external multiboot-compatible bootloader such as grub.

The system should be able to be built on Unix-like systems.


# Installation
Attach media from the `releases` section to a virtual machine or write the media to run on a physical system.


# Build Dependencies
Linux: `gcc` `gmp` `mpfr` `mpc` `curl` `grep` `cut` `tar` `grub` `libburn` `libisofs` `libisoburn` `xorriso` `mtools` `grub-mkrescue` `qemu`

macOS: `gcc` `automake` `autoconf` `xorriso` `i686-elf-binutils` `i686-elf-gcc` `qemu`

Install these dependencies using the package manager for your OS.

______

*Tested build environments include:* Arch Linux 2020.03.01 x64 (Kernel 5.5.6), macOS Catalina 10.15.7

QEMU packages for Arch Linux: `qemu` `qemu-arch-extra`


# Building
`make linux-tools` - **[Linux only]** Install the required toolchain and cross-compiler for the i686-elf target

`make` - Build the OS

`make run` - Run the OS in QEMU

`make clean-tools` - Remove the downloaded toolchain sources after install

______

Thanks for reading.
