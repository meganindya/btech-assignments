#!/bin/bash

if [ "$#" != "0" ];
then
    if  [ "$1" == "1" ] || [ "$1" == "2" ] || [ "$1" == "3" ] ||
        [ "$1" == "4" ] || [ "$1" == "5" ] || [ "$1" == "6" ] ||
        [ "$1" == "7" ] || [ "$1" == "9" ] || [ "$1" == "10" ] ||
        [ "$1" == "8a" ] || [ "$1" == "8b" ];
    then
        lex $1.l
        cc lex.yy.c -ll
        rm lex.yy.c
        ./a.out
        rm a.out
    else
        echo "invalid question"
    fi
else
    echo "invalid question"
fi
