#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char send_msg[50];
    char recv_msg[50];

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid = fork(); 
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        
        close(pipe_fd[0]); 
        snprintf(send_msg, sizeof(send_msg), "Hello from PID %d", getpid());
        write(pipe_fd[1], send_msg, strlen(send_msg) + 1);
        close(pipe_fd[1]);
    } else {
        
        close(pipe_fd[1]);
        read(pipe_fd[0], recv_msg, sizeof(recv_msg));
        close(pipe_fd[0]); 
        printf("Send: [%d] %s\n", pid, recv_msg);
        printf("Recv: [%d] %s\n", getpid(), recv_msg);
    }
    return 0;
}

