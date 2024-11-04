#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // объявлен внешний двумерный массив environ

//  All enviroment variables have type char*,
//  so enviroment has type cahr**, due to store all chars*.
//  
//   хранится копия окружения процесса.
extern char **environ;

void myAddVar() {
    char *envVarName = calloc(50, sizeof(char));
    char *envVarVal = calloc(50, sizeof(char));

    printf("Add enviroment variable\nVariable name: ");
    scanf("%s", envVarName);

    printf("Variable value: ");
    scanf("%s", envVarVal);

    if (setenv(envVarName, envVarVal, 0) != 0) {
        printf("setenv -> error occured while adding env variable");
        printf("Nothing was not found\n");
    } else {
        printf("Variable was added successfully\nUse 2 option to view results\n");
    }
}

void myGetVar() {
    char *envVarName = calloc(50, sizeof(char));

    printf("Enter name of variable to be output: ");
    scanf("%s", envVarName);

    char *envVarvALUE = getenv(envVarName);
    if (envVarvALUE == NULL) {
        printf("getenv -> error occured while getting env variable");
        exit(1);
    }
    printf ("'%s=%s' found\n", envVarName, envVarvALUE);    
}

void myPrintAll() {
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int option = -1;
    bool go = true;

    while (go) {
        printf("\nChoose action:\n1: Add new env variable\n2: Get env variable\n3: Output all env variables\n4: Stop\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                myAddVar();
                break;
            case 2:
                myGetVar();
                break;
            case 3:
                myPrintAll();
                break;
            default:
                go = false;
                break;
        }

    }

    return 0;
}