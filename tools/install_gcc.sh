#!/bin/sh

if [ -z $PREFIX ] || [ -z $TARGET ]; then
    echo "The prefix or target variable is not set. Please set these variables or run from the project makefile"
    exit
fi

if [ ! -d src ]; then
    echo "src directory does not exist. Please extract the source code for gcc to a subdirectory under the directory src, or use the script. Exiting..."
    exit
fi

RELEASENAME=$(ls src/ | grep gcc | tail -1)
RELEASEDIR=$PWD/src/$RELEASENAME

if [ -d "$RELEASEDIR" ]; then
    cd $RELEASEDIR
    if [ -d build ]; then
        rm -rf build
    fi

    mkdir build && \
    cd build && \

    # Headers found with: `gcc -print-prog-name=cpp` -v

    if [ "$OSTYPE" == "darwin"* ] && [ -d "/Applications/Xcode.app" ]; then
        if [ -d "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform" ]; then
            HEADERS="/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include"
        else
            HEADERS="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include"
        fi
    else
        HEADERS="/usr/include"
    fi

    # CONFIG_FLAGS="--target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --enable-languages=c,c++ --without-headers"
    CONFIG_FLAGS="--target=$TARGET --prefix="$PREFIX" --with-native-system-header-dir=$HEADERS --disable-nls --enable-languages=c,c++ --without-headers"

    echo "Configure flags: $CONFIG_FLAGS"

    $RELEASEDIR/configure $CONFIG_FLAGS && \
    make all-gcc && \
    # make all-target-libgcc && \
    sudo make install-gcc
    # sudo make install-target-libgcc
fi
