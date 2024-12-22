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
    int fd[2];  // Init array
    pipe(fd);   // Init pipe

    if (fork() == 0) {  // Child
        close(fd[0]);   // Close reading end of a pipe
        dup2(fd[1], STDOUT_FILENO); // Copy eriting pipe end in stdout
        execl("./4_1", "./4_1", NULL); // execute 4_1 bin
    } else {
        close(fd[1]); // Close fd which was used for reading
        int r;
        char buf[80] = {0};
        do {
            memset(buf, 0, 80);
            r = read(fd[0], buf, 80); // Reading end pipe
            printf("%s", buf);
        } while(r);
        close(fd[0]);
    }

    return 0;
}