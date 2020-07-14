#!/bin/sh

if [ -z $PREFIX ] || [ -z $TARGET ];
then
    echo
    echo "The prefix or target variable is not set. Please set these variables or run from the project makefile!"
    echo
    exit
fi

if [ ! -d src ];
then
    echo
    echo "src directory does not exist. Please extract the source code for gcc to a subdirectory under the directory src, or use the script. Exiting..."
    echo
    exit
fi

# To avoid the error: the directory that should contain system headers does not exist, when building gcc
if [ ! -d $PREFIX/$TARGET/sys-root/usr/include ];
then
    sudo mkdir -p /usr/local/i686-elf/sys-root/usr/include
fi

# sudo mkdir /usr/local/i686-elf/sys-root
# sudo mkdir /usr/local/i686-elf/sys-root/usr
# sudo mkdir /usr/local/i686-elf/sys-root/usr/include

RELEASENAME=$(ls src/ | grep gcc | tail -1)
RELEASEDIR=$PWD/src/$RELEASENAME

cd $RELEASEDIR
if [ -d build ];
then
    rm -rf build
fi

mkdir build && \
cd build && \
$RELEASEDIR/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --enable-languages=c,c++ --without-headers && \
make all-gcc && \
# make all-target-libgcc && \
sudo make install-gcc # && \
# sudo make install-target-libgcc