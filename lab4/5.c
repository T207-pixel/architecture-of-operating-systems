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
    pipe(fd);

    if (fork() == 0) { // Child process writes in pipe
        close(fd[0]); // Close read
        dup2(fd[1], STDOUT_FILENO); // Copy writing pipe in stdout (1)
        system("who"); // Exec cmd from child
    } else { // Parent process reads from pipe output of child process `who`
        close(fd[1]); // Clode write
        dup2(fd[0], STDIN_FILENO); // Copy read pipe end in stdin (0)
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}