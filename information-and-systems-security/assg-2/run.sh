#!/bin/bash

if [ "$#" != "0" ];
then
    if [ $1 == "1A" ] || [ $1 == "1B" ] || [ $1 == "1C" ] || [ $1 == "1D" ] ||
       [ $1 == "1E" ] || [ $1 == "2A" ] || [ $1 == "2B" ] || [ $1 == "2C" ]
    then
        gcc -c utils.c -o utils.o
        ar rcs libutils.a utils.o
    fi

    if [ $1 == "1A" ]
    then
        gcc -o main.o -c 1-a-cipher-shift.c
        gcc main.o -L. -lutils
    elif [ "$1" == "1B" ]
    then
        gcc -o main.o -c 1-b-cipher-multiplicative.c
        gcc main.o -L. -lutils
    elif [ "$1" == "1C" ]
    then
        gcc -o main.o -c 1-c-cipher-affine.c
        gcc main.o -L. -lutils
    elif [ "$1" == "1D" ]
    then
        gcc -o main.o -c 1-d-cipher-playfair.c
        gcc main.o -L. -lutils
    elif [ "$1" == "1E" ]
    then
        gcc -o main.o -c 1-e-cipher-hill.c
        gcc main.o -L. -lutils
    elif [ "$1" == "2A" ]
    then
        gcc -o main.o -c 2-a-attack-cipher-shift.c
        gcc main.o -L. -lutils
    elif [ "$1" == "2B" ]
    then
        gcc -o main.o -c 2-b-attack-cipher-multiplicative.c
        gcc main.o -L. -lutils
    elif [ "$1" == "2C" ]
    then
        gcc -o main.o -c 2-c-attack-cipher-affine.c
        gcc main.o -L. -lutils
    else
        echo "invalid question"
    fi

    ./a.out
    if [ $1 == "1A" ] || [ $1 == "1B" ] || [ $1 == "1C" ] || [ $1 == "1D" ] ||
       [ $1 == "1E" ] || [ $1 == "2A" ] || [ $1 == "2B" ] || [ $1 == "2C" ]
    then
        rm utils.o && rm libutils.a && rm main.o
    fi
    rm a.out
else
    echo "invalid question"
fi
