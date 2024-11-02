#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // open - function
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
        return O_WRONLY ;
    case 444:
        return O_RDONLY;
    case 666:
        return  O_RDWR;
    default:
        return -1;
    }
}

void check(const char* log, int resCode) {
    if (resCode < 0) {
        printf(log, resCode);
        // exit(1);
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
    printf("Creating file %s with passed permissions...\n", filename);
    int fd = -1;
    // fd = open(filename, O_CREAT, filePermissionOnlyReading); // alternative approach - to use open file
    long filePermissionOnlyReading = permissions(mode);
    printf("filePermissionOnlyReading: %ld\n", filePermissionOnlyReading);
    fd = open(filename, O_CREAT | filePermissionOnlyReading| 0444);
    printf("Status (create) fd: %d\n", fd);
    check("File wasn't created\nfd status is: %d\n", fd);
    printf("1. File was created successfully.\n\n");
    
    // 3. WRITE FEW LINES IN FILE (how does it work if we create file only for reading)
    const char *data = {"Line 1\nLine 2\nLine 3\n"};
    ssize_t bytesWritten = write(fd, data, strlen(data) + 1);
    printf("Status (write) bytesWritten: %ld\n", bytesWritten);
    check("Data was not written in file: %ld\nFailed to write in file\n", bytesWritten);
    printf("3. Data was written successfully.\n\n");

    // 4. CLOSE FILE (file descriptor)
    int res = close(fd);
    printf("Satatus (close) res: %d\n", res);
    check("File wasn't closed\nClose status: %d\nFailed to close file\n", res);
    printf("4. File was closed successfully.\n\n");

    // 5. OPEN FILE (READ)
    fd = open(filename, O_RDONLY);
    printf("Satatus (open) fd: %d\n", fd);
    check("File wasn't opened\nOpen status: %d\n", fd);
    if (fd > 0) {
        printf("5. File was opened successfully.\n\n");
        // 6. READ DATA FROM FILE
        char buf[100];
        ssize_t readBytes = read(fd, buf, 100);
        printf("Satatus (read) readBytes: %ld\n", readBytes);
        check("Failed to read file\nRead ststus: %d", readBytes);
        printf("6. Data was read successfully.\n\n");

        // 7. OUTPUT DATA ON SCREEN
        printf("Message:\n%s\nRead %ld bytes\n", buf, readBytes);
        printf("7. Data was outputed successfully.\n\n");
    }
    

    // 8. CLOSE FILE
    res = close(fd);
    printf("Satatus (close) res: %d\n", res);
    check("File wasn't closed\nClose status: %d\nFailed to close file\n", res);
    printf("8. File was closed successfully.\n\n");

    // 9. OPERN FILE (READ, WRITE)
    fd = open(filename, O_RDWR);
    printf("Satatus (open) fd: %d\n", fd);
    check("File wasn't opened\nOpen status: %d\n", fd);
    printf("9. File was opened successfully.\n\n");

    return 0;
}