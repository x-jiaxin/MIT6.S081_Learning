#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

int main()
{
    mkdir("test_dir");
    chdir("test_dir");
    int fd = open("test_file1.txt", O_CREATE | O_RDWR);
    link("test_file1.txt", "test_file2.txt");
    struct stat node1 = {};
    fstat(fd, &node1);
    fprintf(1, "dev: %d\n", node1.dev);
    fprintf(1, "info: %d\n", node1.ino);
    fprintf(1, "nlink: %d\n", node1.nlink);
    fprintf(1, "size: %d\n", node1.size);
    fprintf(1, "type: %d\n", node1.type);

    fprintf(1, "\n");
    struct stat node2 = {};
    fstat(fd, &node2);
    fprintf(1, "dev: %d\n", node2.dev);
    fprintf(1, "info: %d\n", node2.ino);
    fprintf(1, "nlink: %d\n", node2.nlink);
    fprintf(1, "size: %d\n", node2.size);
    fprintf(1, "type: %d\n", node2.type);
    exit(0);
}