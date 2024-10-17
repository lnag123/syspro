#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int, int);
int isHidden(const char*);

int main(int argc, char** argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    int longFormat = 0, allFiles = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; j++) {
                if (argv[i][j] == 'l') longFormat = 1;
                if (argv[i][j] == 'a') allFiles = 1;
            }
        } else {
            dir = argv[i];
        }
    }

    if (dir == NULL) dir = ".";

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    while ((d = readdir(dp)) != NULL) {
        if (!allFiles && isHidden(d->d_name)) {
            continue;
        }

        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) {
            perror(path);
        } else {
            printStat(path, d->d_name, &st, longFormat, allFiles);
        }
    }
    closedir(dp);
    exit(EXIT_SUCCESS);
}

void printStat(char *pathname, char *file, struct stat *st, int longFormat, int allFiles) {
    if (longFormat) {
        printf("%5d", st->st_blocks);
        printf("%c%s", type(st->st_mode), perm(st->st_mode));
        printf("%3d", st->st_nlink);
        printf("%s %s", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
        printf("%9d ", st->st_size);
        printf("%.12s ", ctime(&st->st_mtime) + 4);
    }
    printf("%s\n", file);
}

char type(mode_t mode) {
    if (S_ISREG(mode)) return('-');
    if (S_ISDIR(mode)) return('d');
    if (S_ISCHR(mode)) return('c');
    if (S_ISBLK(mode)) return('b');
    if (S_ISLNK(mode)) return('l');
    if (S_ISFIFO(mode)) return('p');
    if (S_ISSOCK(mode)) return('s');
    return '?';
}

char* perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "--------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> i * 3)) perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3)) perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3)) perms[i * 3 + 2] = 'x';
    }
    return perms;
}

int isHidden(const char* filename) {
    return filename[0] == '.';
}

