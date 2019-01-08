#!/bin/bash -e

SED=sed

    # first rename all directories
#    for i in $(find . -type d | grep -v "^./.git" | grep kazusilver); do 
#        mv $i $(echo $i| $SED "s/kazusilver/kazusilver/")
#    done

    # then rename all files
    for i in $(find . -type f | grep -v "^./.git" | grep AltillyCoin); do
        mv $i $(echo $i| $SED "s/AltillyCoin/KazuSilver/")
    done

    # now replace all litecoin references to the new coin name
#    for i in $(find . -type f | grep -v "^./.git"); do
#        $SED -i "s/KazuSilver/KazuSilver/g" $i
#    done
