#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>


void synced(pid_t other_pid) {
    pid_t this_pid = getpid();
    sigset_t sigset;
    sigset_t e_sigset;
    sigaddset(&sigset, SIGUSR1);
    sigemptyset(&e_sigset);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    if (this_pid < other_pid) {
        sigsuspend(&e_sigset);
    }

    while(1) {
        printf("%d\n", this_pid);
        sleep(1);
        kill(other_pid, SIGUSR1);
        sigsuspend(&e_sigset);
    }
}

void handle_signal(int sig) {
    if (sig == SIGUSR1) {

    } else {
        SIG_DFL;
    }
}

void main() {
    struct sigaction sa;

    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    int parent_pid = getpid();
    int child_pid = fork();

    if (child_pid == 0) {
        synced(parent_pid);
    } else {
        synced(child_pid);
    }
        
}