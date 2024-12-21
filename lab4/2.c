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
    int fd[2];  // Init array
    pipe(fd);   // Init pipe

    if (fork() == 0) {  // Child
        close(fd[0]);   // Close reading end of a pipe
        int n;

        while(1) {
            char buf[80] = {0};
            n = read(STDIN_FILENO, buf, 80);    // Read fron stdin
            if (n <= 0)     // Exit if was pressed Ctrl+D
                break;
            write(fd[1], buf, n); // Write from stdin in kernel buffer for output from pipe
        }

        close(fd[1]); // Close fd which was used for reading
    } else {
        close(fd[1]); // Close writing end for pipe
        int r;

        do {
            char buf[80] = {0};
            r = read(fd[0], buf, 80); // Reading end pipe
            printf("%s", buf);
        } while(r);
        close(fd[0]);
    }

    return 0;
}