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
        printf("Childs info is above\n\n");
    } else {
        n = 6;
        printf("Parent info is above\n\n");
    }

    if (id == 0) { // allow child process to finish without interuptions from main process id != 0
        sleep(8);
        printInfo();
    }

    for (int i = n; i < n + 5; i++) {
        printf("%d ", i);
        sleep(1);
        if (id == 0) {
            sleep(100);
        }
        fflush(stdout);
    }

    printf("\n");
    return 0;
}

// Commands
// ps -o ppid= -p <PID> - output perents PID
// ps -o ppid=<PID> - output all perents PIDs