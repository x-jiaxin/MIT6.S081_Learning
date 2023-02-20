#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

void find(char *path, char *file_name) {
  struct dirent dt;
  struct stat st;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(2, "Usage: find path filename\n");
    exit(1);
  }
  find(argv[1], argv[2]);
  exit(0);
}