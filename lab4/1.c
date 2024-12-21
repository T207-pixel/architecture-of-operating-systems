#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>

// pipefd1: parent[1] --> child[0] // writes data from parent to child via one pipe
// pipefd2: parent[0] <-- child[1] // writes data from child to parent via another pipe

int main() {
    // Declared two arrays of left and right ends for two pipes
    int pipefd1[2];
    int pipefd2[2];

    // Created two pipes
    pipe(pipefd1);
    pipe(pipefd2);

    if (fork() == 0) { // Child process
        printf("C\n");
        close(pipefd1[1]); // Close write for first pipe
        close(pipefd2[0]); // Close read for second pipe

        char parentMessage[1024] = {0}; // Declared buffer for 1024 bytes initialized with zeros
        read(pipefd1[0], parentMessage, 1024); // Read from first pipe (from kernel buffer)
        printf("Parent: %s\n", parentMessage);

        const char* reply = "Information from child process, passed to parent process via second pipe!\n";
        write(pipefd2[1], reply, strlen(reply)); // Write info in second pipe (in kernel buffer)
        
        close(pipefd1[0]); // Close all opened pipes in this process due to except deadlocks
        close(pipefd2[1]);
        
    } else {
        printf("P\n");
        close(pipefd1[0]); // Close read from first pipe
        close(pipefd2[1]); // Close write from second pipe
        const char* buf = "Information from parent process, passed to child process via first pipe!\n";
        write(pipefd1[1], buf, strlen(buf)); // Write info in first pipe (kernel buffer)

        char reply[1024] = {0};
        read(pipefd2[0], reply, 1024); //  Read info from second pipe
        printf("Child: %s\n", reply);
        
        close(pipefd1[1]); // Close all opened pipes in this process due to except deadlocks
        close(pipefd2[0]);
        
    }

    return 0;
}