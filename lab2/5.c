#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void printInfo() {
    pid_t pid, ppid; // PID - process id, PPID - parent process id.
    gid_t gid;
    
    pid = getpid();
    ppid = getppid();
    gid = getgid();
    printf("pid=%d\nppid=%d\ngid=%d\n\n", pid, ppid, gid);
}

int main() {
    int id;
    int status;
    int parrent = getpid();
    
    printf("Before fork\n");
    printInfo();
    
    id = fork(); // create new process
    printf("After fork\n");
    printInfo();

    int n;
    if (id == 0) {
        n = 1;
        printf("Child\n\n");
    } else {
        n = 6;
        printf("Parent\n\n");
    }

    if (id) { // sleep if main process
        sleep(300);
        printInfo();
    }

    for (int i = n; i < n + 5; i++) {
        printf("%d ", i);
        sleep(1);
        fflush(stdout);
    }

    printf("\n");
    return 0;
}