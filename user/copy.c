//
// Created by 幻想 on 2022/8/5.
//
#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    char buf[64];
    while (1) {
        int n = read(0, buf, sizeof(buf));
        if (n <= 0) {
            break;
        }
        write(1, buf, n);
    }
    exit(0);
}