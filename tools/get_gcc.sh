#!/bin/sh

SERVER_URL=https://ftp.gnu.org/gnu/gcc/

curl "$SERVER_URL" > tmp.html
RELEASENAME=$(cat tmp.html | sed -e 's/.*\/\">//' -e 's/\/<\/a>.*//' | grep -v tar | grep -v \< | tail -1)
rm tmp.html

if [ ! -d src ];
then
    mkdir src
fi

RELEASEARC_PATH=$PWD/src/$RELEASENAME.tar.gz
curl "$SERVER_URL/$RELEASENAME/$RELEASENAME.tar.gz" > $RELEASEARC_PATH

tar -xzvf $RELEASEARC_PATH -C src/
rm $RELEASEARC_PATH