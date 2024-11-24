#include<stdio.h> 
#include<signal.h> 
  
// Handler for SIGINT, caused by
// Ctrl-C at keyboard
void handle_sigint(int sig) { // ignor SIGINT (2)
    printf("Caught signal %d\n", sig);
    signal(sig, SIG_DFL); // is 0
}
  
int main()  {
    while (1) {
        signal(SIGINT, handle_sigint); 
        sleep(1);
        printf("running: 1,c\n");
    }; 
    return 0; 
}
