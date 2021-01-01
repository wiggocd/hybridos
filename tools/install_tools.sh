#!/bin/bash

create_tree() {
    if [ ! -d "src" ]; then
        mkdir src
    fi
}

linux() {
    create_tree && \
    ./get_binutils.sh && \
    ./install_binutils.sh && \
    ./get_gcc.sh && \
    ./install_gcc.sh
}

mac() {
    create_tree && \
    ./install_grub.sh
}

if [[ "$OSTYPE" == "darwin"* ]]; then
    mac
else
    linux
fi