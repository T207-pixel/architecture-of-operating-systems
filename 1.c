// C program to illustrate
// open system call and error codes
#include <errno.h>
#include <fcntl.h>
#include <stdio.h> // printf
#include <unistd.h>
#include <string.h>  // for useing %s strerror

// extern int errno;

int main() {
    
    int fd = open("foo.txt", O_RDONLY);

    printf("fd = %d\n", fd);

    if (fd == -1) {
        // print which type of error have in a code
        printf("Error Number %d\n", errno);

        // print program detail "Success or failure"
        perror("perror log: ");

        // with strerror
        printf("strerror message is : %s\n", strerror(errno));

        // with sys_errlist (deprecated)
        // printf("%s\n", sys_errlist[errno]); // doesn't work
    }
    return 0;
}