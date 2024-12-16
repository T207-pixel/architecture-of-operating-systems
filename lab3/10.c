#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("caught SIGINT\n");
    } else {
        signal(sig, SIG_DFL);
    }
}

int main() {
    signal(SIGINT, handle_signal);

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGALRM);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    printf("Try to do Ctrl -c or try to send -ALRM <PID>\n");
    sleep(30);
    printf("Unblocked.\n");
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);

    return 0;
}