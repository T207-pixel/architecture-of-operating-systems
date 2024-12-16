#include<stdio.h> 
#include<signal.h> 
#include <unistd.h>

void handle_sigint(int sig) {
    if (sig == SIGINT)
        printf("Caught signal %d\n", sig);
    if (sig == SIGHUP)
        printf("Caught signal %d\n", sig);
    else 
        SIG_DFL;
}
  
int main()  {
    while (1) {
        signal(SIGINT, handle_sigint);
        signal(SIGHUP, handle_sigint); 
        sleep(1);
        printf("running: 1,c\n");
    }; 
    return 0; 
}
