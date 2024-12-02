#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#define BUFFER_SIZE 100

void convert_to_uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32; 
        }
    }
}

int main() {
    int pipe_fd[2]; 
    pid_t child1, child2;

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    printf("parent process start\n");

    child1 = fork();
    if (child1 == -1) {
        perror("Fork failed for child 1");
        return 1;
    }

    if (child1 == 0) {
        close(pipe_fd[0]); 
        char input[BUFFER_SIZE];
        printf("input string: ");
        fgets(input, BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0';
        write(pipe_fd[1], input, strlen(input) + 1); 
        close(pipe_fd[1]); 
        return 0;
    }

    child2 = fork();
    if (child2 == -1) {
        perror("Fork failed for child 2");
        return 1;
    }

    if (child2 == 0) {
        close(pipe_fd[1]); 
        char buffer[BUFFER_SIZE];
        read(pipe_fd[0], buffer, BUFFER_SIZE); 
        convert_to_uppercase(buffer); 
        printf("%s\n", buffer);        
        close(pipe_fd[0]); 
        return 0;
    }

    close(pipe_fd[0]); 
    close(pipe_fd[1]); 
    wait(NULL); 
    wait(NULL); 
    return 0;
}

