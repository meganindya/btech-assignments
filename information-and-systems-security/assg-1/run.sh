#!/bin/bash

if [ "$#" != "0" ];
then
    if [ $1 == "A1" ]
    then
        gcc A-1-additive-inverse.c
    elif [ "$1" == "A2" ]
    then
        gcc A-2-multiplicative-inverse.c
    elif [ "$1" == "A3" ]
    then
        gcc A-3-matrix-inverse.c -lm
    elif [ "$1" == "A4" ]
    then
        gcc A-4-diffie-hellman.c -lm
    elif [ "$1" == "B1" ]
    then
        gcc B-1-euclid-gcd-algorithm.c
    elif [ "$1" == "B2" ]
    then
        gcc B-2-extended-euclid-algorithm.c
    else
        echo "invalid question"
    fi

    ./a.out
    rm a.out
else
    echo "invalid question"
fi
