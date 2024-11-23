#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]) {
    // Init vars
    int srcFd = -2;
    int dstFd = -2;
    int forkResult = -2;
    ssize_t readBytes;
    const char *srcFile = argv[1];
    char* createdFilename;

    // Read file from CLI
    if (argc != 2) {
        printf("wrong input of parameters\nUse: %s filename\n", argv[0]);
        exit(1);
    }

    // Open file with big size
    srcFd = open(srcFile, O_RDONLY);

    // Creat new process with fork
    forkResult = fork();

    if (forkResult != 0) {
        createdFilename = "parentResFile";
    } else if (forkResult == 0) {
        createdFilename = "childResFile";
    }

    // Creat new file
    dstFd = open(createdFilename, O_RDWR | O_CREAT, 0644);

    // Read data with buffer untill everything won't be read
    char buf[256]; // НЕ ПОНИМАЮ КАК РАБОТАЕТ ЭТОТ КУСОК
    do {
        readBytes = read(srcFd, buf, sizeof(buf));
        write(dstFd, buf, readBytes);
        // printf("%s", buf);
        memset(buf, '\0', sizeof(buf));
    } while (readBytes == sizeof(buf));

    // Move pointer to the beginning of the file
    lseek(dstFd, 0, SEEK_SET);

    if (forkResult != 0) {
        int child_result;
        wait(&child_result);
        printf("parent result\n");
    } else {
        printf("child result\n");
    }

    // Read data from file in stdout
    do {
        readBytes = read(dstFd, buf, sizeof(buf));
        printf("%s", buf);
        memset(buf, '\0', sizeof(buf));
    } while(readBytes == sizeof(buf));

    exit(EXIT_SUCCESS);
}