#!/bin/bash

SERVER_URL=https://ftp.gnu.org/gnu/binutils/

curl "$SERVER_URL" > tmp.html
RELEASE_ARCNAME=$(cat tmp.html | grep -v '.sig' | grep '.tar.gz' | tail -1 | sed -e 's/^[^-]*href=\"//' -e 's/\".*//')
rm tmp.html

DIRPATH=src/$(echo $RELEASE_ARCNAME | sed 's/\.tar\.gz.*//')

if [ ! -d $DIRPATH ]; then
    if [ ! -d src ];
    then
        mkdir src
    fi

    RELEASEARC_PATH=$PWD/src/$RELEASE_ARCNAME
    curl "$SERVER_URL/$RELEASE_ARCNAME" > $RELEASEARC_PATH

    tar -xzvf $RELEASEARC_PATH -C src
    rm $RELEASEARC_PATH
fi