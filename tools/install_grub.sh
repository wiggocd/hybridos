#!/bin/bash

if [ ! -d "src/grub" ]; then
    git clone git://git.savannah.gnu.org/grub.git src/grub
fi

if [ ! -d "src/objconv" ]; then
    git clone https://github.com/vertis/objconv src/objconv
fi

if [ ! -f "src/objconv/objconv" ]; then
    if [ ! -f "/usr/local/bin/objconv" ]; then
        cd src/objconv && \
        g++ -o objconv -O2 src/*.cpp && \
        sudo cp objconv /usr/local/bin && \
        cd ../..
    fi
fi

if [ -d "src/grub" ]; then
    cd src

    cd grub
    ./bootstrap
    ./autogen.sh
    # aclocal
    # autoheader
    # automake --add-missing
    # autoreconf -f -i -Wall,no-obsolete
    cd ..

    if [ ! -d "grub_build" ]; then
        mkdir grub_build
    fi

    cd grub_build && \
    ../grub/configure --disable-werror TARGET_CC=i686-elf-gcc TARGET_OBJCOPY=i686-elf-objcopy \
    TARGET_STRIP=i686-elf-strip TARGET_NM=i686-elf-nm TARGET_RANLIB=i686-elf-ranlib --target=i686-elf && \
    make && \
    make install && \
    cd ../..
fi
