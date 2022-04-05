//
// Created by foliet on 2022/4/3.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char *target;

/*读取path中的文件名*/
char *
filename(char *path) {
    char *p = path;
    while (*p)
        p++;
    while (*p != '/' && p != path)
        p--;
    return p == path ? p : ++p;
}

void
find(char *path) {
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512], *p;
    if ((fd = open(path, O_RDONLY)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type) {
        case T_FILE:
            if (strcmp(filename(path), target) == 0) {
                printf("%s\n", path);
            }
            break;
        case T_DIR:
            if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
                printf("find: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf + strlen(buf);
            *p++ = '/';
            while (read(fd, &de, sizeof(de)) == sizeof(de)) {
                if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                    continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                find(buf);
            }
            break;
    }
    close(fd);
}

int
main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(2, "Usage: find path filename\n");
        exit(1);
    }
    target = argv[2];
    find(argv[1]);
    exit(0);
}