#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong input arguments\nDo: ./a.out filename\n");
        exit(1);
    }

    const char *file = argv[1];
    struct stat buf; // stores data
    int ret = stat(file, &buf); // POSIX function
    printf("File name: %s\n", file);
    printf("Status ret: %d\n", ret);
    printf("Data stored in buf\n\n");

    printf("Device: %lu\n", buf.st_dev);                                /* Device.  */
    printf("File serial number: %lu\n", buf.st_ino);                    /* File serial number.	*/
    printf("Link count: %lu\n", buf.st_nlink);                          /* Link count.  */
    printf("File mode: %d\n", buf.st_mode);                             /* File mode.  */
    printf("User ID of the file's owner: %u\n", buf.st_uid);            /* User ID of the file's owner.	*/
    printf("Group ID of the file's group: %u\n", buf.st_gid);           /* Group ID of the file's group.*/
    printf("Device number, if device: %lu\n", buf.st_rdev);             /* Device number, if device.  */
    printf("Size of file, in bytes: %ld\n", buf.st_size);               /* Size of file, in bytes.  */
    printf("Optimal block size for I/O: %ld\n", buf.st_blksize);        /* Optimal block size for I/O.  */
    printf("Number 512-byte blocks allocated: %ld\n", buf.st_blocks);   /* Number 512-byte blocks allocated. */
    printf("Time of last access: %ld\n", buf.st_atime);                 /* Time of last access.  */
    printf("Time of last modification: %ld\n", buf.st_mtime);           /* Time of last modification.  */
    printf("Time of last status change: %ld\n\n\n", buf.st_ctime);      /* Time of last status change.  */

    return 0;
}