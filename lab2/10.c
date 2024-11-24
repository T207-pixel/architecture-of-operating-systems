#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char ** environ;

void print_args_and_env(char **args) {
    printf("Аргументы:\n");
    for (int i = 0; args[i] != NULL; i++) {
        printf("%s\n", args[i]);
    }
    
    printf("Окружение:\n");
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s 10-1\n", argv[0]);
        exit(1);
    }
    
    // Child process 
    if (fork() == 0) {
        print_args_and_env(argv);
        
        // Call exec
        // 1 - path to binary, 2 - name of binary somehow it is not first parameter in second program
        // 3 - parameter (random string)
        execl(argv[1], argv[1], "Carried away by ghosts", NULL);
        
        // If fail
        perror("execl failed");
        exit(1);
    } else { // Parent process
        print_args_and_env(argv);
        
        wait(NULL); // wait child process
        
        return 0;
    }
}