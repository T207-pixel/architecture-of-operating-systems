#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MSG_LEN 32

extern int errno;

// structure for message queue
typedef struct msg_ds {
    long type;
    char data[MSG_LEN + 1];
} msg_ds;

// Outputs queue statistic
void print_stats(struct msqid_ds ds) {
    struct ipc_perm perm = ds.msg_perm;
    printf("Ownership and permissions\n");
    printf("Key: %d\n", perm.__key);
    printf("Effective UID of owner: %d\n", perm.uid);
    printf("Effective GID of owner: %d\n", perm.gid);
    printf("Effective UID of creator: %d\n", perm.cuid);
    printf("Effective GID of creator: %d\n", perm.cgid);
    printf("Permissions: %o\n", perm.mode);
    printf("Sequence number: %u\n\n", perm.__seq);
    printf("Time of last msgsnd: %ld\n", ds.msg_ctime);
    printf("Time of last msgrcv: %ld\n", ds.msg_rtime);
    printf("Time of last change: %ld\n", ds.msg_ctime);
    printf("Current number of bytes in queue: %lu\n", ds.__msg_cbytes);
    printf("Current number of messages in queue: %lu\n", ds.msg_qnum);
    printf("Maximum number of bytes allowed in queue: %lu\n", ds.msg_qbytes);
    printf("PID of last msgsnd: %d\n", ds.msg_lspid);
    printf("PID of last msgrcv: %d\n", ds.msg_lrpid);
}

int main(int argc, char *argv[]) {
    
    key_t key = ftok("progfile", 'a'); /* ftok(): is use to generate a unique key. Generates key for System V style IPC.  ftok - convert a pathname and a project identifier to a System V IPC key*/
    int msqid = msgget(key, IPC_CREAT | 0666); // Like ipc, but for x86.  system call returns the System V message queue identifier associated with the value of the key argument.
    if (msqid == -1) {
        printf("Unable to get message queue identifier\n");
        exit(errno);
    }
    printf("msqid: %d\n", msqid);

    msg_ds msg;

    int message_types[] = {1, 2, 3};
    const char* messages[] = {"type 1", "type 2", "type 3"};

    for (int i = 0; i < 3; i++) {
        msg.type = message_types[i];
        strcpy(msg.data, messages[i]);
        msgsnd(msqid, &msg, sizeof(msg), 0); // Data is placed on to a message queue by calling msgsnd(). System calls are used to send messages to, and receive messages from, a System V message queue.
    }

    struct msqid_ds ds = {0}; /* Structure of record for one message inside the kernel. The type `struct msg' is opaque.  */
    msgctl(msqid, IPC_STAT, &ds); /* It performs various operations on a queue. Generally it is use to destroy message queue. Get `ipc_perm' options.  */
    print_stats(ds);

    return 0;
}