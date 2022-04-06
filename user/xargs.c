//
// Created by foliet on 2022/4/6.
//
#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
    char buf[64], *xargs[32];
    for (int i = 1; i < argc; i++)
        xargs[i - 1] = argv[i];
    while (1) {
        int x = argc - 1;
        gets(buf, 64);
        if (buf[0] == 0)
            break;
        xargs[x++] = buf;
        for (char *p = buf; *p; p++) {
            if (*p == ' ') {
                *p = 0;
                xargs[x++] = p + 1;
            } else if (*p == '\n') {
                *p = 0;
            }
        }
        if (fork() == 0) {
            exec(argv[1], xargs);
        }
    }
    wait(0);
    exit(0);
}
