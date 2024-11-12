#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARG 64    
#define MAXINPUT 1024 
void execute_command(char *args[], int background) {
    pid_t pid = fork();  

    if (pid < 0) {
        perror("Fork failed"); 
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) { 
            perror("Exec failed");
            exit(EXIT_FAILURE);
        }
    } else { // 부모 프로세스의 경우
        if (!background) {  
            waitpid(pid, NULL, 0);
        }
    }
}

int main() {
    char input[MAXINPUT]; 
    char *args[MAXARG]; 
    while (1) {
        printf("Pls input cmd:  ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Input failed");
            break;
        }
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) { 
            continue;
        }

        int background = 0;
        if (input[strlen(input) - 1] == '&') {
            background = 1;
            input[strlen(input) - 1] = '\0'; // '&' x
        }

        char *token;
        char *rest = input;
        int i = 0;

        while ((token = strtok_r(rest, " ", &rest)) != NULL && i < MAXARG - 1) {
            args[i++] = token;
        }
        args[i] = NULL; 
        execute_command(args, background);
    }

    return 0;
}

