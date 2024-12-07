#define _XOPEN_SOURCE 700 // guarantees no red lines due to sigaction in vscode
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {

    signal(SIGCHLD, SIG_IGN);

    printf("parent pid %d\n", getpid());

    for (int i = 0; i < 3; i++) { // Totaly created 4 processes
        if (fork() == 0) {
            printf("child pid %d\n", getpid());
            sleep(1);
            exit(0);
        }
    }

    while(1) {
        sleep(1);
    }

    return 0;
}