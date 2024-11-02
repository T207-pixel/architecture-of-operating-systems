#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

void myRead(int fd) {
    while (lseek(fd, -2, SEEK_CUR) >= 0) {
        char letter = 0;
        read(fd, &letter, 1);
        printf("%c", letter);
    }
    printf("\n"); // new line in EOF for better output
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong input arguments\nDo: ./a.out file\n(One single file is required!\n)");
        exit(1);
    }

    const char *fileNmae = argv[1];
    int fd = open(fileNmae, O_RDONLY);
    long fileSize = lseek(fd, 0, SEEK_END);
    printf("File Size: %ld\n", fileSize);

    if (fileSize > 0) {
        myRead(fd);
    } else {
        printf("File is empty!\nNothing to read\n");
        return 0;
    }

    return 0;
}