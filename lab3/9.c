#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h> 

// Uncomment to show behaviour with handling
// #define withHandler

void handle_signal(int sig) {
    if (sig == SIGALRM) {
        for (int i = 0; i < 1000; i++) {
            printf("iteration number: %d\n", i);
            for (int j = 0; j < 1000; j++)
                for (int k = 0; k < 1000; k++) ;
        }
    }
}

void child() {
    #ifdef withHandler
    signal(SIGALRM, handle_signal);
    #endif
    printf("before pause\n");
    alarm(5); // sends SIGALRM after passed seconds
    pause();
    printf("after pause\n");
}

int main() {
    int childPid = fork();

    if (!childPid) { // child process
        child();
    } else {
        int res; // parent process
        sleep(2);
        wait(&res);
        printf("wait res: %d\n", res);
    }
}