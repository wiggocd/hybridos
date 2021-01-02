#!/bin/bash

SERVER_URL=https://ftp.gnu.org/gnu/gcc/

curl "$SERVER_URL" > tmp.html
RELEASE_DIR=$(cat tmp.html | grep 'DIR' | grep 'gcc' | tail -1 | sed -e 's/^[^-]*href=\"//' -e 's/\".*//')
rm tmp.html

curl "$SERVER_URL/$RELEASE_DIR" > tmp.html
RELEASE_ARCNAME=$(cat tmp.html | grep '.tar.gz\"' | tail -1 | sed -e 's/^[^-]*href=\"//' -e 's/\".*//')

DIRPATH=src/$RELEASE_DIR

if [ ! -d $DIRPATH ]; then
    if [ ! -d src ];
    then
        mkdir src
    fi

    RELEASEARC_PATH=$PWD/src/$RELEASE_ARCNAME
    curl "$SERVER_URL/$RELEASE_DIR$RELEASE_ARCNAME" > $RELEASEARC_PATH

    tar -xzvf $RELEASEARC_PATH -C src
    rm $RELEASEARC_PATH
fi