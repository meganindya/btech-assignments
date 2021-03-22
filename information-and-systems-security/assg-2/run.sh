#!/bin/bash

if [ "$#" != "0" ];
then
    if [ $1 == "1A" ]
    then
        gcc 1-a-cipher-shift.c
    elif [ "$1" == "1B" ]
    then
        gcc 1-b-cipher-multiplicative.c
    else
        echo "invalid question"
    fi

    ./a.out
    rm a.out
else
    echo "invalid question"
fi
