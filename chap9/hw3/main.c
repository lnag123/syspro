#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024

void parse_command(char *cmd, int *background, char **infile, char **outfile) {
    *background = 0;
    *infile = NULL;
    *outfile = NULL;

    if (cmd[strlen(cmd) - 1] == '&') {
        *background = 1;
        cmd[strlen(cmd) - 1] = '\0';
    }

    char *in_pos = strstr(cmd, "<");
    char *out_pos = strstr(cmd, ">");
    if (in_pos != NULL) {
        *in_pos = '\0';
        *infile = strtok(in_pos + 1, " \t");
    }
    if (out_pos != NULL) {
        *out_pos = '\0';
        *outfile = strtok(out_pos + 1, " \t");
    }
}

void execute_single_command(char *cmd, int background, char *infile, char *outfile) {
    char *token;
    char *args[MAX_INPUT_SIZE];
    int i = 0;

    token = strtok(cmd, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        if (infile) {
            int fd_in = open(infile, O_RDONLY);
            if (fd_in < 0) {
                perror("Input file open failed");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (outfile) {
            int fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("Output file open failed");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        execvp(args[0], args);
        perror("Execution failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed");
    } else {
        if (!background) {
            waitpid(pid, NULL, 0);
        }
    }
}

void execute_command(char *cmd) {
    char *token = strtok(cmd, ";");
    while (token != NULL) {
        int background;
        char *infile, *outfile;

        parse_command(token, &background, &infile, &outfile);
        execute_single_command(token, background, infile, outfile);

        token = strtok(NULL, ";");
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("[shell] ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';

        execute_command(input);
    }

    return 0;
}

