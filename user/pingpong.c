//
// Created by foliet on 2022/4/3.
//
#include "kernel/types.h"
#include "user/user.h"

int
main() {
    int p1[2];//parent->child
    int p2[2];//child->parent
    pipe(p1);
    pipe(p2);
    if (fork() == 0) {
        //child
        char buffer[] = {'y'};
        read(p1[0], buffer, sizeof(buffer));
        fprintf(2, "%d: received ping\n", getpid());
        write(p2[1], buffer, sizeof(buffer));
        exit(0);
    }
    //parent
    char buffer[] = {'x'};
    write(p1[1], buffer, sizeof(buffer));
    wait(0);
    read(p2[0], buffer, sizeof(buffer));
    fprintf(2, "%d: received pong\n", getpid());
    exit(0);
}