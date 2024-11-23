#!/bin/bash

creat_file() {
    for n in {1..3}; # prev value 100000
    do
        echo 'Frodo is main charachter of "The Lord of the rings"!!!' >> my_big_file
    done
}

rm -f my_big_file childResFile parentResFile

creat_file

gcc 9.c
./a.out my_big_file