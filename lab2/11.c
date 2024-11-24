#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: %s 11-1 ls\n", argv[0]);
        exit(1);
    }
    
    if (fork() == 0) {
        execl(argv[1], argv[1], argv[2], NULL); // argv[2] - cli command
    } else {
        wait(NULL);
        return 0;
    }
}