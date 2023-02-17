//
// Created by 幻想 on 2022/8/8.
//
#include "kernel/types.h"
#include "user/user.h"

int main()
{
    char *argv[] = {"echo", "this", "is", "echo", 0};
    exec("echo", argv);
    printf("exec failed!\n");
    exit(0);
}