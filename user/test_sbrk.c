//
// Created by jiaxin on 2023/4/6-21:46.
//
#include "kernel/types.h"
#include "user/user.h"
int main()
{
    char *p = malloc(2);
    printf("p:%p\n", p);
    return 0;
}