#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>

#define MESSAGE_SIZE    64

// Message structure
struct message {
    long msg_type;
    char msg_text[MESSAGE_SIZE];
};

int main(int argc, char* argv[]) {
    if (argc != 3) { // Check args quantity
        fprintf(stderr, "Usage: %s <server file> <sleep delay>\n", argv[0]);
        return 1;
    }

    int key = ftok(argv[1], 'a'); // Get server key
    if (key == -1) {
        perror("ftok() error");
        return 1;
    }
    int pid = getpid();
    printf("[client %d] generated key: %d.\n", pid, key);

    int server_msgid = msgget(key, 0666); // Get access to server queue
    if (server_msgid == -1) {
        perror("msgget() error");
        return 1;
    }
    printf("[client %d] has got server queue id: %d.\n", pid, server_msgid);

    int client_msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT); // Generate new queue (client's queue)
    if (client_msgid == -1) {
        perror("msgget() error");
        return 1;
    }
    printf("[client %d] has got their own queue id: %d.\n", pid, client_msgid);

    int delay = atoi(argv[2]); // Convert char* in int

    struct message request, response;
    for(int i = 1;; ++i) {
        request.msg_type = client_msgid; // Always the same type
        snprintf(request.msg_text, sizeof(request.msg_text), "hello x%d from client %d", i, pid); // Formed string

        if (msgsnd(server_msgid, &request, sizeof(request.msg_text), 0) == -1) { // Sending msg to a server [message type is changing]
            perror("msgsnd() error");
            msgctl(client_msgid, IPC_RMID, NULL);
            return 1;
        }
        printf("[client %d] has sent %d message to server.\n", pid, i);

        if (msgrcv(client_msgid, &response, sizeof(response.msg_text), 0, 0) == -1) { // Getting response
            perror("msgrcv error()");
            msgctl(client_msgid, IPC_RMID, NULL);
            return 1;
        } else {
            printf("[client %d] recieved a message of type %ld: \"%s\"\n", pid, response.msg_type, response.msg_text);
        }

        printf("\n");

        sleep(delay);
    }

    return 0;
}