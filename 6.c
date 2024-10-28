#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern int errno;

void myLog(char *syscall, int fd, int errorCode, char *errorString) {
    printf("Syscall: %s\nRet: %d\nError code: %d\nError string: %s\n", syscall, fd,
     errorCode, errorString);
}

long permissions(int permission) {
    switch (permission) {
    case 222:
        return O_WRONLY ;
    case 444:
        return O_RDONLY;
    case 666:
        return  O_RDWR;
    default:
        return -1;
    }
}

void myWrite(int fd) {
    char arr[100];
    printf("Write data in file\n");
    scanf("%s", arr);
    write(fd, arr, strlen(arr));
    myLog("write", fd, errno, strerror(errno));
}

void myRead(int fd, char isSimplRead) {
    int n = 0;
    if (isSimplRead == 0){
        lseek(fd, 0, SEEK_SET); // mv pointer to the beginning of file, overwise doesn't work reading
        myLog("lseek", fd, errno, strerror(errno));
    }

    printf("number of bytes to read: ");
    scanf("%d", &n);

    char *buf = calloc(n, sizeof(char));
    read(fd, buf, n);
    myLog("read", fd, errno, strerror(errno));

    printf("%s\n", buf);
    printf("(read %d bytes)\n", n);

    free(buf);
}

void mySeek(int fd) {
    int offset = 0;
    int seekStart = SEEK_SET;

    printf("Enter offset: ");
    scanf("%d", &offset);
    printf("Choose start position:\n1. SEEK_SET (default)\n2. SEEK_CUR\n3. SEEK_END\n");
    scanf("%d", &seekStart);

    if (seekStart == 1) {
        seekStart = SEEK_SET; // puts pointer to the beginning
    } else if (seekStart == 2) {
        seekStart = SEEK_CUR; // sores pointer at a last read byte
    } else if (seekStart == 3) {
        seekStart = SEEK_END; // enter offset -n and (n = quantity of bytes to output)
    } else {
        printf("Was entered wrong value\n");
        return;
    }
    lseek(fd, offset, seekStart);
    myLog("lseek", fd, errno, strerror(errno));

    myRead(fd, 1);
}

int main(int argc, char *argv[]) {
    // argv[0] - binary name
    // argv[1] - filename
    // argv[2] - permission
    if (argc != 3) {
        fprintf(stderr, "Usage: %s $1 (filename) $2 (mode)\n", argv[0]);
        exit(1); 
    }

    const char *filename = argv[1];
    int mode = atoi(argv[2]);

    int fd = open(filename, O_CREAT | permissions(mode) | 0666);
    myLog("open", fd, errno, strerror(errno));

    long fileSize = 1024 * 1024 * 1024; // 1GB file
    int res = fallocate(fd, 0, 0, fileSize); // Function: int posix_fallocate (int fd, off_t offset, off_t length). Zero on success, errno is not set
    if (res != 1) {
        perror("Failed to create file without gap zeros with fallocate");
        exit(1);
    }

    int option = -1;

    int go = 1;
    while (go) {
        printf("Choose number:\n1 - write\n2 - read\n3 - seek\n4 - exit\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("fd: %d\n", fd);
                myWrite(fd);
                break;
            case 2:
                printf("fd: %d\n", fd);
                myRead(fd, 0);
                break;
            case 3:
                mySeek(fd);
                break;
            case 4:
                go = 0;
                break;
            default:
                go = 1;
                break;
        }
    }

    close(fd);
    myLog("close", fd, errno, strerror(errno));
    
    return 0;
}