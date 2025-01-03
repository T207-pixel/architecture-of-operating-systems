#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void child() {
    printf("before pause\n");
    pause();
    printf("after pause\n");
}

int main() {
    int childPid = fork();

    if (!childPid) { // child process
        child();
    } else {
        sleep(2);
        int res; // parent process
        kill(childPid, SIGUSR1);
        wait(&res);
        printf("wait res: %d\n", res);
    }
}