#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

extern char ** environ;

int main(int argc, char * argv[]) {
    printf("Процесс: %s\n", argv[0]);
    
    printf("Аргументы:\n");
    for (int i = 0; argv[i] != NULL; i++) {
        printf("%s\n", argv[i]);
    }

    printf("Окружение:\n");
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }


    exit(EXIT_SUCCESS);
}