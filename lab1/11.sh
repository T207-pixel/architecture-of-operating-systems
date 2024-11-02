#!/bin/bash

# Compile
gcc 11.c

# Clean directory
rm -rf dir11
mkdir dir11
cd dir11

# Create files
echo "abc" > f1
echo "abcd" > f2
echo "abcde" > f3
echo "abcd" > f4
echo "ab" > f5

# Run program
cd ..
./a.out dir11/*