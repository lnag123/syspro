#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void get_environment_value(const char* env_name) {
    if (env_name && *env_name) {
        char* env_value = getenv(env_name);
        if (env_value) {
            printf("%s: %s\n", env_name, env_value);
        } else {
            printf("Environment variable '%s' not found.\n", env_name);
        }
    } else {
        printf("Please provide an environment variable name after '-e'.\n");
    }
}

void print_user_info() {
    printf("My Realistic User ID: %d\n", getuid());
    printf("My Valid  User ID: %d\n", geteuid());
}

void print_group_info() {
    printf("My Realistic Group ID: %d\n", getgid());
    printf("My Valid Group ID: %d\n", getegid());
}

void print_process_info() {
    printf("my process number: %d\n", getpid());
}

void print_parent_info() {
    printf("my parent's process number: %d\n", getppid());
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [-e ENV_NAME] [-u] [-g] [-i] [-p]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'e':
                    if (i + 1 < argc && argv[i + 1][0] != '-') {
                        get_environment_value(argv[++i]);
                    } else {
                        get_environment_value(NULL);
                    }
                    break;
                case 'u':
                    print_user_info();
                    break;
                case 'g':
                    print_group_info();
                    break;
                case 'i':
                    print_process_info();
                    break;
                case 'p':
                    print_parent_info();
                    break;
                default:
                    printf("Unknown option: %c\n", argv[i][1]);
                    break;
            }
        }
    }

    return 0;
}

