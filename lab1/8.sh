#!/bin/bash

gcc 8.c

echo -e "1) Copy from one file to another file\n2) Copy from stdin to stdout"
read choice

if [ $choice -eq 1 ] 
then
    # Create directory with sample files
    rm -rf dir8
    mkdir dir8
    cd dir8

    # Create orig file and write daya in it
    echo "abcdefg123" > origFile

    # Run binary
    cd ..
    ./a.out dir8/origFile dir8/cloneFile
else
    ./a.out
fi


