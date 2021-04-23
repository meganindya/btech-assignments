#!/bin/bash

if [ "$#" != "0" ];
then
    if [ $1 == "1" ] || [ $1 == "2A" ] || [ $1 == "2B" ] ||
       [ $1 == "3" ] || [ $1 == "4A" ] || [ $1 == "4B" ]
    then
        gcc -c ../utils.c -o utils.o
        ar rcs libutils.a utils.o
    fi

    if [ $1 == "1" ]
    then
        gcc -o main.o -c 1-cipher-auto-key.c
        gcc main.o -L. -lutils
    elif [ "$1" == "2A" ]
    then
        gcc -o main.o -c 2-a-cipher-vigenere.c
        gcc main.o -L. -lutils
    elif [ "$1" == "2B" ]
    then
        1
        # gcc -o main.o -c 1-b-cipher-multiplicative.c
        # gcc main.o -L. -lutils
    elif [ "$1" == "3" ]
    then
        1
        # gcc -o main.o -c 1-c-cipher-affine.c
        # gcc main.o -L. -lutils
    elif [ "$1" == "4A" ]
    then
        1
        # gcc -o main.o -c 1-d-cipher-playfair.c
        # gcc main.o -L. -lutils
    elif [ "$1" == "4B" ]
    then
        1
        # gcc -o main.o -c 1-e-cipher-hill.c
        # gcc main.o -L. -lutils
    else
        echo "invalid question"
    fi

    ./a.out
    if [ $1 == "1" ] || [ $1 == "2A" ] || [ $1 == "2B" ] ||
       [ $1 == "3" ] || [ $1 == "4A" ] || [ $1 == "4B" ]
    then
        rm utils.o && rm libutils.a && rm main.o
    fi
    rm a.out
else
    echo "invalid question"
fi
