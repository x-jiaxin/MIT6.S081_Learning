//
// Created by 幻想 on 2022/8/8.
//
#include "kernel/types.h"
#include "user.h"
#include "kernel/fcntl.h"

int main()
{
    int fd = open("output.txt", O_WRONLY | O_CREATE);
    write(fd, "ooooo\n", 4);
    exit(0);
}