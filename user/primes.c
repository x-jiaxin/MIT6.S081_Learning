//
// Created by 幻想 on 2022/8/22.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define WR 1
#define RD 0
/**
 * 从管道读一个数，读到返回0
 * @param lpipe 存放数据的管道
 * @param first 存放读出的数据
 * @return 成功为0
 */
int lpipe_first_data(int *lpipe, int *first)
{
    if (read(lpipe[RD], first, sizeof(int)) == sizeof(int)) {
        printf("prime %d\n", *first);
        return 0;
    }
    return -1;
}

/**
 * 筛选数据，并写入到新的管道
 * @param lpipe
 * @param rpipe
 * @param first
 */
void transmit_data(int *lpipe, int *rpipe, int first)
{
    int value = 0;
    //    一直从左管道读数字
    //条件少了
    while (read(lpipe[RD], &value, sizeof(int)) == sizeof(int)) {
        if (value % first != 0) {
            //        if (value % first) {
            write(rpipe[WR], &value, sizeof(int));
        }
    }
    close(lpipe[RD]);
    close(rpipe[WR]);
}

__attribute__((noreturn))
/**
 * 迭代的处理管道内的数据
 * @param lpipe 当前管道
 */

void
primes(int *lpipe)
{
    close(lpipe[WR]);
    int first = 0;
    if (lpipe_first_data(lpipe, &first) == 0) {
        int p[2];
        //        开辟管道
        pipe(p);
        //        传送数据
        transmit_data(lpipe, p, first);
        if (fork() == 0) {
            primes(p);
        }
        else {
            wait(0);
        }
    }
    exit(0);
}

int main()
{
    int p[2];
    pipe(p);
    for (int i = 2; i < 100; ++i) {
        write(p[WR], &i, sizeof(int));
    }
    //    child
    if (fork() == 0) {
        primes(p);
    }
    else {
        close(p[WR]);
        close(p[RD]);
        wait(0);
    }
    exit(0);
}
