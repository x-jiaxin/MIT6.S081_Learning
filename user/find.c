//
// Created by 幻想 on 2022/8/23.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

/**
 * 在当前path查找file,打印完整路径
 * @param path  查找目录
 * @param filename  文件名
 */
void find(char *path, const char *filename)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "open error\n");
        exit(1);
    }
    if (fstat(fd, &st) < 0) {
        fprintf(2, "stat error\n");
        close(fd);
        exit(1);
    }
    if (st.type != T_DIR) {
        fprintf(2, "open must be a dir\n");
        exit(1);
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0) {
            continue;
        }
//        更新p为单个名字
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0) {
            printf("ls: cannot stat %s\n", buf);
            continue;
        }
//        if (st.type == T_DIR && strcmp(buf, ".") != 0 && strcmp(buf, "..") != 0) {
        if (st.type == T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..") != 0) {
            find(buf, filename);
        }
//        else if (strcmp(buf, filename) == 0) {
        else if (strcmp(p, filename) == 0) {
            printf("%s\n", buf);
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc == 3) {
        find(argv[1], argv[2]);
    }
    else if (argc == 2) {
        find(".", argv[1]);
    }
    else {
        fprintf(2, "arguments error!\n");
        exit(1);
    }
    exit(0);
}