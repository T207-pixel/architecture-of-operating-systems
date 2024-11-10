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

    if (id != 0) { // allow child process to finish without interuptions
        int childRes;
        pid_t childPid = wait(&childRes);
        printf("Check child id and result after child exits\n");
        printf("child pid %d\n", childPid);
        printf("child result %d\n\n", childRes);
    }

    for (int i = n; i < n + 5; i++) {
        printf("%d ", i);
        sleep(1);
        fflush(stdout);
    }

    printf("\n");
    return 0;
}