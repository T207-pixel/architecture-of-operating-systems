#!/bin/bash

# Compile
gcc 9.c

# Clean previous results
rm -rf dir9
mkdir dir9
cd dir9

# Create file
echo "abc" > f1
cd ..

# Run programm
./a.out dir9/f1 dir9/f2
