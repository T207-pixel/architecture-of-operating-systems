#!/bin/bash

# Before script
gcc 7.c
rm -rf ./dir7
mkdir dir7
cd dir7

#Create different type of files

# Basic
mkdir testDir	# directory
touch testFile1	# common file
echo "abcde" > testFile1

# Special bits
touch testFile2 # file with suid bit
chmod u+s testFile2 

touch testFile3 # file with guid bit for
chmod g+s testFile3 

# Different types of devices
mknod named-pipe p	# Named pipe file
sudo mknod full-device c 1 7 # Character device file (like /dev/full due to priorities)
sudo mknod /tmp/dvd-rom b 11 0 # Block device like /dev/sr0

# Output everything
ls -lS

# Multiple runs program passing it all files
for file in *; do
	../a.out $file | tee -a ./7.log;
done

