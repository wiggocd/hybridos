#!/bin/sh

if [ -z $PREFIX ] || [ -z $TARGET ]; then
    echo "The prefix or target variable is not set. Please set these variables or run from the project makefile"
    exit
fi

if [ ! -d src ]; then
    echo "src directory does not exist. Please extract the source code for binutils to a subdirectory under the directory src, or use the script. Exiting..."
    exit
fi

RELEASENAME=$(ls src/ | grep binutils | tail -1)
RELEASEDIR=src/$RELEASENAME

if [ -d "$RELEASEDIR" ]; then
    cd $RELEASEDIR

    if [ "$OSTYPE" == "darwin"* ] && [ -d "/Applications/Xcode.app" ]; then
        if [ -d "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform" ]; then
            HEADERS="/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include"
        else
            HEADERS="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include"
        fi
    else
        HEADERS="/usr/include"
    fi

    CONFIG_FLAGS="--target=$TARGET --prefix="$PREFIX" --with-native-system-header-dir=$HEADERS --with-sysroot --disable-nls --disable-werror"

    ./configure $CONFIG_FLAGS && \
    make && \
    sudo make install
fi