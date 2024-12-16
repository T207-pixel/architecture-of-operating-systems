#include<stdio.h> 
#include<signal.h> 
#include <unistd.h>

void handle_sigint(int sig) {
    printf("Caught signal %d\n", sig);
}
  
int main()  {
    while (1) {
        signal(SIGINT, handle_sigint); 
        sleep(1);
        printf("running: 1,c\n");
    }; 
    return 0; 
}
