#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int fd;
    char saveText[BUFSIZE][BUFSIZE];
    ssize_t nread;
    char input[BUFSIZE];
    int line_total = 0;

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    char buf[1];
    int row = 0, col = 0;
    while ((nread = read(fd, buf, 1)) > 0) {
        if (buf[0] == '\n') {
            saveText[row][col] = '\0';
            row++;
            col = 0;
        } else {
            saveText[row][col++] = buf[0];
        }
    }
    line_total = row;
    close(fd);
    printf("File read success\n");
    printf("Total Line: %d\n", line_total);
    printf("You can choose 1 ~ %d Line\n", line_total);
    printf("Pls 'Enter' The line to select : ");
    scanf("%s", input);

    if (strcmp(input, "*") == 0) {
        for (int k = 0; k < line_total; k++) {
            printf("%s\n", saveText[k]);
        }
        return 0;
    }

    char *dash = strchr(input, '-');
    if (dash != NULL) {
        int start = atoi(input);
        int end = atoi(dash + 1);
        if (start > 0 && end <= line_total) {
            for (int k = start - 1; k <= end - 1; k++) {
                printf("%s\n", saveText[k]);
            }
        } else {
            printf("Invalid range\n");
        }
        return 0;
    }


    char *comma = strchr(input, ',');
    if (comma != NULL) {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int line = atoi(token);
            if (line > 0 && line <= line_total) {
                printf("%s\n", saveText[line - 1]);
            } else {
                printf("Invalid line number: %d\n", line);
            }
            token = strtok(NULL, ",");
        }
        return 0;
    }

  
    int line = atoi(input);
    if (line > 0 && line <= line_total) {
        printf("%s\n", saveText[line - 1]);
    } else {
        printf("Choose 1 ~ %d\n", line_total);
    }
    return 0;
}

