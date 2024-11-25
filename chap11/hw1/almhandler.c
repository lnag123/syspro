#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void custom_signal(int signo, void (*handler)(int)) {
    struct sigaction sa;
    sa.sa_handler = handler; 
    sa.sa_flags = 0;       
    sigemptyset(&sa.sa_mask); 

    if (sigaction(signo, &sa, NULL) == -1) { 
		perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

void alarmHandler(int signo) {
    printf("Wake up\n");
    exit(0);
}

int main() {
    custom_signal(SIGALRM, alarmHandler);
    alarm(5);

    short i = 0;
    while (1) {
        sleep(1); 
        i++;
        printf("%d second\n", i);
    }
    printf("end\n"); 
    return 0;
}

