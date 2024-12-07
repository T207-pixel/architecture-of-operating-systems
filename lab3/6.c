#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void child() {
    for (int i = 0; i < 100; i++) {
        printf("loop %d\n", i);
        for (int j = 0; j < 100; j++)
            for (int k = 0; k < 100; k++);
    }
}

int main() {
    int childPid = fork();

    if (!childPid) {
        child();
    } else {
        int res;
        kill(childPid, SIGUSR2);
        wait(&res);
        printf("wait res: %d\n", res);
    }
}