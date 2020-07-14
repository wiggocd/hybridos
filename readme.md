# HybridOS
The goal of this project is to create a basic operating system in 32-bit x86 protected mode with text video output on a command line, booting from an external multiboot-compatible bootloader such as grub.

The os should be able to be built on posix systems such as Linux.
## Dependencies
<sub>Seperated by whitespace</sub>
> nasm curl grep cut tar

gcc and binutils are required, however are built from source as follows which is done by using the makefile linking to scripts from the tools directory.


## Building
Please run these commands from the project root.

To install the required toolchain/cross-compiler for the i686-elf target:
`make install`

To remove the downloaded source after install:
`make clean-install`

To build the OS:
`make`

To run the OS in qemu:
`make run`

Thank you for reading.
