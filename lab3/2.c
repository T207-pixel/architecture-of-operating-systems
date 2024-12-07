#define _XOPEN_SOURCE 700 // guarantees no red lines due to sigaction in vscode
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigint(int sig) {
    printf("Caught signal %d\n", sig);
    exit(0);
}

int main() {
    struct sigaction sigAct;

    sigAct.sa_handler = handle_sigint;
    sigemptyset(&sigAct.sa_mask); // clear signals mask ensures, that other signals won't be ignored during execution of handler
    sigaction(SIGINT, &sigAct, NULL);

    while(1) {
        sleep(1);
    }

    return 0;
}