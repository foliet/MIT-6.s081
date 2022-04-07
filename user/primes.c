//
// Created by foliet on 2022/4/6.
//
#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p1[2];
    pipe(p1);
    int i;
    for (i = 2; i <= 35; i++) {
        write(p1[1], &i, sizeof(i));
    }
    i = 0;
    write(p1[1], &i, sizeof(i));
    while (1) {
        int n, prime, p2[2];
        pipe(p2);
        read(p1[0], &prime, sizeof(prime));
        printf("prime %d\n", prime);
        if (read(p1[0], &n, sizeof(n)) && n) {
            if (fork() == 0) {
                close(p1[0]);
                close(p1[1]);
                p1[0] = p2[0];
                p1[1] = p2[1];
                continue;
            }
            do {
                if (n % prime != 0)
                    write(p2[1], &n, sizeof(n));
            } while (read(p1[0], &n, sizeof(n)) && n);
            write(p2[1], &n, sizeof(n));
        }
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);
        break;
    }
    wait(0);
    exit(0);
}