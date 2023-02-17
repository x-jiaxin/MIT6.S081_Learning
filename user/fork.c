//
// Created by 幻想 on 2022/8/5.
//
#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    int pid = fork();
    printf("fork() returned %d\n", pid);

    if (pid == 0) {
        printf("child\n");
    }
    else {
        printf("parent\n");
    }
    exit(0);
}