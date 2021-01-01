#!/bin/sh

SERVER_URL=https://ftp.gnu.org/gnu/binutils/

curl "$SERVER_URL" > tmp.html
RELEASE_ARCNAME=$(cat tmp.html | grep -v .sig | grep .tar.gz | tail -1 | sed -e 's/.*.gz\">//' -e 's/<\/a>.*//')
rm tmp.html

if [ ! -d src ];
then
    mkdir src
fi

# RELEASE=$($RELEASE_URL | cut -d "/" -f6)
RELEASEARC_PATH=$PWD/src/$RELEASE_ARCNAME
curl "$SERVER_URL/$RELEASE_ARCNAME" > $RELEASEARC_PATH

tar -xzvf $RELEASEARC_PATH -C src
rm $RELEASEARC_PATH