#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Wrong input arguments\nDo: ./a.out file1 ...\n(Minimum one file is required!\n)");
        exit(1);
    }

    long maxFileSize = -1;
    char *fileWithMaxSizeName = "";
    struct stat buf = {0}; // buffer, stores file info

    for (int i = 1; i < argc; i++) {
        char *currentFile = argv[i];
        int ret = stat(currentFile, &buf); // POSIX function
        
        if (ret < 0) {
            printf("stat() didn't return != 0\nstat: %d error %d %s\n", ret, errno, strerror(errno));
            exit(1);
        }

        long currentFileSize = buf.st_size;
        printf("Current file name: %s\nCurrent file size is: %ld\n", currentFile, currentFileSize); // log info
        if (currentFileSize >= maxFileSize) {
            maxFileSize = currentFileSize;
            fileWithMaxSizeName = currentFile;
        }
    }

    printf("\nHeaviest filename: %s\nHeaviest file size: %ld\n", fileWithMaxSizeName, maxFileSize);

    return 0;
}