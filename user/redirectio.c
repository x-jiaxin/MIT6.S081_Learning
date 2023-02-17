//
// Created by 幻想 on 2022/8/8.
//
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main()
{
    int pid;
    pid = fork();
    if (pid == 0) {
        close(1);
        open("xjx.txt", O_WRONLY | O_CREATE);
        char *argv[] = {"echo", "this", "is", "echo", 0};
        exec("exec", argv);
        printf("exected failed");
        exit(1);
    }
    else {
        wait((int *)0);
    }
    exit(0);
}