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
        close(p1[0]);
        close(p2[1]);
        char* buffer = malloc(2);
        read(p1[1],buffer,sizeof(buffer));
        fprintf(2,"%d: received ping\n",getpid());
        write(p2[0],buffer,sizeof(buffer));
        exit(0);
    }
    //parent
    close(p1[1]);
    close(p2[0]);
    char buffer[] = {'x'};
    read(p1[0],buffer,sizeof(buffer));
    fprintf(2,"%d: received pong\n",getpid());
    write(p2[1],buffer,sizeof(buffer));
    wait(0);
    exit(0);
}

