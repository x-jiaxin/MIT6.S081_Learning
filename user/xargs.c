//
// Created by 幻想 on 2022/8/25.
//
#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

#define SIZE 32
// echo "1\n2" | xargs echo line
// buf:"1\n2"
/*argv[0]:xargs
argv[1]:echo
argv[2]:line
 */
int main(int argc, char *argv[])
{
    sleep(10);
    char buf[SIZE];
    char *xargv[SIZE];
    int xargc = 0;
    char *command = argv[1];
    for (int i = 1; i < argc; ++i) {
        xargv[xargc++] = argv[i];
    }
    while (read(0, buf, SIZE) > 0) {
        if (fork() == 0) {
            char *p = (char *)malloc(sizeof(buf));
            int pi = 0;
            for (int i = 0; i < sizeof(buf); ++i) {
                if (buf[i] == ' ' || buf[i] == '\n') {
                    xargv[xargc++] = p;
                    pi = 0;
                    p = (char *)malloc(sizeof(buf));
                }
                else {
                    p[pi++] = buf[i];
                }
            }
            free(p);
            xargv[xargc] = 0;
            exec(command, xargv);
        }
        else {
            wait(0);
        }
    }
    exit(0);
}