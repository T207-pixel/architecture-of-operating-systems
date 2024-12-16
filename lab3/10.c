#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

int main() {
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigaddset(&sigset, SIGUSR2);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    printf("Blocked\nTry to execute command:\nkill -USR1 <PID>\nkill -USR2 <PID>\n");
    sleep(30);
    printf("Unblocked.\n");
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);

    return 0;
}