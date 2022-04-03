//
// Created by foliet on 2022/4/2.
//
#include "kernel/types.h"
#include "user/user.h"

int
main(int argc,char* argv[]){
    if(argc != 2){
        fprintf(2, "Usage: sleep ticks\n");
        exit(1);
    }
    int ticks = atoi(argv[1]);
    sleep(ticks);
    exit(0);
}
