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

void do_action(char* processName) {
    char* msg = calloc(sizeof(processName) + 100, sizeof(char));
    strcpy(msg, processName);
    while(1) {
        char buf[100] = {0};
        int r = read(STDIN_FILENO, buf, 100);
        write(STDOUT_FILENO, strcat(msg, buf), sizeof(processName) + r);
        strcpy(msg, processName);
    }
}

int main() {
    int r = fork();
    do_action(r == 0 ? "[c]" : "[p]"); // Output if stdout gone in parent process or in child process 
}