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
    echo "src directory does not exist. Please extract the source code for binutils to a subdirectory under the directory src, or use the script. Exiting..."
    echo
    exit
fi

RELEASENAME=$(ls src/ | grep binutils | tail -1)
RELEASEDIR=$PWD/src/$RELEASENAME

cd src/$RELEASEDIR
./configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror && \
make && \
sudo make install