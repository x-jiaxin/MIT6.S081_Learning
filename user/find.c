#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

void find(char *path, char *file_name)
{
    struct dirent dt;
    struct stat st;
    char buf[512], *p;
    int fd = open(path, 0);
    if (fd < 0) {
        fprintf(2, "open dir failed!\n");
        exit(1);
    }
    if (fstat(fd, &st) < 0) {
        fprintf(2, "stat dir failed!\n");
        close(fd);
        exit(1);
    }
    if (st.type != T_DIR) {
        fprintf(2, "not a dir\n");
        exit(1);
    }

    strcpy(buf, path);
    p = buf + strlen(path);
    *p++ = '/';
    while (read(fd, &dt, sizeof(dt)) == sizeof(dt)) {
        if (dt.inum == 0) {
            continue;
        }
        memmove(p, dt.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0) {
            continue;
        }
        switch (st.type) {
            case T_FILE:
                if (strcmp(p, file_name) == 0) {
                    fprintf(1, "%s\n", buf);
                }
                break;
            case T_DIR:
                if (strcmp(p, ".") != 0 && strcmp(p, "..") != 0) {
                    find(buf, file_name);
                }
                break;
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        if (argc == 2) {
            find(".", argv[1]);
            exit(0);
        }
        else {
            fprintf(2, "Usage: find path filename\n");
            exit(1);
        }
    }
    else {
        find(argv[1], argv[2]);
        exit(0);
    }
}
