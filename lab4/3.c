#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>

int main() {
    int fd[2]; 
    int fd_rev[2];

    // fd:     parent[0] <-- child[1]
    // fd_rev: parent[1] --> child[0]

    pipe2(fd, O_NONBLOCK);
    pipe2(fd_rev, O_NONBLOCK);

    if (fork() == 0) {  // Child process
        close(fd[0]);   // Close reading end for pipe fd
        close(fd_rev[1]); // Close writing end for pipe fd_rev
        int n, r;
        char buf[80] = {0};
        while(1) {
            memset(buf, 0, 80);
            n = read(STDIN_FILENO, buf, 80);
            if (n <= 0)     // Exit if was pressed Ctrl+D
                break;
            write(fd[1], buf, n); // Write from stdin in kernel buffer for output from pipe
            memset(buf, 0, 80);
            r = read(fd_rev[0], buf, 80); // Read from reading end of pipe fd_rev
            if (r > 0)
                printf("Child: %s", buf);
        }
        close(fd[1]);
        close(fd_rev[0]);
    } else {                // Parent process
        close(fd[1]);       // Close writing end pipe fd
        close(fd_rev[0]);   // Close reding end pipe fe_rev
        int r;

        do {
            char buf[80] = {0};
            r = read(fd[0], buf, 80);
            if (r > 0) {
                printf("Parent: %s", buf);
                write(fd_rev[1], buf, r);
            }
        } while(r);
        close(fd[0]);
        close(fd_rev[1]);
    }

    return 0;
}