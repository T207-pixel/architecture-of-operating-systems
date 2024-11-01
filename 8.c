#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdint.h>

extern int errno;

void myCopy(int origFd, int cloneFd, long origFileSize) {
    int result = -1;
    uint8_t *buffer = (uint8_t*)calloc(origFileSize, sizeof(uint8_t));
    int quantityOfBytes = read(origFd, buffer, origFileSize);
    
    if (quantityOfBytes >= 0) {
        result = write(cloneFd, buffer, origFileSize);
    } else {
        printf("write didn't return > 0\nstat: %d error %d %s\n", result, errno, strerror(errno));
        exit(1);
    }
        
    printf("Data was outputed in terminal, check string above\n");
    free(buffer);
}

void checkRetValue(int retValue, const char *errorStr) {
    if (retValue != 0) {
            printf(errorStr, retValue, errno, strerror(errno));
            exit(1);
        }
}

void checkOpen(int fd, const char *errorStr) {
    if (fd < 0) {
        printf(errorStr, fd, errno, strerror(errno));
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    // Init variables
    int origFd = -1;
    int cloneFd = -1;
    long origFileSize = -1;
    
    // For standart input, output
    if (argc == 1) {
        origFd = 0;
        cloneFd = 1;
        origFileSize = 4096;

        myCopy(origFd, cloneFd, origFileSize);
    // For files
    } else if (argc == 3) {
        const char *origFile = argv[1];
        const char *cloneFile = argv[2];

        origFd = open(origFile, O_RDONLY); // why we don't set here perms like 444
        checkOpen(origFd, "open origFile didn't return > 2\nstat: %d error %d %s\n");
        printf("origFd: %d\n", origFd);
        
        // Get previous file mode with stat.h and set same perms to new creating file
        struct stat buf; // stores stat data                                                
        int ret = stat(origFile, &buf); // POSIX function
        origFileSize = buf.st_size;
        if (origFileSize == 0) {
            printf("Warning: Copying file is empty\n");
        }
        checkRetValue(ret, "Stat didn't return 0\nstat: %d error %d %s\n");

        cloneFd = open(cloneFile, O_CREAT | O_RDWR, buf.st_mode);
        checkOpen(origFd, "open cloneFile didn't return > 2\nstat: %d error %d %s\n");
        printf("cloneFd: %d\n", origFd);

        myCopy(origFd, cloneFd, origFileSize);
        
        int res = close(origFd);
        checkRetValue(res, "1close didn't return 0\nclose: %d error %d %s\n");
        res = close(cloneFd);
        checkRetValue(res, "2close didn't return 0\nclose: %d error %d %s\n");

        printf("Everything was copied.\nCheck dir8\n");
    } else {
        printf("Wrong input arguments\nDo: ./a.out srcfile distfile\nOr Do: ./a.out (run without args)\n");
        exit(1);
    }

    return 0;
}