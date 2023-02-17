/*
//
// Created by 幻想 on 2022/8/22.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define strSize 4

int main()
{
    int pfd[2], cfd[2];
    char buf[5];
//    parent pipe
    pipe(pfd);
//    child pipe
    pipe(cfd);
    int pid = fork();
    if (pid < 0) {
        fprintf(2, "fork error!");
        exit(1);
    }
//    parent
    else if (pid > 0) {
        write(pfd[1], "ping", strSize);
        wait(0);
        read(cfd[0], buf, strSize);
        printf("%d: received %s\n", getpid(), buf);

    }
//    child
    else {
        read(pfd[0], buf, strSize);
        printf("%d: received %s\n", getpid(), buf);
        write(cfd[1], "pong", strSize);
        close(cfd[1]);
    }
    exit(0);
}*/
//
// Created by 幻想 on 2022/8/23.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define WR 1
#define RD 0

int main()
{
    char buffer = 'P';
    int parentFileDescribe[2], childFileDescribe[2];
    int exitStatus = 0;
    pipe(parentFileDescribe);
    pipe(childFileDescribe);
    int pid = fork();
    if (pid < 0) {
        fprintf(2, "fork error!\n");
        close(parentFileDescribe[WR]);
        close(childFileDescribe[WR]);
        close(parentFileDescribe[RD]);
        close(childFileDescribe[RD]);
//        exit(1);
        exitStatus = 1;
    }
//    parent
    else if (pid > 0) {
//        parent read from child
//        parent write
        close(childFileDescribe[WR]);
        close(parentFileDescribe[RD]);
        if (write(parentFileDescribe[WR], &buffer, sizeof(char)) != sizeof(char)) {
            fprintf(2, "parent write error\n");
            exitStatus = 1;
        }
        if (read(childFileDescribe[RD], &buffer, sizeof(char)) != sizeof(char)) {
            fprintf(2, "parent read error\n");
            exitStatus = 1;
        }
        else {
            fprintf(1, "%d: received pong\n", getpid());
//            printf("parent: %d receive pong\n", getpid());/**/
        }
        close(parentFileDescribe[WR]);
        close(childFileDescribe[RD]);
//        exit(exitStatus);
    }
//    child
    else {
        close(childFileDescribe[RD]);
        close(parentFileDescribe[WR]);
        if (read(parentFileDescribe[RD], &buffer, 1) != 1) {
            fprintf(2, "child read error\n");
            exitStatus = 1;
        }
        else {
//            printf("child: %d received ping\n", getpid());
            fprintf(1, "%d: received ping\n", getpid());
        }
        if (write(childFileDescribe[WR], &buffer, sizeof(char)) != sizeof(char)) {
            fprintf(2, "child write error\n");
            exitStatus = 1;
        }
        close(childFileDescribe[WR]);
        close(parentFileDescribe[RD]);
//        exit(exitStatus);
    }
    exit(exitStatus);
}
