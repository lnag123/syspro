#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
    char str[1024];
    char *command1[10], *command2[10];
    int fd[2];

    if (argc == 1) {
		strcpy(str, "ls | wc");
    } else {

		strcpy(str, argv[1]);
        for (int i = 2; i < argc; i++) {
            strcat(str, " ");
            strcat(str, argv[i]);
        }
    }
	if (strchr(str, '|') != NULL) {
        char *token;
        char *part1 = strtok(str, "|");
        char *part2 = strtok(NULL, "|");

        int i = 0;
        token = strtok(part1, " ");
        while (token != NULL) {
            command1[i++] = token;
            token = strtok(NULL, " ");
        }
        command1[i] = NULL;

        i = 0;
        token = strtok(part2, " ");
        while (token != NULL) {
            command2[i++] = token;
            token = strtok(NULL, " ");
        }
        command2[i] = NULL;
    } else {
        fprintf(stderr, "Error: No pipe (|) found in the input.\n");
        exit(1);
    }

   
	if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

   
	pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed for command1");
        exit(1);
    }

    if (pid1 == 0) {
        close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);
        execvp(command1[0], command1);
        perror("Exec failed for command1");
        exit(1);
    }

   	pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed for command2");
        exit(1);
    }

    if (pid2 == 0) {
        close(fd[WRITE]);
        dup2(fd[READ], STDIN_FILENO);
        close(fd[READ]);
        execvp(command2[0], command2);
        perror("Exec failed for command2");
        exit(1);
    }

    close(fd[READ]);
    close(fd[WRITE]);
   
	waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}

