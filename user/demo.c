//
// Created by 幻想 on 2022/8/22.
//
#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"

int main()
{
    int pid = fork();
    if (pid == 0)
    {
        write(1, "hello", 6);
        exit(0);
    }

    else
    {
        wait(0);
        write(1, "world!\n", 7);
    }
    exit(0);
}