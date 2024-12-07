#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void child() {
    pause();
    exit(0);
}

int main() {
    int childPid = fork();

    if (!childPid) {
        child();
    } else {
        int res;
        kill(childPid, SIGUSR1);
        wait(&res);
        printf("wait res: %d\n", res);
    }
}