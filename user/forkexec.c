//
// Created by 幻想 on 2022/8/8.
//
#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int pid, status, status1;
    pid = fork();
    if (pid == 0) {
        char *argv[] = {"echo", "this", "is", "echo", 0};
        wait(&status1);
        printf("child's child exited with status %d\n", status1);
        exec("exec", argv);
        printf("exec failed!\n");
        exit(1);
    }
    else {
        printf("parent waiting\n");
        wait(&status);
        printf("the child exited with status %d\n", status);
    }
    exit(0);
}