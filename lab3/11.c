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
    sigset_t  empty_sigset;
    sigemptyset(&empty_sigset);

    if (this_pid < other_pid) {
        sigsuspend(&empty_sigset); // suspend for child
    }

    while(1) {
        printf("%d\n", this_pid);
        sleep(1);
        kill(other_pid, SIGUSR1);
        sigsuspend(&empty_sigset); // suspend for parent
    }
}

void signal_handler(int sig) {
    if (sig == SIGUSR1) {

    };
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    int parent_pid = getpid();
    int child_pid = fork();
    
    if ((child_pid) == 0) {
        synced(parent_pid);
    }
    else {
        synced(child_pid);
    }

    return 0;
}