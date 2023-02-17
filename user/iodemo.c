//
// Created by jiaxin on 2023/2/17 21:46.
//
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"
int main()
{
    char *argv[2];
    argv[0] = "cat";
    argv[1] = 0;

    if (fork() == 0) {
        // in the child process
        close(0);                   // this step is to release the stdin file descriptor
        open("input.txt", O_RDONLY);// the newly allocated fd for input.txt is 0, since the previous fd 0 is released
        exec("cat", argv);          // execute the cat program, by default takes in the fd 0 as input, which is input.txt
    }
    exit(0);
}