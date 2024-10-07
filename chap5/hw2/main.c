#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 2;
    }

    char *lines[100]; 
	char buffer[1024];
    int line_count = 0;

	while (fgets(buffer, sizeof(buffer), file)) {
        lines[line_count] = strdup(buffer);
        line_count++;
    }
    fclose(file);

    for (int i = line_count - 1; i >= 0; i--) {
        printf("%s", lines[i]);
        free(lines[i]); 
    }

    return 0;
}

