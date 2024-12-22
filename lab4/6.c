#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong input params!\nUsage: ./a.out <pipe_name>\n");
        exit(1);
    }

    mkfifo( argv[1], 0777);
    int fd = open(argv[1], O_WRONLY /*| O_NDELAY*/); // If O_NDELAY not set -> blocking until another process won't open file for reading
    write(fd, "Hello", 6);
    close(fd);
}