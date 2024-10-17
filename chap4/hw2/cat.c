#include <stdio.h>
#include <string.h>

void print_file(FILE *fp, int show_line_numbers) {
    int c;
    int line_number = 1;

    if (show_line_numbers) {
        printf("%d ", line_number++);
    }

    while ((c = getc(fp)) != EOF) {
        putc(c, stdout);
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int show_line_numbers = 0;
    int i = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        show_line_numbers = 1;
		i = 2;
    }

    if (argc == i) {
        fp = stdin;
        print_file(fp, show_line_numbers);
    } else {
        for (; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "File Error: %s\n", argv[i]);
                continue;
            }

            print_file(fp, show_line_numbers);
            fclose(fp);
        }
    }
    return 0;
}


