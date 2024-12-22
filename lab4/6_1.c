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
        printf("Wrong input params!\nUsage: ./6_1 <pipe_name>\n");
        exit(1);
    }
    
    int fd = open(argv[1], O_RDONLY /*| O_NDELAY*/);  // If O_NDELAY not set -> blocking until another process won't open file for writing
    char buf[256];
    int r = read(fd, buf, 256);
    printf("Read %d bytes from channel: %s", r, buf);
    close(fd);
}