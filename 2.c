#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> // outputs errors

// #define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
// #undef _POSIX_SOURCE

extern int errno;

long permissions(int permission) {
    switch (permission) {
    case 222:
        return S_IWUSR | S_IWGRP | S_IWOTH; // S_IWOTH - doesn't set w for other users
    case 444:
        return S_IRUSR | S_IRGRP | S_IROTH;
    case 666:
        return  O_RDWR;
    default:
        return -1;
    }
}

void check(const char* log, int resCode) {
    if (resCode < 0) {
        printf(log, resCode);
        exit(1);
    }
}

void createFileCheck(int fd) {
    if (fd < 0) {
        printf("File wasn't created\nfd status is: %d", fd);
        exit(1);
    }
}

void writeDataInFileCheck(ssize_t bytesSize) {
    if (bytesSize < 0) {
        printf("Data was not written in file: %ld\nFailed to write in file\n", bytesSize);
        exit(1);
    }
}

void closeFileCheck(int closeStatus) {
    if (closeStatus < 0) {
        printf("File wasn't closed\nClose status: %d\nFailed to close file\n", closeStatus);
        exit(1);
    }
}

void openFileCheck(int fd) {
    if (fd < 0) {
        printf("File wasn't opened\nOpen status: %d\n", fd);
        exit(1);
    }
}

void readFileCheck(int readStatus) {
    if (readStatus < 0) {
        printf("Failed to read file\nRead ststus: %d", readStatus);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    // 2. PASS ARGUMENTS WITH CLI
    if (argc != 3) {
        fprintf(stderr, "Usage: %s $1 (filename) $2 (mode)\n", argv[0]);
        exit(1); 
    }

    // Init variables
    const char *filename = argv[1];
    int mode = atoi(argv[2]);
    printf("file: %s\n", filename);
    printf("mode: %d\n\n", mode);

    // 1. CREATING FILE ONLY FOR READING
    printf("Creating file %s with read-only permissions...\n", filename);
    int fd = -1;
    // fd = open(filename, O_CREAT, filePermissionOnlyReading); // alternative approach - to use open file
    long filePermissionOnlyReading = permissions(mode);
    if (filePermissionOnlyReading < 0)
        exit(1);
    printf("filePermissionOnlyReading: %ld\n", filePermissionOnlyReading);
    fd = creat(filename, filePermissionOnlyReading);
    printf("Status (create) fd: %d\n", fd);
    createFileCheck(fd);
    printf("1. File was created successfully.\n\n");
    
    // 3. WRITE FEW LINES IN FILE
    const char *data = {"Line 1\nLine 2\nLine 3\n"};
    ssize_t bytesWritten = write(fd, data, strlen(data) + 1);
    printf("Status (write) bytesWritten: %ld\n", bytesWritten);
    writeDataInFileCheck(bytesWritten);
    printf("3. Data was written successfully.\n\n");

    // 4. CLOSE FILE (file descriptor)
    int res = close(fd);
    printf("Satatus (close) res: %d\n", res);
    closeFileCheck(res);
    printf("4. File was closes successfully.\n\n");

    // 5. OPEN FILE (READ)
    fd = open(filename, O_RDONLY);
    printf("Satatus (open) fd: %d\n", fd);
    openFileCheck(fd);
    printf("5. File was opened successfully.\n\n");

    // 6. READ DATA FROM FILE
    char buf[100];
    ssize_t readBytes = read(fd, buf, 100);
    printf("Satatus (read) readBytes: %ld\n", readBytes);
    readFileCheck(readBytes);
    printf("6. Data was read successfully.\n\n");

    // 7. OUTPUT DATA ON SCREEN
    printf("Message:\n%s\nRead %ld bytes\n", buf, readBytes);
    printf("7. Data was outputed successfully.\n\n");

    // 8. CLOSE FILE 
    res = close(fd);
    printf("Satatus (close) res: %d\n", res);
    closeFileCheck(res);
    printf("8. File was closes successfully.\n\n");

    // 9. OPERN FILE (READ, WRITE)
    fd = open(filename, O_RDWR);
    printf("Satatus (open) fd: %d\n", fd);
    openFileCheck(fd);
    printf("9. File was opened successfully.\n\n");

}