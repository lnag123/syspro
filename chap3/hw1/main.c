#include <stdio.h>
#include <string.h>
#define MAXLINE 100
#define MAXLINES 5

char lines[MAXLINES][MAXLINE];

int main() {
    int len, max = 0;

    for (int i = 0; i < MAXLINES; i++) {
        if (fgets(lines[i], MAXLINE, stdin) == NULL) {
            break;
        }
        len = strlen(lines[i]);
        if (len > max) {
            max = len;
        }
    }

    for (int i = 0; i < MAXLINES - 1; i++) {
        for (int j = 0; j < MAXLINES - i - 1; j++) {
            if (strlen(lines[j]) < strlen(lines[j + 1])) {
                char temp[MAXLINE];
                strcpy(temp, lines[j]);
                strcpy(lines[j], lines[j + 1]);
                strcpy(lines[j + 1], temp);
            }
        }
    }

    for (int i = 0; i < MAXLINES; i++) {
        if (strlen(lines[i]) > 0) {
            printf("%s", lines[i]);
        }
    }
    return 0;
}

